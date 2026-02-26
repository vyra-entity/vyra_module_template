#!/bin/bash
###############################################################################
# Core Startup Script - Unified entrypoint for SLIM and normal ROS2 modes
#
# VYRA_SLIM=true  → Pure Python execution, no ROS2
# VYRA_SLIM=false → Full ROS2 core with gRPC and ROS2 services
###############################################################################

set -e  # Exit on any error

# Load environment variables from .env if present
if [ -f "/workspace/.env" ]; then
    set -a
    source /workspace/.env
    set +a
fi

# Default VYRA_SLIM to false (normal ROS2 mode)
VYRA_SLIM="${VYRA_SLIM:-false}"
LOG_DIR="${LOG_DIR:-/workspace/log}"
MODULE_NAME="${MODULE_NAME:-v2_modulemanager}"

# Ensure log directory exists
mkdir -p "$LOG_DIR/core"

echo "=========================================="
echo "🔧 VYRA Core Startup"
echo "=========================================="
echo "VYRA_SLIM: $VYRA_SLIM"
echo "LOG_DIR: $LOG_DIR"
echo "MODULE_NAME: $MODULE_NAME"
echo "=========================================="

# Determine startup mode
if [ "$VYRA_SLIM" = "true" ]; then
    echo "🎯 SLIM Mode: Running Python application directly (no ROS2)"
    
    # Install SLIM dependencies with Poetry if not already installed
    if [ -f "/workspace/pyproject.toml" ]; then
        echo "📦 Ensuring SLIM dependencies are installed..."
        cd /workspace
        poetry install --only main -E slim --no-interaction
    fi
    
    # Execute Python main() via Poetry
    cd /workspace
    exec poetry run python3 -m v2_modulemanager.main

else
    echo "🎯 Normal Mode: Starting with Full ROS2 core"
    
    # Delegate to startup_ros2_core.sh for ROS2-based startup
    if [ -f "/workspace/tools/startup_ros2_core.sh" ]; then
        exec bash /workspace/tools/startup_ros2_core.sh
    else
        echo "❌ ERROR: startup_ros2_core.sh not found at /workspace/tools/startup_ros2_core.sh"
        exit 1
    fi
fi
