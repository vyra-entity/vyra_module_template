# VYRA Dashboard - Vue.js Frontend Integration

## ✅ Supervisord-basiertes Server-Management

Das VYRA Dashboard verwendet jetzt **Supervisord** für das gesamte Server-Management. Sowohl Frontend (Nginx) als auch Backend (Gunicorn) werden automatisch über Supervisord gestartet und verwaltet.

## 🚀 Server starten

### Production-Modus (Standard):
```bash
# Container starten - Supervisord übernimmt Server-Management
docker compose up v2_dashboard

# Oder direkt:
./vyra_entrypoint.sh
```

### Development-Modus:
```bash
# Environment-Variable setzen
export VYRA_DEV_MODE=true

# Container starten - Vue Dev Server wird automatisch gestartet
docker compose up v2_dashboard
```

## 🌐 Zugriff

### Production-Modus:
- **Frontend URL:** http://localhost:3000 (Nginx)
- **Backend API:** https://localhost:8443 (Gunicorn)

### Development-Modus:
- **Frontend URL:** http://localhost:3000 (Vue Dev Server mit Hot-Reload)
- **Backend API:** https://localhost:8443 (Gunicorn über Supervisord)

## 📁 Datei-Struktur

```
v2_dashboard/
├── supervisord.conf         # Supervisord Konfiguration
├── gunicorn.conf           # Gunicorn Konfiguration
├── wsgi.py                 # Dynamische WSGI-App (basiert auf MODULE_NAME)
├── nginx.conf              # Nginx Konfiguration
├── frontend/               # Vue.js Quellcode
│   ├── src/
│   │   ├── App.vue
│   │   ├── main.js
│   │   └── views/
│   ├── package.json
│   └── vite.config.js
└── src/v2_dashboard/v2_dashboard/application/
    ├── minimal_rest.py     # Flask-Backend
    ├── vue_dev_manager.py  # Vue Development Server Manager
    └── application.py      # Haupt-Anwendung (nur Vue Dev Server in DEV_MODE)
```

## 🔧 Architektur-Änderungen

1. **Supervisord-Management:** Alle Server werden über Supervisord verwaltet
2. **Dynamische WSGI:** `wsgi.py` lädt automatisch die richtige App basierend auf MODULE_NAME
3. **Environment-basiert:** VYRA_DEV_MODE, ENABLE_FRONTEND_WEBSERVER, ENABLE_BACKEND_WEBSERVER
4. **Vereinfachte application.py:** Startet nur Vue Dev Server in Development-Modus

## 🛠️ Technische Details

- **Process Management:** Supervisord für Nginx, Gunicorn, ROS2
- **Backend:** Flask mit dynamischem WSGI-Loading
- **Frontend:** Vue.js 3 mit Development/Production Modi
- **Development:** Vue Dev Server mit Hot-Reload und API-Proxy
- **Production:** Nginx + Gunicorn über Supervisord

## 📋 Service-Konfiguration

### Supervisord Services:
- **nginx:** Frontend Web Server (Port 3000)
- **gunicorn:** Backend API Server (Port 8443)
- **ros2_daemon:** ROS2 Daemon für Backend-Kommunikation

### Environment Variables:
- `VYRA_DEV_MODE=true` → Vue Dev Server statt Nginx
- `ENABLE_FRONTEND_WEBSERVER=true` → Nginx aktivieren
- `ENABLE_BACKEND_WEBSERVER=true` → Gunicorn aktivieren
- `MODULE_NAME=v2_dashboard` → Automatisches WSGI-Loading

## 📝 Logs und Debugging

### Supervisord Logs:
```bash
# Alle Services anzeigen
docker exec v2_dashboard supervisorctl status

# Service-spezifische Logs
docker exec v2_dashboard supervisorctl tail nginx
docker exec v2_dashboard supervisorctl tail gunicorn

# Live-Logs verfolgen
docker exec v2_dashboard supervisorctl tail -f nginx
```

### Development-Logs:
- Vue Dev Server: Läuft im Vordergrund mit Hot-Reload-Output
- Backend API: Über Supervisord (siehe oben)

Das Dashboard ist jetzt vollständig supervisord-basiert und bietet sowohl Development- als auch Production-Modi!
