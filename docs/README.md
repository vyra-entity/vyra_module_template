# V2 ModuleManager Documentation

## 📚 Documentation Structure

Welcome to the V2 ModuleManager documentation. This documentation is organized into the following categories:

### 🎨 Frontend (`frontend/`)
Frontend architecture, components, and development guides.
- [Frontend Architecture](frontend/FRONTEND_ARCHITECTURE.md) - System architecture and design patterns
- [Frontend Interfaces](frontend/FRONTEND_INTERFACES.md) - API interfaces and TypeScript types
- [Frontend Examples](frontend/FRONTEND_EXAMPLES.md) - Code examples and usage patterns
- [Frontend Configuration](frontend/FRONTEND_CONFIGURATION.md) - Configuration and setup

### ⚙️ Backend (`backend/` and root docs)
Backend services, APIs, and data management.
- [**Backend Webserver Architecture**](BACKEND_WEBSERVER_ARCHITECTURE.md) - ⭐ **NEW**: Direct DI architecture, migration from gRPC
- [Backend API](BACKEND_API.md) - REST API reference
- [**SLIM Mode**](SLIM_MODE.md) - ⭐ **NEW**: Lightweight Python-only deployment with Zenoh and Poetry
- [**Build System**](BUILD_SYSTEM.md) - ⭐ **NEW**: Poetry + Docker optimization with layer caching
- [Logging](LOGGING.md) - Structured logging with structlog
- [Authentication](AUTHENTICATION.md) - Authentication system and UserManager integration
- [Backend README](backend/BACKEND_README.md) - Backend overview and architecture
- [**Authentication API**](backend/AUTHENTICATION_API.md) - Login, logout, session management
- [**WebSocket API**](backend/WEBSOCKET_API.md) - Real-time updates and operation tracking
- [~~gRPC Quick Start~~](backend/GRPC_QUICK_START.md) - ⚠️ **DEPRECATED**: gRPC replaced by Direct DI (Feb 2026)
- [Module Installation Process](backend/MODULE_INSTALLATION_PROCESS.md)
- [Module Repository](backend/MODULE_REPOSITORY.md)
- [Registration Process](backend/REGISTRATION_PROCESS.md)
- [Status System](backend/STATUS_SYSTEM.md)
- [Interface Update Guide](backend/INTERFACE_UPDATE_GUIDE.md)
- [Git Tag Upstream Guide](GIT_TAG_UPSTREAM_GUIDE.md)
- [Redis Migration Guide](backend/REDIS_MIGRATION_GUIDE.md)
- [Task-Based Operations](backend/TASK_BASED_OPERATIONS.md)

### 🚀 Deployment (`deployment/`)
Deployment, configuration, and production setup.
- [Deployment Guide](deployment/DEPLOYMENT.md)
- [HTTPS Configuration](deployment/HTTPS_CONFIGURATION.md)
- [Nginx Integration](deployment/NGINX_INTEGRATION.md)

### 🔧 Development (`development/`)
Development setup, workflows, and best practices.
- [Development Guide](development/DEVEL.md)
- [Dependency Installation](development/DEPENDENCY_INSTALLATION.md)
- [Environment Variables](development/ENVIRONMENT_VARIABLES.md)
- [Git Template as Upstream](development/GIT_TEMPLATE_AS_UPSTREAM_GUIDE.md)
- [Hot Reload ROS2](development/HOT_RELOAD_ROS2_GUIDE.md)

### 🔒 Security (`security/`)
Security configuration, authentication, and certificates.
- [ROS2 Security Guide](security/ROS2_SECURITY_GUIDE.md)
- [SROS2 Authentication Process](security/SROS2_AUTHENTIFICATION_PROCESS.md)
- [SSL Certificate Management](security/SSL_CERTIFICATE_MANAGEMENT.md)
- [Permissions Example XML](security/permissions_example.xml)

## 🎯 Quick Start

1. **Setup Development Environment**: See [Development Guide](development/DEVEL.md)
2. **Understand Architecture**: Read [Frontend Architecture](frontend/FRONTEND_ARCHITECTURE.md) and [Backend README](backend/BACKEND_README.md)
3. **Deploy**: Follow [Deployment Guide](deployment/DEPLOYMENT.md)

## 🤝 Contributing

When adding new documentation:
- Place backend-related docs in `backend/`
- Place frontend-related docs in `frontend/`
- Place deployment/infrastructure docs in `deployment/`
- Place development workflow docs in `development/`
- Place security-related docs in `security/`

## 📝 Documentation Standards

- Use clear, descriptive titles
- Include code examples where applicable
- Keep documentation up-to-date with code changes
- Use Markdown formatting consistently
- Include diagrams for complex architectures
