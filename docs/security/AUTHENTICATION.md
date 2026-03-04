# Authentication System - <module_name>

## Übersicht

Das neue Authentication-System für <module_name> bietet lokale Authentifizierung und Integration mit einem zukünftigen Usermanager-Service.

## Architektur

### Backend (FastAPI + Direct Dependency Injection)

**Komponenten:**
- `src/<module_name>/<module_name>/backend_webserver/auth/auth_service.py` - Authentication Service
- `src/<module_name>/<module_name>/backend_webserver/auth/router.py` - REST API Endpoints
- `src/<module_name>/<module_name>/backend_webserver/main_rest.py` - Integration in FastAPI App
- `src/<module_name>/<module_name>/container_injection.py` - Dependency Injection Container

**Authentifizierungs-Flow:**
```
User Login Request
    ↓
FastAPI Endpoint (auth/router.py)
    ↓
AuthService.authenticate_user()
    ↓
container_injection.get_component()  ← Direct DI (no IPC)
    ↓
component.internal_usermanager.authenticate()
    ↓
Return JWT Token
```

**Datenspeicherung:**
- Benutzer: Managed by InternalUserManager (in-memory + Redis persistence)
- Sessions: JWT tokens (stateless)
- Token-Gültigkeit: 8 Stunden

**Standard-Benutzer:**
- Benutzername: `admin`
- Passwort: `admin` (sollte nach Erst login geändert werden)

### Frontend (Vue 3 + Pinia)

**Komponenten:**
- `frontend/src/api/auth.api.ts` - API Client
- `frontend/src/store/auth.ts` - Pinia Store
- `frontend/src/features/auth/LoginView.vue` - Login-Seite
- `frontend/src/router/index.ts` - Route Guards

## API Endpoints

### POST `/api/auth/login`
Benutzer anmelden

**Request:**
```json
{
  "username": "admin",
  "password": "admin",
  "auth_mode": "local"  // oder "usermanager"
}
```

**Response:**
```json
{
  "success": true,
  "token": "session_token",
  "username": "admin",
  "auth_mode": "local",
  "message": "Login successful"
}
```

### POST `/api/auth/logout`
Benutzer abmelden

### GET `/api/auth/verify`
Token verifizieren

**Response:**
```json
{
  "success": true,
  "user": {
    "username": "admin",
    "token": "session_token",
    "module_id": "<module_name>"
  }
}
```

### POST `/api/auth/change-password`
Passwort ändern

**Request:**
```json
{
  "username": "admin",
  "old_password": "admin",
  "new_password": "new_secure_password"
}
```

### GET `/api/auth/check-usermanager`
Prüfen ob Usermanager verfügbar ist

**Response:**
```json
{
  "available": false,
  "message": "Usermanager not available"
}
```

### GET `/api/auth/users` (Admin only)
Alle lokalen Benutzer auflisten

### POST `/api/auth/users` (Admin only)
Neuen Benutzer erstellen

## Authentifizierungsmodi

### UserManager Authentication (Current Implementation)
- Verwendet InternalUserManager aus dem Component
- Zugriff via **Direct Dependency Injection** (`container_injection.get_component()`)
- **Keine IPC-Overhead** - direkte Methodenaufrufe im gleichen Prozess
- Zentrale Benutzerverwaltung innerhalb des Moduls
- Passwörter werden gehashed und sicher gespeichert

**Implementierung:**
```python
from ....container_injection import get_component

async def authenticate_user(username: str, password: str) -> tuple[bool, str]:
    # Direct access to InternalUserManager via DI
    component = get_component()
    success = await component.internal_usermanager.authenticate(username, password)
    
    if success:
        token = create_access_token(username)
        return True, token
    
    return False, ""
```

### Architektur-Migration (Februar 2026)
**Vorher** (gRPC über Unix Domain Sockets):
```
AuthService → UserManagerGrpcClient → UDS Socket → gRPC Server → InternalUserManager
              (IPC: ~3-5ms Latenz)
```

**Aktuell** (Direct Dependency Injection):
```
AuthService → container_injection.get_component() → component.internal_usermanager
              (Direct: ~0.01-0.1ms Latenz)
```

**Vorteile der neuen Architektur:**
- ⚡ **50x schneller**: Keine Socket-/Serialisierungs-Overhead
- 🎯 **Einfacher**: Keine gRPC-Proto-Generierung notwendig
- 🔧 **Wartbar**: Direkte Methodenaufrufe statt IPC-Abstraktion
- 🏗️ **Monolithisch**: Backend und Core im gleichen Prozess

## Frontend-Integration

### Route Guards
Alle Routen außer `/login` sind geschützt:

```typescript
{
  path: '/<module_name>/home',
  name: 'home',
  component: HomeView,
  meta: { requiresAuth: true }
}
```

### Auth Store
Zentraler Pinia Store für Authentifizierung:

