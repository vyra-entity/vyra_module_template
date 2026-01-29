"""
Status management package for v2_modulemanager.

Provides 3-layer state machine integration for module status management:
- Lifecycle Layer: Module existence and lifecycle events
- Operational Layer: Runtime activity states
- Health Layer: System health and diagnostics

Integrated as async task in core main.py with vyra_base patterns.
"""

from .status_manager import StatusManager, status_manager_runner
from .status_types import (
    ThreeLayerStatus,
    StatusRequest,
    StatusResponse,
)
from .service_client import (
    StatusServiceClient,
    StatusSubscriber
)

__all__ = [
    "ThreeLayerStatus",
    "StatusRequest",
    "StatusResponse",
    "StatusServiceClient",
    "StatusSubscriber",
    "StatusManager",
    "status_manager_runner",
]
