# 🚀 Quick Start: ASGI/Uvicorn v2_dashboard

## 1️⃣ Base Image neu bauen

```bash
cd /home/holgder/VOS2_WORKSPACE
docker compose build vyra_base_image
```

## 2️⃣ Container starten

```bash
docker compose up -d v2_dashboard
```

## 3️⃣ Status prüfen

```bash
# Logs anzeigen
docker logs v2_dashboard 2>&1 | tail -50

# Uvicorn-Status prüfen
docker exec v2_dashboard ps aux | grep uvicorn

# Uvicorn-Logs
docker exec v2_dashboard tail -f /workspace/log/uvicorn/uvicorn_error.log
```

## 4️⃣ HTTPS testen

```bash
# Frontend (Nginx)
curl -k -I https://localhost:3000

# API über Nginx Proxy  
curl -k https://localhost:3000/api/status

# Sollte zurückgeben:
# {"service":"v2_dashboard","status":"running","version":"0.1.0"}
```

## 5️⃣ Async Features nutzen (Optional)

### Option A: Flask mit async Routes (begrenzt)
Flask unterstützt async nur teilweise. Besser:

### Option B: Auf Quart migrieren (Async Flask)

```bash
# In requirements.txt
quart==0.19.4
```

```python
# In minimal_rest.py
from quart import Quart
import asyncio

app = Quart(__name__)

@app.route('/api/async-status')
async def async_status():
    # Echter async Code
    await asyncio.sleep(0.1)
    return {"status": "running", "async": True}
```

### Option C: Auf FastAPI migrieren (Empfohlen)

```bash
# In requirements.txt
fastapi==0.104.1
uvicorn[standard]==0.30.6
```

```python
# In minimal_rest.py
from fastapi import FastAPI

asgi_app = FastAPI()

@asgi_app.get("/api/status")
async def get_status():
    return {"status": "running", "async": True}

# Wichtig: Export als asgi_app statt app
# asgi.py wird asgi_app automatisch erkennen
```

## 🔍 Troubleshooting

### Problem: Uvicorn startet nicht

```bash
# Prüfe Logs
docker logs v2_dashboard 2>&1 | grep -i error

# Prüfe ob asgiref installiert ist
docker exec v2_dashboard pip list | grep asgiref

# Manuelle Installation
docker exec v2_dashboard pip install uvicorn[standard] asgiref
```

### Problem: SSL-Fehler

```bash
# Zertifikate neu erstellen
docker exec v2_dashboard /workspace/tools/create_ssl_certificates.sh --name webserver
docker exec v2_dashboard /workspace/tools/create_ssl_certificates.sh --name frontend

# Container neu starten
docker compose restart v2_dashboard
```

### Problem: Fallback auf Gunicorn

Wenn asgi.py fehlt, startet automatisch Gunicorn mit wsgi.py

```bash
# Prüfen welcher Server läuft
docker exec v2_dashboard ps aux | grep -E "(uvicorn|gunicorn)"
```

## 📊 Performance-Check

```bash
# Requests/sec Test mit Apache Bench
ab -n 1000 -c 10 -k https://localhost:3000/api/status

# Oder mit wrk
wrk -t2 -c10 -d30s https://localhost:3000/api/status
```

## ✅ Erfolgs-Checkliste

- [ ] vyra_base_image neu gebaut
- [ ] v2_dashboard Container läuft
- [ ] Uvicorn Prozess läuft (nicht Gunicorn)
- [ ] HTTPS Frontend erreichbar (Port 3000)
- [ ] API über Nginx Proxy funktioniert
- [ ] Logs zeigen keine Fehler
- [ ] SSL-Zertifikate vorhanden
- [ ] (Optional) Async Features implementiert

## 📚 Weitere Infos

Siehe `ASGI_MIGRATION.md` für detaillierte Informationen.
