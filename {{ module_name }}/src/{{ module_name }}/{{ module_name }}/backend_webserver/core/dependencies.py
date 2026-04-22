"""
Common dependencies for VYRA Module Manager API
"""
from fastapi import HTTPException, BackgroundTasks, Depends
from typing import Optional, Dict, Any
from {{ module_name }}.logging_config import get_logger, log_exception, log_function_call, log_function_result
import uuid
from pathlib import Path

from .config import settings

# Logger Setup
logger = get_logger(__name__)

# Import container_injection for accessing VyraEntity and Component
try:
    from ...container_injection import (
        provide_entity,
        provide_component,
        provide_task_manager,
        provide_state_manager,
        ContainerNotInitializedError
    )
    CONTAINER_AVAILABLE = True
except ImportError:
    logger.warning("⚠️ container_injection not available - REST API running standalone")
    CONTAINER_AVAILABLE = False
    ContainerNotInitializedError = Exception  # Fallback for type hints

# Global operation tracking
module_operations: Dict[str, Dict[str, Any]] = {}

def get_settings():
    """Dependency to get application settings"""
    return settings

def get_background_tasks() -> BackgroundTasks:
    """Get background tasks instance"""
    return BackgroundTasks()

def create_operation_id() -> str:
    """Create a unique operation ID"""
    return str(uuid.uuid4())

def get_operation_status(operation_id: str) -> Optional[Dict[str, Any]]:
    """Get status of a background operation"""
    return module_operations.get(operation_id)

def set_operation_status(operation_id: str, status: Dict[str, Any]):
    """Set status of a background operation"""
    module_operations[operation_id] = status

def validate_module_name(module_name: str) -> str:
    """Validate module name format"""
    if not module_name:
        raise HTTPException(status_code=400, detail="Module name cannot be empty")
    
    if not module_name.replace("_", "").replace("-", "").isalnum():
        raise HTTPException(
            status_code=400, 
            detail="Module name can only contain letters, numbers, underscores and hyphens"
        )
    
    return module_name

def validate_instance_id(instance_id: str) -> str:
    """
    Validate instance ID format
    
    Accepts two formats:
    1. Pure 32-character hex string (e.g., "aef036f639d3486a985b65ee25df8fec")
    2. Prefixed format: {prefix}_{32-char-hex} (e.g., "v3_ff063be9da4d4e44892fff113a885d17")
    
    The prefixed format is used by test modules and some legacy installations.
    """
    if not instance_id:
        raise HTTPException(status_code=400, detail="Instance ID cannot be empty")
    
    # Check for prefixed format (e.g., "v3_abc123...")
    if "_" in instance_id:
        parts = instance_id.split("_", 1)
        if len(parts) == 2:
            prefix, hex_part = parts
            # Validate prefix (alphanumeric)
            if not prefix.replace("-", "").isalnum():
                raise HTTPException(
                    status_code=400,
                    detail="Instance ID prefix must be alphanumeric"
                )
            # Validate hex part (32 chars, hex)
            if len(hex_part) == 32 and all(c in "0123456789abcdef" for c in hex_part):
                return instance_id
            raise HTTPException(
                status_code=400,
                detail="Instance ID hex part must be a 32-character hexadecimal string"
            )
    
    # Check for pure hex format (original format)
    if len(instance_id) == 32 and all(c in "0123456789abcdef" for c in instance_id):
        return instance_id
    
    raise HTTPException(
        status_code=400,
        detail="Instance ID must be either a 32-character hexadecimal string or {prefix}_{32-char-hex}"
    )


def get_module_path(module_name: str, instance_id: str) -> Path:
    """Get the file system path for a module instance"""
    module_dir = f"{module_name}_{instance_id}"
    return settings.MODULES_PATH / module_dir

def check_module_exists(module_name: str, instance_id: str) -> bool:
    """Check if a module instance exists on the file system"""
    module_path = get_module_path(module_name, instance_id)
    return module_path.exists() and module_path.is_dir()

class ModuleNotFoundError(HTTPException):
    """Exception raised when a module is not found"""
    def __init__(self, module_name: str, instance_id: Optional[str] = None):
        if instance_id:
            detail = f"Module instance {module_name}/{instance_id} not found"
        else:
            detail = f"Module {module_name} not found"
        super().__init__(status_code=404, detail=detail)

class ModuleOperationError(HTTPException):
    """Exception raised when a module operation fails"""
    def __init__(self, operation: str, module_name: str, detail: str):
        super().__init__(
            status_code=500, 
            detail=f"Failed to {operation} module {module_name}: {detail}"
        )

def validate_operation_status(status: str) -> str:
    """Validate operation status"""
    valid_statuses = ["queued", "running", "completed", "failed", "cancelled"]
    if status not in valid_statuses:
        raise HTTPException(
            status_code=400, 
            detail=f"Invalid status. Must be one of: {', '.join(valid_statuses)}"
        )
    return status

def get_docker_service_name(module_name: str, instance_id: str) -> str:
    """Generate Docker service name for a module instance"""
    return f"{settings.DOCKER_STACK_NAME}_{module_name}_{instance_id}"

def get_vyra_entity():
    """
    FastAPI dependency to get VyraEntity from container_injection.
    
    This allows REST API endpoints to access the ROS2 node and ROS2 services
    without requiring gRPC over UDS.
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(entity = Depends(get_vyra_entity)):
            result = await entity.call_service(...)
            return result
    
    Returns:
        VyraEntity instance from container_injection
        
    Raises:
        HTTPException: If container is not initialized or not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available - REST API running standalone"
        )
    
    try:
        return provide_entity()
    except ContainerNotInitializedError as e:
        raise HTTPException(
            status_code=503,
            detail=f"VyraEntity not yet initialized: {str(e)}"
        )

def get_component():
    """
    FastAPI dependency to get Component from container_injection.
    
    This allows REST API endpoints to access the application Component
    and its methods without requiring gRPC over UDS.
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(component = Depends(get_component)):
            result = await component.some_method()
            return result
    
    Returns:
        Component instance from container_injection
        
    Raises:
        HTTPException: If container is not initialized or not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available - REST API running standalone"
        )
    
    try:
        return provide_component()
    except ContainerNotInitializedError as e:
        raise HTTPException(
            status_code=503,
            detail=f"Component not yet initialized: {str(e)}"
        )

def get_task_manager():
    """
    FastAPI dependency to get TaskManager from container_injection.
    
    Usage:
        from fastapi import Depends
        
        @router.get("/tasks")
        async def tasks(task_manager = Depends(get_task_manager)):
            return task_manager.get_status()
    
    Returns:
        TaskManager instance from container_injection
        
    Raises:
        HTTPException: If container is not initialized or not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available - REST API running standalone"
        )
    
    try:
        return provide_task_manager()
    except ContainerNotInitializedError as e:
        raise HTTPException(
            status_code=503,
            detail=f"TaskManager not yet initialized: {str(e)}"
        )

def get_status_manager():
    """
    FastAPI dependency to get StatusManager from container_injection.
    
    Usage:
        from fastapi import Depends
        
        @router.get("/status")
        async def status(status_manager = Depends(get_status_manager)):
            return status_manager.get_current_state()
    
    Returns:
        StatusManager instance from container_injection
        
    Raises:
        HTTPException: If container is not initialized or not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available - REST API running standalone"
        )
    
    try:
        return provide_state_manager()
    except ContainerNotInitializedError as e:
        raise HTTPException(
            status_code=503,
            detail=f"StatusManager not yet initialized: {str(e)}"
        )