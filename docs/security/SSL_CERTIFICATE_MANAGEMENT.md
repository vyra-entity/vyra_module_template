# SSL Certificate Auto-Management

The VYRA Dashboard automatically manages SSL certificates for secure HTTPS communication.

## 🔐 Automatic Certificate Creation

When `ENABLE_BACKEND_WEBSERVER=true` is set, the container startup process automatically:

1. **Checks for existing certificates** in `/workspace/storage/certificates/`
2. **Validates certificate expiration** (regenerates if <24h remaining)
3. **Creates new certificates** if none exist
4. **Sets secure permissions** (600 for private key, 644 for certificate)

## 📁 Certificate Storage

SSL certificates are stored in:
```
/workspace/storage/certificates/
├── webserver.crt    # SSL Certificate (644 permissions)
└── webserver.key    # Private Key (600 permissions)
```

## 🛠️ Manual Certificate Management

### Create certificates manually:
```bash
# Default settings (localhost, 365 days)
./tools/create_ssl_certificates.sh

# Custom domain
./tools/create_ssl_certificates.sh --domain vyra-dashboard.local

# Extended validity
./tools/create_ssl_certificates.sh --domain localhost --days 3650
```

### Check certificate details:
```bash
# View certificate information
openssl x509 -in storage/certificates/webserver.crt -text -noout

# Check expiration
openssl x509 -in storage/certificates/webserver.crt -enddate -noout
```

## 🚀 Container Startup Behavior

| Scenario | Action |
|----------|--------|
| `ENABLE_BACKEND_WEBSERVER=false` | ⏭️ Skip SSL certificate check |
| Certificates exist and valid | ✅ Use existing certificates |
| Certificates expire <24h | 🔄 Regenerate automatically |
| No certificates found | 🔨 Create new certificates |
| Certificate creation fails | ⚠️ Continue in HTTP mode |

## 🔍 Troubleshooting

### Container logs show SSL errors:
```bash
# Check if certificates exist
ls -la storage/certificates/

# Manually recreate certificates
./tools/create_ssl_certificates.sh

# Restart container
docker compose restart v2_dashboard
```

### Custom SSL certificates:
Replace the auto-generated certificates with your own:
```bash
# Copy your certificates
cp your-cert.crt storage/certificates/webserver.crt
cp your-key.key storage/certificates/webserver.key

# Set correct permissions
chmod 644 storage/certificates/webserver.crt
chmod 600 storage/certificates/webserver.key
```

## 🌐 HTTPS Access

After successful certificate setup:
- **Frontend**: http://localhost:3000 (Nginx proxy to backend)
- **Backend API**: https://localhost:8443 (Direct HTTPS access)

> **Note**: Self-signed certificates will show browser security warnings. For production, use certificates from a trusted CA.
