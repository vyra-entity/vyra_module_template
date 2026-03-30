# Container Injection Migration

## Aktueller Stand (Februar 2026)

### Backend Webserver Integration

**Neueste Änderungen:**
- REST API wurde in Modulstruktur verschoben: `src/{module_name}/{module_name}/backend_webserver/`
- Alle gRPC-Kommunikation vollständig durch Direct DI ersetzt
- UserManager direkt in Component integriert
- Auth-Service nutzt jetzt `get_component().internal_usermanager`
- Module-Service nutzt jetzt `get_component().registry`

**Backend Webserver Struktur:**
```
src/{module_name}/{module_name}/
├── backend_webserver/        # Vorher: src/rest_api/
│   ├── asgi.py
│   ├── main_rest.py
│   ├── auth/                 # Nutzt container_injection für UserManager
│   │   ├── auth_service.py   # → get_component().internal_usermanager
│   │   └── router.py
│   └── module/               # Nutzt container_injection für ModuleRegistry
│       ├── service.py        # → get_component().registry
│       └── router.py
├── container_injection.py    # Erweitert: user_manager hinzugefügt
└── application/
    └── application.py        # Component initialisiert UserManager
```

**Beispiel - Auth Service:**
```python
# backend_webserver/auth/auth_service.py
from ....container_injection import get_component

async def authenticate_user(username: str, password: str):
    component = get_component()
    # Direct method call - no gRPC
    success = await component.internal_usermanager.authenticate(username, password)
    if success:
        return create_jwt_token(username)
```

**Beispiel - Module Service:**
```python
# backend_webserver/module/service.py
from ....container_injection import get_component

async def install_module(module_name: str, ...):
    component = get_component()
    # Direct access to registry
    await component.registry.register_new_module_impl(
        module_name=module_name,
        instance_id=instance_id,
        base_node_name=base_node_name,
        function_scope=function_scope
    )
```

**Siehe auch:**
- [Backend Webserver Architecture](./BACKEND_WEBSERVER_ARCHITECTURE.md) - Vollständige Architektur-Dokumentation
- [Authentication](./AUTHENTICATION.md) - Authentifizierungs-Flow mit Direct DI

---

## Übersicht (Ursprüngliche Migration)

Mit diesem Umbau wurde die Architektur von {module_name} modernisiert:

**Vorher:**
- REST API (Uvicorn) wurde separat über supervisord gestartet
- Kommunikation zwischen REST API und ROS2-Core erfolgte über gRPC over UDS

**Nachher:**
- REST API (Uvicorn) wird als Task im TaskManager gestartet
- Direkte Kommunikation über `container_injection` mit **dependency_injector** Framework
- Kein gRPC over UDS mehr nötig
- Bessere Integration und Ressourcenverwaltung

## Dependency Injector Framework

