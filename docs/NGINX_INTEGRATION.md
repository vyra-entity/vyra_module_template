# v2_dashboard Supervisord & Nginx Integration

## 🌐 Übersicht

Das v2_dashboard nutzt **Supervisord** für das vollständige Server-Management mit **Nginx als Frontend-Server** für optimale Performance und professionelle Architektur.

## 🎯 Verfügbare Modi

### 1. **Development Mode** (`VYRA_DEV_MODE=true`)
- **Frontend**: Vue.js Dev Server (Port 3000) - Managed durch application.py
- **Backend**: Gunicorn Flask API (Port 8443) - Managed durch Supervisord
- **Für**: Entwicklung mit Hot-Reload und schnellem Feedback

### 2. **Production Mode** (Default - `VYRA_DEV_MODE=false`)
- **Frontend**: Nginx Static Files (Port 3000) - Managed durch Supervisord
- **Backend**: Gunicorn Flask API (Port 8443) - Managed durch Supervisord
- **Für**: Production-Deployment mit optimaler Performance

## 🚀 Modi aktivieren

### Development-Modus:
```bash
export VYRA_DEV_MODE=true
export ENABLE_BACKEND_WEBSERVER=true
docker compose up v2_dashboard
```

### Production-Modus (Standard):
```bash
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=true
docker compose up v2_dashboard
```

## 📁 Supervisord-basierte Architektur

```
v2_dashboard/
├── supervisord.conf                     # Supervisord Hauptkonfiguration
├── nginx.conf                          # Nginx Konfiguration
├── gunicorn.conf                       # Gunicorn Konfiguration
├── wsgi.py                             # Dynamisches WSGI-Loading
├── src/v2_dashboard/application/
│   ├── vue_dev_manager.py              # Nur Vue Dev Server (Development)
│   └── application.py                  # Vereinfacht - nur Dev-Mode
└── frontend/
    ├── vite.config.js                  # Vue Build-Konfiguration
    └── package.json                    # Build-Scripts
```

## ⚙️ Supervisord-Services
Die Supervisord-Konfiguration verwaltet:

### Service-Programme:
- **nginx**: Frontend Web Server (Port 3000) - Conditional via `ENABLE_FRONTEND_WEBSERVER`
- **gunicorn**: Backend API Server (Port 8443) - Conditional via `ENABLE_BACKEND_WEBSERVER`
- **ros2_daemon**: ROS2 Backend für Service-Kommunikation

### Features:
- **Conditional Startup**: Services starten nur bei entsprechenden Environment Variables
- **Automatic Restart**: Bei Fehlern oder Crashes
- **Centralized Logging**: Alle Service-Logs über Supervisord
- **Process Management**: Start/Stop/Restart über supervisorctl

## 🔧 Nginx-Konfiguration Features

Die `nginx.conf` bietet:
- **Static File Serving**: Optimiert für Vue.js Build-Output
- **API Proxy**: `/api/*` → Backend (Port 8443)
- **SPA Support**: Fallback zu `index.html` für Vue Router
- **Gzip Compression**: Für bessere Performance
- **Security Headers**: Basis-Schutz
- **Caching**: Für Assets mit Hash-Namen

## 🏗️ Frontend Build

### Für Nginx optimierter Build:
```bash
cd frontend
npm run build
```

### Features:
- **Hash-basierte Asset-Namen** für Browser-Caching
- **Komprimierte Assets** (JS/CSS)
- **Optimierte Chunk-Aufteilung**
- **Production-optimierte Builds**

## 🏗️ Architektur-Diagramm

### Development-Modus:
```
Browser → Vue Dev Server (3000) ← Hot Reload + HMR
                     ↘ /api/* → Gunicorn (8443) Flask API ← Supervisord
```

### Production-Modus:
```
Browser → Nginx (3000) → Static Files (Vue Build) ← Supervisord
                     ↘ /api/* → Gunicorn (8443) Flask API ← Supervisord
```

