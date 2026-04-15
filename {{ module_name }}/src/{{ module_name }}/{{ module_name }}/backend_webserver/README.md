# backend_webserver

FastAPI/Uvicorn-based REST API and WebSocket server for the `{{ module_name }}` module.
Runs on HTTPS port `8443` inside the container. Exposed externally via Traefik and Nginx at
`/<module_name>/api/` and `/<module_name>/ws/`.

## Structure

```
backend_webserver/
├── asgi.py              ← ASGI application entry point (Uvicorn target)
├── main_rest.py         ← FastAPI app creation, router registration, middleware setup
├── core/
│   ├── config.py        ← Settings: paths, network, SSL, debug flags
│   └── dependencies.py  ← FastAPI dependency injection helpers
├── auth/
│   ├── router.py        ← Login, logout, token refresh endpoints
│   └── auth_service.py  ← JWT issuance and verification logic
├── websocket/
│   ├── router.py        ← WebSocket endpoint registration
│   └── service.py       ← Connection manager, message dispatch
├── services/
│   ├── operation_tracker.py  ← Tracks async operation state (pending / running / done)
│   ├── redis_service.py      ← Redis pub/sub listener and event forwarding
│   ├── feed_streamer.py      ← SSE / streamed feeds from state, news and error feeders
│   ├── plugin_bridge.py      ← Bridges WASM plugin events into REST and WebSocket
│   └── base_event_bridge.py  ← Base class for event bridging services
├── clients/
│   ├── grpc/            ← gRPC clients for inter-module communication
│   └── http/            ← HTTP clients (e.g. for Module Manager API)
└── plugin/
    ├── router.py        ← REST endpoints for plugin management
    └── models.py        ← Pydantic models for plugin API
```

## Auth (`auth/`)

Redis-session-based authentication using `vyra_base.auth.BaseAuthService`.

### Endpoints

| Endpoint | Method | Auth required | Description |
|---|---|---|---|
| `/api/auth/login` | POST | ✗ | Authenticate and receive a session token |
| `/api/auth/logout` | POST | ✗ | Revoke the current session token |
| `/api/auth/verify` | GET | ✓ | Verify the current token and return user info |
| `/api/auth/change-password` | POST | ✓ | Change the current user's password |
| `/api/auth/check-usermanager` | GET | ✗ | Probe whether the external UserManager is reachable |
| `/api/auth/users` | GET | ✓ admin | List all local users |
| `/api/auth/users` | POST | ✓ admin | Create a new local user |

Tokens are delivered as:
- **Cookie** (`auth_token`) — set automatically on login, `HttpOnly`, 8 h TTL.
- **Header** (`Authorization: Bearer <token>`) — accepted on all protected routes.

### Architecture

```
auth/
├── auth_service.py   ← Module-specific subclass of BaseAuthService
└── router.py         ← FastAPI router; uses make_auth_service_di() for DI setup
```

All shared logic lives in **`vyra_base.auth`** (shared across all modules):

| Component | Location | Description |
|---|---|---|
| `BaseAuthService` | `vyra_base.auth.base_auth_service` | ABC — session creation, token validation/revocation, local-user management |
| `UsermanagerUnavailableError` | `vyra_base.auth.exceptions` | Raised when the UM REST API / registry is unreachable |
| `AuthToken`, `LoginRequest`, `LoginResponse`, … | `vyra_base.auth.models` | Shared Pydantic models |
| `make_auth_service_di()` | `vyra_base.auth.router_utils` | Factory for `(set_auth_service, get_auth_service)` DI closures |
| `_extract_token()`, `security`, `TOKEN_COOKIE_MAX_AGE` | `vyra_base.auth.router_utils` | Shared router utilities |

### Module-specific overrides

Each module's `auth_service.py` extends `BaseAuthService` and implements:

