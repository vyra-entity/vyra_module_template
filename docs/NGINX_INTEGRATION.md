# v2_dashboard Nginx Integration

## 🌐 Übersicht

Das v2_dashboard nutzt **Nginx als alleinigen Frontend-Server** für optimale Performance und professionelle Architektur.

## 🎯 Verfügbare Modi

### 1. **Development Mode** (`VYRA_DEV_MODE=true`)
- **Frontend**: Vue.js Dev Server (Port 3000)
- **Backend**: Gunicorn Flask API (Port 8443)
- **Für**: Entwicklung mit Hot-Reload und schnellem Feedback

### 2. **Production Mode** (Default - `VYRA_DEV_MODE=false`)
- **Frontend**: Nginx Static Files (Port 3000)
- **Backend**: Gunicorn Flask API (Port 8443)
- **Für**: Production-Deployment mit optimaler Performance

## 🚀 Modi aktivieren

### Development-Modus:
```bash
export VYRA_DEV_MODE=true
docker-compose up v2_dashboard
```

### Production-Modus (Standard):
```bash
export VYRA_DEV_MODE=false  # oder unset
docker-compose up v2_dashboard
```

## 📁 Neue Dateien

```
v2_dashboard/
├── nginx.conf                           # Nginx Konfiguration
├── src/v2_dashboard/application/
│   ├── nginx_manager.py                 # Nginx Process Manager
│   ├── supervisor_manager.py            # Supervisord Integration
│   └── vue_dev_manager.py              # Erweitert für Nginx
└── frontend/
    ├── vite.config.js                   # Nginx-optimiert
    └── package.json                     # Build-Scripts erweitert
```

## ⚙️ Nginx-Konfiguration

Die `nginx.conf` bietet:
- **Static File Serving**: Optimiert für Vue.js Build
- **API Proxy**: `/api/*` → Backend (Port 8443)
- **SPA Support**: Fallback zu `index.html`
- **Gzip Compression**: Für bessere Performance
- **Security Headers**: Basis-Schutz
- **Caching**: Für Assets mit Hash-Namen

## 🔧 Frontend Build

### Für Nginx optimierter Build:
```bash
cd frontend
npm run build:nginx
```

### Features:
- **Hash-basierte Asset-Namen** für Caching
- **Komprimierte Assets** (JS/CSS)
- **Optimierte Chunk-Aufteilung**
- **Production-optimierte Builds**

## 🏗️ Architektur

### Development-Modus:
```
Browser → Vue Dev Server (3000) ← Hot Reload
                     ↘ /api/* → Gunicorn (8443) Flask API
```

### Production-Modus:
```
Browser → Nginx (3000) → Static Files (Vue Build)
                     ↘ /api/* → Gunicorn (8443) Flask API
```

## 📈 **Nginx-Vorteile gegenüber Flask Static Serving:**

- **~3x Performance** für statische Dateien
- **Professional Setup** mit separaten Services  
- **Besseres Caching** und Compression
- **Skalierbare Architektur**
- **Concurrent Connections** ohne Python GIL

## 🎛️ Supervisord Integration

Das vyra_base_image wurde erweitert:

### Neue Programme:
- **nginx**: Conditional über `VYRA_ENABLE_NGINX`
- **gunicorn**: Erweitert für Module-spezifische Konfiguration

### Management:
```python
from .supervisor_manager import SupervisorServiceManager

manager = SupervisorServiceManager()
manager.enable_nginx("/workspace/nginx.conf")
manager.enable_gunicorn("my_app:app")
```

## 🚦 Status & Monitoring

### Service Status prüfen:
```python
status = manager.get_all_services_status()
print(status["nginx"]["running"])  # True/False
```

### Health Check:
- **Nginx**: `GET /nginx-health`
- **Backend**: `GET /api/health`

## 🔧 Troubleshooting

### Nginx startet nicht:
1. Prüfe `VYRA_ENABLE_NGINX=true`
2. Prüfe Frontend Build: `npm run build:nginx`
3. Prüfe nginx.conf Syntax: `nginx -t -c /workspace/nginx.conf`

### Frontend nicht erreichbar:
1. Prüfe Port-Mapping: `3000:3000`
2. Prüfe nginx Status: `supervisorctl status nginx`
3. Prüfe Logs: `/var/log/nginx/v2_dashboard_error.log`

### API Proxy funktioniert nicht:
1. Prüfe Backend läuft: `curl https://localhost:8443/api/health`
2. Prüfe SSL-Konfiguration in nginx.conf
3. Prüfe CORS-Headers

## 🔄 Migration von altem Setup

### Von Flask-integriertem Frontend zu Nginx:

Das v2_dashboard nutzt jetzt **standardmäßig Nginx** für das Frontend. Keine Migration nötig - der Production-Modus ist automatisch Nginx.

### Environment Variables:
```bash
# Development (Vue Dev Server)
export VYRA_DEV_MODE=true

# Production (Nginx) - Standard
export VYRA_DEV_MODE=false  # oder unset
```

### Container neu starten:
```bash
docker-compose restart v2_dashboard
```

## 📈 Performance-Vorteile

### Nginx vs. Flask Static Serving:
- **~3x schneller** für statische Dateien
- **Besseres Caching** mit ETags/Last-Modified
- **Gzip Compression** standardmäßig
- **Concurrent Connections** ohne Python GIL
- **Memory-efficient** für große Assets

### Monitoring:
- **Access Logs**: `/var/log/nginx/v2_dashboard_access.log`
- **Error Logs**: `/var/log/nginx/v2_dashboard_error.log`
- **Performance**: `curl -w "@curl-format.txt" http://localhost:3000`