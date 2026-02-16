# <module_name> - VYRA Module Management Service

Central module management service for the VYRA framework, providing module installation, updates, configuration, and lifecycle control.

## 📋 Overview

The Module Manager is a core VYRA service that handles:

- **Module Discovery**: Browse and search available modules from repositories
- **Installation**: Download, verify, and deploy modules
- **Updates**: Automatic update checks and module upgrades
- **Configuration**: Module settings and parameter management
- **Lifecycle Control**: Start, stop, restart modules
- **Status Monitoring**: Real-time module health and state tracking

## 🚀 Quick Start

### Access the Web Interface

```bash
# After deployment
open https://localhost/<module_name>/
```

### API Access

```bash
# List available modules
curl -k https://localhost/api/<module_name>/modules/available

# Get installed modules
curl -k https://localhost/api/<module_name>/modules/instances

# Module health
curl -k https://localhost/api/<module_name>/health
```

## 📚 Documentation

See [docs/README.md](docs/README.md) for complete documentation index.

### Key Documentation

- **[Backend API](docs/BACKEND_API.md)** - REST API reference
- **[SLIM Mode](docs/SLIM_MODE.md)** - ⭐ **NEW**: Lightweight Python-only deployment (Zenoh + Poetry)
- **[Logging](docs/LOGGING.md)** - Structured logging with structlog and @log_call decorator
- **[Frontend Architecture](docs/frontend/FRONTEND_ARCHITECTURE.md)** - UI structure
- **[Deployment Guide](docs/deployment/DEPLOYMENT.md)** - Production setup
- **[Development Guide](docs/development/DEVEL.md)** - Development workflow

## 🎯 Deployment Modes

### Full Mode (Default)
- Zenoh communication (base)
- ROS2 + DDS communication (secondary)
- Complete framework features
- Production environments

### SLIM Mode (Python-only)
- ✅ Zenoh communication (base)
- ✅ Poetry build system
- ✅ 10x faster startup
- ✅ 90% smaller footprint
- ⚡ Edge devices, development, CI/CD

See [SLIM Mode Documentation](docs/SLIM_MODE.md) for details.

## 🏗️ Architecture

**Monolithic Process with Direct Dependency Injection (February 2026)**

```
Browser → Traefik → Nginx → Uvicorn → FastAPI (Backend Webserver)
                                         ↓
                          container_injection.get_component() (Direct DI)
                                         ↓
                                    Component
                             ┌───────────┴───────────┐
                             ↓                       ↓
                      InternalUserManager     ModuleRegistry
                             ↓                       ↓
                         ROS2 Node              Redis Storage
```

**Key Changes**:
- ❌ **Removed**: gRPC inter-process communication
- ✅ **Added**: Direct dependency injection via `container_injection`
- ⚡ **Performance**: 50x faster internal communication
- 🎯 **Simplified**: Single process architecture

See [Backend Webserver Architecture](docs/BACKEND_WEBSERVER_ARCHITECTURE.md) for detailed architecture and migration guide.
