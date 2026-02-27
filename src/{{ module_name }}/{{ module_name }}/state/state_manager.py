"""
State Manager for {{ module_name }}.

Manages the 3-layer state machine (Lifecycle, Operational, Health) and
exposes **read-only** Zenoh interfaces so that other modules can query the
current state without being able to mutate it.

Architecture
------------
* Runs as an async task embedded in core main.py.
* Uses the VyraEntity instance provided by the application for StateFeeder
  broadcasting and @remote_service interface registration.
* Internal state mutations are triggered only by the application itself
  (container_injection, taskmanager, etc.); they are **never** exposed
  via network interfaces.

Zenoh read interfaces (registered via @remote_service):
    get_state()              — Full 3-layer state snapshot (JSON).
    get_lifecycle_state()    — Current lifecycle state string.
    get_operational_state()  — Current operational state string.
    get_health_state()       — Current health state string.
    get_last_error_state()   — Last stored error context (JSON).
    get_state_summary()      — Human-readable status summary (JSON).
    get_state_history()      — Recent state-change history (JSON list).
"""

from __future__ import annotations

import asyncio
import logging
import yaml
from collections import deque
from datetime import datetime
from pathlib import Path
from typing import Any, Deque, Dict, List, Optional

# NOTE: auto_register_interfaces is imported lazily inside setup_interfaces()
# to avoid pulling in ament_index_python / rclpy at module load time.
# This keeps state_manager testable without a full ROS2 environment.

from ..logging_config import get_logger, log_exception

from vyra_base.com import remote_service
from vyra_base.core.entity import VyraEntity
from vyra_base.helper.error_handler import ErrorTraceback
from vyra_base.state.state_types import (
    HealthState,
    LifecycleState,
    OperationalState,
)
from vyra_base.state.unified import UnifiedStateMachine

from .state_types import (
    LAYER_ACTIONS,
    StateHistoryEntry,
    StateRequest,
    StateResponse,
    ThreeLayerState,
    is_valid_action,
)

logger = get_logger(__name__)

# ─────────────────────────────────────────────────────────────────────────────
# Default configuration (overridden by module_state_meta.json when present)
# ─────────────────────────────────────────────────────────────────────────────
_DEFAULT_CONFIG: Dict[str, Any] = {
    "broadcast_interval_hz": 1.0,
    "max_state_history_size": 50,
    "max_error_history_size": 10,
    "debug_transitions": False,
}


