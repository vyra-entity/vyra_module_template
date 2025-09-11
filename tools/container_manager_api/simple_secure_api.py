#!/usr/bin/env python3
"""
Einfacher sicherer Container Manager - nur mit subprocess
Ohne Docker Python Library - verwendet nur docker compose Befehle
"""

import subprocess
import yaml
import json
import os
import signal
import sys
from pathlib import Path
from typing import Dict, List, Optional
import logging
from http.server import HTTPServer, BaseHTTPRequestHandler
import urllib.parse

logger = logging.getLogger(__name__)

class SimpleContainerManagementHandler(BaseHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self.compose_file = Path("/workspace/docker-compose.yml")
        self.security_token = os.environ.get('VYRA_SECURITY_TOKEN', 'default-token')
        super().__init__(*args, **kwargs)
    
    def _verify_security_token(self):
        """Überprüft Security Token"""
        auth_header = self.headers.get('Authorization')
        if not auth_header or not auth_header.startswith('Bearer '):
            return False
        
        token = auth_header.split(' ')[1]
        return token == self.security_token
    
    def _send_json_response(self, status_code: int, data: dict):
        """Sendet JSON Response"""
        self.send_response(status_code)
        self.send_header('Content-type', 'application/json')
        self.send_header('Access-Control-Allow-Origin', '*')
        self.end_headers()
        self.wfile.write(json.dumps(data).encode('utf-8'))
    
    def _send_error(self, status_code: int, message: str):
        """Sendet Fehler-Response"""
        self._send_json_response(status_code, {'error': message})
    
    def do_OPTIONS(self):
        """CORS Preflight"""
        self.send_response(200)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, DELETE, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type, Authorization')
        self.end_headers()
    
    def do_GET(self):
        """GET /modules - Liste alle Module"""
        if not self._verify_security_token():
            self._send_error(401, "Unauthorized")
            return
        
        try:
            parsed_path = urllib.parse.urlparse(self.path)
            
            if parsed_path.path == "/modules":
                modules = self._list_modules()
                self._send_json_response(200, {'modules': modules})
            
            elif parsed_path.path.startswith("/modules/") and parsed_path.path.endswith("/logs"):
                module_name = parsed_path.path.split("/")[2]
                query_params = urllib.parse.parse_qs(parsed_path.query)
                tail = int(query_params.get('tail', [100])[0])
                
                logs = self._get_module_logs(module_name, tail)
                self._send_json_response(200, {'logs': logs})
            
            else:
                self._send_error(404, "Not found")
                
        except Exception as e:
            logger.error(f"GET Error: {e}")
            self._send_error(500, f"Internal server error: {e}")
    
    def do_POST(self):
        """POST /modules/{name} - Installiere Modul oder POST /modules/{name}/restart - Restart"""
        if not self._verify_security_token():
            self._send_error(401, "Unauthorized")
            return
        
        try:
            parsed_path = urllib.parse.urlparse(self.path)
            path_parts = parsed_path.path.strip("/").split("/")
            
            if len(path_parts) == 2 and path_parts[0] == "modules":
                # POST /modules/{name} - Install
                module_name = path_parts[1]
                content_length = int(self.headers['Content-Length'])
                post_data = self.rfile.read(content_length)
                module_config = json.loads(post_data.decode('utf-8'))
                
                success = self._install_module(module_name, module_config)
                if success:
                    self._send_json_response(200, {'message': f'Module {module_name} installed successfully'})
                else:
                    self._send_error(500, f'Failed to install module {module_name}')
            
            elif len(path_parts) == 3 and path_parts[0] == "modules" and path_parts[2] == "restart":
                # POST /modules/{name}/restart
                module_name = path_parts[1]
                success = self._restart_module(module_name)
                if success:
                    self._send_json_response(200, {'message': f'Module {module_name} restarted successfully'})
                else:
                    self._send_error(500, f'Failed to restart module {module_name}')
            
            else:
                self._send_error(404, "Not found")
                
        except Exception as e:
            logger.error(f"POST Error: {e}")
            self._send_error(500, f"Internal server error: {e}")
    
    def do_DELETE(self):
        """DELETE /modules/{name} - Deinstalliere Modul"""
        if not self._verify_security_token():
            self._send_error(401, "Unauthorized")
            return
        
        try:
            parsed_path = urllib.parse.urlparse(self.path)
            path_parts = parsed_path.path.strip("/").split("/")
            
            if len(path_parts) == 2 and path_parts[0] == "modules":
                module_name = path_parts[1]
                success = self._uninstall_module(module_name)
                if success:
                    self._send_json_response(200, {'message': f'Module {module_name} uninstalled successfully'})
                else:
                    self._send_error(500, f'Failed to uninstall module {module_name}')
            else:
                self._send_error(404, "Not found")
                
        except Exception as e:
            logger.error(f"DELETE Error: {e}")
            self._send_error(500, f"Internal server error: {e}")
    
    def _install_module(self, module_name: str, module_config: Dict) -> bool:
        """Installiert ein neues Modul"""
        try:
            logger.info(f"Installing module {module_name} with config: {module_config}")
            
            # Prüfe ob Container bereits existiert
            status = self._get_container_status(module_name)
            if status != "not_found":
                logger.warning(f"Container {module_name} already exists with status: {status}")
                # Entferne bestehenden Container
                remove_result = subprocess.run([
                    "docker", "rm", "-f", module_name
                ], capture_output=True, text=True)
                logger.info(f"Removed existing container: {remove_result.returncode}")
            
            # Validierung der Konfiguration
            if not self._validate_module_config(module_config):
                logger.error(f"Invalid module config for {module_name}")
                return False
            
            # Füge zur compose Datei hinzu
            self._add_service_to_compose(module_name, module_config)
            logger.info(f"Added {module_name} to compose file")
            
            # Starte Container
            result = subprocess.run([
                "docker-compose", "-f", str(self.compose_file),
                "up", "-d", "--no-deps", module_name
            ], capture_output=True, text=True, cwd="/workspace")
            
            logger.info(f"Docker compose up result: returncode={result.returncode}, stdout={result.stdout}, stderr={result.stderr}")
            
            if result.returncode == 0:
                logger.info(f"Module {module_name} successfully installed")
                return True
            else:
                logger.error(f"Failed to install {module_name}: {result.stderr}")
                return False
            
        except Exception as e:
            logger.error(f"Install error: {e}")
            return False
    
    def _uninstall_module(self, module_name: str) -> bool:
        """Deinstalliert ein Modul"""
        try:
            # Stoppe und entferne Container
            stop_result = subprocess.run([
                "docker-compose", "-f", str(self.compose_file),
                "stop", module_name
            ], capture_output=True, text=True, cwd="/workspace")
            
            rm_result = subprocess.run([
                "docker-compose", "-f", str(self.compose_file),
                "rm", "-f", module_name
            ], capture_output=True, text=True, cwd="/workspace")
            
            # Entferne aus compose
            self._remove_service_from_compose(module_name)
            
            if stop_result.returncode == 0 or rm_result.returncode == 0:
                logger.info(f"Module {module_name} uninstalled")
                return True
            else:
                logger.error(f"Failed to uninstall {module_name}: stop={stop_result.stderr}, rm={rm_result.stderr}")
                return False
            
        except Exception as e:
            logger.error(f"Uninstall error: {e}")
            return False
    
    def _restart_module(self, module_name: str) -> bool:
        """Startet ein Modul neu"""
        try:
            logger.info(f"Restarting module {module_name}")
            
            # Prüfe zuerst den Container-Status
            status = self._get_container_status(module_name)
            logger.info(f"Current status of {module_name}: {status}")
            
            if status == "running":
                # Container läuft - verwende docker restart (direkt)
                result = subprocess.run([
                    "docker", "restart", module_name
                ], capture_output=True, text=True)
                
                logger.info(f"Docker restart result: returncode={result.returncode}, stdout={result.stdout}, stderr={result.stderr}")
                
                if result.returncode == 0:
                    logger.info(f"Module {module_name} restarted successfully")
                    return True
            
            # Fallback oder wenn Container nicht läuft: compose up
            logger.info(f"Starting {module_name} via docker-compose up")
            up_result = subprocess.run([
                "docker-compose", "-f", str(self.compose_file),
                "up", "-d", "--no-deps", module_name
            ], capture_output=True, text=True, cwd="/workspace")
            
            logger.info(f"Docker compose up result: returncode={up_result.returncode}, stdout={up_result.stdout}, stderr={up_result.stderr}")
            
            if up_result.returncode == 0:
                logger.info(f"Module {module_name} started successfully")
                return True
            else:
                logger.error(f"Failed to restart {module_name}: {up_result.stderr}")
                return False
            
        except Exception as e:
            logger.error(f"Restart error: {e}")
            return False
    
    def _list_modules(self) -> List[Dict]:
        """Listet alle Module auf"""
        try:
            with open(self.compose_file, 'r') as f:
                compose_data = yaml.safe_load(f)
            
            modules = []
            for service_name, service_config in compose_data.get('services', {}).items():
                if service_name in ['redis', 'vyra_base_image', 'container-management-api']:
                    continue  # System Services überspringen
                
                # Prüfe Container-Status via docker ps
                status = self._get_container_status(service_name)
                
                modules.append({
                    'name': service_name,
                    'image': service_config.get('image', 'unknown'),
                    'status': status,
                    'working_dir': service_config.get('working_dir', ''),
                    'volumes': service_config.get('volumes', [])
                })
            
            return modules
            
        except Exception as e:
            logger.error(f"List modules error: {e}")
            return []
    
    def _get_container_status(self, container_name: str) -> str:
        """Holt Container Status via docker ps"""
        try:
            # Verwende docker inspect statt docker ps für bessere Genauigkeit
            result = subprocess.run([
                "docker", "inspect", "--format", "{{.State.Status}}", container_name
            ], capture_output=True, text=True)
            
            if result.returncode == 0 and result.stdout.strip():
                status = result.stdout.strip()
                return status
            else:
                return "not_found"
                
        except Exception as e:
            logger.error(f"Status check error: {e}")
            return "error"
    
    def _get_module_logs(self, module_name: str, tail: int = 100) -> str:
        """Holt Module Logs"""
        try:
            result = subprocess.run([
                "docker-compose", "-f", str(self.compose_file),
                "logs", "--tail", str(tail), module_name
            ], capture_output=True, text=True, cwd="/workspace")
            
            return result.stdout if result.returncode == 0 else result.stderr
            
        except Exception as e:
            logger.error(f"Get logs error: {e}")
            return f"Error getting logs: {e}"
    
    def _validate_module_config(self, config: Dict) -> bool:
        """Validiert Module-Konfiguration für Sicherheit"""
        # Sichere Defaults erzwingen
        allowed_images = ['vyra_base_image:latest']
        
        image = config.get('image', 'vyra_base_image:latest')
        if image not in allowed_images:
            logger.warning(f"Nicht erlaubtes Image: {image}")
            return False
        
        # Verhindere privileged Mode
        if config.get('privileged', False):
            logger.warning("Privileged Mode nicht erlaubt")
            return False
        
        # Verhindere Host-Netzwerk
        networks = config.get('networks', [])
        if 'host' in networks:
            logger.warning("Host-Netzwerk nicht erlaubt")
            return False
        
        return True
    
    def _add_service_to_compose(self, service_name: str, config: Dict):
        """Fügt Service zur Compose-Datei hinzu"""
        with open(self.compose_file, 'r') as f:
            compose_data = yaml.safe_load(f)
        
        default_config = {
            'image': 'vyra_base_image:latest',
            'container_name': service_name,
            'depends_on': {
                'vyra_base_image': {
                    'condition': 'service_completed_successfully'
                }
            },
            'volumes': [f'./modules/{service_name}:/workspace'],
            'working_dir': '/workspace',
            'command': ['/workspace/vyra_entrypoint.sh'],
            'stdin_open': True,
            'tty': True,
            'environment': [
                'ROS_SECURITY_ENABLE=false',
                'VYRA_PRODUCTIVE=false'
            ],
            'networks': ['vyra-network']
        }
        
        # Merge mit Sicherheitsvalidierung
        service_config = {**default_config, **config}
        compose_data['services'][service_name] = service_config
        
        with open(self.compose_file, 'w') as f:
            yaml.dump(compose_data, f, default_flow_style=False, sort_keys=False)
    
    def _remove_service_from_compose(self, service_name: str):
        """Entfernt Service aus Compose-Datei"""
        with open(self.compose_file, 'r') as f:
            compose_data = yaml.safe_load(f)
        
        if service_name in compose_data.get('services', {}):
            del compose_data['services'][service_name]
            
            with open(self.compose_file, 'w') as f:
                yaml.dump(compose_data, f, default_flow_style=False, sort_keys=False)


def main():
    """Hauptfunktion - startet den API Server"""
    port = int(os.environ.get('API_PORT', 8080))
    
    # Logging-Konfiguration mit Datei und Konsole
    log_file = "/workspace/log/container-management-api.log"
    
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            logging.StreamHandler(),  # Konsole (für docker logs)
            logging.FileHandler(log_file)  # Datei (persistent)
        ]
    )
    
    logger.info("🔒 Einfacher sicherer Container Management API startet...")
    logger.info(f"📝 Logs werden gespeichert in: {log_file}")
    
    server = HTTPServer(('0.0.0.0', port), SimpleContainerManagementHandler)
    server.timeout = 1  # 1 Sekunde Timeout für handle_request
    logger.info(f"✅ Sicherer Container Management API läuft auf Port {port}")
    
    # Shutdown Flag
    shutdown_flag = False
    
    # Signal Handler für graceful shutdown
    def signal_handler(signum, frame):
        nonlocal shutdown_flag
        logger.info(f"🛑 Signal {signum} empfangen, stoppe Server graceful...")
        shutdown_flag = True
    
    # Register signal handlers
    signal.signal(signal.SIGTERM, signal_handler)  # Docker sendet SIGTERM
    signal.signal(signal.SIGINT, signal_handler)   # Ctrl+C sendet SIGINT
    
    try:
        # Verwende handle_request() in einer Schleife statt serve_forever()
        while not shutdown_flag:
            server.handle_request()
    except (KeyboardInterrupt, SystemExit):
        logger.info("🛑 API Server unterbrochen")
    finally:
        logger.info("🔄 Stoppe Server...")
        server.server_close()
        logger.info("✅ Server ordnungsgemäß gestoppt")


if __name__ == '__main__':
    main()
