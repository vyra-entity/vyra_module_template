# {{ module_name }}

This is a **VYRA module** — a self-contained service built on the [VYRA Framework](https://github.com/Variobotic-GmbH/vyra_framework).
It was generated from the [vyra_module_template](https://github.com/vyra-entity/vyra_module_template).
For template and Copier usage instructions see the [template README](https://github.com/vyra-entity/vyra_module_template#readme).

## Overview

VYRA modules **cannot run standalone**. They require a running VYRA Framework deployment that provides:

- **Docker Swarm** orchestration
- **Traefik** reverse proxy / routing
- **Redis** shared state storage
- **ROS2 / Zenoh** communication bus
- **Module Manager** (`v2_modulemanager`) — installation, lifecycle, plugin management

The Module Manager is the only correct way to install, start, stop, or update a module. Do not start the module container directly.

## Foundation: vyra_base_python

Every VYRA module is built on [`vyra_base_python`](https://github.com/vyra-entity/vyra_base_python), which provides:

- **`VyraEntity`** — the module's network identity and main interface point
- **3-layer state machine** — Lifecycle / Operational / Health states with automatic transitions
- **CAL (Communication Abstraction Layer)** — unified interface over all supported protocols
- **Feeders** — structured publishing of state changes, news, and error events
- **Security** — SROS2 policies and access-level enforcement

Do not re-implement any of these concerns from scratch.

## Communication Protocols (CAL)

All inter-module communication goes through the CAL. The four core protocols are:

| Protocol | Use Case |
|---|---|
| **ROS2** | Robot Operating System 2 — industrial-standard DDS-based messaging (services, actions, topics). Full Mode only. |
| **Zenoh** | Lightweight, high-performance pub/sub and query layer. Works in both Full and SLIM Mode. Recommended for new service interfaces. |
| **Redis** | Key-value store pub/sub and shared state. Fast event distribution and cross-cluster state sharing. |
| **UDS** | Unix Domain Sockets — low-latency local IPC within the same container or host. |

The protocol(s) a function is exposed on are declared per interface in the interface config files (see below).

## Interfaces

Module interfaces — the remote-callable functions and published events — live in:

```
src/{{ module_name }}_interfaces/
```

They are **automatically generated** from JSON config files during `colcon build`. Config files are placed in:

```
src/{{ module_name }}_interfaces/config/
```

Preferred naming convention for config files:

```
<module_name>_<area>.meta.json
```

For example: `{{ module_name }}_sensors.meta.json`, `{{ module_name }}_control.meta.json`. The name can be freely chosen as long as it is unique within the `config/` directory.

See [src/{{ module_name }}_interfaces/README.md](src/{{ module_name }}_interfaces/README.md) for the full config format and generation details.

## Deployment Modes

| Mode | Protocols | Notes |
|---|---|---|
| **Full Mode** (default) | ROS2 + Zenoh + Redis + UDS | Full framework feature set, production-ready |
| **SLIM Mode** | Zenoh + Redis + UDS | Python-only, no ROS2 runtime. Faster startup, smaller footprint. Enable via `VYRA_SLIM=true`. |

See [docs/architecture/SLIM_MODE.md](docs/architecture/SLIM_MODE.md) for details.

## Directory Overview

```
{{ module_name }}/
├── src/
│   ├── {{ module_name }}_interfaces/   ← ROS2/Zenoh interface definitions (auto-generated from config/)
│   │   └── README.md
│   └── {{ module_name }}/              ← Python source package
│       ├── README.md
│       └── {{ module_name }}/          ← Main Python module
│           └── README.md
├── frontend/                           ← Vue 3 + TypeScript UI (if enabled)
│   └── README.md
├── tests/                              ← Pytest: unit / integration / e2e
├── examples/                           ← Isolated usage examples
├── config/                             ← Runtime config (logging, nginx, cyclonedds, uvicorn)
├── storage/                            ← Persistent runtime data and DB files
├── logs/                               ← Runtime logs (core_stdout.log, etc.)
├── .module/                            ← Module metadata and plugin interface definitions
├── docs/                               ← Extended architecture and deployment documentation
└── Dockerfile
```

### Internal Code Structure

- [src/{{ module_name }}_interfaces/README.md](src/{{ module_name }}_interfaces/README.md) — Interface config format, protocol tags, auto-generation
- [src/{{ module_name }}/README.md](src/{{ module_name }}/README.md) — Python package layout, Alembic migrations
- [src/{{ module_name }}/{{ module_name }}/README.md](src/{{ module_name }}/{{ module_name }}/README.md) — Entry points, state machine, application, interfaces, user management
- [src/{{ module_name }}/{{ module_name }}/backend_webserver/README.md](src/{{ module_name }}/{{ module_name }}/backend_webserver/README.md) — REST API, WebSocket, auth, services
- [src/{{ module_name }}/{{ module_name }}/plugin/README.md](src/{{ module_name }}/{{ module_name }}/plugin/README.md) — WASM plugin system

### Frontend

The Vue 3 frontend lives in `frontend/`. It uses Vite for development (with a dev proxy to the backend),
PrimeVue as the component library, and Pinia for state management.

See [frontend/README.md](frontend/README.md) for the full structure, available stores, and development instructions.

### Examples

`examples/` contains isolated, runnable Python snippets demonstrating key patterns such as feeders,
state transitions, interface definitions, config helpers, and access policy patterns.
Read [examples/README.md](examples/README.md) for an index of all examples.

### Tests

`tests/` uses pytest with three tiers:

| Marker | Scope | External Dependencies |
|---|---|---|
| `@pytest.mark.unit` | Single class / function | None |
| `@pytest.mark.integration` | Service interaction | Redis, ROS2 |
| `@pytest.mark.e2e` | Full module workflow | Full VYRA stack |

Run with:
```bash
pytest -m unit          # fast, no external services required
pytest -m integration   # requires Redis and ROS2
pytest -m e2e           # requires full VYRA deployment
```

## Further Documentation

| Document | Description |
|---|---|
| [docs/README.md](docs/README.md) | Full documentation index |
| [docs/development/DEVEL.md](docs/development/DEVEL.md) | Development workflow |
| [docs/deployment/DEPLOYMENT.md](docs/deployment/DEPLOYMENT.md) | Production deployment |
| [docs/architecture/](docs/architecture/) | Architecture deep-dives |
| [docs/plugin/](docs/plugin/) | Plugin development |