```typescript
import { useAuthStore } from '@/store/auth'

const authStore = useAuthStore()

// Login
await authStore.login('admin', 'admin', 'local')

// Logout
await authStore.logout()

// Check auth status
await authStore.verifyAuth()
```

## Testing

### Feed-Simulation testen
```bash
cd /home/holgder/VOS2_WORKSPACE/modules/<module_name>_733256b82d6b48a48bc52b5ec73ebfff
./tools/test_feed_simulation.py
```

### Login testen
1. Navigate to `https://localhost/<module_name>/login`
2. Login with `admin` / `admin`
3. Check that feeds are displayed in HomeView and MonitoringView

## Migration zu anderen Modulen

### 1. Backend kopieren
```bash
# Copy auth package
cp -r src/<module_name>/<module_name>/backend_webserver/auth /path/to/other/module/src/<module_name>/<module_name>/backend_webserver/

# Copy container_injection.py if not exists
cp src/<module_name>/<module_name>/container_injection.py /path/to/other/module/src/<module_name>/<module_name>/

# Ensure Component has user_manager initialized
# In application/application.py:
async def initialize(self):
    self.user_manager = UserManager(self.entity)
    await self.user_manager.initialize()
    from ..container_injection import set_user_manager
    set_user_manager(self.user_manager)
```

### 2. Frontend kopieren
```bash
# Copy API client
cp frontend/src/api/auth.api.ts /path/to/other/module/frontend/src/api/

# Copy store
cp frontend/src/store/auth.ts /path/to/other/module/frontend/src/store/

# Copy login view
cp frontend/src/features/auth/LoginView.vue /path/to/other/module/frontend/src/features/auth/
```

### 3. Router aktualisieren
- Login-Route hinzufügen
- Route Guards implementieren
- Auth Store importieren

### 4. App.vue aktualisieren
- Logout-Button hinzufügen
- Benutzername anzeigen

## Sicherheitshinweise

1. **Standard-Passwort ändern:** Nach dem ersten Login das admin-Passwort ändern
2. **HTTPS verwenden:** Authentifizierung nur über HTTPS (Traefik)
3. **Token-Sicherheit:** Tokens werden als httpOnly Cookies gespeichert
4. **Session-Timeout:** Sessions laufen nach 8 Stunden ab

## Zukünftige Erweiterungen

1. **✅ Usermanager-Integration:** (Implementiert in Februar 2026)
   - Direct Dependency Injection via `container_injection`
   - InternalUserManager für zentrale Authentifizierung
   - Keine IPC-Overhead

2. **Erweiterte Features:**
   - Rollen und Berechtigungen
   - Zwei-Faktor-Authentifizierung
   - Passwort-Reset via Email
   - Session-Management (alle Sessions anzeigen/beenden)

3. **Audit Logging:**
   - Login-Versuche protokollieren
   - Passwortänderungen tracken
   - Admin-Aktionen loggen

4. **Multi-Modul Authentication:**
   - Shared UserManager für alle Module
   - Single Sign-On (SSO) über Module hinweg
   - Zentrale Token-Verwaltung

## Fehlerbehebung

### Login funktioniert nicht
1. Component Initialization prüfen:
   ```bash
   docker service logs vos2_ws_<module_name> -f | grep "Component initialized"
   ```
2. Container Injection prüfen:
   ```python
   from <module_name>.<module_name>.container_injection import is_initialized
   print(f"Container ready: {is_initialized()}")
   ```
3. Logs prüfen:
   ```bash
   docker service logs vos2_ws_<module_name> -f | grep auth
   ```

### HTTP 503 "Services not initialized yet"
- **Ursache**: FastAPI Endpoint wurde aufgerufen bevor Component initialisiert wurde
- **Lösung**: Warten bis ROS2 Initialisierung abgeschlossen (ca. 2-3 Minuten nach Container Start)
- **Debug**:
  ```bash
  # Im Container
  docker exec -it <container_id> python3 -c "from <module_name>.<module_name>.container_injection import is_initialized; print(is_initialized())"
  ```

### Token wird nicht gespeichert
- Browser-Cookies prüfen
- HTTPS-Verbindung sicherstellen
- SameSite Cookie-Settings prüfen

### AttributeError: 'NoneType' object has no attribute 'internal_usermanager'
- **Ursache**: `get_component()` gibt None zurück (nicht gesetzt)
- **Lösung**: Prüfen ob `container_injection.set_component(component)` in main.py aufgerufen wurde
- **Debug**: Siehe [Backend Webserver Architecture](./BACKEND_WEBSERVER_ARCHITECTURE.md#troubleshooting)

## Changelog

### 2026-02-13
- ✅ **Usermanager Integration via Direct DI**
- ✅ Migrated from gRPC to container_injection
- ✅ Removed IPC overhead (50x performance improvement)
- ✅ Moved auth module to backend_webserver/
- 📚 Updated documentation

### 2026-01-27
- ✅ Initial implementation
- ✅ Local authentication
- ✅ Frontend login page
- ✅ Route guards
- ✅ Token-based sessions
- ✅ Password management
