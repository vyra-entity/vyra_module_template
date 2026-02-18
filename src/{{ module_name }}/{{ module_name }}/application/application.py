import asyncio
import datetime
import json
from ..logging_config import get_logger, log_exception
from typing import Any
import yaml

from pathlib import Path

from vyra_base import state
from vyra_base.state import (
    UnifiedStateMachine,
    OperationalStateMachine
)
from vyra_base.core.entity import VyraEntity
from vyra_base.com import remote_service

from ..taskmanager import TaskManager
from ..interface import auto_register_interfaces

logger = get_logger(__name__)


class Component(OperationalStateMachine):
    """
    Base component class for VYRA Module Manager application.
    
    Provides operational state management following industrial automation
    best practices with automatic state transitions.
    
    The Component uses the operational layer of the UnifiedStateMachine to manage
    its state (IDLE, READY, RUNNING, PAUSED, STOPPED, ERROR).
    
    User-defined lifecycle methods are prefixed with 'on_' (on_initialize, on_pause, etc.)
    and are automatically wrapped by the metaclass to handle state transitions.
    
    Public API methods are called without 'on_' prefix:
    - component.initialize()  -> calls on_initialize() with state management
    - component.pause()       -> calls on_pause() with state management
    - component.resume()      -> calls on_resume() with state management
    - component.stop()        -> calls on_stop() with state management
    - component.reset()       -> calls on_reset() with state management
    """
    
    def __init__(self, unified_state_machine: UnifiedStateMachine, entity: VyraEntity, task_manager: TaskManager):
        """
        Initialize the Component with unified state machine and entity.
        
        Args:
            unified_state_machine: The UnifiedStateMachine instance from StatusManager
            entity: The VyraEntity containing the ROS 2 node
            task_manager: The TaskManager instance to manage parallel application tasks
        """
        # Initialize parent OperationalStateMachine
        super().__init__(unified_state_machine)
        
        self.entity = entity
        self.task_manager = task_manager
        
        # Component instances
        # Define your instances here
    
    async def set_interfaces(self):
        """
        Setup @remote_service interfaces in VyraEntity.
        Automatically registers all methods decorated with @remote_service.
        """
        await auto_register_interfaces(self.entity, callback_parent=self)
    
    @remote_service
    async def initialize(self, request: Any=None, response: Any=None) -> bool:
        """
        Initialize the VYRA Module Manager components.
        
        State Transition: IDLE -> READY
        On Success: Module Manager fully initialized and ready for operations
        On Failure: IDLE -> ERROR
        
        Returns:
            bool: True on success, False on failure
        """
        try:
            logger.info("🚀 Initializing VYRA Module Manager components...")
            
            # Initialize user management
            self.internal_usermanager.set_entity(self.entity)
            asyncio.create_task(self.internal_usermanager.initialize_default_admin())
            self.usermanager_detector.set_registry(self.registry if hasattr(self, 'registry') else None)
            logger.info("✅ User Management initialized")
            
            # TODO: Implement initialize logic
            
            logger.info("✅ Component initialization complete")
            return True
            
        except Exception as e:
            logger.exception(f"❌ Component initialization failed: {e}")
            return False
    
    @remote_service
    async def pause(self, request: Any=None, response: Any=None) -> bool:
        """
        Pause ongoing operations.
        
        State Transition: RUNNING -> PAUSED
        On Success: Operations temporarily suspended
        On Failure: RUNNING -> ERROR
        
        Returns:
            bool: True on success, False on failure
        """
        # TODO: Implement pause logic
        # - Suspend ongoing operations
        # - Save current state/checkpoints
        # - Release temporary resources
        logger.info("⏸️  Component pause requested")
        return True  # Placeholder for actual implementation
    
    @remote_service
    async def resume(self, request: Any=None, response: Any=None) -> bool:
        """
        Resume from paused state.
        
        State Transition: PAUSED -> READY
        On Success: Operations resumed, operation counter reset
        On Failure: PAUSED -> ERROR
        
        Returns:
            bool: True on success, False on failure
        """
        # TODO: Implement resume logic
        # - Restore saved state/checkpoints
        # - Re-acquire resources
        # - Resume suspended operations
        logger.info("▶️  Component resume requested")
        return True
    
    @remote_service
    async def stop(self, request: Any=None, response: Any=None) -> bool:
        """
        Stop component operations cleanly.
        
        State Transition: RUNNING/PAUSED -> STOPPED
        On Success: Clean shutdown completed
        On Failure: -> ERROR
        
        Returns:
            bool: True on success, False on failure
        """
        # TODO: Implement stop logic
        # - Stop gRPC servers
        # - Close database connections
        # - Finalize ongoing operations
        # - Release all resources
        logger.info("⏹️  Component stop requested")
        
        return True
    
    @remote_service
    async def reset(self, request: Any=None, response: Any=None) -> bool:
        """
        Reset component to initial state.
        
        State Transition: STOPPED/ERROR -> IDLE
        On Success: Ready for re-initialization
        
        Returns:
            bool: True on success, False on failure
        """
        # TODO: Implement reset logic
        # - Clear all state
        # - Release remaining resources
        # - Reset to initial configuration
        logger.info("🔄 Component reset requested")
        
        return True
    
    # @remote_service
    # @state.operation
    # async def template_test(self, request: Any=None, response: Any=None) -> dict:
    #     """
    #     Template test function demonstrating @remote_service + @state.operation.
        
    #     This function serves as a template showing how to combine both decorators:
    #     - @remote_service: Exposes method as ROS2 service
    #     - @state.operation: Automatic READY <-> RUNNING state management with reference counting
        
    #     State Flow: READY -> RUNNING (counter++) -> execute -> RUNNING (counter--) -> READY (if counter=0)
        
    #     Args:
    #         test_data: Optional test data dictionary
            
    #     Returns:
    #         dict: Test result with status and data
    #     """
    #     test_data = request.test_data if request and hasattr(request, 'test_data') else {}
        
    #     logger.info(f"🧪 Template test function called with data: {test_data}")
        
    #     # TODO: Implement actual test logic here
    #     # This is just a template demonstration
        
    #     logger.info(f"✅ Template test completed: {result['message']}")
    #     return result


