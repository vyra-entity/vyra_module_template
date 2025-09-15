# VYRA Dashboard - Vue.js Frontend Integration

## ✅ Problem gelöst: Gunicorn Frontend-Server

Das Problem mit dem Gunicorn-Start wurde erfolgreich behoben. Der Server läuft jetzt auf **Port 8444** mit dem korrekten Modul-Pfad.

## 🚀 Frontend starten

### Einfache Methode:
```bash
cd /home/holgder/VOS2_WORKSPACE/modules/v2_dashboard
python3 start_frontend.py
```

### Im Hintergrund:
```bash
cd /home/holgder/VOS2_WORKSPACE/modules/v2_dashboard
nohup python3 start_frontend.py > frontend.log 2>&1 &
```

## 🌐 Zugriff

- **Frontend URL:** http://localhost:8444
- **API Endpoints:**
  - `GET /` - Haupt-Dashboard
  - `GET /api/modules` - Module-Liste
  - `GET /api/status` - System-Status

## 📁 Datei-Struktur

```
v2_dashboard/
├── minimal_rest.py          # Flask-Backend (kopiert für direkten Zugriff)
├── start_frontend.py        # Einfaches Start-Skript
├── frontend/               # Vue.js Quellcode
│   ├── src/
│   │   ├── App.vue
│   │   ├── main.js
│   │   └── views/
│   ├── package.json
│   └── vite.config.js
└── src/v2_dashboard/v2_dashboard/application/
    ├── minimal_rest.py     # Original Flask-Backend
    ├── gunicorn_manager.py # Gunicorn Manager
    └── application.py      # Haupt-Anwendung
```

## 🔧 Änderungen

1. **Port geändert:** 8443 → 8444 (Port 8443 war belegt)
2. **Modul-Pfad:** `v2_dashboard.application.minimal_rest:app` → `minimal_rest:app`
3. **Workspace-Pfad:** Absoluter Pfad zu `/home/holgder/VOS2_WORKSPACE/modules/v2_dashboard`
4. **Start-Skript:** Einfaches `start_frontend.py` für direkte Nutzung

## 🛠️ Technische Details

- **Backend:** Flask mit Gunicorn WSGI-Server
- **Frontend:** Vue.js 3 mit SPA-Routing
- **API:** RESTful endpoints für Modul-Management
- **Build:** Vite für Frontend-Entwicklung und -Build

## 📝 Logs

Logs werden geschrieben nach:
- `frontend.log` (wenn im Hintergrund gestartet)
- `log/gunicorn.log` (Gunicorn-spezifische Logs)

Das Frontend ist jetzt vollständig funktionsfähig und kann über den einfachen Start-Befehl gestartet werden!
