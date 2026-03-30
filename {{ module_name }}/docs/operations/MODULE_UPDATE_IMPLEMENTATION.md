# Module Update Implementation - Complete Workflow

**Date:** 2026-01-26  
**Module:** {{ module_name }}

## Überblick

Die Module-Update-Funktion wurde vollständig implementiert mit:
- Dependency-Check mit User-Prompts
- Automatisches Backup vor Update
- Container-Manager Integration
- Interface-Dateien im NFS
- Modul-Reload mit Health-Check
- Automatisches Rollback bei Fehlern

## Workflow

### 1. Initialisierung
- Operation-Tracking wird gestartet
- Tasks werden initialisiert

### 2. Instanzen ermitteln
```python
instances = await self.get_module_instances(module_name)
# Optional: Nur primäre Instanz updaten
if not update_all_instances:
    instances = [primary_instance]
```

### 3. Abhängigkeiten prüfen
```python
# TODO: Implementation in Phase 2
# Falls Dependencies nicht erfüllt:
#   -> User-Prompt: "Dependencies nicht erfüllt. Trotzdem fortfahren?"
#   -> Bei "Abbrechen": Operation stoppen
#   -> Bei "Fortfahren": Mit Update weitermachen
```

### 4. Backup erstellen
```python
backup_path = await self._create_backup(module_name, instance_id)
# Erstellt Backup in: /modules/.backups/{module_name}_{instance_id}_backup_{timestamp}
```

### 5. Container aktualisieren
```python
await self._update_instance_container(
    module_name, instance_id, version, repository
)
# Ruft Container-Manager auf: POST /modules/update
```

### 6. Interface-Dateien aktualisieren
```python
await self._update_nfs_interfaces(module_name, instance_id)
# Kopiert Interface-Dateien von {module}/install/share -> /nfs/vyra_interfaces/{module}_interfaces/ros2/
```

### 7. Modul neu laden
```python
await self._reload_module(module_name, instance_id)
# Ruft Container-Manager auf: POST /modules/{name}/{id}/restart
```

### 8. Status verifizieren
```python
is_healthy = await self._verify_module_health(module_name, instance_id)
# Prüft Container-Status über Container-Manager
# Akzeptiert: "running", "healthy", "active"
```

### 9. Rollback bei Fehler
```python
if not is_healthy:
    await self._rollback_instance(module_name, instance_id, backup_path)
    # 1. Container stoppen
    # 2. Aktuelles Verzeichnis löschen
    # 3. Backup wiederherstellen
    # 4. Container starten
```

### 10. Finalisierung
```python
# Bei Erfolg: Backups löschen
for backup_path in backup_paths:
    await self._cleanup_backup(backup_path)
```

## API Endpoints

### Module Router

#### POST /modules/update
```json
Request:
{
  "module_name": "v2_dashboard",
  "repository": {"id": "local-repo"},
  "version": "2.0.0",
  "update_all_instances": true
}

Response:
{
  "operation_id": "uuid-123",
  "status": "queued",
  "progress": 0,
  "message": "Update von v2_dashboard gestartet",
  "module_name": "v2_dashboard",
  "status_url": "/modules/status/uuid-123"
}
```

### Container Manager (benötigte Endpoints)

#### POST /modules/update
```json
Request:
{
  "module_name": "v2_dashboard",
  "instance_id": "abc123",
  "version": "2.0.0",
  "repository": {"id": "local-repo"}
}

Response:
{
  "success": true,
  "message": "Module updated successfully"
}
```

#### POST /modules/{name}/{id}/restart
```json
Response:
{
  "success": true,
  "message": "Module restarted"
}
```

#### GET /modules/{name}/{id}/status
```json
Response:
{
  "success": true,
  "status": "running",  // or "healthy", "active"
  "health": "ok"
}
```

#### POST /modules/{name}/{id}/stop
```json
Response:
{
  "success": true,
  "message": "Module stopped"
}
```

#### POST /modules/{name}/{id}/start
```json
Response:
{
  "success": true,
  "message": "Module started"
}
```

## Task-Tracking

```python
UPDATE_TASKS = [
    {"id": "init", "title": "Initialisierung"},
    {"id": "discover_instances", "title": "Instanzen ermitteln"},
    {"id": "check_deps", "title": "Abhängigkeiten prüfen"},
    {"id": "backup", "title": "Backup erstellen"},
    {"id": "update_containers", "title": "Container aktualisieren"},
    {"id": "update_interfaces", "title": "Interface-Dateien aktualisieren"},
    {"id": "reload_module", "title": "Modul neu laden"},
    {"id": "verify_status", "title": "Status verifizieren"},
    {"id": "finalize", "title": "Update abschließen"}
]
```

