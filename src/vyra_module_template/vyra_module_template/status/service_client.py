"""
Service client wrapper for status node interaction.

Provides convenient Python API for interacting with the status node
from other ROS2 nodes or Python applications.
"""

import json
import logging
from typing import Dict, Any, Optional

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

from .status_types import StatusRequest, StatusResponse, ThreeLayerStatus


logger = logging.getLogger(__name__)


class StatusServiceClient:
    """
    Client wrapper for status node service calls.
    
    Example usage:
        >>> client = StatusServiceClient(node, module_name="v2_modulemanager")
        >>> response = client.set_lifecycle("shutdown", reason="manual")
        >>> if response.success:
        >>>     print(f"New state: {response.current_status.lifecycle}")
    """
    
    def __init__(self, node: Node, module_name: str = "v2_modulemanager"):
        """
        Initialize status service client.
        
        Args:
            node: ROS2 node to use for service calls
            module_name: Module name for service namespace
        """
        self.node = node
        self.module_name = module_name
        
        # Create service client
        self.cli = node.create_client(
            String,
            f"{module_name}/set_status"
        )
        
        # Wait for service to be available
        logger.info(f"Waiting for {module_name}/set_status service...")
        self.cli.wait_for_service(timeout_sec=5.0)
        logger.info("Status service connected")
    
    def _call_service(
        self,
        layer: str,
        action: str,
        metadata: Optional[Dict[str, Any]] = None,
        timeout_sec: float = 2.0,
    ) -> StatusResponse:
        """
        Call set_status service.
        
        Args:
            layer: Layer to affect
            action: Action to execute
            metadata: Additional parameters
            timeout_sec: Service call timeout
            
        Returns:
            StatusResponse with result
            
        Raises:
            TimeoutError: If service call times out
            RuntimeError: If service call fails
        """
        # Create request
        request_obj = StatusRequest(
            layer=layer,
            action=action,
            metadata=metadata,
        )
        
        request_msg = String()
        request_msg.data = json.dumps(request_obj.to_dict())
        
        # Call service
        future = self.cli.call_async(request_msg)
        
        # Wait for result
        rclpy.spin_until_future_complete(
            self.node,
            future,
            timeout_sec=timeout_sec,
        )
        
        if not future.done():
            raise TimeoutError(f"Service call timeout after {timeout_sec}s")
        
        # Parse response
        response_msg = future.result()
        if response_msg is None:
            raise RuntimeError("Service call failed: no response")
        
        response_data = json.loads(response_msg.data)
        
        # Reconstruct StatusResponse
        return StatusResponse(
            success=response_data["success"],
            current_status=ThreeLayerStatus(**response_data["current_status"]),
            message=response_data["message"],
            error=response_data.get("error"),
        )
    
    # -------------------------------------------------------------------------
    # Lifecycle Layer Methods
    # -------------------------------------------------------------------------
    
    def set_lifecycle(
        self,
        action: str,
        **kwargs
    ) -> StatusResponse:
        """
        Execute lifecycle action.
        
        Args:
            action: Lifecycle action (start/complete_init/shutdown/etc)
            **kwargs: Action-specific metadata
            
        Returns:
            StatusResponse
        """
        return self._call_service("lifecycle", action, kwargs)
    
    def start_module(self) -> StatusResponse:
        """Start module initialization."""
        return self.set_lifecycle("start", auto_start=False)
    
    def complete_initialization(self) -> StatusResponse:
        """Complete initialization successfully."""
        return self.set_lifecycle("complete_init")
    
    def shutdown_module(self, reason: str = "manual") -> StatusResponse:
        """Shutdown module."""
        return self.set_lifecycle("shutdown", reason=reason)
    
    # -------------------------------------------------------------------------
    # Operational Layer Methods
    # -------------------------------------------------------------------------
    
    def set_operational(
        self,
        action: str,
        **kwargs
    ) -> StatusResponse:
        """
        Execute operational action.
        
        Args:
            action: Operational action (ready/start_task/pause/etc)
            **kwargs: Action-specific metadata
            
        Returns:
            StatusResponse
        """
        return self._call_service("operational", action, kwargs)
    
    def set_ready(self) -> StatusResponse:
        """Set operational state to ready."""
        return self.set_operational("ready")
    
    def start_task(self, task_data: Dict[str, Any]) -> StatusResponse:
        """Start a task."""
        return self.set_operational("start_task", **task_data)
    
    def pause_task(self, reason: str = "manual") -> StatusResponse:
        """Pause current task."""
        return self.set_operational("pause", reason=reason)
    
    def resume_task(self) -> StatusResponse:
        """Resume paused task."""
        return self.set_operational("resume")
    
    # -------------------------------------------------------------------------
    # Health Layer Methods
    # -------------------------------------------------------------------------
    
    def set_health(
        self,
        action: str,
        **kwargs
    ) -> StatusResponse:
        """
        Execute health action.
        
        Args:
            action: Health action (report_warning/report_fault/etc)
            **kwargs: Action-specific metadata
            
        Returns:
            StatusResponse
        """
        return self._call_service("health", action, kwargs)
    
    def report_warning(self, details: Dict[str, Any]) -> StatusResponse:
        """Report warning condition."""
        return self.set_health("report_warning", **details)
    
    def report_fault(self, error: str) -> StatusResponse:
        """Report fault condition."""
        return self.set_health("report_fault", error=error)
    
    def clear_health(self) -> StatusResponse:
        """Clear health warnings."""
        return self.set_health("clear_warning")


class StatusSubscriber:
    """
    Subscriber for monitoring status updates.
    
    Example usage:
        >>> def on_status_update(status: ThreeLayerStatus):
        >>>     print(f"New status: {status.lifecycle}")
        >>> 
        >>> subscriber = StatusSubscriber(node, on_status_update)
    """
    
    def __init__(
        self,
        node: Node,
        callback,
        module_name: str = "v2_modulemanager",
    ):
        """
        Initialize status subscriber.
        
        Args:
            node: ROS2 node
            callback: Function to call on status updates
            module_name: Module name for topic namespace
        """
        self.node = node
        self.callback = callback
        
        # Create subscription
        self.sub = node.create_subscription(
            String,
            f"{module_name}/get_status",
            self._handle_status_update,
            10,
        )
        
        logger.info(f"Subscribed to {module_name}/get_status")
    
    def _handle_status_update(self, msg: String):
        """
        Handle incoming status update.
        
        Args:
            msg: Status message (JSON)
        """
        try:
            data = json.loads(msg.data)
            status = ThreeLayerStatus(**data)
            self.callback(status)
        except Exception as e:
            logger.error(f"Failed to parse status update: {e}")