Das Projekt verwendet jetzt das professionelle [dependency-injector](https://python-dependency-injector.ets-labs.org/) Framework für Dependency Injection.

**Vorteile:**
- Industry-standard DI-Framework für Python
- Thread-safe Singleton-Provider
- Bessere Testbarkeit durch Container-Override
- Klare API und Dokumentation
- Integration mit FastAPI

## Geänderte Dateien

### 1. `src/{module_name}/{module_name}/container_injection.py` (NEU)

Globaler Dependency Injection Container mit **dependency-injector** Framework für:
- `VyraEntity` - ROS2 Node und Kommunikation
- `Component` - Anwendungslogik
- `TaskManager` - Task-Verwaltung
- `StatusManager` - Status-Broadcasting

**Architektur:**
```python
from dependency_injector import containers, providers

class ApplicationContainer(containers.DeclarativeContainer):
    entity = providers.Singleton(lambda: None)
    component = providers.Singleton(lambda: None)
    task_manager = providers.Singleton(lambda: None)
    status_manager = providers.Singleton(lambda: None)

# Global container instance
container = ApplicationContainer()
```

**API:**
```python
# Setzen (in main.py nach Initialisierung)
from .container_injection import (
    set_entity, set_component, 
    set_task_manager, set_status_manager
)

set_entity(entity)
set_component(component)
set_task_manager(taskmanager)
set_status_manager(statusmanager)

# Abrufen (in REST API oder anderen Modulen)
from src.{module_name}.{module_name}.container_injection import (
    get_entity, get_component,
    provide_entity, provide_component  # For FastAPI Depends()
)

entity = get_entity()
component = get_component()
```

**FastAPI Integration:**
```python
from fastapi import Depends
from ....backend_webserver.core.dependencies import (
    get_vyra_entity,
    get_component,
    get_task_manager,
    get_status_manager
)

# In Router/Endpoint verwenden:
@router.get("/some-endpoint")
async def endpoint(
    entity = Depends(get_vyra_entity),
    component = Depends(get_component)
):
    # Direkter Zugriff auf entity und component
    # Keine gRPC-Calls mehr nötig!
    result = await component.some_method()
    return {"result": result}
```

Die Dependencies nutzen intern die `provide_*` Funktionen aus `container_injection`.

**Verfügbare Dependencies:**
- `get_vyra_entity()` - Zugriff auf ROS2 Node
- `get_component()` - Zugriff auf Application Component
- `get_task_manager()` - Zugriff auf TaskManager
- `get_status_manager()` - Zugriff auf StatusManager

### 4. `.module/requirements.txt`

**Hinzugefügt:**
```txt
dependency-injector==4.42.0
```

Das dependency-injector Framework ist jetzt eine Kern-Dependency des Projekts.
- Import von `container_injection`
- Neue Funktion `web_backend_runner()` für Uvicorn-Server
- Nach Initialisierung werden alle Instanzen in container_injection gesetzt
- Web backend Task wird bedingt gestartet (wenn `ENABLE_BACKEND_WEBSERVER=true`)

**Code-Snippet:**
```python
# In initialize_module()
container_injection.set_entity(entity)
container_injection.set_component(component)
container_injection.set_task_manager(taskmanager)
container_injection.set_status_manager(statusmanager)

# Conditionally start web backend
enable_webserver = os.getenv('ENABLE_BACKEND_WEBSERVER', 'false').lower() == 'true'
if enable_webserver:
    taskmanager.add_task(web_backend_runner)
```

### 3. `src/{module_name}/{module_name}/backend_webserver/core/dependencies.py`

**Neue Dependencies für FastAPI:**
```python
from fastapi import Depends

# In Router/Endpoint verwenden:
@router.get("/some-endpoint")
async def endpoint(
    entity = Depends(get_vyra_entity),
    component = Depends(get_component)
):
    # Direkter Zugriff auf entity und component
    # Keine gRPC-Calls mehr nötig!
    pass
```

**Verfügbare Dependencies:**
- `get_vyra_entity()` - Zugriff auf ROS2 Node
- `get_component()` - Zugriff auf Application Component
- `get_task_manager()` - Zugriff auf TaskManager
- `get_status_manager()` - Zugriff auf StatusManager

### 4. `vyra_base_image/supervisord.conf`

**Änderung:**
- `[program:uvicorn]` ist jetzt auskommentiert
- Hinweis: Uvicorn wird jetzt über TaskManager in main.py gestartet

## Vorteile

### 1. **Professionelles DI-Framework**
- Industry-standard dependency-injector Framework
- Thread-safe Singleton-Provider
- Bessere Testbarkeit durch Container-Mocking
- Declarative Container API

### 2. **Vereinfachte Architektur**
- Keine separaten Prozesse mehr für REST API
- Alles läuft im gleichen Python-Prozess
- Kein gRPC over UDS mehr nötig

### 2. **Vereinfachte Architektur**
- Keine separaten Prozesse mehr für REST API
- Alles läuft im gleichen Python-Prozess
- Kein gRPC over UDS mehr nötig

### 3. **Bessere Ressourcenverwaltung**
- TaskManager überwacht alle Tasks einheitlich
- Automatische Restarts bei Fehlern
- Zentrale Fehlerbehandlung

### 4. **Performance**
- Direkter Zugriff auf Instanzen ohne Serialisierung
- Keine Netzwerk-Latenz (auch nicht lokal)
- Weniger Memory overhead

### 5. **Bessere Ressourcenverwaltung**
- TaskManager überwacht alle Tasks einheitlich
- Automatische Restarts bei Fehlern
- Zentrale Fehlerbehandlung

### 3. **Performance**
- Direkter Zugriff auf Instanzen ohne Serialisierung
- Keine Netzwerk-Latenz (auch nicht lokal)
- Weniger Memory overhead

### 4. **Entwickler-Erfahrung**
- Einfachere Debugging
- Direkter Zugriff auf Objekte
- Weniger Boilerpdependency_injector):
```python
from fastapi import Depends
from src.rest_api.core.dependencies import get_vyra_entity, get_component

@router.get("/endpoint")
async def endpoint(
    entity = Depends(get_vyra_entity),
    component = Depends(get_component)
):
    # Direkter Zugriff
    result = await entity.call_service(...)
    # oder
    result = await component.some_method(...)
    return {"result": result}
```

### Alternative (direkt mit provide_* Funktionen):
```python
from fastapi import Depends
from src.{module_name}.{module_name}.container_injection import (
    provide_entity,
    provide_component
)

@router.get("/endpoint")
async def endpoint(
    entity = Depends(provide_entity),
    component = Depends(provide_component)
):
    # Direkter Zugriff mit provide_* Funktionen
    result = await component.some_method()
    return {"result": result}
### Nachher (mit container_injection):
```python
from src.rest_api.core.dependencies import get_vyra_entity, get_component
from fastapi import Depends

@router.get("/endpoint")
async def endpoint(
    entity = Depends(get_vyra_entity),
    component = Depends(get_component)
):
    # Direkter Zugriff.container_injection import (
    container,
    set_entity,
    set_component,
    get_entity,
    reset
)

