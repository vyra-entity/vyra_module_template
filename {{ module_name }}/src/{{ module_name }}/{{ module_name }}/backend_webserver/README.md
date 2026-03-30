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

JWT-based authentication backed by `UserManager`.

| Endpoint | Method | Description |
|---|---|---|
| `/api/auth/login` | POST | Authenticate and receive access + refresh tokens |
| `/api/auth/logout` | POST | Invalidate the current session |
| `/api/auth/verify` | GET | Verify the current token is still valid |
| `/api/auth/password` | PUT | Change user password |

Tokens are passed as `Authorization: Bearer <token>` headers on all protected routes.
Route protection is applied via FastAPI dependencies defined in `core/dependencies.py`.

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
