# HTTPS Configuration für VYRA Dashboard

## 📋 Übersicht

Das VYRA Dashboard ist vollständig für HTTPS konfiguriert, sowohl für das Frontend (Nginx) als auch für das Backend (Flask/Gunicorn).

## 🔐 SSL-Zertifikate

### Verfügbare Zertifikate

1. **Frontend-Zertifikat** (`frontend.crt` / `frontend.key`)
   - Verwendet von: Nginx auf Port 3000
   - Zweck: HTTPS für Vue.js Frontend

2. **Backend-Zertifikat** (`webserver.crt` / `webserver.key`)
   - Verwendet von: Gunicorn auf Port 8443
   - Zweck: HTTPS für Flask API

### Zertifikate erstellen

Mit dem erweiterten `create_ssl_certificates.sh` Script können Sie benannte Zertifikate erstellen:

```bash
# Frontend-Zertifikat erstellen
sudo ./tools/create_ssl_certificates.sh --name frontend --domain localhost

# Backend-Zertifikat erstellen
sudo ./tools/create_ssl_certificates.sh --name webserver --domain localhost

# Custom-Zertifikat erstellen
sudo ./tools/create_ssl_certificates.sh --name api-gateway --domain api.vyra.local --days 730
```

### Script-Parameter

- `--name`: Name des Zertifikats (z.B. frontend, webserver, api-gateway)
- `--domain`: Domain-Name für das Zertifikat (Standard: localhost)
- `--days`: Gültigkeit in Tagen (Standard: 365)

## 🌐 Nginx HTTPS-Konfiguration

### Frontend HTTPS (Port 3000)

Die nginx.conf ist für HTTPS konfiguriert:

```nginx
server {
    listen 3000 ssl http2;
    server_name localhost;

    # SSL-Zertifikate
    ssl_certificate /workspace/ssl/frontend.crt;
    ssl_certificate_key /workspace/ssl/frontend.key;
    
    # SSL-Sicherheitseinstellungen
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers HIGH:!aNULL:!MD5;
    ssl_prefer_server_ciphers on;
    ssl_session_cache shared:SSL:10m;
    ssl_session_timeout 10m;
}
```

### Sicherheits-Header

```nginx
add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
add_header X-Frame-Options "SAMEORIGIN" always;
add_header X-Content-Type-Options "nosniff" always;
add_header X-XSS-Protection "1; mode=block" always;
add_header Referrer-Policy "strict-origin-when-cross-origin" always;
```

## 🔧 Backend HTTPS-Konfiguration

### Gunicorn SSL-Konfiguration

In `gunicorn.py`:

```python
# SSL-Konfiguration
certfile = '/workspace/ssl/webserver.crt'
keyfile = '/workspace/ssl/webserver.key'
ssl_version = ssl.PROTOCOL_TLS
```

### Flask-Konfiguration

Flask läuft hinter Gunicorn und muss keine eigene SSL-Konfiguration haben.

## 🐳 Docker-Container-Zugriff

### Port-Mapping

```yaml
ports:
  - "3000:3000"   # Frontend HTTPS
  - "8443:8443"   # Backend HTTPS
```

### Zugriff vom Browser

- **Frontend**: https://localhost:3000
- **Backend API**: https://localhost:8443/api/status

## ⚠️ Self-Signed Certificates

### Browser-Warnungen

Self-signed Zertifikate zeigen Sicherheitswarnungen im Browser:

- Chrome/Edge: "Your connection is not private" (NET::ERR_CERT_AUTHORITY_INVALID)
- Firefox: "Warning: Potential Security Risk Ahead"

### Warnungen umgehen

**Für Entwicklung:**

1. **Chrome/Edge**: Klicken Sie auf "Advanced" → "Proceed to localhost (unsafe)"
2. **Firefox**: Klicken Sie auf "Advanced" → "Accept the Risk and Continue"

**Für Testing mit curl:**

```bash
curl --insecure https://localhost:3000
# oder
curl -k https://localhost:3000
```

**Für Production:**