## 📈 **Supervisord + Nginx Vorteile:**

- **Process Management**: Zentralisierte Kontrolle aller Services
- **~3x Performance** für statische Dateien vs. Flask
- **Professional Setup** mit separaten Services
- **Besseres Caching** und Compression
- **Skalierbare Architektur** mit Service-Isolation
- **Concurrent Connections** ohne Python GIL
- **Automatic Recovery** bei Service-Fehlern

## 🎛️ Supervisord-Steuerung

### Service-Management über supervisorctl:
```bash
# Status aller Services prüfen
docker exec v2_dashboard supervisorctl status

# Einzelne Services steuern
docker exec v2_dashboard supervisorctl start nginx
docker exec v2_dashboard supervisorctl stop gunicorn
docker exec v2_dashboard supervisorctl restart nginx

# Live-Logs verfolgen
docker exec v2_dashboard supervisorctl tail -f nginx
docker exec v2_dashboard supervisorctl tail -f gunicorn
```

### Environment-basierte Aktivierung:
```bash
# Production: Nginx + Gunicorn
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=true

# Development: Nur Gunicorn (Vue Dev Server läuft außerhalb Supervisord)
export VYRA_DEV_MODE=true
export ENABLE_BACKEND_WEBSERVER=true
```

## 🚦 Status & Monitoring

### Service Status prüfen:
```bash
# Supervisord Status
docker exec v2_dashboard supervisorctl status

# Health Checks
curl http://localhost:3000/api/status  # Nginx → Backend
curl https://localhost:8443/api/status # Direkter Backend-Zugriff
```

### Log-Monitoring:
```bash
# Service-Logs anzeigen
docker exec v2_dashboard supervisorctl tail nginx stdout
docker exec v2_dashboard supervisorctl tail gunicorn stderr

# Container-Logs
docker logs v2_dashboard
```

## 🔧 Troubleshooting

### Nginx startet nicht:
1. Prüfe `ENABLE_FRONTEND_WEBSERVER=true`
2. Prüfe Frontend Build: `npm run build` (in frontend/)
3. Prüfe nginx.conf Syntax: `nginx -t -c /workspace/nginx.conf`
4. Prüfe supervisorctl Status: `supervisorctl status nginx`

### Frontend nicht erreichbar:
1. Prüfe Port-Mapping: `3000:3000` in docker-compose.yml
2. Prüfe nginx Status: `supervisorctl status nginx`
3. Prüfe Service-Logs: `supervisorctl tail nginx`

### API Proxy funktioniert nicht:
1. Prüfe Backend läuft: `curl https://localhost:8443/api/status`
2. Prüfe Gunicorn Status: `supervisorctl status gunicorn`
3. Prüfe SSL-Konfiguration in nginx.conf
4. Prüfe CORS-Headers im Backend

### Development-Mode startet nicht:
1. Prüfe `VYRA_DEV_MODE=true`
2. Prüfe Frontend-Verzeichnis existiert: `/workspace/frontend/`
3. Prüfe package.json: `npm` ist installiert
4. Prüfe application.py Logs

## 🔄 Migration & Deployment

### Von direkter Server-Verwaltung zu Supervisord:

Das v2_dashboard nutzt jetzt **vollständig Supervisord** für Server-Management. Alle manuellen Start/Stop-Kommandos wurden durch Environment-basierte Supervisord-Steuerung ersetzt.

### Environment Variables:
```bash
# Vollständiger Stack
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=true

# Development-Modus (Vue Dev Server)
export VYRA_DEV_MODE=true
export ENABLE_BACKEND_WEBSERVER=true

# Nur Backend (API-Only)
export ENABLE_FRONTEND_WEBSERVER=false
export ENABLE_BACKEND_WEBSERVER=true
```

### Container neu starten:
```bash
docker compose restart v2_dashboard
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