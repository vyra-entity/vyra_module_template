"""
Status Manager for v2_modulemanager.

Manages the 3-layer state machine (Lifecycle, Operational, Health) and
provides ROS2 interfaces for status monitoring and control.

Features:
- Runs as async task integrated in core main.py
- vyra_base integration with @remote_callable decorator
- StateFeeder for periodic status broadcasting via existing VyraEntity
- Integration with vyra_base UnifiedStateMachine
"""

import asyncio
import logging
import json
import yaml
from pathlib import Path
from typing import Dict, Any, Optional
from datetime import datetime

from ..interface import auto_register_callable_interfaces

from vyra_base.state.unified import UnifiedStateMachine
from vyra_base.state.state_types import (
    LifecycleState,
    OperationalState,
    HealthState,
)
from vyra_base.com import remote_callable
from vyra_base.core.entity import VyraEntity

from .status_types import (
    ThreeLayerStatus,
    StatusRequest,
    StatusResponse,
    is_valid_action,
    LAYER_ACTIONS,
)


logger = logging.getLogger(__name__)


class StatusManager:
    """
    Status manager for 3-layer status management.
    
    Runs as async task integrated in core main.py.
    Uses existing VyraEntity instance for StateFeeder and @remote_callable.
    
    Responsibilities:
    1. Initialize and manage UnifiedStateMachine
    2. Automatically activate module on container startup
    3. Provide @remote_callable interfaces via vyra_base
    4. Publish status via StateFeeder (periodic broadcasting)
    
    ROS2 Interfaces (via @remote_callable):
        get_status() - Returns current 3-layer status (JSON)
        set_status(action, metadata) - Request state changes
    """
    
    def __init__(self, entity: VyraEntity):
        """
        Initialize status manager.
        
        Args:
            entity: VyraEntity instance from core application
        """
        self.entity = entity
        
        # Load module identification from .module/module_data.yaml
        module_data = self._load_module_data()
        self.module_name = module_data.get("name", "unknown_module")
        self.module_id = module_data.get("uuid", "")
        
        logger.info(f"📋 Module: {self.module_name}")
        logger.info(f"🆔 UUID: {self.module_id}")
        
        # Initialize 3-layer state machine
        self.state_machine: UnifiedStateMachine = UnifiedStateMachine()
        
        # Last published status (for change detection)
        self._last_status: Optional[ThreeLayerStatus] = None
        
        logger.info(f"StatusManager initialized for module: {self.module_name}")
        
        # Automatically start module lifecycle
        self.auto_start_module()
    
    async def setup_interfaces(self):
        """
        Setup @remote_callable interfaces in VyraEntity.
        """
        await auto_register_callable_interfaces(self.entity, callback_parent=self)
        logger.info("✅ StatusManager interfaces registered")

    def _load_module_data(self) -> Dict[str, Any]:
        """
        Load module metadata from .module/module_data.yaml.
        
        Returns:
            Dictionary with module data (name, uuid, version, etc.)
        """
        module_data_path = Path("/workspace/.module/module_data.yaml")
        
        try:
            if module_data_path.exists():
                with open(module_data_path, "r") as f:
                    data = yaml.safe_load(f)
                    return data if data else {}
            else:
                logger.warning(
                    f"⚠️ Module data file not found: {module_data_path}"
                )
                return {}
        except Exception as e:
            logger.error(
                f"❌ Failed to load module data: {e}"
            )
            return {}
    
    def auto_start_module(self):
        """
        Automatically start module lifecycle on container startup.
        
        Sequence:
        1. Start: UNINITIALIZED → INITIALIZING
        2. Complete initialization: INITIALIZING → ACTIVE
        3. Set operational ready: IDLE → READY
        """
        try:
            logger.info("🚀 Auto-starting module lifecycle...")
            
            # Step 1: Start initialization
            self.state_machine.start(metadata={"auto_start": True})
            logger.info("  ✓ Lifecycle: INITIALIZING")
            
            # Step 2: Complete initialization (assuming no errors)
            self.state_machine.complete_initialization(
                result={"container_ready": True}
            )
            logger.info("  ✓ Lifecycle: ACTIVE")
            
            # Step 3: Set operational ready
            self.state_machine.ready()
            logger.info("  ✓ Operational: READY")
            
            logger.info("✅ Module successfully activated!")
            
        except Exception as e:
            logger.error(f"❌ Failed to auto-start module: {e}")
            # Try to set health to faulted
            try:
                self.state_machine.report_fault(error=str(e))
            except Exception:
                pass
    
    def get_current_status(self) -> ThreeLayerStatus:
        """
        Get current 3-layer status from state machine.
        
        Returns:
            ThreeLayerStatus with current states
        """
        states = self.state_machine.get_all_states()
        return ThreeLayerStatus(
            lifecycle=states["lifecycle"],
            operational=states["operational"],
            health=states["health"],
            timestamp=datetime.now(),
            metadata={
                "module_name": self.module_name,
                "module_id": self.module_id,
                "is_operational": self.state_machine.is_operational(),
                "is_healthy": self.state_machine.is_healthy(),
            },
        )
    
    async def broadcast_status(self):
        """
        Broadcast current status via StateFeeder.
        
        Called periodically in async loop (1 Hz).
        Uses vyra_base StateFeeder for standardized state broadcasting.
        """
        try:
            current_status = self.get_current_status()
            states = self.state_machine.get_all_states()
            
            # Broadcast via StateFeeder
            self.entity.state_feeder.feed_state(
                lifecycle_state=states["lifecycle"],
                operational_state=states["operational"],
                health_state=states["health"],
                metadata={
                    "module_name": self.module_name,
                    "module_id": self.module_id,
                    "is_operational": self.state_machine.is_operational(),
                    "is_healthy": self.state_machine.is_healthy(),
                    "timestamp": current_status.timestamp.isoformat(),
                }
            )
            
            self._last_status = current_status
                
        except Exception as e:
            logger.error(f"Failed to broadcast status: {e}")
    
    @remote_callable
    def get_status(self, request, response):
        """
        Get current 3-layer status (via @remote_callable).
        
        Returns:
            JSON with current lifecycle, operational, and health states
        """
        try:
            current_status = self.get_current_status()
            response.data = json.dumps(current_status.to_dict())
            return response
            
        except Exception as e:
            logger.error(f"Get status request failed: {e}")
            error_response = {
                "error": str(e),
                "message": "Failed to get status"
            }
            response.data = json.dumps(error_response)
            return response
    
    @remote_callable
    async def set_status(self, request, response):
        """
        Set status via state machine action (via @remote_callable).
        
        Request format (JSON in String message):
        {
            "layer": "lifecycle|operational|health",
            "action": "start|shutdown|ready|fault|...",
            "metadata": {...}  // optional
        }
        
        Args:
            request: String message with JSON payload
            response: String message with JSON result
            
        Returns:
            Response with success status and current state
        """
        try:
            # Parse request
            request_data = json.loads(request.data)
            status_req = StatusRequest.from_dict(request_data)
            
            logger.info(
                f"Set status request: {status_req.layer}.{status_req.action}"
            )
            
            # Validate action
            if not is_valid_action(status_req.layer, status_req.action):
                raise ValueError(
                    f"Invalid action '{status_req.action}' for layer '{status_req.layer}'"
                )
            
            # Execute action
            result = self.execute_status_action(status_req)
            
            # Return response
            response.data = json.dumps(result.to_dict())
            
            # Broadcast updated status immediately
            await self.broadcast_status()
            
            return response
            
        except Exception as e:
            logger.error(f"Set status request failed: {e}")
            
            # Return error response
            error_response = StatusResponse(
                success=False,
                current_status=self.get_current_status(),
                message="Failed to execute action",
                error=str(e),
            )
            response.data = json.dumps(error_response.to_dict())
            return response
    
    def execute_status_action(self, request: StatusRequest) -> StatusResponse:
        """
        Execute state machine action based on request.
        
        Args:
            request: Status change request
            
        Returns:
            StatusResponse with result
            
        Raises:
            ValueError: If action is invalid
        """
        layer = request.layer
        action = request.action
        metadata = request.metadata or {}
        
        try:
            # Lifecycle actions
            if layer == "lifecycle":
                if action == "start":
                    self.state_machine.start(metadata)
                elif action == "complete_init":
                    self.state_machine.complete_initialization(metadata)
                elif action == "fail_init":
                    self.state_machine.fail_initialization(metadata.get("error"))
                elif action == "shutdown":
                    self.state_machine.shutdown(metadata.get("reason"))
                elif action == "recover":
                    self.state_machine.start_recovery(metadata.get("error"))
                elif action == "complete_recovery":
                    self.state_machine.complete_recovery()
                elif action == "fail_recovery":
                    self.state_machine.fail_recovery()
                else:
                    raise ValueError(f"Unknown lifecycle action: {action}")
            
            # Operational actions
            elif layer == "operational":
                if action == "ready":
                    self.state_machine.ready()
                elif action == "start_task":
                    self.state_machine.start_task(metadata)
                elif action == "pause":
                    self.state_machine.pause_task(metadata.get("reason"))
                elif action == "resume":
                    self.state_machine.resume_task()
                elif action == "block":
                    self.state_machine.block(metadata.get("reason"))
                elif action == "unblock":
                    self.state_machine.unblock()
                elif action == "delegate":
                    self.state_machine.delegate(metadata)
                elif action == "complete":
                    self.state_machine.complete_task(metadata)
                elif action == "reset":
                    self.state_machine.reset_to_ready()
                else:
                    raise ValueError(f"Unknown operational action: {action}")
            
            # Health actions
            elif layer == "health":
                if action == "report_warning":
                    self.state_machine.report_warning(metadata)
                elif action == "report_overload":
                    self.state_machine.report_overload(metadata)
                elif action == "report_fault":
                    self.state_machine.report_fault(metadata.get("error"))
                elif action == "clear_warning":
                    self.state_machine.clear_health()
                elif action == "reduce_load":
                    self.state_machine.reduce_load()
                elif action == "recover":
                    self.state_machine.recover_from_fault()
                elif action == "escalate_critical":
                    self.state_machine.escalate_to_critical(metadata)
                else:
                    raise ValueError(f"Unknown health action: {action}")
            
            else:
                raise ValueError(f"Unknown layer: {layer}")
            
            # Success response
            return StatusResponse(
                success=True,
                current_status=self.get_current_status(),
                message=f"Successfully executed {layer}.{action}",
            )
            
        except Exception as e:
            logger.error(f"Failed to execute action {layer}.{action}: {e}")
            raise


async def status_manager_runner(entity: VyraEntity) -> None:
    """
    Status manager runner as async task.
    
    Initializes StatusManager and runs periodic status broadcasting.
    
    Args:
        entity: VyraEntity instance from core application
    """
    logger.info('Starting status manager...')
    try:
        # Initialize status manager
        status_manager = StatusManager(entity)
        
        await status_manager.setup_interfaces()

        # Run periodic status broadcasting (1 Hz)
        while True:
            # await status_manager.broadcast_status()
            await asyncio.sleep(1.0)
            
    except asyncio.CancelledError:
        logger.info('Status manager task cancelled.')
        raise
    except Exception as e:
        logger.exception(f'Status manager error: {e}')
        raise
    finally:
        logger.info('Status manager finished.')
