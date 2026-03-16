# vyra_module_template - VYRA Module Template

> **This is a [Copier](https://copier.readthedocs.io/) template** for creating new VYRA modules.
> It is **not** a runnable module itself — use it to scaffold a new module project.

## 📋 Overview

VYRA modules are the building blocks of the [VYRA Framework](https://github.com/Variobotic-GmbH/vyra_framework). Each module is a self-contained service that runs inside a **VYRA Framework deployment** (Docker Swarm) and communicates with other modules via ROS2/Zenoh.

This template provides:

- **Standardized project structure** matching all official VYRA modules
- **Backend scaffold** using `vyra_base_python` as the core library
- **Optional Vue.js frontend** with Vite dev proxy and hot-reload
- **Docker / Docker Swarm** deployment files
- **Full Mode** (ROS2 + Zenoh) and **SLIM Mode** (Python-only, no ROS2) support
- **Testing scaffold** with pytest (unit, integration, e2e)

## ⚙️ Prerequisites

| Requirement | Notes |
|---|---|
| [Copier](https://copier.readthedocs.io/) ≥ 9 | `pip install copier` |
| [VYRA Framework](https://github.com/Variobotic-GmbH/vyra_framework) | The runtime environment for all modules |
| [vyra_base_python](https://github.com/vyra-entity/vyra_base_python) | Core library used by every module |
| Docker + Docker Swarm | For deployment |
| Python ≥ 3.11 | Backend development |

## 🚀 Creating a New Module

Use Copier to generate a new module from this template:

```bash
# Generate a new module into a target directory
copier copy https://github.com/vyra-entity/vyra_module_template ./modules/my_new_module

# Or use a local copy of the template
copier copy /path/to/vyra_module_template ./modules/my_new_module
```

### Copier prompts

| Variable | Description | Example |
|---|---|---|
| `module_name` | Snake_case module identifier | `my_detector` |
| `module_display_name` | Human-readable name | `My Detector Module` |
| `module_description` | Short description | `Detects things` |
| `author_name` | Your name | `Jane Doe` |
| `author_email` | Your email | `jane@example.com` |
| `enable_frontend` | Include Vue.js frontend | `true` / `false` |
| `enable_dev_mode` | Enable hot-reload dev mode by default | `true` / `false` |
| `enable_slim_mode` | SLIM mode (no ROS2, Python-only) | `false` (default) |

After generation the module is ready to be built and deployed via the VYRA Framework.

## 🏗️ VYRA Framework Requirement

VYRA modules **cannot run standalone**. They require a running VYRA Framework deployment that provides:

- **Docker Swarm** orchestration
- **Traefik** reverse proxy / routing
- **Redis** shared state storage
- **ROS2 / Zenoh** communication bus
- **Module Manager** (`v2_modulemanager`) for lifecycle management

```
VYRA Framework (Docker Swarm)
  ├── Traefik          → routing / TLS termination
  ├── Redis            → shared state
  ├── v2_modulemanager → module lifecycle & plugin management
  └── <your module>    → your custom service
```

See the [VYRA Framework repository](https://github.com/Variobotic-GmbH/vyra_framework) for setup instructions.

## 📦 Module Manager & Plugin Installation

All modules and plugins are managed by the **Module Manager** (`v2_modulemanager`). You do not install modules by hand — the Module Manager handles:

- **Module installation** from a configured repository (local or remote)
- **Plugin installation** (lightweight extensions added on top of modules)
- **Updates** for both modules and plugins
- **Lifecycle control** (start, stop, restart)

Once your module is published to a VYRA repository, it can be discovered and installed directly from the Module Manager UI or API:

```bash
# Install a module via the Module Manager API
curl -k -X POST https://localhost/v2_modulemanager/api/modules/install \
  -H "Content-Type: application/json" \
  -d '{"module_name": "my_detector", "version": "1.0.0"}'

# Install a plugin
curl -k -X POST https://localhost/v2_modulemanager/api/plugins/install \
  -H "Content-Type: application/json" \
  -d '{"plugin_name": "my-plugin", "version": "1.0.0"}'
```

See the [Module Manager documentation](https://github.com/Variobotic-GmbH/vyra_framework) for repository configuration and publishing details.

## 🔧 vyra_base_python

Every VYRA module is built on top of [`vyra_base_python`](https://github.com/vyra-entity/vyra_base_python), which provides:

- **`VyraEntity`** — base class for all modules (state machine, lifecycle hooks)
- **ROS2 / Zenoh** communication abstractions
- **Redis** integration helpers
- **Structured logging** via `structlog`
- **Security** (SROS2, access levels)
- **Plugin loader** — dynamic plugin system

The generated module already has `vyra_base_python` as a dependency. Do not implement these concerns from scratch.

## 🎯 Deployment Modes

### Full Mode (Default)
- ROS2 + Zenoh communication
- Full framework feature set
- Suitable for production environments

### SLIM Mode (Python-only)
- Zenoh communication only (no ROS2)
- 10x faster startup, ~90% smaller footprint
- Ideal for edge devices, CI/CD, and lightweight services

Enable via `enable_slim_mode: true` during template generation, or set `VYRA_SLIM=true` at runtime.

See [SLIM Mode Documentation](docs/SLIM_MODE.md) for details.

## 📚 Documentation

| Document | Description |
|---|---|
| [docs/README.md](docs/README.md) | Full documentation index |
| [docs/development/DEVEL.md](docs/development/DEVEL.md) | Development workflow |
| [docs/deployment/DEPLOYMENT.md](docs/deployment/DEPLOYMENT.md) | Production deployment |
| [docs/backend/](docs/backend/) | Backend API reference |
| [docs/frontend/FRONTEND_ARCHITECTURE.md](docs/frontend/FRONTEND_ARCHITECTURE.md) | UI structure |
| [docs/architecture/](docs/architecture/) | Module architecture |
| [docs/plugin/](docs/plugin/) | Plugin development |
| [examples/README.md](examples/README.md) | Isolated usage examples |
