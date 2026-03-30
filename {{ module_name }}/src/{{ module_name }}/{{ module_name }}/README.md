# {{ module_name }} — Main Python Package

This is the main Python package of the module. It contains every backend subsystem, from the
entry point and state machine to the REST API, plugin runtime, and user management.

## Entry Points

### `main.py`

The module entry point. Instantiates all core objects, starts the `TaskManager`, and handles
graceful shutdown on `SIGTERM` / `SIGINT` (transitions to `ShuttingDown` → `Offline`).

Two entry points are registered in `setup.cfg`:
- `{{ module_name }}` — Full Mode (ROS2 + Zenoh)
- `{{ module_name }}-slim` — SLIM Mode (Zenoh-only, `VYRA_SLIM=true`)

### `_base_.py`

Provides helper functions for loading resource files from the module's package share directory.
Supports `.ini`, `.json`, and `.yaml` formats. Abstracts the difference between Full Mode
(uses `ament_index_python` to locate the ROS2 package share directory) and SLIM Mode (searches
the Python source tree directly).

### `logging_config.py`

Provides `get_logger(__name__)` which returns a `VyraLogger` instance — a structured logger
compatible with Python `logging` and `structlog`-style APIs. Always use this instead of
instantiating a logger directly.

```python
from .logging_config import get_logger
logger = get_logger(__name__)

logger.info("Component started")
logger.error("Something went wrong", error=str(e))
```

---

## `container_injection.py` — Dependency Injection

Provides `ApplicationContainer`, a fixed-set container holding the core singleton objects of
the module:

| Object | Type | Description |
|---|---|---|
| `entity` | `VyraEntity` | The module's network identity and CAL interface |
| `component` | `Component` | The application business logic class |
| `task_manager` | `TaskManager` | AsyncIO task lifecycle manager |
| `state_manager` | `StateManager` | 3-layer state machine access |
| `user_manager` | `UserManager` | User authentication orchestrator |
| `plugin_gateway` | `PluginGateway` | WASM plugin runtime |

Also provides `ServiceRegistry` for registering and resolving dynamic runtime services
(e.g. a plugin manager registered at startup).

**Accessing core objects from `backend_webserver`:**

```python
from {{ module_name }}.container_injection import ApplicationContainer

container = ApplicationContainer()
component = container.component()
state_manager = container.state_manager()
```

This is the recommended pattern for wiring backend API routes to the module's core logic.

---

## `taskmanager.py` — Task Manager

Manages all long-running `asyncio` tasks for the module. Tasks are started, monitored,
and gracefully cancelled through this manager.

Tasks running inside the module:

| Task | Description |
|---|---|
| `application_runner` | Drives the `Component` lifecycle (initialize → ready → running) |
| `plugin_gateway_runner` | WASM plugin runtime event loop |
| `state_broadcast` | Periodically broadcasts current state over Zenoh/ROS2 channels |
| `websocket_event_loop` | WebSocket connection manager for the frontend |
| `redis_service` | Redis pub/sub listener and state synchronisation |

Key methods:

```python
task_manager.add_task("my_task", my_coroutine())
task_manager.restart_task("my_task")
await task_manager.cancel_all()
```

---

## `interface.py` — Interface Registration

Loads interface definitions from `{{ module_name }}_interfaces/config/*.meta.json` and merges
them with the Python callbacks defined in `Component`.

The core function is:

```python
await auto_register_interfaces(
    entity=entity,
    callback_parent=component,   # or callback_list=[component.my_func, ...]
)
```

The method scans `component` for methods decorated with `@remote_service`, matches each by
`functionname` against the config JSON, constructs a `FunctionConfigEntry` for each match,
and finally calls `entity.set_interfaces(interface_functions)` to activate the interfaces
on the CAL.

Any function not found in the config produces a warning in `logs/core_stdout.log` and is skipped.

---

## `application/` — Application and Business Logic

### `application.py` — `Component` class

