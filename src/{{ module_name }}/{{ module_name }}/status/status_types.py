"""
Type definitions for status management.

Provides data structures for 3-layer status representation and
ROS2 service message mapping.
"""

from dataclasses import dataclass, asdict
from typing import Dict, Any, Optional
from datetime import datetime

from vyra_base.state.state_types import (
    LifecycleState,
    OperationalState,
    HealthState,
)


@dataclass
class ThreeLayerStatus:
    """
    Complete 3-layer status representation.
    
    Attributes:
        lifecycle: Current lifecycle state (existence/activation)
        operational: Current operational state (activity)
        health: Current health state (diagnostics)
        timestamp: When status was last updated
        metadata: Additional context information
    """
    lifecycle: str
    operational: str
    health: str
    timestamp: datetime
    metadata: Optional[Dict[str, Any]] = None
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary for JSON serialization."""
        return {
            "lifecycle": self.lifecycle,
            "operational": self.operational,
            "health": self.health,
            "timestamp": self.timestamp.isoformat(),
            "metadata": self.metadata or {},
        }
    
    @classmethod
    def from_states(
        cls,
        lifecycle: LifecycleState,
        operational: OperationalState,
        health: HealthState,
        metadata: Optional[Dict[str, Any]] = None,
    ) -> "ThreeLayerStatus":
        """
        Create from vyra_base state enums.
        
        Args:
            lifecycle: Lifecycle state enum
            operational: Operational state enum
            health: Health state enum
            metadata: Additional context
            
        Returns:
            ThreeLayerStatus instance
        """
        return cls(
            lifecycle=lifecycle.value,
            operational=operational.value,
            health=health.value,
            timestamp=datetime.now(),
            metadata=metadata,
        )


@dataclass
class StatusRequest:
    """
    Request to change status on specific layer.
    
    Attributes:
        layer: Which layer to affect (lifecycle/operational/health)
        action: Action to perform (start/shutdown/ready/fault/etc)
        metadata: Additional parameters for the action
    """
    layer: str  # "lifecycle" | "operational" | "health"
    action: str
    metadata: Optional[Dict[str, Any]] = None
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary."""
        return asdict(self)
    
    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "StatusRequest":
        """Create from dictionary."""
        return cls(
            layer=data["layer"],
            action=data["action"],
            metadata=data.get("metadata"),
        )


@dataclass
class StatusResponse:
    """
    Response from status change request.
    
    Attributes:
        success: Whether the action succeeded
        current_status: Status after action (or unchanged if failed)
        message: Human-readable result message
        error: Error details if failed
    """
    success: bool
    current_status: ThreeLayerStatus
    message: str
    error: Optional[str] = None
    
    def to_dict(self) -> Dict[str, Any]:
        """Convert to dictionary."""
        return {
            "success": self.success,
            "current_status": self.current_status.to_dict(),
            "message": self.message,
            "error": self.error,
        }


# Mapping of layer names to their valid actions
LAYER_ACTIONS = {
    "lifecycle": [
        "start",                  # UNINITIALIZED → INITIALIZING
        "complete_init",          # INITIALIZING → ACTIVE
        "fail_init",              # INITIALIZING → RECOVERING
        "shutdown",               # ACTIVE → SHUTTING_DOWN
        "recover",                # FAULTED → RECOVERING
        "complete_recovery",      # RECOVERING → ACTIVE
        "fail_recovery",          # RECOVERING → DEACTIVATED
    ],
    "operational": [
        "ready",                  # IDLE → READY
        "start_task",             # READY → RUNNING
        "pause",                  # RUNNING → PAUSED
        "resume",                 # PAUSED → RUNNING
        "block",                  # RUNNING → BLOCKED
        "unblock",                # BLOCKED → RUNNING
        "delegate",               # RUNNING → DELEGATING
        "complete",               # RUNNING → COMPLETED
        "reset",                  # COMPLETED → READY/IDLE
    ],
    "health": [
        "report_warning",         # OK → WARNING
        "report_overload",        # WARNING → OVERLOADED
        "report_fault",           # WARNING → FAULTED
        "clear_warning",          # WARNING → OK
        "reduce_load",            # OVERLOADED → WARNING
        "recover",                # FAULTED → OK
        "escalate_critical",      # FAULTED → CRITICAL
    ],
}


def is_valid_action(layer: str, action: str) -> bool:
    """
    Check if action is valid for given layer.
    
    Args:
        layer: Layer name
        action: Action name
        
    Returns:
        True if valid combination
    """
    return layer in LAYER_ACTIONS and action in LAYER_ACTIONS[layer]