```python
class AuthenticationService(BaseAuthService):

    def _get_user_manager(self) -> Any:
        """Return the UserManager DI instance (from container_injection)."""

    async def _validate_usermanager_credentials(
        self, username: str, password: str
    ) -> Optional[Dict[str, Any]]:
        """
        Module-specific UM validation:
        - v2_modulemanager  → cert-based JWT verification
        - v2_dashboard / {{ module_name }} → HTTP delegation to v2_usermanager REST
        """

    async def check_usermanager_available(self) -> Dict[str, Any]:
        """
        Probe whether the external UM is reachable:
        - v2_modulemanager  → queries internal module registry directly
        - v2_dashboard / {{ module_name }} → HTTP GET to v2_modulemanager endpoint
        """
```

### DI wiring (router.py)

```python
from vyra_base.auth import make_auth_service_di, _extract_token, security, TOKEN_COOKIE_MAX_AGE
from vyra_base.auth import LoginRequest, LoginResponse, ChangePasswordRequest, CreateUserRequest

set_auth_service, get_auth_service = make_auth_service_di()
```

`set_auth_service` is called once in `main_rest.py` at application startup.
`get_auth_service` is used as a `Depends()` target in every route handler.

## WebSocket (`websocket/`)

Real-time bidirectional channel between frontend and backend.

- **`router.py`** — registers the WebSocket endpoint at `/ws`
- **`service.py`** — `ConnectionManager`: accepts connections, broadcasts messages to all
  connected clients, and handles disconnection cleanup

Events are pushed by the backend (state changes, news, errors, plugin events) and consumed
by the Vue frontend's `store/moduleFeed.ts`.

## Plugin Bridge (`services/plugin_bridge.py`)

Forwards events emitted by WASM plugins (via `PluginGateway`) into the WebSocket channel,
making plugin-generated events visible in the frontend without polling.
Also handles frontend-initiated plugin slot registrations for UI component injection.

## Services (`services/`)

| Service | Description |
|---|---|
| `operation_tracker.py` | Tracks long-running operations (start, progress, completion). Frontend polls via REST or receives updates via WebSocket. |
| `redis_service.py` | Subscribes to Redis pub/sub channels and forwards relevant events to connected WebSocket clients and internal handlers. |
| `feed_streamer.py` | Streams state, news, and error feed entries to the frontend. Can be consumed via Server-Sent Events (SSE) or WebSocket. |

## Recommended Structure for New Endpoints

For each new functional area (e.g. device control, data export), the recommended layout is:

```
backend_webserver/
└── <area>/
    ├── router.py    ← FastAPI APIRouter with all route handlers
    ├── service.py   ← Business logic, separates route handlers from implementation
    └── models.py    ← Pydantic request/response models for this area
```

Register the new router in `main_rest.py`:

```python
from .my_area.router import router as my_area_router
app.include_router(my_area_router, prefix="/api/my-area", tags=["My Area"])
```

## Core Configuration (`core/`)

### `config.py` — `Settings`

Central settings class (Pydantic `BaseSettings`, loaded from environment variables and defaults):

| Setting | Description |
|---|---|
| `WORKSPACE_ROOT` | Root path of the VYRA workspace inside the container |
| `MODULES_PATH` | Path where module packages are mounted |
| `STORAGE_PATH` | Persistent storage directory (SQLite, uploaded files, etc.) |
| `LOG_PATH` | Log file directory (`core_stdout.log`, etc.) |
| `REDIS_HOST` / `REDIS_PORT` | Redis connection parameters |
| `CONTAINER_MANAGER_URL` | URL of the Docker container management API |
| `SSL_CERTFILE` / `SSL_KEYFILE` | TLS certificate paths for Uvicorn |
| `DEBUG` / `LOG_LEVEL` | Development flags |

Import anywhere with:

```python
from {{ module_name }}.backend_webserver.core.config import settings
```

### `dependencies.py` — FastAPI Dependencies

Provides reusable FastAPI `Depends()` helpers:

- `get_current_user` — validates the JWT and returns the authenticated user
- `require_admin` — raises 403 if the user does not have admin access
- `get_component` — returns the `Component` instance from `ApplicationContainer`
- `get_state_manager` — returns the `StateManager` instance

Example:

```python
from {{ module_name }}.backend_webserver.core.dependencies import get_current_user, get_component

@router.get("/status")
async def get_status(
    user=Depends(get_current_user),
    component=Depends(get_component),
):
    return {"state": component.get_state()}
```