class StateManager:
    """
    State manager for the 3-layer state machine (Lifecycle / Operational / Health).

    Lifecycle (intended usage):
    1. Instantiate with the shared VyraEntity.
    2. Call ``await setup_interfaces()`` once the entity is ready.
    3. Schedule ``broadcast_state()`` at the configured interval.
    4. Delegate state mutations explicitly via ``execute_state_action()``.

    Other modules may query the current state via the registered Zenoh
    interfaces; they **cannot** change it through these interfaces.
    """

    def __init__(self, entity: VyraEntity) -> None:
        """
        Args:
            entity: The shared VyraEntity for this module.
        """
        self.entity = entity

        # ── Load StateManager configuration ──────────────────────────────────
        self._config: Dict[str, Any] = self._load_state_meta()
        _max_hist = int(self._config.get("max_state_history_size", 50))
        _max_err = int(self._config.get("max_error_history_size", 10))

        # ── Module identity ───────────────────────────────────────────────────
        module_data = self._load_module_data()
        self.module_name: str = module_data.get("name", "unknown_module")
        self.module_id: str = module_data.get("uuid", "")

        logger.info(f"📋 Module: {self.module_name}")
        logger.info(f"🆔 UUID:   {self.module_id}")

        # ── 3-layer state machine ────────────────────────────────────────────
        self._state_machine: UnifiedStateMachine = UnifiedStateMachine()

        # ── History / diagnostics ─────────────────────────────────────────────
        self._state_history: Deque[StateHistoryEntry] = deque(maxlen=_max_hist)
        self._error_history: Deque[Dict[str, Any]] = deque(maxlen=_max_err)
        self._last_error_state: Optional[Dict[str, Any]] = None
        self._last_state: Optional[ThreeLayerState] = None

        logger.info(f"StateManager initialised for module: {self.module_name}")

    # ─────────────────────────────────────────────────────────────────────────
    # Properties
    # ─────────────────────────────────────────────────────────────────────────

    @property
    def state_machine(self) -> UnifiedStateMachine:
        """Direct access to the underlying UnifiedStateMachine."""
        return self._state_machine

    @property
    def broadcast_interval(self) -> float:
        """Broadcast interval in seconds derived from configured Hz."""
        hz = float(self._config.get("broadcast_interval_hz", 1.0))
        return 1.0 / hz if hz > 0 else 1.0

    # ─────────────────────────────────────────────────────────────────────────
    # Setup
    # ─────────────────────────────────────────────────────────────────────────

    async def setup_interfaces(self) -> None:
        """Register all Zenoh @remote_service handlers with the VyraEntity."""
        from ..interface import auto_register_interfaces  # lazy – needs ROS2 env
        await auto_register_interfaces(self.entity, callback_parent=self)
        logger.info("✅ StateManager Zenoh interfaces registered")

    async def initialize(self) -> bool:
        """
        Run the startup lifecycle sequence.

        Called by ``application.py`` when ``behavior.auto_start: true`` is set
        in ``module_params.yaml``.  The sequence is:

          1. OFFLINE → INITIALIZING  (``start``)
          2. INITIALIZING → ACTIVE   (``complete_initialization``)
          3. IDLE → READY            (``set_ready``)

        Returns:
            ``True`` on success, ``False`` if any step failed.
        """
        try:
            logger.info("🚀 Initialising module lifecycle…")

            prev = self.get_current_state()

            self._state_machine.start(metadata={"source": "application"})
            logger.info("  ✓ Lifecycle: INITIALIZING")

            self._state_machine.complete_initialization(
                result={"container_ready": True}
            )
            logger.info("  ✓ Lifecycle: ACTIVE")

            self._state_machine.set_ready()
            logger.info("  ✓ Operational: READY")

            current = self.get_current_state()
            self._record_history_diff(prev, current)

            logger.info("✅ Module successfully activated!")
            return True

        except Exception as exc:
            logger.error(f"❌ Failed to initialise module: {exc}")
            error_details: Dict[str, Any] = {}
            ErrorTraceback.check_error_exist(error_details=error_details)
            self._record_error(str(exc), error_details)
            try:
                self._state_machine.report_fault(error=str(exc))
            except Exception:
                pass
            return False

    # ─────────────────────────────────────────────────────────────────────────
    # Config loading
    # ─────────────────────────────────────────────────────────────────────────

    def _load_state_meta(self) -> Dict[str, Any]:
        """
        Load StateManager configuration from ``module_params.yaml``.

        Reads the ``state_manager:`` section of
        ``/workspace/.module/module_params.yaml``.
        Falls back to :data:`_DEFAULT_CONFIG` if the file or section is absent.
        """
        params_path = Path("/workspace/.module/module_params.yaml")
        config: Dict[str, Any] = dict(_DEFAULT_CONFIG)

        try:
            if params_path.exists():
                with open(params_path, "r") as fh:
                    data = yaml.safe_load(fh) or {}
                sm_cfg = data.get("state_manager", {})
                if sm_cfg:
                    config.update(sm_cfg)
                    logger.debug(
                        f"Loaded StateManager config from {params_path}: {sm_cfg}"
                    )
                else:
                    logger.debug(
                        "No 'state_manager' section in module_params.yaml, "
                        "using defaults."
                    )
            else:
                logger.debug(
                    f"module_params.yaml not found at {params_path}, "
                    "using defaults."
                )
        except Exception as exc:
            logger.warning(f"⚠️ Could not load module_params.yaml: {exc}")

        return config

    def _load_module_data(self) -> Dict[str, Any]:
        """Load module identity from ``/workspace/.module/module_data.yaml``."""
        module_data_path = Path("/workspace/.module/module_data.yaml")
        try:
            if module_data_path.exists():
                with open(module_data_path, "r") as fh:
                    data = yaml.safe_load(fh)
                    return data or {}
        except Exception as exc:
            logger.error(f"❌ Failed to load module data: {exc}")
        return {}

    # ─────────────────────────────────────────────────────────────────────────
    # Core state accessors (internal)
    # ─────────────────────────────────────────────────────────────────────────

    def get_current_state(self) -> ThreeLayerState:
        """
        Build a :class:`ThreeLayerState` snapshot from the state machine.

        Returns:
            Current state with module metadata attached.
        """
        states = self._state_machine.get_all_states()
        return ThreeLayerState(
            lifecycle=states["lifecycle"],
            operational=states["operational"],
            health=states["health"],
            timestamp=datetime.now(),
            metadata={
                "module_name": self.module_name,
                "module_id": self.module_id,
                "is_operational": self._state_machine.is_operational(),
                "is_healthy": self._state_machine.is_healthy(),
            },
        )

    # Backward-compatibility alias
    def get_current_status(self) -> ThreeLayerState:
        """Alias for :meth:`get_current_state` (backward compatibility)."""
        return self.get_current_state()

    # ─────────────────────────────────────────────────────────────────────────
    # Read-only Zenoh interface methods (decorated with @remote_service)
    # Other modules can call these via Zenoh – they never mutate state.
    # ─────────────────────────────────────────────────────────────────────────

    @remote_service
    def get_state(self, request: Dict[str, Any], response: Dict[str, Any]) -> Dict[str, Any]:
        """
        Return the full 3-layer state snapshot.

        Response fields:
            lifecycle  (str)  – Current lifecycle state value.
            operational (str) – Current operational state value.
            health     (str)  – Current health state value.
            timestamp  (str)  – ISO 8601 timestamp of the snapshot.
            metadata   (dict) – Module name, UUID and derived flags.
            success    (bool) – Always True on successful call.
        """
        try:
            state = self.get_current_state()
            response.update(state.to_dict())
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_state failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_lifecycle_state(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return only the lifecycle layer state.

        Response fields:
            lifecycle (str)  – Current lifecycle state value.
            timestamp (str)  – ISO 8601 timestamp.
            success   (bool) – Always True on successful call.
        """
        try:
            states = self._state_machine.get_all_states()
            response["lifecycle"] = states["lifecycle"]
            response["timestamp"] = datetime.now().isoformat()
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_lifecycle_state failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_operational_state(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return only the operational layer state.

        Response fields:
            operational (str) – Current operational state value.
            timestamp   (str) – ISO 8601 timestamp.
            success     (bool) – Always True on successful call.
        """
        try:
            states = self._state_machine.get_all_states()
            response["operational"] = states["operational"]
            response["timestamp"] = datetime.now().isoformat()
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_operational_state failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_health_state(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return only the health layer state.

        Response fields:
            health    (str)  – Current health state value.
            timestamp (str)  – ISO 8601 timestamp.
            success   (bool) – Always True on successful call.
        """
        try:
            states = self._state_machine.get_all_states()
            response["health"] = states["health"]
            response["timestamp"] = datetime.now().isoformat()
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_health_state failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_last_error_state(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return the last recorded error context.

        Response fields:
            has_error      (bool)  – False when no error has occurred yet.
            error_message  (str)   – Error message (empty string if none).
            error_details  (dict)  – Traceback / additional info.
            timestamp      (str)   – ISO 8601 time of the error.
            error_history  (list)  – Up to N recent error entries.
            success        (bool)  – Always True on successful call.
        """
        try:
            if self._last_error_state is not None:
                response.update(self._last_error_state)
                response["has_error"] = True
                response["error_history"] = [
                    e for e in list(self._error_history)
                ]
            else:
                response["has_error"] = False
                response["error_message"] = ""
                response["error_details"] = {}
                response["timestamp"] = datetime.now().isoformat()
                response["error_history"] = []
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_last_error_state failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_state_summary(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return a human-readable state summary.

        Response fields:
            summary        (str)   – One-line status description.
            is_operational (bool)  – True when lifecycle=ACTIVE and op≠ERROR.
            is_healthy     (bool)  – True when health=HEALTHY.
            lifecycle      (str)   – Lifecycle state value.
            operational    (str)   – Operational state value.
            health         (str)   – Health state value.
            module_name    (str)   – Module identifier.
            timestamp      (str)   – ISO 8601 timestamp.
            success        (bool)  – Always True on successful call.
        """
        try:
            states = self._state_machine.get_all_states()
            is_op = self._state_machine.is_operational()
            is_healthy = self._state_machine.is_healthy()

            summary = (
                f"{self.module_name}: "
                f"lifecycle={states['lifecycle']} | "
                f"operational={states['operational']} | "
                f"health={states['health']}"
            )

            response.update(
                {
                    "summary": summary,
                    "is_operational": is_op,
                    "is_healthy": is_healthy,
                    "lifecycle": states["lifecycle"],
                    "operational": states["operational"],
                    "health": states["health"],
                    "module_name": self.module_name,
                    "timestamp": datetime.now().isoformat(),
                    "success": True,
                }
            )
        except Exception as exc:
            logger.error(f"get_state_summary failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    @remote_service
    def get_state_history(
        self, request: Dict[str, Any], response: Dict[str, Any]
    ) -> Dict[str, Any]:
        """
        Return the recent state-change history.

        Request fields (all optional):
            limit (int) – Maximum number of entries to return (default: all).
            layer (str) – Filter by layer name (lifecycle / operational / health).

        Response fields:
            history   (list) – List of state-change dicts (newest last).
            count     (int)  – Number of entries returned.
            total     (int)  – Total entries in history buffer.
            success   (bool) – Always True on successful call.
        """
        try:
            history = list(self._state_history)

            # Optional filters
            layer_filter: Optional[str] = request.get("layer") if request else None
            if layer_filter:
                history = [e for e in history if e.layer == layer_filter]

            limit: Optional[int] = request.get("limit") if request else None
            if limit and limit > 0:
                history = history[-limit:]

            response["history"] = [e.to_dict() for e in history]
            response["count"] = len(history)
            response["total"] = len(self._state_history)
            response["success"] = True
        except Exception as exc:
            logger.error(f"get_state_history failed: {exc}")
            response["success"] = False
            response["error"] = str(exc)
        return response

    # ─────────────────────────────────────────────────────────────────────────
    # State broadcasting (called by async task runner)
    # ─────────────────────────────────────────────────────────────────────────

    async def broadcast_state(self) -> None:
        """
        Broadcast the current state via the VyraEntity StateFeeder (1 Hz).

        Detects changes since the last broadcast and records them in the
        history buffer.
        """
        try:
            current = self.get_current_state()
            states = self._state_machine.get_all_states()

            self.entity.state_feeder.feed_state(
                lifecycle_state=states["lifecycle"],
                operational_state=states["operational"],
                health_state=states["health"],
                metadata={
                    "module_name": self.module_name,
                    "module_id": self.module_id,
                    "is_operational": self._state_machine.is_operational(),
                    "is_healthy": self._state_machine.is_healthy(),
                    "timestamp": current.timestamp.isoformat(),
                },
            )

            if self._last_state is not None:
                self._record_history_diff(self._last_state, current)

            self._last_state = current

        except Exception as exc:
            logger.error(f"Failed to broadcast state: {exc}")

    # Backward-compatibility alias
    async def broadcast_status(self) -> None:
        """Alias for :meth:`broadcast_state` (backward compatibility)."""
        await self.broadcast_state()

    # ─────────────────────────────────────────────────────────────────────────
    # Internal state-mutation helpers (called only by application code)
    # ─────────────────────────────────────────────────────────────────────────

    def execute_state_action(self, request: StateRequest) -> StateResponse:
        """
        Execute a state-machine action.

        This method is intentionally **not** decorated with @remote_service.
        State mutations are triggered only by application-internal code.

        Args:
            request: Describes the layer, action and optional metadata.

        Returns:
            :class:`StateResponse` with success flag and updated state.

        Raises:
            ValueError: If the layer or action is unknown.
        """
        layer = request.layer
        action = request.action
        metadata = request.metadata or {}

        prev_state = self.get_current_state()

        try:
            self._dispatch_action(layer, action, metadata)

            current = self.get_current_state()
            self._record_history_diff(prev_state, current)

            return StateResponse(
                success=True,
                current_state=current,
                message=f"Successfully executed {layer}.{action}",
            )

        except Exception as exc:
            logger.error(f"Failed to execute action {layer}.{action}: {exc}")
            self._record_error(str(exc), {"layer": layer, "action": action})
            raise

    # Backward-compatibility alias
    def execute_status_action(self, request: "StateRequest") -> "StateResponse":
        """Alias for :meth:`execute_state_action` (backward compatibility)."""
        return self.execute_state_action(request)

    def _dispatch_action(
        self, layer: str, action: str, metadata: Dict[str, Any]
    ) -> None:
        """Translate layer/action pairs to UnifiedStateMachine calls."""
        if layer == "lifecycle":
            if action == "start":
                self._state_machine.start(metadata)
            elif action == "complete_init":
                self._state_machine.complete_initialization(metadata)
            elif action == "fail_init":
                self._state_machine.fail_initialization(metadata.get("error"))
            elif action == "shutdown":
                self._state_machine.shutdown(metadata.get("reason"))
            elif action == "suspend":
                self._state_machine.suspend(metadata.get("reason"))
            elif action == "resume_from_suspend":
                self._state_machine.resume_from_suspend()
            elif action == "recover":
                self._state_machine.start_recovery(metadata.get("error"))
            elif action == "complete_recovery":
                self._state_machine.complete_recovery()
            elif action == "fail_recovery":
                self._state_machine.fail_recovery()
            else:
                raise ValueError(f"Unknown lifecycle action: {action}")

        elif layer == "operational":
            if action == "ready":
                self._state_machine.set_ready()
            elif action == "start_task":
                self._state_machine.start_task(metadata)
            elif action == "pause":
                self._state_machine.pause_task(metadata.get("reason"))
            elif action == "resume":
                self._state_machine.resume_task()
            elif action == "block":
                self._state_machine.block(metadata.get("reason"))
            elif action == "unblock":
                self._state_machine.unblock()
            elif action == "delegate":
                self._state_machine.delegate(metadata)
            elif action == "complete":
                self._state_machine.complete_task(metadata)
            elif action == "reset":
                self._state_machine.reset_to_ready()
            else:
                raise ValueError(f"Unknown operational action: {action}")

        elif layer == "health":
            if action == "report_warning":
                self._state_machine.report_warning(metadata)
            elif action == "report_overload":
                self._state_machine.report_overload(metadata)
            elif action == "report_fault":
                self._state_machine.report_fault(metadata.get("error"))
            elif action == "clear_warning":
                self._state_machine.clear_health()
            elif action == "reduce_load":
                self._state_machine.reduce_load()
            elif action == "recover":
                self._state_machine.recover_from_fault()
            elif action == "escalate_critical":
                self._state_machine.escalate_to_critical(metadata)
            else:
                raise ValueError(f"Unknown health action: {action}")

        else:
            raise ValueError(f"Unknown layer: {layer}")

    # ─────────────────────────────────────────────────────────────────────────
    # History & diagnostics helpers
    # ─────────────────────────────────────────────────────────────────────────

    def _record_history_diff(
        self, before: ThreeLayerState, after: ThreeLayerState
    ) -> None:
        """Record any state changes between two snapshots."""
        now = datetime.now()

        if before.lifecycle != after.lifecycle:
            self._state_history.append(
                StateHistoryEntry(
                    layer="lifecycle",
                    from_state=before.lifecycle,
                    to_state=after.lifecycle,
                    timestamp=now,
                )
            )

        if before.operational != after.operational:
            self._state_history.append(
                StateHistoryEntry(
                    layer="operational",
                    from_state=before.operational,
                    to_state=after.operational,
                    timestamp=now,
                )
            )

        if before.health != after.health:
            self._state_history.append(
                StateHistoryEntry(
                    layer="health",
                    from_state=before.health,
                    to_state=after.health,
                    timestamp=now,
                )
            )

    def _record_error(
        self, message: str, details: Optional[Dict[str, Any]] = None
    ) -> None:
        """Store an error entry in the error history buffer."""
        entry: Dict[str, Any] = {
            "error_message": message,
            "error_details": details or {},
            "timestamp": datetime.now().isoformat(),
            "state_at_error": (
                self.get_current_state().to_dict()
                if self._state_machine is not None
                else None
            ),
        }
        self._last_error_state = entry
        self._error_history.append(entry)


# ─────────────────────────────────────────────────────────────────────────────
# Async runner (used by main.py / taskmanager)
# ─────────────────────────────────────────────────────────────────────────────


async def state_manager_runner(state_manager: StateManager) -> None:
    """
    Async broadcast loop for the StateManager.

    Runs at the interval configured in ``module_state_meta.json``
    (default 1 Hz).  Should be scheduled as an asyncio Task.

    Args:
        state_manager: The :class:`StateManager` instance to run.
    """
    interval = state_manager.broadcast_interval
    logger.info(
        f"▶️  StateManager broadcast loop started "
        f"(interval={interval:.2f}s / "
        f"{state_manager._config.get('broadcast_interval_hz', 1.0):.1f} Hz)"
    )
    while True:
        try:
            await state_manager.broadcast_state()
        except asyncio.CancelledError:
            logger.info("StateManager broadcast loop cancelled")
            break
        except Exception as exc:
            logger.error(f"StateManager loop error: {exc}")
        await asyncio.sleep(interval)
