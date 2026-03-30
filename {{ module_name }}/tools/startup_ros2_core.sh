#!/bin/bash
# startup_ros2_core.sh - Start the Core ROS2 Module
# Formerly: startup_ros2_node.sh
# Note: Status Node is now started separately via ros2_status supervisor program

pushd /workspace

echo "---------------------------------------------------------------"
echo " 🚀 Starting ROS2 Core Module: $MODULE_NAME "

# Load environment variables from .env (filter comments and empty lines)
export $(grep -v '^#' .env | sed 's/#.*$//' | grep -v '^$' | xargs)

# Set ROS_LOG_DIR for runtime logs
export ROS_LOG_DIR="/workspace/log/ros2"

# Set CycloneDDS config file (must be set before sourcing setup.bash)
if [ -f "/workspace/config/cyclonedds.xml" ]; then
    export CYCLONEDDS_URI="file:///workspace/config/cyclonedds.xml"
    echo "✅ CYCLONEDDS_URI=$CYCLONEDDS_URI"
else
    echo "⚠️ cyclonedds.xml not found at /workspace/config/cyclonedds.xml, using default DDS config"
fi

source install/setup.bash

echo "SECURITY ENCLAVE: $ROS_SECURITY_ENCLAVE"

# Disable Python stdout buffering so logs appear immediately in supervisord log files
# Without this, Python buffers stdout in 8 KB blocks when writing to a pipe (non-TTY),
# causing log entries to appear in bursts instead of in real time.
export PYTHONUNBUFFERED=1

# Start main module node
echo "🚀 Starting Core Module..."
# All logs are now handled by Python Logger -> log/ros2/ros2_stdout.log
# ROS2 stdout/stderr goes to supervisord and is formatted there
exec ros2 run $MODULE_NAME core


if [ $? -eq 0 ]; then
    echo "✅ Module $MODULE_NAME run successfully"
else
    echo "❌ Module $MODULE_NAME runtime failed"
    exit 1
fi

popd