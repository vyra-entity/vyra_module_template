#!/bin/bash
# Cleanup script for ROS2 per-thread log files
# These files are created by rcl logging for each thread but are now disabled

echo "🧹 Cleaning up old ROS2 thread log files..."

# Remove python3 thread logs
find /workspace/log/ros2 -name "python3_*.log" -type f -delete 2>/dev/null || true

echo "✅ Cleanup complete"
