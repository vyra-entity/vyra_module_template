#!/bin/bash
# Container Port Check Script für Development Server

echo "=== VYRA Development Server Port Check ==="

PORT=${1:-3000}  # Standard Port 3000, oder als Argument übergeben

echo "Prüfe Port $PORT..."

# 1. Prozess-Check
echo "📋 Prozess-Check:"
ps aux | grep -E "(vite|vue-cli-service|npm.*dev)" | grep -v grep

# 2. Port-Check mit ss (moderne netstat Alternative)
echo ""
echo "🔌 Port-Check (ss):"
ss -tlnp | grep ":$PORT" || echo "Port $PORT nicht gefunden"

# 3. Port-Check mit netstat (falls verfügbar)
echo ""
echo "🔌 Port-Check (netstat):"
if command -v netstat &> /dev/null; then
    netstat -tlnp | grep ":$PORT" || echo "Port $PORT nicht gefunden"
else
    echo "netstat nicht verfügbar"
fi

# 4. HTTP-Test
echo ""
echo "🌐 HTTP-Test:"
if command -v curl &> /dev/null; then
    if curl -s --connect-timeout 2 http://localhost:$PORT >/dev/null; then
        echo "✅ HTTP Server antwortet auf Port $PORT"
    else
        echo "❌ HTTP Server antwortet nicht auf Port $PORT"
    fi
else
    echo "curl nicht verfügbar"
fi

# 5. Socket-Test mit nc
echo ""
echo "🔗 Socket-Test (nc):"
if command -v nc &> /dev/null; then
    if nc -z localhost $PORT 2>/dev/null; then
        echo "✅ Port $PORT ist offen"
    else
        echo "❌ Port $PORT ist geschlossen"
    fi
else
    echo "nc nicht verfügbar"
fi

# 6. /proc/net/tcp Check (immer verfügbar)
echo ""
echo "📂 /proc/net/tcp Check:"
# Port in Hex konvertieren
PORT_HEX=$(printf "%04X" $PORT)
if grep -q ":$PORT_HEX " /proc/net/tcp; then
    echo "✅ Port $PORT gefunden in /proc/net/tcp"
    grep ":$PORT_HEX " /proc/net/tcp
else
    echo "❌ Port $PORT nicht in /proc/net/tcp gefunden"
fi

echo ""
echo "=== Port Check abgeschlossen ==="
