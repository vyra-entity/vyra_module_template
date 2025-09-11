#!/bin/bash
# Optimiertes Script für die API - Docker sollte bereits im Base-Image sein

# Signal Handler für graceful shutdown
cleanup() {
    echo "🛑 Stoppe API Server..."
    if [ ! -z "$API_PID" ]; then
        kill -TERM "$API_PID" 2>/dev/null
        wait "$API_PID" 2>/dev/null
    fi
    exit 0
}

# Signal traps setzen
trap cleanup SIGTERM SIGINT

echo "=== Secure Container Management API Startup ==="
echo "Datum: $(date)"
echo "Arbeitsverzeichnis: $(pwd)"

# Kurze Verfügbarkeitsprüfung (ohne Installation)
if command -v docker &> /dev/null; then
    echo "✅ Docker CLI verfügbar: $(docker --version)"
else
    echo "❌ Docker CLI nicht verfügbar!"
fi

if command -v docker-compose &> /dev/null; then
    echo "✅ Docker Compose (standalone) verfügbar: $(docker-compose --version)"
elif docker compose version &> /dev/null 2>&1; then
    echo "✅ Docker Compose (plugin) verfügbar: $(docker compose version)"
else
    echo "❌ Docker Compose nicht verfügbar!"
fi

# Docker Socket prüfen
if [ -S /var/run/docker.sock ]; then
    echo "✅ Docker Socket verfügbar: /var/run/docker.sock"
else
    echo "❌ Docker Socket nicht verfügbar!"
fi

# Check if requirements are installed otherwise install them

echo "=== Starte API Server ==="
python3 /workspace/simple_secure_api.py &
API_PID=$!

echo "API Server PID: $API_PID"

# Warte auf den API Prozess
wait "$API_PID"
