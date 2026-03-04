# {{ module_display_name }} Documentation

## Struktur

Diese Dokumentation nutzt eine kombinierte Struktur:

1. **Kuratierte Querschnittsordner** (`architecture/`, `api/`, `operations/`, `migrations/`)
2. **Fachbereiche** (`frontend/`, `backend/`, `deployment/`, `development/`, `security/`)

## Root-Konvention

- Im `docs/`-Root liegen nur `README.md` und `INDEX.md`.
- Weitere Dateien sind in Unterordnern organisiert.
- Schnelle Navigation: [INDEX.md](INDEX.md)

## Kuratierte Einstiegspunkte

### Architektur (`architecture/`)
- [Backend Webserver Architecture](architecture/BACKEND_WEBSERVER_ARCHITECTURE.md)
- [SLIM Mode](architecture/SLIM_MODE.md)
- [Build System](architecture/BUILD_SYSTEM.md)
- [Logging](architecture/LOGGING.md)

### API (`api/`)
- [Backend API](api/BACKEND_API.md)
- [Feature: Module Feed and Updates](api/FEATURE_MODULE_FEED_AND_UPDATES.md)

### Betrieb (`operations/`)
- [Internal UserManager](operations/INTERNAL_USERMANAGER.md)
- [User Manager](operations/USER_MANAGER.md)
- [Module Update Implementation](operations/MODULE_UPDATE_IMPLEMENTATION.md)

### Migrationen (`migrations/`)
- [Container Injection Migration](migrations/CONTAINER_INJECTION_MIGRATION.md)
- [Structlog Migration Summary](migrations/STRUCTLOG_MIGRATION_SUMMARY.md)
- [Git Tag Upstream Guide](migrations/GIT_TAG_UPSTREAM_GUIDE.md)

## Fachbereiche

### Frontend (`frontend/`)
- [Frontend README](FRONTEND_README.md)
- [REST API Client Architecture](REST_API_CLIENT_ARCHITECTURE.md)

### Backend (`backend/`)
- Backend-spezifische Details im Unterordner `backend/`.

### Deployment (`deployment/`)
- [HTTPS Configuration](HTTPS_CONFIGURATION.md)
- [Nginx Integration](NGINX_INTEGRATION.md)
- [Quick Start ASGI](QUICK_START_ASGI.md)

### Development (`development/`)
- [Dependency Installation](DEPENDENCY_INSTALLATION.md)
- [Environment Variables](ENVIRONMENT_VARIABLES.md)

### Security (`security/`)
- [Authentication](security/AUTHENTICATION.md)
- [SROS2 Authentication Process](SROS2_AUTHENTIFICATION_PROCESS.md)
- [SSL Certificate Management](SSL_CERTIFICATE_MANAGEMENT.md)

## Pflegehinweise

- Neue Querschnittsdokumente zuerst in `architecture/`, `api/`, `operations/` oder `migrations/` einordnen.
- Bereichsspezifische Detaildokumente in den Fachordnern halten.
- Bei Template-Anpassungen Platzhalter (`{{ module_name }}`, `{{ module_display_name }}`) beibehalten.
