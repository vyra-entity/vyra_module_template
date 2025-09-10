#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/vyra_module_template/tools/update_ros.sh

pushd /workspace

# Vyra Base installieren
pip uninstall vyra_base -y --break-system-packages
pip install wheels/vyra_base-0.1.5-py3-none-any.whl --break-system-packages

if [ "$VYRA_PRODUCTIVE" != "true" ]; then
    # Interfaces setup
    python3 tools/setup_interfaces.py

    # Clean build
    rm -rf log/build_* # build/ 
fi

source /opt/ros/kilted/setup.bash

# Build mit dependency resolution
echo "=== BUILDING PACKAGES ==="

# Only build if not productive (VYRA_PRODUCTIVE=false)
if [ "$VYRA_PRODUCTIVE" != "true" ]; then
    echo "=== DEVELOPMENT MODE: BUILDING WORKSPACE ==="
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
else
    echo "=== PRODUCTIVE MODE: SKIPPING BUILD ==="
fi

# Prüfe Build-Erfolg
if [ $? -eq 0 ]; then
    echo "✅ Build erfolgreich"
else
    echo "❌ Build fehlgeschlagen"
    exit 1
fi

# WICHTIG: Environment VOR den ros2-Befehlen laden!
echo "=== ENVIRONMENT SETUP ==="

source install/setup.bash

# Extended Debug
echo "=== PACKAGES CHECK ==="
ros2 pkg list | grep vyra_module_template

echo "=== EXECUTABLES CHECK ==="
ros2 pkg executables vyra_module_template

echo "=== DIRECT EXECUTABLE TEST ==="
echo "Executable exists:"
ls -la install/vyra_module_template/lib/vyra_module_template/core

# Jetzt sollte ros2 run funktionieren
echo "=== STARTING MODULE (ROS2 RUN) ==="
export ROS_SECURITY_ENCLAVE="/vyra_module_template/core"
exec ros2 run vyra_module_template core --ros-args --enclave $ROS_SECURITY_ENCLAVE

popd