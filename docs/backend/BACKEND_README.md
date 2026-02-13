# VYRA Module Manager - Backend Documentation

## 📚 API Documentation

Complete API documentation is available in separate documents:

- **[REST API Reference](../BACKEND_API.md)** - Complete REST API documentation with all endpoints
- **[Authentication API](AUTHENTICATION_API.md)** - Login, logout, session management
- **[WebSocket API](WEBSOCKET_API.md)** - Real-time updates and operation tracking
- **[Auto-generated Docs](https://localhost:8443/api/docs)** - Interactive Swagger UI
- **[ReDoc](https://localhost:8443/api/redoc)** - Alternative API documentation

## 🏗️ Architecture Overview

Das VYRA Module Manager Backend ist eine moderne **FastAPI**-Anwendung mit einer sauberen, modularen Architektur. Die API folgt REST-Prinzipien und bietet sowohl synchrone als auch asynchrone Endpunkte für die Modulverwaltung.

## 📁 Projektstruktur

```
src/rest_api/
├── main_rest.py                 # Hauptanwendung & Router-Konfiguration
├── core/                        # Zentrale Konfiguration & Dependencies
│   ├── __init__.py
│   ├── config.py               # Anwendungseinstellungen & Pfade
│   └── dependencies.py         # Gemeinsame Dependencies & Validierung
├── modules/                     # Modul-Management API
│   ├── __init__.py
│   ├── models.py               # Gemeinsame Datenmodelle
│   ├── schemas.py              # Request/Response Schemas
│   ├── management/             # Installation & Update-Operationen
│   │   ├── __init__.py
│   │   ├── router.py           # Management API Endpunkte
│   │   ├── models.py           # Management-spezifische Modelle
│   │   └── service.py          # Business Logic für Installation/Updates
│   └── instances/              # Instanz-Verwaltung
│       ├── __init__.py
│       ├── router.py           # Instanz API Endpunkte
│       ├── models.py           # Instanz-spezifische Modelle
│       ├── schemas.py          # Instanz Request/Response Schemas
│       └── service.py          # Business Logic für Instanzen
├── repository/                 # Repository & Katalog-Verwaltung
│   ├── __init__.py
│   ├── router.py               # Repository API Endpunkte
│   ├── database.py             # Datenbank-Abstraktion
│   ├── crud.py                 # CRUD-Operationen
│   └── list.py                 # Legacy Repository-Liste (deprecated)
└── docker_service_manager.py   # Docker Swarm Integration
```

## 🚀 Hauptkomponenten

### 1. Core (`src/rest_api/core/`)

#### `config.py`
- **Zweck**: Zentrale Konfiguration für die gesamte Anwendung
- **Funktionen**:
  - Anwendungseinstellungen (Titel, Version, Beschreibung)
  - Pfad-Konfiguration (Workspace, Module, Storage, etc.)
  - Docker-Konfiguration (Stack-Name, Netzwerk)
  - SSL/TLS-Einstellungen
  - Development/Production-Modi

```python
from src.rest_api.core.config import settings

# Beispiel-Nutzung
workspace_path = settings.WORKSPACE_ROOT
modules_path = settings.MODULES_PATH
has_ssl = settings.has_ssl_certificates
```

#### `dependencies.py`
- **Zweck**: Gemeinsame Dependencies und Validierungsfunktionen
- **Funktionen**:
  - Operation-Status-Tracking
  - Modul- und Instanz-ID-Validierung
  - Pfad-Utilities
  - Fehlerbehandlung (Custom Exceptions)

### 2. Repository Management (`src/rest_api/repository/`)

#### `router.py`
- **Endpunkte**:
  - `GET /repository/list` - Alle Repositories mit Modulen auflisten
  - `GET /repository/modules` - Verfügbare Module (mit Filtern)
  - `POST /repository/install` - Module aus Repository installieren
  - `GET /repository/install/status/{operation_id}` - Installations-Status
  - `DELETE /repository/uninstall/{module_id}` - Modul deinstallieren

#### `database.py`
- **Zweck**: Datenbank-Abstraktion für Repository-Operationen
- **Funktionen**:
  - Repository-Konfiguration verwalten
  - Module aus lokalen/Remote-Repositories laden
  - File-based und HTTPS-Repository-Support

#### `crud.py`
- **Zweck**: CRUD-Operationen für Repositories und Module
- **Funktionen**:
  - Repository-Statistiken berechnen
  - Modul-Suche und -Filterung
  - Installations-Status ermitteln
  - Kategorie-Aggregation

### 3. Module Management (`src/rest_api/modules/management/`)

#### `router.py`
- **Endpunkte**:
  - `POST /modules/update` - Modul auf neueste Version aktualisieren
  - `POST /modules/install-instance` - Zusätzliche Instanz installieren
  - `GET /modules/status/{operation_id}` - Operation-Status abfragen

#### `service.py`
- **Zweck**: Business Logic für Installation und Updates
- **Funktionen**:
  - Asynchrone Modul-Installation
  - Update-Prozess mit Progress-Tracking
  - Docker-Service-Integration
  - Fehlerbehandlung und Rollback

### 4. Instance Management (`src/rest_api/modules/instances/`)

#### `router.py`
- **Endpunkte**:
  - `GET /modules/instances` - Alle Instanzen auflisten
  - `GET /modules/instance/{module_name}/{instance_id}` - Spezifische Instanz
  - `DELETE /modules/instance/{module_name}/{instance_id}` - Instanz löschen
  - `GET /modules/primary/{module_name}` - Primäre Instanz ermitteln
  - `POST /modules/primary/{module_name}/{instance_id}` - Primäre Instanz setzen

#### `service.py`
- **Zweck**: Business Logic für Instanz-Verwaltung
- **Funktionen**:
  - Instanz-Lebenszyklus (Erstellen, Löschen, Status)
  - Primäre Instanz-Verwaltung
  - Docker-Service-Koordination
  - Dateisystem-Operationen

## 🔧 API-Endpunkte im Detail

### System-Endpunkte

| Endpunkt | Methode | Beschreibung |
|----------|---------|--------------|
| `/` | GET | API-Übersicht und verfügbare Endpunkte |
| `/status` | GET | System-Status und Konfiguration |
| `/health` | GET | Gesundheitsprüfung für Monitoring |
| `/api/docs` | GET | Swagger UI Dokumentation |
| `/api/redoc` | GET | ReDoc Dokumentation |

### Repository-Endpunkte

| Endpunkt | Methode | Beschreibung |
|----------|---------|--------------|
| `/repository/list` | GET | Alle Repositories mit Statistiken |
| `/repository/modules` | GET | Verfügbare Module (optional gefiltert) |
| `/repository/install` | POST | Module aus Repository installieren |
| `/repository/install/status/{operation_id}` | GET | Installations-Status prüfen |
| `/repository/uninstall/{module_id}` | DELETE | Modul deinstallieren |

### Module-Management-Endpunkte

| Endpunkt | Methode | Beschreibung |
|----------|---------|--------------|
| `/modules/update` | POST | Modul aktualisieren |
| `/modules/install-instance` | POST | Neue Instanz installieren |
| `/modules/status/{operation_id}` | GET | Operation-Status verfolgen |

### Instanz-Verwaltung-Endpunkte

| Endpunkt | Methode | Beschreibung |
|----------|---------|--------------|
| `/modules/instances` | GET | Alle Instanzen auflisten |
| `/modules/instance/{module_name}/{instance_id}` | GET | Spezifische Instanz abrufen |
| `/modules/instance/{module_name}/{instance_id}` | DELETE | Instanz löschen |
| `/modules/primary/{module_name}` | GET | Primäre Instanz ermitteln |
| `/modules/primary/{module_name}/{instance_id}` | POST | Primäre Instanz setzen |

## 🔄 Background Tasks

Das Backend verwendet **FastAPI Background Tasks** für langwierige Operationen:

### Installation von Modulen
```python
# Beispiel: Neue Instanz installieren
POST /modules/install-instance
{
    "module_name": "v2_dashboard",
    "repository_id": "local-module-repository",
    "version": "0.1.0"
}

# Response:
{
    "operation_id": "uuid-hier",
    "status": "queued",
    "status_url": "/modules/status/uuid-hier"
}
```

### Status-Verfolgung
```python
# Status abfragen
GET /modules/status/{operation_id}

# Response:
{
    "operation_id": "uuid-hier",
    "status": "running",
    "progress": 45,
    "message": "Module files copied",
    "module_name": "v2_dashboard"
}
```

## 🐳 Docker Integration

### Docker Swarm Services
Das Backend verwaltet Module als Docker Swarm Services:

- **Service-Namen**: `{stack_name}_{module_name}_{instance_id}`
- **Netzwerk**: Automatische Integration in Stack-Netzwerk
- **Volumes**: Automatisches Mounting von Modul-Verzeichnissen

### Container-Manager Integration
- Kommunikation mit `container-manager` Service
- Sichere Service-Erstellung über API
- Wildcard-Berechtigung für Modul-Services

## 📊 Datenmodelle

### ModuleInstance
```python
{
    "instance_id": "32-char-hex-string",
    "path": "/modules/module_name_instance_id",
    "version": "0.1.0",
    "status": "installed|running|stopped|error",
    "is_primary": true,
    "frontend_url": "/module_name/",
    "created_at": "2025-10-28T13:30:00Z",
    "updated_at": "2025-10-28T13:30:00Z"
}
```

### OperationResponse
```python
{
    "operation_id": "uuid4-string",
    "status": "queued|running|completed|failed",
    "progress": 0-100,
    "message": "Human readable status",
    "module_name": "module_name",
    "status_url": "/modules/status/operation_id"
}
```

## 🔐 Sicherheit

### SSL/TLS
- **Zertifikate**: Automatische Erkennung in `/workspace/storage/certificates/`
- **HTTPS**: Uvicorn läuft auf Port 8443 mit SSL
- **Entwicklung**: HTTP-Fallback wenn keine Zertifikate vorhanden

### Validierung
- **Modul-Namen**: Alphanumerisch + Unterstriche/Bindestriche
- **Instanz-IDs**: 32-Zeichen Hexadecimal-Strings
- **Pfad-Sicherheit**: Automatische Validierung gegen Path-Traversal

## 🚀 Deployment

### Development-Modus
```bash
export DEVELOPMENT_MODE=true
export DEBUG=true
uvicorn src.rest_api.main_rest:app --reload --host 0.0.0.0 --port 8000
```

### Production-Modus
```bash
uvicorn src.rest_api.main_rest:app --host 0.0.0.0 --port 8443 \
    --ssl-certfile /workspace/storage/certificates/webserver.crt \
    --ssl-keyfile /workspace/storage/certificates/webserver.key
```

### Docker Swarm
```bash
docker stack deploy -c docker-compose.yml vos2_ws
```

## 🔍 Debugging

### Logs
- **Uvicorn**: `/workspace/log/uvicorn/`
- **Application**: Stdout/Stderr über Docker Logs
- **Service Logs**: `docker service logs vos2_ws_{module_name}`

### Health Checks
```bash
# Basis-Gesundheit
curl -k https://localhost:8443/health

# Detaillierter Status
curl -k https://localhost:8443/status

# API-Dokumentation
curl -k https://localhost:8443/api/docs
```

### Direkte Container-Tests
```bash
# In Container einloggen
docker exec -it $(docker ps --filter name={module_name} --format "{{.ID}}") bash

# API direkt testen
curl -k https://localhost:8443/modules/instances
```

## 🧪 Testing

### Unit Tests
```bash
# Pytest ausführen
python -m pytest tests/

# Mit Coverage
python -m pytest --cov=src/rest_api tests/
```

### Integration Tests
```bash
# API-Tests
python -m pytest tests/integration/

# Docker-Tests
python -m pytest tests/docker/
```

### Manuelle Tests
```bash
# Repository-Liste
curl -k https://localhost:8443/repository/list

# Module-Instanzen
curl -k https://localhost:8443/modules/instances

# Neue Instanz installieren
curl -k -X POST https://localhost:8443/modules/install-instance \
  -H "Content-Type: application/json" \
  -d '{"module_name": "v2_dashboard"}'
```

## 📈 Performance

### Async/Await
- Alle Service-Layer-Funktionen sind asynchron
- Non-blocking I/O für Dateisystem-Operationen
- Concurrent Background Tasks

### Caching
- Repository-Daten werden zwischengespeichert
- Modul-Status wird lazy geladen
- Docker-Service-Status wird gecacht

### Monitoring
- Health-Check-Endpunkt für Load Balancer
- Metrics-Integration möglich
- Structured Logging für Observability

## 🔄 Migration von Legacy API

Die neue API ist rückwärtskompatibel mit der Vue.js Frontend:

### Legacy-Endpunkte (Kompatibilität)
- `GET /api/modules` → weiterleitung zu neuer Struktur
- `GET /api/modules/{module_name}` → primäre Instanz
- `POST /api/install/{module_name}` → weiterleitung zu install-instance

### Migration-Schritte
1. Neue API parallel zur alten betreiben
2. Frontend schrittweise auf neue Endpunkte umstellen
3. Legacy-Endpunkte als deprecated markieren
4. Nach Übergangsphase entfernen

## 📚 Weitere Dokumentation

- **Frontend Integration**: [FRONTEND_README.md](./FRONTEND_README.md)
- **HTTPS-Konfiguration**: [HTTPS_CONFIGURATION.md](./HTTPS_CONFIGURATION.md)
- **SSL-Zertifikate**: [SSL_CERTIFICATE_MANAGEMENT.md](./SSL_CERTIFICATE_MANAGEMENT.md)
- **Nginx-Integration**: [NGINX_INTEGRATION.md](./NGINX_INTEGRATION.md)
- **Modul-Installation**: [MODULE_INSTALLATION_PROCESS.md](./MODULE_INSTALLATION_PROCESS.md)