`Component` is the central class for the module's business logic. It extends
`OperationalStateMachine` from `vyra_base`, which automatically manages the operational
state transitions.

**Lifecycle methods** (called automatically by the state machine):

| Method | Trigger |
|---|---|
| `initialize()` | Module moves to Initializing — set up resources here |
| `on_ready()` | Module enters Ready state — one-time post-init logic |
| `pause()` | Module receives a pause request |
| `resume()` | Module resumes from paused |
| `stop()` | Module is stopping |
| `reset()` | Module resets to initial state |

Additional classes and helper functions can freely be added inside `application/`. The framework
imposes no restrictions beyond the lifecycle interface.

**Remote functions and `@state.operation`:**

Functions callable from outside (via the CAL interfaces registered in `interface.py`) that
modify internal state should be decorated with `@state.operation`:

```python
from vyra_base import state

class Component(state.OperationalStateMachine):

    @state.operation
    async def process_data(self, request, response=None):
        # State transitions automatically:
        # Before: READY → RUNNING (reference counter incremented)
        # After:  RUNNING → READY (reference counter decremented, if last caller)
        result = await self._do_processing(request)
        return result
```

- If the module is in `READY` state when the function is called, it transitions to `RUNNING`.
- When the function returns, the state transitions back to `READY` (if no other `@state.operation`
  calls are in flight — reference counted).
- If an unhandled exception occurs, the module moves to `OperationalError`.

The CAL callback itself (declared in the interface config and registered by `interface.py`)
is marked with `@remote_service()` from `vyra_base`. The `@state.operation` decorator is
applied in addition to handle state management around the execution.

---

## `plugin/` — WASM Plugin System

See [plugin/README.md](plugin/README.md) for the full plugin documentation.

`PluginGateway` loads and runs WASM plugins at runtime. Host functions exposed to plugins
are defined in `.module/plugin_interfaces.yaml` and must be implemented as gate methods
in `PluginGateway`.

---

## `state/` — State Management

`StateManager` provides the module's view into the `vyra_base` 3-layer state machine:

| Layer | States |
|---|---|
| **Lifecycle** | `OFFLINE` → `INITIALIZING` → `READY` → `RECOVERING` → `SHUTTINGDOWN` → `OFFLINE` |
| **Operational** | `IDLE` → `READY` → `RUNNING` → `PAUSED` → `STOPPED` → `ERROR` |
| **Health** | `HEALTHY` → `DEGRADED` → `CRITICAL` → `FAILED` |

`StateManager` exposes Zenoh read-only interfaces for each layer (`get_state`, `get_lifecycle_state`,
`get_operational_state`, `get_health_state`, `get_state_history`) and broadcasts state changes
periodically.

Lifecycle callbacks (e.g. on module suspend or resume) are also wired through `StateManager`.

---

## `user/` — User Management

`UserManager` is the orchestrator for authentication and user-related operations.

If a dedicated external `usermanager` module is available in the VYRA deployment, `UserManager`
delegates to it automatically (detected by `usermanager_detector.py`). The external module
provides a centralized identity store shared across all modules.

If **no external usermanager module is running** — for example during development or in a
minimal deployment — `InternalUserManager` is used instead. It provides a local SQLite-backed
user store with:

- Username/password authentication
- Admin user bootstrap from environment variables (`INITIAL_ADMIN_USER`, `INITIAL_ADMIN_PASSWORD`)
- JWT token issuance for the web interface
- Role and access-level enforcement

This means the web UI and REST API are secured out-of-the-box without requiring any additional
setup.

---

## `backend_webserver/` — REST API and WebSocket Server

See [backend_webserver/README.md](backend_webserver/README.md) for full details.

FastAPI/Uvicorn server running on HTTPS port `8443` inside the container. Provides:
- JWT authentication
- WebSocket channels
- Plugin bridge
- Operational services (operation tracker, Redis service, feed streamer)