Verwenden Sie ein Zertifikat von einer vertrauenswürdigen CA (z.B. Let's Encrypt).

## 🔍 Zertifikat-Informationen anzeigen

```bash
# Zertifikat-Details anzeigen
openssl x509 -in /workspace/ssl/frontend.crt -text -noout

# Gültigkeit prüfen
openssl x509 -in /workspace/ssl/frontend.crt -noout -dates

# Zertifikat und Key zusammenführen (wenn benötigt)
cat /workspace/ssl/frontend.crt /workspace/ssl/frontend.key > /workspace/ssl/frontend.pem
```

## 🔄 Zertifikate erneuern

Zertifikate müssen vor Ablauf erneuert werden:

```bash
# Altes Zertifikat löschen
sudo rm /workspace/ssl/frontend.crt /workspace/ssl/frontend.key

# Neues Zertifikat erstellen
sudo ./tools/create_ssl_certificates.sh --name frontend --domain localhost --days 365

# Container neu starten
docker compose restart v2_dashboard
```

## 🛡️ Sicherheits-Best-Practices

### Produktionsumgebung

1. **Verwenden Sie CA-signierte Zertifikate** (z.B. Let's Encrypt)
2. **Aktivieren Sie HSTS** (bereits konfiguriert)
3. **Verwenden Sie starke Cipher Suites** (bereits konfiguriert)
4. **Setzen Sie Zertifikat-Permissions korrekt**:
   ```bash
   chmod 600 /workspace/ssl/*.key  # Private Keys
   chmod 644 /workspace/ssl/*.crt  # Certificates
   ```

### Development-Umgebung

1. **Self-signed Certificates sind OK**
2. **Fügen Sie das CA-Zertifikat zum Browser hinzu** (optional)
3. **Verwenden Sie --insecure für curl-Tests**

## 🔗 Nginx → Backend Proxy

Nginx leitet API-Requests an das HTTPS-Backend weiter:

```nginx
location /api/ {
    proxy_pass https://backend_api/;
    proxy_ssl_verify off;              # Für self-signed certificates
    proxy_ssl_session_reuse on;        # Performance-Optimierung
}
```

## 📊 Testing

### Test Frontend HTTPS

```bash
# HTTPS-Verbindung testen
curl -k https://localhost:3000

# Zertifikat-Details abrufen
openssl s_client -connect localhost:3000 -showcerts

# HTTP/2 Support prüfen
curl -I -k --http2 https://localhost:3000
```

### Test Backend HTTPS

```bash
# API-Endpunkt testen
curl -k https://localhost:8443/api/status

# Direkte Backend-Verbindung
curl -k https://localhost:8443/health
```

## 🚀 Deployment

### Container-Start

Die Zertifikate werden beim Container-Start automatisch geladen:

```bash
docker compose up -d v2_dashboard
```

### Zertifikat-Volumes

Stellen Sie sicher, dass das SSL-Verzeichnis als Volume gemountet ist:

```yaml
volumes:
  - ./ssl:/workspace/ssl:ro  # read-only für Sicherheit
```

## 📝 Troubleshooting

### Problem: "SSL certificate not found"

```bash
# Prüfen ob Zertifikate existieren
ls -la /workspace/ssl/

# Zertifikate neu erstellen
sudo ./tools/create_ssl_certificates.sh --name frontend
sudo ./tools/create_ssl_certificates.sh --name webserver
```

### Problem: "Permission denied"

```bash
# Permissions korrigieren
sudo chmod 600 /workspace/ssl/*.key
sudo chmod 644 /workspace/ssl/*.crt
sudo chown root:root /workspace/ssl/*
```

### Problem: "Certificate has expired"

```bash
# Zertifikat-Gültigkeit prüfen
openssl x509 -in /workspace/ssl/frontend.crt -noout -dates

# Neues Zertifikat erstellen
sudo ./tools/create_ssl_certificates.sh --name frontend --days 365
```

## 📚 Weitere Ressourcen

- [Nginx SSL Module Dokumentation](https://nginx.org/en/docs/http/ngx_http_ssl_module.html)
- [Mozilla SSL Configuration Generator](https://ssl-config.mozilla.org/)
- [Let's Encrypt für Production](https://letsencrypt.org/)
- [SSL Labs Server Test](https://www.ssllabs.com/ssltest/)
