"""
State type definitions for {{ module_name }} state management.

Re-exports all state types from vyra_base.state.state_types and adds
module-specific data structures for the 3-layer state machine.

All enums, transition tables and validators are sourced from vyra_base
to keep a single source of truth.

LAYER_ACTIONS is derived dynamically from the vyra_base layer classes
so that it automatically stays in sync when vyra_base is updated.
"""

import inspect
from dataclasses import dataclass, asdict
from typing import Dict, Any, Optional, List
from datetime import datetime

# ──────────────────────────────────────────────────────────────────────────────
# Re-export everything from vyra_base – single source of truth
# ──────────────────────────────────────────────────────────────────────────────
from vyra_base.state.state_types import (
    LifecycleState,
    OperationalState,
    HealthState,
    LIFECYCLE_TRANSITIONS,
    OPERATIONAL_TRANSITIONS,
    HEALTH_TRANSITIONS,
    LIFECYCLE_OPERATIONAL_RULES,
    is_valid_lifecycle_transition,
    is_valid_operational_transition,
    is_valid_health_transition,
    is_operational_allowed_in_lifecycle,
)
from vyra_base.state.lifecycle_layer import LifecycleLayer
from vyra_base.state.operational_layer import OperationalLayer
from vyra_base.state.health_layer import HealthLayer

__all__ = [
    # Enums (from vyra_base)
    "LifecycleState",
    "OperationalState",
    "HealthState",
    # Transition tables (from vyra_base)
    "LIFECYCLE_TRANSITIONS",
    "OPERATIONAL_TRANSITIONS",
    "HEALTH_TRANSITIONS",
    "LIFECYCLE_OPERATIONAL_RULES",
    # Validators (from vyra_base)
    "is_valid_lifecycle_transition",
    "is_valid_operational_transition",
    "is_valid_health_transition",
    "is_operational_allowed_in_lifecycle",
    # Module-specific types
    "ThreeLayerState",
    "StateRequest",
    "StateResponse",
    "StateHistoryEntry",
    # Dynamic action helpers
    "get_layer_actions",
    "LAYER_ACTIONS",
    "is_valid_action",
    # Backward-compatibility aliases
    "ThreeLayerStatus",
    "StatusRequest",
    "StatusResponse",
]


# ──────────────────────────────────────────────────────────────────────────────
# Module-specific data structures
# ──────────────────────────────────────────────────────────────────────────────


@dataclass
class ThreeLayerState:
    """
    Complete 3-layer state snapshot.

    Attributes:
        lifecycle:  Current lifecycle state (existence/activation).
        operational: Current operational state (activity).
        health:     Current health state (diagnostics).
        timestamp:  When the state was sampled.
        metadata:   Optional additional context.
    """

    lifecycle: str
    operational: str
    health: str
    timestamp: datetime
    metadata: Optional[Dict[str, Any]] = None

    def to_dict(self) -> Dict[str, Any]:
        """Serialise to a JSON-compatible dictionary."""
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
    ) -> "ThreeLayerState":
        """
        Create from vyra_base state enums.

        Args:
            lifecycle:  Lifecycle state enum value.
            operational: Operational state enum value.
            health:     Health state enum value.
            metadata:   Optional context information.

        Returns:
            ThreeLayerState populated from enum values.
        """
        return cls(
            lifecycle=lifecycle.value,
            operational=operational.value,
            health=health.value,
            timestamp=datetime.now(),
            metadata=metadata,
        )


@dataclass
class StateHistoryEntry:
    """
    A single recorded state transition.

    Attributes:
        layer:       Which layer changed (lifecycle / operational / health).
        from_state:  State value before the transition.
        to_state:    State value after the transition.
        timestamp:   When the transition occurred.
        metadata:    Optional context (reason, error text, …).
    """

    layer: str
    from_state: str
    to_state: str
    timestamp: datetime
    metadata: Optional[Dict[str, Any]] = None

    def to_dict(self) -> Dict[str, Any]:
        """Serialise to dictionary."""
        return {
            "layer": self.layer,
            "from_state": self.from_state,
            "to_state": self.to_state,
            "timestamp": self.timestamp.isoformat(),
            "metadata": self.metadata or {},
        }


