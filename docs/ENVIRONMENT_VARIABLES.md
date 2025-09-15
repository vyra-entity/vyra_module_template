# Environment Variables für v2_dashboard

## 🎛️ Webserver-Steuerung

Das v2_dashboard nutzt Environment Variables zur flexiblen Steuerung der Webserver-Services:

### **ENABLE_FRONTEND_WEBSERVER** (Nginx)
```bash
export ENABLE_FRONTEND_WEBSERVER=true   # Nginx für statische Dateien aktivieren
export ENABLE_FRONTEND_WEBSERVER=false  # Nginx deaktivieren
```

### **ENABLE_BACKEND_WEBSERVER** (Gunicorn)
```bash
export ENABLE_BACKEND_WEBSERVER=true    # Gunicorn Flask API aktivieren
export ENABLE_BACKEND_WEBSERVER=false   # Gunicorn deaktivieren
```

## 🚀 Anwendungsfälle

### **Vollständiger Stack (Standard)**
```bash
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=true
export VYRA_DEV_MODE=false
# → Nginx (Port 3000) + Gunicorn (Port 8443)
```

### **Nur Backend (API-Only)**
```bash
export ENABLE_FRONTEND_WEBSERVER=false
export ENABLE_BACKEND_WEBSERVER=true
# → Nur Gunicorn (Port 8443)
```

### **Nur Frontend (Static-Only)**
```bash
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=false
# → Nur Nginx (Port 3000)
```

### **Development-Modus**
```bash
export VYRA_DEV_MODE=true
export ENABLE_BACKEND_WEBSERVER=true
# → Vue Dev Server (Port 3000) + Gunicorn (Port 8443)
# ENABLE_FRONTEND_WEBSERVER wird ignoriert im Dev-Modus
```

### **Microservices-Setup**
```bash
# Container 1: Nur Frontend
export ENABLE_FRONTEND_WEBSERVER=true
export ENABLE_BACKEND_WEBSERVER=false

# Container 2: Nur Backend
export ENABLE_FRONTEND_WEBSERVER=false
export ENABLE_BACKEND_WEBSERVER=true
```

## ⚙️ Implementierung

### **vyra_entrypoint.sh Logik:**
```bash
# Nginx (Frontend) aktivieren
if [ "$ENABLE_FRONTEND_WEBSERVER" = "true" ]; then
    sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' supervisord.conf
fi

# Gunicorn (Backend) aktivieren  
if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
    sed -i '/\[program:gunicorn\]/,/^\[/ s/autostart=false/autostart=true/' supervisord.conf
fi
```

### **Supervisord Integration:**
- **Alle Services** starten mit `autostart=false`
- **vyra_entrypoint.sh** aktiviert selektiv basierend auf Environment Variables
- **Graceful Startup**: Services werden nur bei Bedarf gestartet

## 🎯 Vorteile

### **Flexibilität:**
- **Modulare Architektur**: Frontend und Backend separat steuerbar
- **Resource-Optimierung**: Nur benötigte Services laufen
- **Container-Orchestrierung**: Perfekt für Docker Compose/Kubernetes

### **Development-Workflow:**
- **Schnelle Iteration**: Nur Backend für API-Tests
- **Frontend-Design**: Nur Frontend für UI-Development
- **Full-Stack**: Beide Services für Integration

### **Production-Deployment:**
- **Load Balancing**: Frontend und Backend auf verschiedene Container/Nodes
- **Scaling**: Unterschiedliche Skalierung für Frontend vs. Backend
- **Maintenance**: Services unabhängig restarten/updaten

## 📋 Beispiel docker-compose.yml

```yaml
version: '3.8'
services:
  # Full-Stack Container
  v2_dashboard_full:
    environment:
      - ENABLE_FRONTEND_WEBSERVER=true
      - ENABLE_BACKEND_WEBSERVER=true
      - VYRA_DEV_MODE=false
    ports:
      - "3000:3000"  # Frontend
      - "8443:8443"  # Backend
  
  # Nur Frontend
  v2_dashboard_frontend:
    environment:
      - ENABLE_FRONTEND_WEBSERVER=true
      - ENABLE_BACKEND_WEBSERVER=false
    ports:
      - "3000:3000"
  
  # Nur Backend  
  v2_dashboard_backend:
    environment:
      - ENABLE_FRONTEND_WEBSERVER=false
      - ENABLE_BACKEND_WEBSERVER=true
    ports:
      - "8443:8443"
```

## 🔧 Troubleshooting

### **Service startet nicht:**
```bash
# Prüfe Environment Variables
echo $ENABLE_FRONTEND_WEBSERVER
echo $ENABLE_BACKEND_WEBSERVER

# Prüfe supervisord Status
docker exec container_name supervisorctl status

# Prüfe Logs
docker exec container_name supervisorctl tail nginx
docker exec container_name supervisorctl tail gunicorn
```

### **Port-Konflikte:**
- **Frontend**: Port 3000 (Nginx oder Vue Dev Server)
- **Backend**: Port 8443 (Gunicorn)
- **Stelle sicher**, dass Ports nicht doppelt verwendet werden

### **Service-Dependencies:**
- **Frontend** benötigt Backend für `/api/*` Proxying
- **Backend** kann eigenständig laufen
- **Development-Modus** überschreibt Frontend-Konfiguration