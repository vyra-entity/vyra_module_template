# Module Repository System - Dokumentation

[Siehe vollständige Dokumentation in module_installation_process.md]

## Quick Start

### 1. Repository Config erstellen/prüfen
Die Module-Liste liegt in:
```
/workspace/.module/module-repositories.json
```

### 2. Frontend aufrufen
```
https://localhost/v2_modulemanager/repository
```

### 3. Module installieren
- Module auswählen
- "Install Selected Modules" klicken
- Progress beobachten

### 4. API testen
```bash
# Liste Module
curl -k https://localhost/api/v2_modulemanager/repository/list | jq

# Installiere Modul
curl -k -X POST https://localhost/api/v2_modulemanager/repository/install \
  -H "Content-Type: application/json" \
  -d '{"module_ids": ["v2_dashboard"]}'

# Prüfe Status
curl -k https://localhost/api/v2_modulemanager/repository/install/status/v2_dashboard
```

## Architecture

```
Frontend (Vue.js)
    ↓ HTTP/JSON
Backend (FastAPI)
    ↓ Git Clone
GitHub Repository
    ↓ Copy to
/workspace/../{module_id}/
    ↓ Docker Compose
Container Start → Build → Success
```

Siehe `module_installation_process.md` für Details!