def test_container_injection():
    # Setup
    set_entity(mock_entity)
    set_component(mock_component)
    
    # Test
    assert container.entity() is not None
    entity = get_entity()
    assert entity == mock_entity
    
    # Cleanup
    reset()

def test_container_override():
    # Override für Tests
    from dependency_injector import providers
    
    container.entity.override(providers.Object(test_entity))
    container.component.override(providers.Object(test_component))
    
    # Test mit Mock-Objekten
    entity = get_entity()
    assert entity == test_entity
    
    # Reset nach Test
    reset()
```

### Integration Tests
```bash
# Mit Web Backend
ENABLE_BACKEND_WEBSERVER=true pytest tests/integration/

# Ohne Web Backend
ENABLE_BACKEND_WEBSERVER=false pytest tests/integration/
```

### FastAPI Dependency Testing
```python
from fastapi.testclient import TestClient
from src.rest_api.main_rest import app
from src.{module_name}.{module_name}.container_injection import (
    set_entity,
    set_component
)

def test_api_with_container():
    # Setup container
    set_entity(mock_entity)
    set_component(mock_component)
    
    # Test API
    client = TestClient(app)
    response = client.get("/api/endpoint")
    assert response.status_code == 200

**Docker Compose:**
```yaml
environment:
  - ENABLE_BACKEND_WEBSERVER=true
```

## Testing

### Unit Tests
```python
from src.{module_name}.{module_name} import container_injection

def test_container_injection():
    # Setup
    container_injection.set_entity(mock_entity)
    container_injection.set_component(mock_component)
    
    # Test
    assert container_injection.is_initialized()
    entity = container_injection.get_entity()
    
    # Cleanup
    container_injection.reset()
```

### Integration Tests
```bash
# Mit Web Backend
ENABLE_BACKEND_WEBSERVER=true pytest tests/integration/

# Ohne Web Backend
ENABLE_BACKEND_WEBSERVER=false pytest tests/integration/
```

## Troubleshooting

### Problem: `ContainerNotInitializedError`

**Symptom:**
```
HTTP 503: VyraEntity not yet initialized
```

**Ursache:**
- REST API endpoint wird aufgerufen, bevor `initialize_module()` abgeschlossen ist
- Container wurde nicht korrekt initialisiert

**Lösung:**
1. Warten bis alle Tasks gestartet sind (ca. 2-3 Sekunden nach Container-Start)
2. Health check endpoint verwenden: `GET /health`
3. Logs prüfen: `docker service logs vos2_ws_{module_name}`

### Problem: Web Backend startet nicht

**Symptom:**
- Keine Uvicorn-Logs
- Port 8443 nicht erreichbar

**Ursache:**
- `ENABLE_BACKEND_WEBSERVER=false` in .env

**Lösung:**
```bash
# In .env setzen
ENABLE_BACKEND_WEBSERVER=true

# Container neu starten
cd /home/holgder/VOS2_WORKSPACE/tools
./vyra_up.sh
```

### Problem: "Container injection not available"

**Symptom:**
```
HTTP 503: Container injection not available - REST API running standalone
```

**Ursache:**
- Import von `container_injection` fehlgeschlagen
- REST API läuft in standalone-Modus (z.B. für Tests)

**Lösung:**
- Prüfen, dass alle Imports korrekt sind
- Sicherstellen, dass `/workspace` in `sys.path` ist
- Bei standalone-Tests: Mock container_injection

## Backwards Compatibility

### Legacy gRPC Clients

Alte gRPC-Clients funktionieren weiterhin, falls noch vorhanden:
- `src/rest_api/clients/grpc/` - Legacy code
- Empfohlen: Umstieg auf `container_injection` dependencies

### Supervisord Uvicorn

Falls supervisord Uvicorn wieder aktiviert werden soll:
1. `vyra_base_image/supervisord.conf` - Kommentare entfernen
2. `ENABLE_BACKEND_WEBSERVER=false` in .env setzen
3. Container neu bauen

**Hinweis:** Dies ist **nicht empfohlen** und sollte nur für Legacy-Support verwendet werden.

## Roadmap

### Zukünftige Verbesserungen
- [ ] Health checks für container_injection Status
- [ ] Metrics für Task-Performance
- [ ] Automatische Dependency checks
- [ ] Container-Snapshot für Debugging

### Weitere Module
- [ ] v2_dashboard Migration
- [ ] Andere Module bei Bedarf

## Fragen & Support

Bei Fragen oder Problemen:
1. Logs prüfen: `docker service logs vos2_ws_{module_name} -f`
2. Unit tests laufen lassen: `pytest tests/`
3. Dokumentation lesen: `docs/`
4. Issue erstellen im Repository

---

**Version:** 1.0.0  
**Datum:** 2026-02-12  
**Autor:** VYRA Development Team
