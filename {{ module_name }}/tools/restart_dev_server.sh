#!/bin/bash
# filepath: /workspace/tools/restart_dev_server.sh

echo "🔄 Restarting Vite Dev Server..."

# 1. Kill existing Vite process
echo "🛑 Stopping existing Vite process..."
pkill -f "npm run dev" || echo "No Vite process running"
pkill -f "vite" || echo "No vite process running"
sleep 2

# 2. Check if node_modules exists
if [ ! -d "/workspace/frontend/node_modules" ]; then
    echo "📦 Installing npm dependencies..."
    cd /workspace/frontend
    npm install
fi

# 3. Start Vite Dev Server
echo "🚀 Starting Vite Dev Server..."
cd /workspace/frontend
nohup npm run dev -- --host 0.0.0.0 --port 3000 > /workspace/log/vite.log 2>&1 &
VITE_PID=$!

echo "✅ Vite Dev Server started (PID: $VITE_PID)"
echo "   Frontend URL: https://localhost/v2_modulemanager/"
echo "   Log: /workspace/log/vite.log"

# 4. Wait a moment and verify
sleep 3
if ps -p $VITE_PID > /dev/null; then
    echo "✅ Vite is running!"
    
    # Show last log lines
    echo ""
    echo "📋 Last log lines:"
    tail -n 10 /workspace/log/vite.log
else
    echo "❌ Vite failed to start!"
    echo "📋 Error logs:"
    cat /workspace/log/vite.log
    exit 1
fi
