#!/usr/bin/env bash
# filepath: /workspace/tools/ros/setup_ros.sh
# Setup script to source all ROS2 environments including NFS interfaces
# Can be used with: docker exec <container> bash -c "source /workspace/tools/ros/setup_ros.sh && ros2 ..."

set -eo pipefail

# Source base ROS2 installation
if [ -f "/opt/ros/kilted/setup.bash" ]; then
    source /opt/ros/kilted/setup.bash
else
    echo "Error: ROS2 kilted not found" >&2
    exit 1
fi

# Source workspace install
if [ -f "/workspace/install/setup.bash" ]; then
    source /workspace/install/setup.bash
else
    echo "Warning: /workspace/install/setup.bash not found" >&2
fi

# Source all NFS interface overlays
NFS_VOLUME_PATH="${NFS_VOLUME_PATH:-/nfs/vyra_interfaces}"

if [ -d "$NFS_VOLUME_PATH" ]; then
    for interface_dir in "$NFS_VOLUME_PATH"/*_interfaces; do
        if [ -d "$interface_dir" ] && [ -f "$interface_dir/setup.bash" ]; then
            source "$interface_dir/setup.bash"
        fi
    done
fi

echo "✅ ROS2 environment ready"
echo "   AMENT_PREFIX_PATH: $AMENT_PREFIX_PATH"
