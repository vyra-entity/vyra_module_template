"""
Common dependencies for VYRA modules

Template for dependency injection, validation, and utility functions.

CUSTOMIZATION:
- Add module-specific validation functions
- Add custom exceptions
- Add dependency injection helpers
"""
from fastapi import HTTPException, BackgroundTasks
from typing import Optional, Dict, Any
import logging
import uuid
from pathlib import Path

from .config import settings

logger = logging.getLogger(__name__)

# Global operation tracking (simple in-memory storage)
# For production, use Redis or database
module_operations: Dict[str, Dict[str, Any]] = {}


def get_settings():
    """Dependency to get application settings"""
    return settings


def get_logger(name: str = __name__):
    """Get configured logger for a module"""
    return logging.getLogger(name)


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


# Example validation functions
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


def validate_id(id_value: str, id_name: str = "ID") -> str:
    """Validate generic ID format"""
    if not id_value:
        raise HTTPException(status_code=400, detail=f"{id_name} cannot be empty")
    
    if len(id_value) != 32 or not all(c in "0123456789abcdef" for c in id_value):
        raise HTTPException(
            status_code=400, 
            detail=f"{id_name} must be a 32-character hexadecimal string"
        )
    
    return id_value


# Example custom exceptions
class ResourceNotFoundError(HTTPException):
    """Exception raised when a resource is not found"""
    def __init__(self, resource_type: str, resource_id: str):
        detail = f"{resource_type} {resource_id} not found"
        super().__init__(status_code=404, detail=detail)


class OperationError(HTTPException):
    """Exception raised when an operation fails"""
    def __init__(self, operation: str, detail: str):
        super().__init__(
            status_code=500, 
            detail=f"Failed to {operation}: {detail}"
        )


# TODO: Add your module-specific dependencies here
# Example:
# def get_sensor_client():
#     """Get sensor client singleton"""
#     from ..clients.http.sensor import sensor_client
#     return sensor_client