async def main(task_manager: TaskManager, status_manager, component: Component) -> None:
    """
    Main application entry point for VYRA Module Manager.
    
    Loads configuration, initializes component, and manages lifecycle based on
    module_params.yaml configuration.
    
    Args:
        entity: The VyraEntity containing the ROS 2 node
        task_manager: The TaskManager instance to manage parallel application tasks
        status_manager: The StatusManager instance containing the UnifiedStateMachine
        component: The Component instance (created once, reused across recoveries)
    """
    logger.info("🚀 Starting VYRA Module Manager...")
    
    # Load module configuration
    module_params_path = Path(".module/module_params.yaml")
    if not module_params_path.exists():
        logger.warning(f"⚠️  Module params not found at {module_params_path}, using defaults")
        auto_start = True  # Default to auto-start
    else:
        with open(module_params_path, "r") as f:
            module_params = yaml.safe_load(f)
            auto_start = module_params.get("behavior", {}).get("auto_start", True)
    
    logger.info(f"📋 Configuration: auto_start={auto_start}")
    
    # Auto-start if configured
    if auto_start:
        # Check current operational state and component initialization status
        current_state = component.get_operational_state()
        logger.info(f"🔍 Current operational state: {current_state}")
        
        # Initialize component if not already initialized
        # Note: StatusManager may have set state to READY, but component business logic may not be initialized yet
        component_needs_init = (component.permission is None or component.registry is None)
        
        if component_needs_init:
            # Only call initialize() if state is IDLE, otherwise manually initialize components
            if current_state.value == "Idle":
                logger.info("🔄 Initializing component via initialize() method...")
                success = component.initialize()
                
                if not success:
                    logger.error("❌ Component initialization failed")
                    if component.is_error():
                        logger.error("💥 Component in ERROR state - manual reset required")
            else:
                # State is already READY but components not initialized (e.g., after recovery)
                # Initialize components directly without state transition
                logger.info(f"🔄 Component in state {current_state} but not initialized, initializing components directly...")
                try:
                    # TODO: Implement initialization logic here if manually needed
                    
                    success = True
                except Exception as e:
                    logger.exception(f"❌ Component initialization failed: {e}")
                    success = False
        else:
            logger.info(f"⏭️  Component already initialized (state: {current_state})")
            success = True
        
        if success:
            # Setup async components after initialization
                        
            logger.info("✅ Application setup complete - service running")
    else:
        logger.info("⏸️  Auto-start disabled, waiting for manual initialization")
    
    # Keep service running indefinitely
    logger.info("♾️  Service running indefinitely...")
    
    while True:
        await asyncio.sleep(10)