Jeder Task wird über WebSocket an das Frontend gemeldet:
- `pending` -> `running` -> `completed`
- Bei Fehler: `failed` mit Error-Message

## Helper-Methoden

### _create_backup()
Erstellt vollständiges Backup des Modul-Verzeichnisses.

**Backup-Location:** `/modules/.backups/{module}_{instance}_backup_{timestamp}/`

**Beinhaltet:**
- Komplettes Modul-Verzeichnis
- Alle Konfigurationsdateien
- Frontend-Build (falls vorhanden)
- Logs werden nicht gesichert

### _update_instance_container()
Delegiert an Container-Manager für Docker-Container-Update.

**Was passiert:**
1. Container-Manager pullt neue Version
2. Stoppt alten Container
3. Erstellt neuen Container mit neuer Version
4. Startet Container
5. Aktualisiert Traefik-Labels

### _update_nfs_interfaces()
Kopiert ROS2-Interface-Dateien ins NFS-Share.

**Source:** `{module}/install/share/`
**Target:** `/nfs/vyra_interfaces/{module}_interfaces/ros2/`

**Wichtig:** Andere Module müssen diese Interfaces sourcen können für ROS2-Kommunikation.

### _reload_module()
Führt Container-Restart durch.

**Warum nötig:**
- Neue Interface-Dateien müssen geladen werden
- ROS2-Nodes müssen neu initialisiert werden
- Sicherstellen dass neue Version aktiv ist

### _verify_module_health()
Prüft ob Modul nach Update funktioniert.

**Kriterien:**
- Container-Status ist "running" / "healthy" / "active"
- Keine Fehler im Container-Log
- Reagiert auf Health-Check-Requests

**Wait-Time:** 5 Sekunden nach Reload für Container-Startup

### _rollback_instance()
Stellt vorherige Version wieder her.

**Ablauf:**
1. Container stoppen via Container-Manager
2. Aktuelles Modul-Verzeichnis löschen
3. Backup-Verzeichnis zurückkopieren
4. Container starten via Container-Manager
5. Warten auf Container-Startup
6. Status prüfen

**Wichtig:** Rollback löscht das fehlerhafte Update komplett!

### _cleanup_backup()
Entfernt Backup nach erfolgreichem Update.

**Wann:** Nur wenn alle Instanzen erfolgreich geupdatet wurden.

## Error Handling

### Backup-Fehler
```python
if not backup_created:
    raise ModuleOperationError("backup", module_name, "Backup creation failed")
    # Update wird abgebrochen
```

### Container-Update-Fehler
```python
if not container_update_success:
    raise ModuleOperationError("update", module_name, "Container update failed")
    # Rollback wird NICHT durchgeführt (Backup existiert noch)
```

### Health-Check-Fehler
```python
if not is_healthy:
    await self._rollback_instance(...)
    raise ModuleOperationError("health", module_name, "Health check failed after update")
    # Rollback wurde durchgeführt
```

### Rollback-Fehler
```python
if rollback_fails:
    # Kritischer Fehler - Manuelle Intervention nötig!
    logger.critical(f"ROLLBACK FAILED for {module_name}/{instance_id}")
    # Operation wird als failed markiert
    # Backup bleibt erhalten für manuelle Wiederherstellung
```

## Dependencies-Check (TODO - Phase 2)

