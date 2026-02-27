"""
FastAPI Dependencies for Backend Webserver

Provides dependency injection for accessing core application components
via container_injection (VyraEntity, Component, TaskManager, StatusManager).
"""

import logging
from fastapi import HTTPException

logger = logging.getLogger(__name__)

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


# FastAPI dependency functions
def get_vyra_entity():
    """
    FastAPI dependency: Get VyraEntity from container_injection
    
    Usage in routers:
        @router.get("/endpoint")
        async def endpoint(entity = Depends(get_vyra_entity)):
            # Access entity.node, entity.call_service(), etc.
            pass
    
    Raises:
        HTTPException: If container not initialized or entity not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available"
        )
    
    try:
        return provide_entity()
    except ContainerNotInitializedError:
        raise HTTPException(
            status_code=503,
            detail="Services not initialized yet, please wait"
        )


def get_component():
    """
    FastAPI dependency: Get Component from container_injection
    
    Usage in routers:
        @router.get("/endpoint")
        async def endpoint(component = Depends(get_component)):
            # Access component methods
            result = await component.some_method()
            pass
    
    Raises:
        HTTPException: If container not initialized or component not available
    """
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available"
        )
    
    try:
        return provide_component()
    except ContainerNotInitializedError:
        raise HTTPException(
            status_code=503,
            detail="Services not initialized yet, please wait"
        )


def get_task_manager():
    """FastAPI dependency: Get TaskManager from container_injection"""
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available"
        )
    
    try:
        return provide_task_manager()
    except ContainerNotInitializedError:
        raise HTTPException(
            status_code=503,
            detail="Services not initialized yet, please wait"
        )


def get_status_manager():
    """FastAPI dependency: Get StatusManager from container_injection"""
    if not CONTAINER_AVAILABLE:
        raise HTTPException(
            status_code=503,
            detail="Container injection not available"
        )
    
    try:
        return provide_state_manager()
    except ContainerNotInitializedError:
        raise HTTPException(
            status_code=503,
            detail="Services not initialized yet, please wait"
        )
