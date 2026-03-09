"""
Module HTTP Client

Provides HTTP-based communication with Container Manager for module operations.
Replaces container_manager_client.py with modern architecture.
"""
from v2_modulemanager.logging_config import get_logger, log_exception, log_function_call, log_function_result
from typing import Any, Dict, List, Optional
from pathlib import Path

from .base_client import BaseHttpClient

logger = get_logger(__name__)


class ModuleHttpClient(BaseHttpClient):
    """
    HTTP client for Container Manager module operations.
    
    Handles:
    - Module installation and removal
    - Module stats and monitoring
    - Primary instance management
    - Repository queries
    
    Industrial automation features:
    - Deterministic timeout behavior
    - Detailed operation logging
    - Graceful error handling
    - Connection pooling for performance
    """
    
    async def install_module(
        self,
        module_name: str,
        module_hash: str,
        instance_id: str,
        repository: dict,
        is_primary: bool = False
    ) -> Dict:
        """
        Install module on Container Manager node.
        
        Args:
            module_name: Module identifier (e.g., 'v2_dashboard')
            module_hash: Module version hash
            instance_id: Unique instance identifier (UUID)
            repository: Repository configuration dict
            is_primary: Set as primary instance
            
        Returns:
            {
                "success": bool,
                "operation": "install",
                "module_name": str,
                "instance_id": str,
                "message": str,
                "details": dict
            }
        """
        payload = {
            "module_name": module_name,
            "module_hash": module_hash,
            "instance_id": instance_id,
            "source_type": repository.get("type", "local"),
            "is_primary": is_primary
        }
        
        if repository.get("url"):
            payload["repository_url"] = repository.get("url")

        if repository.get("type") in ["https"]:
            payload["api_key"] = repository.get("api_key", "")
            payload["cert_fingerprint"] = repository.get("cert_fingerprint", "")
        
        result = await self.post("/modules/install", json=payload)
        
        if not result.get("success"):
            logger.error(
                f"❌ Module install failed: {module_name}/{instance_id} "
                f"(status: {result.get('status')})"
            )
        else:
            logger.info(
                f"✅ Module installed: {module_name}/{instance_id}"
            )
        
        return result.get("data", result)
    
    async def remove_module(
        self,
        module_name: str,
        instance_id: str,
        create_backup: bool = True
    ) -> Dict:
        """
        Remove module from Container Manager node.
        
        Args:
            module_name: Module identifier
            instance_id: Instance identifier
            create_backup: Create backup before removal
            
        Returns:
            {
                "success": bool,
                "operation": "remove",
                "module_name": str,
                "instance_id": str,
                "message": str,
                "details": dict
            }
        """
        endpoint = f"/modules/{module_name}/{instance_id}"
        result = await self.delete(endpoint)
        
        if not result.get("success"):
            logger.error(
                f"❌ Module remove failed: {module_name}/{instance_id}"
            )
        else:
            logger.info(
                f"✅ Module removed: {module_name}/{instance_id}"
            )
        
        return result.get("data", result)
    
    async def update_module_labels(
        self,
        module_name: str,
        instance_id: str,
        labels: List[str]
    ) -> Dict:
        """
        Update module labels for Traefik routing.
        
        Args:
            module_name: Module identifier
            instance_id: Instance identifier
            labels: List of Docker labels
            
        Returns:
            Operation result dict
        """
        endpoint = f"/modules/{module_name}/{instance_id}"
        result = await self.put(endpoint, data={"labels": labels})
        
        return result.get("data", result)
    
    async def get_module_stats(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Get module resource statistics (CPU, RAM, disk, network).
        
        Args:
            module_name: Module identifier
            instance_id: Instance identifier
            
        Returns:
            {
                "success": bool,
                "stats": {
                    "module_name": str,
                    "instance_id": str,
                    "cpu": {"percent": float, "count": int},
                    "memory": {"usage_mb": int, "limit_mb": int, "percent": float},
                    "disk": {"usage_mb": int, ...},
                    "network": {"rx_mb": float, "tx_mb": float},
                    "processes": list,
                    "process_count": int,
                    "status": str,
                    "uptime_seconds": int
                }
            }
        """
        endpoint = f"/modules/{module_name}/{instance_id}/stats"
        result = await self.get(endpoint)
        
        return result.get("data", result)
    
    async def get_all_module_stats(self) -> Dict:
        """
        Get statistics for all modules on this node.
        
        Returns:
            {
                "success": bool,
                "count": int,
                "modules": [
                    {"module_name": str, "cpu": dict, ...},
                    ...
                ]
            }
        """
        result = await self.get("/modules/stats/all")
        return result.get("data", result)
    
    async def list_available_modules(
        self,
        repository_url: Optional[str] = None
    ) -> Dict:
        """
        List available modules from repository.
        
        Args:
            repository_url: Optional repository URL filter
            
        Returns:
            {
                "success": bool,
                "modules": [{"name": str, "version": str, ...}]
            }
        """
        params = {}
        if repository_url:
            params["repository_url"] = repository_url
        
        result = await self.get("/modules/available", params=params)
        return result.get("data", result)
    
    async def set_primary_instance(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Set module instance as primary.
        
        Updates Traefik labels so primary instance is accessible at
        /{module_name}/ while other instances remain at
        /{module_name}/{instance_id}/.
        
        Args:
            module_name: Module identifier
            instance_id: Instance identifier to set as primary
            
        Returns:
            {
                "success": bool,
                "operation": "set_primary_instance",
                "module_name": str,
                "instance_id": str,
                "message": str,
                "details": dict
            }
        """
        endpoint = f"/modules/{module_name}/{instance_id}/set-primary"
        result = await self.post(endpoint)
        
        if not result.get("success"):
            logger.error(
                f"❌ Set primary failed: {module_name}/{instance_id}"
            )
        else:
            logger.info(
                f"✅ Primary instance set: {module_name}/{instance_id}"
            )
        
        return result.get("data", result)
    
    async def list_installed_modules(
        self,
        include_hidden: bool = False
    ) -> Dict:
        """
        List all installed modules with their instances.
        
        Args:
            include_hidden: Include hidden instances
            
        Returns:
            {
                "success": bool,
                "count": int,
                "modules": {
                    "module_name": [
                        {
                            "module_name": str,
                            "instance_id": str,
                            "path": str,
                            "is_primary": bool,
                            "version": str,
                            "status": str,
                            "hidden": bool
                        }
                    ]
                }
            }
        """
        params = {}
        if include_hidden:
            params["include_hidden"] = "true"
        
        result = await self.get("/modules", params=params)
        return result.get("data", result)    
    async def get_hardware_info(self) -> Dict:
        """
        Hole Hardware-Informationen des Nodes
        
        Returns:
            {
                "success": True,
                "hardware": {...}
            }
        """
        result = await self.get("/hardware/info")
        return result.get("data", result)
    
    async def update_module(
        self,
        module_name: str,
        instance_id: str,
        version: str,
        repository: dict
    ) -> Dict:
        """
        Update Modul auf neue Version
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            version: Neue Version
            repository: Repository-Konfiguration
            
        Returns:
            {"success": True/False, "message": "...", "error": "..."}
        """
        payload = {
            "module_name": module_name,
            "instance_id": instance_id,
            "version": version,
            "repository": repository
        }
        result = await self.post("/modules/update", json=payload)
        return result.get("data", result)
    
    async def restart_module(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Starte Modul-Container neu
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {"success": True/False, "message": "..."}
        """
        result = await self.post(f"/modules/{module_name}/{instance_id}/restart")
        return result.get("data", result)
    
    async def get_module_status(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Hole Status eines Moduls
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {"success": True, "status": "running"|"stopped"|...}
        """
        result = await self.get(f"/modules/{module_name}/{instance_id}/status")
        return result.get("data", result)
    
    async def create_backup(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Erstelle Backup vom Modul-Verzeichnis über Container-Manager
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {
                "success": True,
                "backup_path": "/modules/.backups/modulename_instance_backup_20260126_123456/",
                "message": "Backup created successfully"
            }
        """
        result = await self.post(f"/modules/{module_name}/{instance_id}/backup")
        return result.get("data", result)
    
    async def rollback_instance(
        self,
        module_name: str,
        instance_id: str,
        backup_path: str
    ) -> Dict:
        """
        Führe Rollback zu vorheriger Version über Container-Manager durch
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            backup_path: Pfad zum Backup-Verzeichnis
            
        Returns:
            {
                "success": True,
                "message": "Rollback completed successfully"
            }
        """
        result = await self.post(
            f"/modules/{module_name}/{instance_id}/rollback",
            params={"backup_path": backup_path}
        )
        return result.get("data", result)
    
    async def cleanup_backup(
        self,
        backup_path: str
    ) -> Dict:
        """
        Lösche Backup über Container-Manager nach erfolgreichem Update
        
        Args:
            backup_path: Pfad zum Backup-Verzeichnis
            
        Returns:
            {
                "success": True,
                "message": "Backup cleaned up successfully"
            }
        """
        result = await self.delete(
            "/modules/backups",
            params={"backup_path": backup_path}
        )
        return result.get("data", result)
    
    async def update_nfs_interfaces(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Aktualisiere Interface-Dateien im NFS über Container-Manager
        
        Interface-Dateien müssen im NFS unter /nfs/vyra_interfaces/ verfügbar sein
        damit andere Module sie sourcen können.
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {
                "success": True,
                "message": "NFS interfaces updated successfully",
                "copied_items": ["interface1", "interface2"]
            }
        """
        result = await self.post(
            f"/modules/{module_name}/{instance_id}/update-interfaces"
        )
        return result.get("data", result)
    
    async def stop_module(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Stoppe Modul-Container
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {"success": True/False, "message": "..."}
        """
        result = await self.post(f"/modules/{module_name}/{instance_id}/stop")
        return result.get("data", result)
    
    async def start_module(
        self,
        module_name: str,
        instance_id: str
    ) -> Dict:
        """
        Starte Modul-Container
        
        Args:
            module_name: Name des Moduls
            instance_id: UUID der Instanz
            
        Returns:
            {"success": True/False, "message": "..."}
        """
        result = await self.post(f"/modules/{module_name}/{instance_id}/start")
        return result.get("data", result)