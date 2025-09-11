#!/usr/bin/env python3
"""
Sicherer Container Manager ohne Docker Socket Mount
Verwendet HTTP API für Container-Management
"""

import requests
import yaml
import json
import os
from pathlib import Path
from typing import Dict, List, Optional
import logging

logger = logging.getLogger(__name__)

class SecureVyraContainerManager:
    def __init__(self, 
                 api_host: str = None, 
                 api_port: int = None,
                 security_token: str = None):
        """
        Sicherer Container Manager über HTTP API
        
        Args:
            api_host: Host des Container Management APIs
            api_port: Port des APIs
            security_token: Sicherheits-Token für Authentifizierung
        """
        self.api_host = api_host or os.environ.get('CONTAINER_API_HOST', 'container-management-api')
        self.api_port = api_port or int(os.environ.get('CONTAINER_API_PORT', 8080))
        self.security_token = security_token or os.environ.get('VYRA_SECURITY_TOKEN', 'default-token')
        
        self.api_base = f"http://{self.api_host}:{self.api_port}"
        self.headers = {
            'Authorization': f'Bearer {self.security_token}',
            'Content-Type': 'application/json'
        }
        
        logger.info(f"Sicherer Container Manager initialisiert - API: {self.api_base}")
    
    def install_module(self, module_name: str, module_config: Dict) -> bool:
        """
        Installiert ein neues Modul über sichere API
        
        Args:
            module_name: Name des Moduls
            module_config: Container-Konfiguration
            
        Returns:
            bool: True wenn erfolgreich
        """
        try:
            # Validiere Konfiguration lokal
            if not self._validate_module_config_local(module_config):
                logger.error(f"Lokale Validierung fehlgeschlagen für {module_name}")
                return False
            
            response = requests.post(
                f"{self.api_base}/modules/{module_name}",
                headers=self.headers,
                json=module_config,
                timeout=30
            )
            
            if response.status_code == 200:
                logger.info(f"Modul {module_name} erfolgreich installiert")
                return True
            elif response.status_code == 401:
                logger.error("Authentifizierung fehlgeschlagen - Security Token ungültig")
                return False
            else:
                logger.error(f"API Fehler beim Installieren von {module_name}: {response.text}")
                return False
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Netzwerk-Fehler beim Installieren von {module_name}: {e}")
            return False
        except Exception as e:
            logger.error(f"Exception beim Installieren von {module_name}: {e}")
            return False
    
    def uninstall_module(self, module_name: str) -> bool:
        """
        Deinstalliert ein Modul über sichere API
        
        Args:
            module_name: Name des Moduls
            
        Returns:
            bool: True wenn erfolgreich
        """
        try:
            response = requests.delete(
                f"{self.api_base}/modules/{module_name}",
                headers=self.headers,
                timeout=30
            )
            
            if response.status_code == 200:
                logger.info(f"Modul {module_name} erfolgreich deinstalliert")
                return True
            elif response.status_code == 401:
                logger.error("Authentifizierung fehlgeschlagen")
                return False
            else:
                logger.error(f"API Fehler beim Deinstallieren von {module_name}: {response.text}")
                return False
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Netzwerk-Fehler beim Deinstallieren von {module_name}: {e}")
            return False
        except Exception as e:
            logger.error(f"Exception beim Deinstallieren von {module_name}: {e}")
            return False
    
    def restart_module(self, module_name: str) -> bool:
        """
        Startet ein Modul über sichere API neu
        
        Args:
            module_name: Name des Moduls
            
        Returns:
            bool: True wenn erfolgreich
        """
        try:
            response = requests.post(
                f"{self.api_base}/modules/{module_name}/restart",
                headers=self.headers,
                timeout=30
            )
            
            if response.status_code == 200:
                logger.info(f"Modul {module_name} erfolgreich neugestartet")
                return True
            elif response.status_code == 401:
                logger.error("Authentifizierung fehlgeschlagen")
                return False
            else:
                logger.error(f"API Fehler beim Neustarten von {module_name}: {response.text}")
                return False
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Netzwerk-Fehler beim Neustarten von {module_name}: {e}")
            return False
        except Exception as e:
            logger.error(f"Exception beim Neustarten von {module_name}: {e}")
            return False
    
    def list_modules(self) -> List[Dict]:
        """
        Listet alle Module über sichere API auf
        
        Returns:
            List[Dict]: Liste aller Module mit Status
        """
        try:
            response = requests.get(
                f"{self.api_base}/modules", 
                headers=self.headers,
                timeout=10
            )
            
            if response.status_code == 200:
                data = response.json()
                return data.get('modules', [])
            elif response.status_code == 401:
                logger.error("Authentifizierung fehlgeschlagen")
                return []
            else:
                logger.error(f"API Fehler beim Auflisten der Module: {response.text}")
                return []
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Netzwerk-Fehler beim Auflisten der Module: {e}")
            return []
        except Exception as e:
            logger.error(f"Exception beim Auflisten der Module: {e}")
            return []
    
    def get_module_logs(self, module_name: str, tail: int = 100) -> str:
        """
        Holt die Logs eines Moduls über sichere API
        
        Args:
            module_name: Name des Moduls
            tail: Anzahl der letzten Zeilen
            
        Returns:
            str: Log-Ausgabe
        """
        try:
            response = requests.get(
                f"{self.api_base}/modules/{module_name}/logs",
                headers=self.headers,
                params={'tail': tail},
                timeout=10
            )
            
            if response.status_code == 200:
                data = response.json()
                return data.get('logs', '')
            elif response.status_code == 401:
                return "Authentifizierung fehlgeschlagen"
            else:
                return f"API Fehler beim Abrufen der Logs: {response.text}"
                
        except requests.exceptions.RequestException as e:
            logger.error(f"Netzwerk-Fehler beim Abrufen der Logs von {module_name}: {e}")
            return f"Netzwerk-Fehler beim Abrufen der Logs: {e}"
        except Exception as e:
            logger.error(f"Exception beim Abrufen der Logs von {module_name}: {e}")
            return f"Fehler beim Abrufen der Logs: {e}"
    
    def _validate_module_config_local(self, config: Dict) -> bool:
        """
        Lokale Validierung der Modul-Konfiguration
        Zusätzliche Sicherheitsschicht vor API-Aufruf
        
        Args:
            config: Module-Konfiguration
            
        Returns:
            bool: True wenn Konfiguration sicher ist
        """
        # Erlaubte Images
        allowed_images = ['vyra-framework:latest']
        image = config.get('image', 'vyra-framework:latest')
        
        if image not in allowed_images:
            logger.warning(f"Nicht erlaubtes Image: {image}")
            return False
        
        # Verhindere gefährliche Konfigurationen
        if config.get('privileged', False):
            logger.warning("Privileged Mode nicht erlaubt")
            return False
        
        # Verhindere Host-Netzwerk
        networks = config.get('networks', [])
        if 'host' in networks:
            logger.warning("Host-Netzwerk nicht erlaubt")
            return False
        
        # Verhindere Docker Socket Mount
        volumes = config.get('volumes', [])
        for volume in volumes:
            if isinstance(volume, str) and '/var/run/docker.sock' in volume:
                logger.warning("Docker Socket Mount nicht erlaubt")
                return False
        
        return True


