"""
Global Dependency Injection Container for V2 ModuleManager

This module provides a global container for sharing VyraEntity and Component
instances across different parts of the application (ROS2 core, REST API, etc.)
without requiring gRPC over UDS communication.

Uses the dependency_injector framework for professional DI management.

Usage:
    # In main.py after initialization:
    from .container_injection import container
    container.entity.set(entity)
    container.component.set(component)
    
    # In backend_webserver or other modules (use relative imports):
    from ...container_injection import container  # From backend_webserver/*/
    entity = container.entity()
    component = container.component()
"""

from .logging_config import get_logger
from dependency_injector import containers, providers

logger = get_logger(__name__)


class ContainerNotInitializedError(Exception):
    """Raised when trying to access container before initialization"""
    pass


class ApplicationContainer(containers.DeclarativeContainer):
    """
    Dependency Injection Container for V2 ModuleManager.
    
    Provides singleton instances of core application components:
    - VyraEntity: ROS2 node and communication
    - Component: Application logic
    - TaskManager: Task management
    - StateManager: State broadcasting
    - UserManager: User management (internal_usermanager + gRPC server)
    """
    
    # Configuration
    config = providers.Configuration()
    
    # Core components as Singleton providers
    entity = providers.Singleton(lambda: None)
    component = providers.Singleton(lambda: None)
    task_manager = providers.Singleton(lambda: None)
    state_manager = providers.Singleton(lambda: None)
    user_manager = providers.Singleton(lambda: None)


# Global container instance
container = ApplicationContainer()


def set_entity(entity_instance) -> None:
    """
    Set the VyraEntity instance in the global container.
    
    Args:
        entity_instance: VyraEntity instance from core application
    """
    container.entity.override(providers.Object(entity_instance))
    logger.info("✅ VyraEntity set in container_injection")


def get_entity():
    """
    Get the VyraEntity instance from the global container.
    
    Returns:
        VyraEntity instance
        
    Raises:
        ContainerNotInitializedError: If entity has not been set yet
    """
    entity_instance = container.entity()
    if entity_instance is None:
        raise ContainerNotInitializedError(
            "VyraEntity not initialized in container. "
            "Make sure initialize_module() has been called."
        )
    return entity_instance


def set_component(component_instance) -> None:
    """
    Set the Component instance in the global container.
    
    Args:
        component_instance: Component instance from application
    """
    container.component.override(providers.Object(component_instance))
    logger.info("✅ Component set in container_injection")


def get_component():
    """
    Get the Component instance from the global container.
    
    Returns:
        Component instance
        
    Raises:
        ContainerNotInitializedError: If component has not been set yet
    """
    component_instance = container.component()
    if component_instance is None:
        raise ContainerNotInitializedError(
            "Component not initialized in container. "
            "Make sure initialize_module() has been called."
        )
    return component_instance


def set_task_manager(task_manager_instance) -> None:
    """
    Set the TaskManager instance in the global container.
    
    Args:
        task_manager_instance: TaskManager instance
    """
    container.task_manager.override(providers.Object(task_manager_instance))
    logger.info("✅ TaskManager set in container_injection")


def get_task_manager():
    """
    Get the TaskManager instance from the global container.
    
    Returns:
        TaskManager instance
        
    Raises:
        ContainerNotInitializedError: If task_manager has not been set yet
    """
    task_manager_instance = container.task_manager()
    if task_manager_instance is None:
        raise ContainerNotInitializedError(
            "TaskManager not initialized in container. "
            "Make sure runner() has been called."
        )
    return task_manager_instance


def set_state_manager(state_manager_instance) -> None:
    """
    Set the StateManager instance in the global container.
    
    Args:
        state_manager_instance: StateManager instance
    """
    container.state_manager.override(providers.Object(state_manager_instance))
    logger.info("✅ StateManager set in container_injection")


def get_state_manager():
    """
    Get the StateManager instance from the global container.
    
    Returns:
        StateManager instance
        
    Raises:
        ContainerNotInitializedError: If state_manager has not been set yet
    """
    state_manager_instance = container.state_manager()
    if state_manager_instance is None:
        raise ContainerNotInitializedError(
            "StateManager not initialized in container. "
            "Make sure initialize_module() has been called."
        )
    return state_manager_instance


def is_initialized() -> bool:
    """
    Check if the container has been initialized with all required components.
    
    Returns:
        True if entity, component, task_manager, state_manager, and user_manager are all set
    """
    try:
        return all([
            container.entity() is not None,
            container.component() is not None,
            container.task_manager() is not None,
            container.state_manager() is not None,
            container.user_manager() is not None
        ])
    except Exception:
        return False


def reset() -> None:
    """
    Reset the container (mainly for testing purposes).
    """
    container.entity.override(providers.Singleton(lambda: None))
    container.component.override(providers.Singleton(lambda: None))
    container.task_manager.override(providers.Singleton(lambda: None))
    container.state_manager.override(providers.Singleton(lambda: None))
    container.user_manager.override(providers.Singleton(lambda: None))
    logger.info("🔄 Container reset")


# Convenience method for FastAPI Depends()
def provide_entity():
    """
    Provider function for FastAPI Depends().
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(entity = Depends(provide_entity)):
            ...
    """
    return get_entity()


def provide_component():
    """
    Provider function for FastAPI Depends().
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(component = Depends(provide_component)):
            ...
    """
    return get_component()


def provide_task_manager():
    """
    Provider function for FastAPI Depends().
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(task_manager = Depends(provide_task_manager)):
            ...
    """
    return get_task_manager()


def provide_state_manager():
    """
    Provider function for FastAPI Depends().
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(state_manager = Depends(provide_state_manager)):
            ...
    """
    return get_state_manager()


def set_user_manager(user_manager_instance) -> None:
    """
    Set the UserManager instance in the global container.
    
    Args:
        user_manager_instance: UserManager instance
    """
    container.user_manager.override(providers.Object(user_manager_instance))
    logger.info("✅ UserManager set in container_injection")


def get_user_manager():
    """
    Get the UserManager instance from the global container.
    
    Returns:
        UserManager instance
        
    Raises:
        ContainerNotInitializedError: If user_manager has not been set yet
    """
    user_manager_instance = container.user_manager()
    if user_manager_instance is None:
        raise ContainerNotInitializedError(
            "UserManager not initialized in container. "
            "Make sure Component.initialize() has been called."
        )
    return user_manager_instance


def provide_user_manager():
    """
    Provider function for FastAPI Depends().
    
    Usage:
        from fastapi import Depends
        
        @router.get("/endpoint")
        async def endpoint(user_manager = Depends(provide_user_manager)):
            ...
    """
    return get_user_manager()
