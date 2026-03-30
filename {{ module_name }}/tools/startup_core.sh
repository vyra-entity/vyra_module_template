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
MODULE_NAME="${MODULE_NAME:-unknown_module}"

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

    # In SLIM mode there is no ROS2 installation and no colcon build.
    # PYTHONPATH must NOT contain any ROS2 paths (no rclpy, etc.).
    # Reset PYTHONPATH completely and only add the module source tree and any
    # additional pure-Python install paths.
    export PYTHONPATH=""

    # Prepend the source tree so the module is importable directly from src/.
    # This also ensures that edits take effect without a colcon rebuild.
    SRC_DIR="/workspace/src/${MODULE_NAME}"
    if [ -d "$SRC_DIR" ]; then
        export PYTHONPATH="${SRC_DIR}:${PYTHONPATH}"
        echo "📂 PYTHONPATH set to ${SRC_DIR} (SLIM mode, no ROS2)"
    else
        echo "❌ ERROR: Source directory ${SRC_DIR} not found"
        exit 1
    fi

    # Disable Python stdout buffering so log lines appear immediately
    export PYTHONUNBUFFERED=1

    echo "🚀 Launching: python3 -m ${MODULE_NAME}.main"
    cd /workspace
    exec python3 -m "${MODULE_NAME}.main"

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
