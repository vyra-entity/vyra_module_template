# Uvicorn Configuration File
# Python configuration format
# This file is loaded by Uvicorn via --config parameter or used programmatically
#
# Compatible with:
# - FastAPI (native ASGI) ✅ RECOMMENDED
# - Flask (via asgiref wrapper)
# - Starlette, Quart, and other ASGI frameworks

import os
import ssl
import logging

# =============================================================================
# Server Configuration
# =============================================================================

# Bind address and port
host = "0.0.0.0"
port = 8443

# Worker processes (for production)
# Note: Uvicorn workers use the --workers flag, not configured here
# Set via command line: uvicorn --workers 4

# =============================================================================
# Logging Configuration
# =============================================================================

# Log directory
log_dir = "/workspace/log/uvicorn"
os.makedirs(log_dir, exist_ok=True)

# Access log configuration
access_log = True
log_config = {
    "version": 1,
    "disable_existing_loggers": False,
    "formatters": {
        "default": {
            "format": "%(asctime)s - %(name)s - %(levelname)s - %(message)s",
        },
        "access": {
            "format": '%(asctime)s - %(client_addr)s - "%(request_line)s" %(status_code)s',
        },
    },
    "handlers": {
        "default": {
            "formatter": "default",
            "class": "logging.FileHandler",
            "filename": f"{log_dir}/uvicorn_error.log",
        },
        "access": {
            "formatter": "access",
            "class": "logging.FileHandler",
            "filename": f"{log_dir}/uvicorn_access.log",
        },
    },
    "loggers": {
        "uvicorn": {"handlers": ["default"], "level": "INFO"},
        "uvicorn.error": {"level": "INFO"},
        "uvicorn.access": {"handlers": ["access"], "level": "INFO", "propagate": False},
    },
}

# =============================================================================
# SSL/TLS Configuration
# =============================================================================

cert_path = "/workspace/storage/certificates/webserver.crt"
key_path = "/workspace/storage/certificates/webserver.key"

# Check if SSL certificates exist
if os.path.exists(cert_path) and os.path.exists(key_path):
    print(f"🔒 SSL certificates found - enabling HTTPS")
    print(f"   Certificate: {cert_path}")
    print(f"   Private Key: {key_path}")
    
    # Enable SSL
    ssl_certfile = cert_path
    ssl_keyfile = key_path
    
    # SSL/TLS versions (TLS 1.2+)
    ssl_version = ssl.PROTOCOL_TLS_SERVER
    
    # SSL Ciphers (modern, secure)
    ssl_ciphers = "ECDHE+AESGCM:ECDHE+CHACHA20:DHE+AESGCM:DHE+CHACHA20:!aNULL:!MD5:!DSS"
    
    # SSL Certificate requirements
    ssl_cert_reqs = ssl.CERT_NONE  # For self-signed certificates
    
    # SSL CA certificates (optional, for client certificate validation)
    # ssl_ca_certs = "/path/to/ca-bundle.crt"
    
    print("✅ Uvicorn will start with HTTPS enabled (TLS 1.2+)")
else:
    print("⚠️ SSL certificates not found - starting in HTTP mode")
    print(f"   Expected certificate: {cert_path}")
    print(f"   Expected key: {key_path}")
    print("   Run './tools/create_ssl_certificates.sh --name webserver' to create certificates")
    
    # No SSL configuration
    ssl_certfile = None
    ssl_keyfile = None

# =============================================================================
# Performance & Tuning
# =============================================================================

# Timeout for graceful shutdown
timeout_graceful_shutdown = 30

# Limit request line size (security)
limit_max_requests = 1000

# Backlog for connections
backlog = 2048

# Keep-alive timeout
timeout_keep_alive = 5

# =============================================================================
# Development Settings
# =============================================================================

# Reload on code changes (only for development)
reload = False

# Directories to watch for reload
# reload_dirs = ["/workspace/src"]

# =============================================================================
# Headers
# =============================================================================

# Server header (set to False to hide Uvicorn version)
server_header = True

# Date header
date_header = True

# =============================================================================
# WebSocket Configuration
# =============================================================================

# WebSocket ping interval (seconds)
ws_ping_interval = 20.0

# WebSocket ping timeout (seconds)
ws_ping_timeout = 20.0

# Per-message deflate for WebSocket
ws_per_message_deflate = True

# Maximum WebSocket message size (bytes)
ws_max_size = 16 * 1024 * 1024  # 16 MB

# =============================================================================
# Application Interface
# =============================================================================

# Interface type (auto-detect)
interface = "asgi3"

# Loop implementation (auto, asyncio, uvloop)
loop = "auto"  # Will use uvloop if available for better performance

# HTTP protocol implementation
http = "auto"  # Will use httptools if available

# =============================================================================
# Lifespan Events
# =============================================================================

# Handle ASGI lifespan events
lifespan = "auto"

# =============================================================================
# Usage Information
# =============================================================================

"""
Command-line usage:

# Basic start
uvicorn src.asgi:application --host 0.0.0.0 --port 8443

# With SSL
uvicorn src.asgi:application --host 0.0.0.0 --port 8443 \\
    --ssl-certfile /workspace/storage/certificates/webserver.crt \\
    --ssl-keyfile /workspace/storage/certificates/webserver.key

# With workers (production)
uvicorn src.asgi:application --host 0.0.0.0 --port 8443 --workers 4 \\
    --ssl-certfile /workspace/storage/certificates/webserver.crt \\
    --ssl-keyfile /workspace/storage/certificates/webserver.key

# With this config file (programmatic)
python -c "
import uvicorn
from uvicorn_config import *

uvicorn.run(
    'src.asgi:application',
    host=host,
    port=port,
    ssl_certfile=ssl_certfile,
    ssl_keyfile=ssl_keyfile,
    log_config=log_config,
    access_log=access_log
)
"
"""