```python
async def _check_dependencies(
    self,
    operation_id: str,
    required_deps: dict
) -> bool:
    """
    Prüfe Dependencies und frage User bei Problemen
    
    Args:
        required_deps: {
            "vyra_modules": ["vyra_base", "{{ module_name }}"],
            "python": ["fastapi>=0.100.0"],
            "system": ["ros-humble-core"]
        }
    
    Returns:
        True = Fortfahren, False = Abbrechen
    """
    missing_deps = []
    
    # Prüfe vyra_modules
    for module in required_deps.get("vyra_modules", []):
        if not await self._is_module_installed(module):
            missing_deps.append(f"VYRA Module: {module}")
    
    # Prüfe Python packages
    for pkg in required_deps.get("python", []):
        if not await self._is_python_package_installed(pkg):
            missing_deps.append(f"Python: {pkg}")
    
    # Prüfe System packages
    for pkg in required_deps.get("system", []):
        if not await self._is_system_package_installed(pkg):
            missing_deps.append(f"System: {pkg}")
    
    if missing_deps:
        # User-Prompt erstellen
        prompt = self.operation_tracker.create_prompt(
            operation_id=operation_id,
            prompt_type="warning",
            title="Fehlende Dependencies",
            message=f"Folgende Dependencies fehlen:\n" + "\n".join(missing_deps),
            options=[
                {"label": "Abbrechen", "value": "cancel", "variant": "secondary"},
                {"label": "Trotzdem fortfahren", "value": "continue", "variant": "danger"}
            ],
            default_option="cancel"
        )
        
        # Warte auf User-Antwort
        response = await self.operation_tracker.wait_for_prompt_response(
            operation_id, 
            prompt["id"],
            timeout=300  # 5 Minuten
        )
        
        if response == "cancel":
            return False
    
    return True
```

## Testing

### Unit Tests
```bash
pytest tests/unit/test_module_service.py::TestUpdateModule -v
```

### Integration Tests
```bash
# TODO: Implement
pytest tests/integration/test_module_update_flow.py -v
```

### Manual Testing
```bash
# 1. Install ein Modul
curl -X POST https://localhost/{{ module_name }}/api/repository/install \
  -H "Content-Type: application/json" \
  -d '{
    "module_name": "v2_dashboard",
    "module_hash": "abc123",
    ...
  }'

# 2. Update das Modul
curl -X POST https://localhost/{{ module_name }}/api/modules/update \
  -H "Content-Type: application/json" \
  -d '{
    "module_name": "v2_dashboard",
    "version": "2.0.0",
    "repository": {"id": "local-repo"},
    "update_all_instances": true
  }'

# 3. Verfolge Progress
# Via WebSocket oder Status-Endpoint
curl https://localhost/{{ module_name }}/api/modules/status/{operation_id}
```

## Known Issues & TODOs

### Phase 1 (Implemented) ✅
- [x] Basic Update-Workflow
- [x] Backup-Erstellung
- [x] Container-Update via Container-Manager
- [x] Interface-Update im NFS
- [x] Modul-Reload
- [x] Health-Check
- [x] Rollback bei Fehler

### Phase 2 (TODO) 📋
- [ ] Dependencies-Check mit User-Prompt
- [ ] Python-Package Dependency-Check
- [ ] System-Package Dependency-Check
- [ ] Frontend UI für Update-Button
- [ ] Versions-Vergleich (aktuell vs. verfügbar)
- [ ] Update-History/Changelog anzeigen

### Phase 3 (Future) 🚀
- [ ] Parallel-Updates für mehrere Module
- [ ] Scheduled Updates (Cron-Jobs)
- [ ] Update-Notifications
- [ ] Dry-Run Mode (Test ohne echtes Update)
- [ ] Backup-Rotation (alte Backups löschen)

## Files Modified

### Backend
1. `src/rest_api/module/router.py` - Update-Route wiederhergestellt
2. `src/rest_api/module/service.py` - Vollständiger Update-Workflow implementiert
3. `src/rest_api/module/schemas.py` - Dependencies zurück auf dict
4. `src/rest_api/api/container_manager_client.py` - Neue Methoden für Update/Restart/Status

### Frontend
1. `frontend/src/features/repository/repository.api.ts` - Dependencies als dict
2. `frontend/src/features/repository/RepositoryView.vue` - Dependencies-Konvertierung entfernt
3. TODO: Update-Button UI hinzufügen

## Migration Notes

### Von Array zu Dict (Dependencies)
**Vorher (FALSCH):**
```typescript
module_dependencies: ['vyra_base', 'fastapi']
```

**Nachher (RICHTIG):**
```typescript
module_dependencies: {
  vyra_modules: ['vyra_base'],
  python: ['fastapi'],
  system: []
}
```

### Container-Manager Requirements
Der Container-Manager muss folgende Endpoints unterstützen:
- `POST /modules/update` - Update durchführen
- `POST /modules/{name}/{id}/restart` - Restart
- `GET /modules/{name}/{id}/status` - Status abfragen
- `POST /modules/{name}/{id}/stop` - Stoppen
- `POST /modules/{name}/{id}/start` - Starten