# Sichere Nutzung ohne Docker Socket
if __name__ == "__main__":
    # Konfiguriere Logging
    logging.basicConfig(level=logging.INFO)
    
    manager = SecureVyraContainerManager()
    
    print("🔒 Sicherer Container Manager - Teste Verbindung...")
    
    # Teste Verbindung
    modules = manager.list_modules()
    if modules is not None:
        print(f"✅ API Verbindung erfolgreich - {len(modules)} Module gefunden")
        for module in modules:
            print(f"  - {module['name']}: {module['status']}")
    else:
        print("❌ API Verbindung fehlgeschlagen")
    
    # Beispiel: Neues sicheres Modul
    secure_config = {
        'image': 'vyra-framework:latest',
        'volumes': ['./secure_test_module:/workspace'],
        'environment': [
            'ROS_SECURITY_ENABLE=true',  # Sicherheit aktiviert
            'VYRA_PRODUCTIVE=false'
        ],
        'networks': ['vyra-network']  # Nur erlaubte Netzwerke
    }
    
    print("\n🔐 Teste sichere Modul-Installation...")
    success = manager.install_module("secure_test_module", secure_config)
    print(f"Installation: {'✅ Erfolg' if success else '❌ Fehler'}")
    
    # Liste aktualisierte Module
    updated_modules = manager.list_modules()
    if updated_modules:
        print(f"\n📋 Aktualisierte Modulliste ({len(updated_modules)} Module):")
        for module in updated_modules:
            print(f"  - {module['name']}: {module['status']}")
    
    def uninstall_module(self, module_name: str) -> bool:
        """
        Deinstalliert ein Modul über API
        
        Args:
            module_name: Name des Moduls
            
        Returns:
            bool: True wenn erfolgreich
        """
        try:
            response = requests.delete(
                f"{self.api_base}/modules/{module_name}",
                timeout=30
            )
            
            if response.status_code == 200:
                logger.info(f"Modul {module_name} erfolgreich deinstalliert")
                return True
            else:
                logger.error(f"API Fehler beim Deinstallieren von {module_name}: {response.text}")
                return False
                
        except Exception as e:
            logger.error(f"Exception beim Deinstallieren von {module_name}: {e}")
            return False
    
    def restart_module(self, module_name: str) -> bool:
        """
        Startet ein Modul über API neu
        
        Args:
            module_name: Name des Moduls
            
        Returns:
            bool: True wenn erfolgreich
        """
        try:
            response = requests.post(
                f"{self.api_base}/modules/{module_name}/restart",
                timeout=30
            )
            
            if response.status_code == 200:
                logger.info(f"Modul {module_name} erfolgreich neugestartet")
                return True
            else:
                logger.error(f"API Fehler beim Neustarten von {module_name}: {response.text}")
                return False
                
        except Exception as e:
            logger.error(f"Exception beim Neustarten von {module_name}: {e}")
            return False
    
    def list_modules(self) -> List[Dict]:
        """
        Listet alle Module über API auf
        
        Returns:
            List[Dict]: Liste aller Module mit Status
        """
        try:
            response = requests.get(f"{self.api_base}/modules", timeout=10)
            
            if response.status_code == 200:
                return response.json()
            else:
                logger.error(f"API Fehler beim Auflisten der Module: {response.text}")
                return []
                
        except Exception as e:
            logger.error(f"Exception beim Auflisten der Module: {e}")
            return []
    
    def get_module_logs(self, module_name: str, tail: int = 100) -> str:
        """
        Holt die Logs eines Moduls über API
        
        Args:
            module_name: Name des Moduls
            tail: Anzahl der letzten Zeilen
            
        Returns:
            str: Log-Ausgabe
        """
        try:
            response = requests.get(
                f"{self.api_base}/modules/{module_name}/logs",
                params={'tail': tail},
                timeout=10
            )
            
            if response.status_code == 200:
                return response.text
            else:
                return f"API Fehler beim Abrufen der Logs: {response.text}"
                
        except Exception as e:
            logger.error(f"Exception beim Abrufen der Logs von {module_name}: {e}")
            return f"Fehler beim Abrufen der Logs: {e}"


# Sichere Nutzung ohne Docker Socket
if __name__ == "__main__":
    manager = SecureVyraContainerManager()
    
    print("Verfügbare Module (über sichere API):")
    for module in manager.list_modules():
        print(f"- {module['name']}: {module['status']}")
