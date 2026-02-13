#!/bin/bash
# Quick start script for ROS2 Hot Reload

set -e

echo "🔥 ROS2 Hot Reload - Quick Start"
echo "================================"
echo ""

# Check if running inside container
if [ ! -f "/workspace/.env" ]; then
    echo "❌ Error: This script must run inside the Docker container"
    echo "   Use: docker exec -it <container_name> bash"
    exit 1
fi

cd /workspace

# Check dependencies
echo "📦 Checking dependencies..."
if ! pip show watchdog > /dev/null 2>&1; then
    echo "   Installing watchdog..."
    pip install watchdog --break-system-packages
    echo "   ✅ watchdog installed"
else
    echo "   ✅ watchdog already installed"
fi

# Get package and node name
PACKAGE_NAME=${1:-vyra_module_template}
NODE_NAME=${2:-core}
SUPERVISORD_PROGRAM=${3:-ros2_core}

echo ""
echo "🎯 Configuration:"
echo "   Package: $PACKAGE_NAME"
echo "   Node: $NODE_NAME"
echo "   Supervisord Program: $SUPERVISORD_PROGRAM"
echo "   Watch Path: /workspace/src"
echo ""
echo "📝 Logs will be written to:"
echo "   /workspace/log/ros2/hot_reload.log"
echo ""
echo "⚡ Starting Hot Reload Watcher..."
echo "   (Press Ctrl+C to stop)"
echo ""

# Start hot reload
exec python3 /workspace/tools/ros2_hot_reload.py "$PACKAGE_NAME" "$NODE_NAME" "$SUPERVISORD_PROGRAM"