@dataclass
class StateRequest:
    """
    Request to trigger a state-machine action.

    Attributes:
        layer:    Which layer to act on (lifecycle / operational / health).
        action:   The action to perform (e.g. start, shutdown, ready, …).
        metadata: Additional parameters for the action.
    """

    layer: str
    action: str
    metadata: Optional[Dict[str, Any]] = None

    def to_dict(self) -> Dict[str, Any]:
        """Serialise to dictionary."""
        return asdict(self)

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "StateRequest":
        """Deserialise from dictionary."""
        return cls(
            layer=data.get("layer", data.get("layer_name", "")),
            action=data["action"],
            metadata=data.get("metadata", {}),
        )


@dataclass
class StateResponse:
    """
    Response from a state-machine action.

    Attributes:
        success:       Whether the action was executed successfully.
        current_state: State snapshot after the action (or unchanged if failed).
        message:       Human-readable result.
        error:         Error details, present only when success is False.
    """

    success: bool
    current_state: ThreeLayerState
    message: str
    error: Optional[str] = None

    def to_dict(self) -> Dict[str, Any]:
        """Serialise to dictionary."""
        return {
            "success": self.success,
            "current_state": self.current_state.to_dict(),
            "message": self.message,
            "error": self.error,
        }


# ──────────────────────────────────────────────────────────────────────────────
# Backward-compatibility aliases (deprecated – will be removed in a future release)
# ──────────────────────────────────────────────────────────────────────────────

# ThreeLayerStatus → ThreeLayerState
ThreeLayerStatus = ThreeLayerState
# StatusRequest → StateRequest
StatusRequest = StateRequest
# StatusResponse → StateResponse
StatusResponse = StateResponse


# ──────────────────────────────────────────────────────────────────────────────
# LAYER_ACTIONS — dynamically derived from vyra_base layer classes
# This ensures the available actions stay in sync with vyra_base updates.
# ──────────────────────────────────────────────────────────────────────────────

# Prefixes that identify query / registration helpers, not state-change actions
_ACTION_EXCLUDE_PREFIXES: tuple = ("get_", "is_", "can_", "on_", "check_")


def get_layer_actions() -> Dict[str, List[str]]:
    """
    Derive available state-machine actions for each layer from vyra_base.

    Introspects the public methods of :class:`~vyra_base.state.LifecycleLayer`,
    :class:`~vyra_base.state.OperationalLayer`, and
    :class:`~vyra_base.state.HealthLayer` to build the action map.

    The result is cached on first call so subsequent calls are free.

    Returns:
        Dictionary mapping layer name → sorted list of action method names.
    """
    if get_layer_actions._cache is not None:  # type: ignore[attr-defined]
        return get_layer_actions._cache  # type: ignore[attr-defined]

    def _public_actions(cls: type) -> List[str]:
        return sorted(
            name
            for name, member in inspect.getmembers(cls, predicate=inspect.isfunction)
            if not name.startswith("_")
            and not any(name.startswith(p) for p in _ACTION_EXCLUDE_PREFIXES)
        )

    result: Dict[str, List[str]] = {
        "lifecycle": _public_actions(LifecycleLayer),
        "operational": _public_actions(OperationalLayer),
        "health": _public_actions(HealthLayer),
    }

    get_layer_actions._cache = result  # type: ignore[attr-defined]
    return result


get_layer_actions._cache = None  # type: ignore[attr-defined]

# Module-level constant for convenience: populated once at import time.
LAYER_ACTIONS: Dict[str, List[str]] = get_layer_actions()


def is_valid_action(layer: str, action: str) -> bool:
    """
    Return True if *action* is a valid trigger for *layer*.

    Derived dynamically from vyra_base layer classes so it always
    reflects the current library version.

    Args:
        layer:  Layer name (lifecycle / operational / health).
        action: Action identifier (method name on the layer class).

    Returns:
        True when the combination is known and valid.
    """
    actions = get_layer_actions()
    return layer in actions and action in actions[layer]
