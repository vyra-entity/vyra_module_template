#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/v2_modulemanager/vyra_entrypoint.sh

echo "=== VYRA ENTRYPOINT STARTING ==="

# Warte kurz für vollständige Installation
# sleep 2

export $(grep -v '^#' .env | xargs)

# Vyra Base installieren
source /workspace/tools/setup_ros_global.sh

if [ $? -eq 0 ]; then
    echo "✅ Source ROS global setup successful"
else
    echo "❌ Source ROS global setup failed"
    exit 1
fi

# Create log directory
mkdir -p /workspace/log/vyra

if ! grep -q '^VYRA_STARTUP_ACTIVE=' .env; then
    echo "VYRA_STARTUP_ACTIVE=true" >> .env
fi

# Only build on first start or if manually set (VYRA_STARTUP_ACTIVE=false)
if [ "$VYRA_STARTUP_ACTIVE" == "true" ]; then
    echo "=== STARTUP ACTIVE: INSTALL DEPS AND BUILDING WORKSPACE ==="

    # Clear vyra_base
    if pip show vyra_base > /dev/null 2>&1; then
        pip uninstall vyra_base -y --break-system-packages
    else
        echo "vyra_base ist nicht installiert, überspringe Uninstall."
    fi

    # Interfaces setup
    # Installing all wheels dependencies
    pip install wheels/*.whl --break-system-packages

    if [ $? -eq 0 ]; then
        echo "✅ All wheels installed successfully"
    else
        echo "❌ Wheels installation failed"
        exit 1
    fi

    # Setting up interfaces (cmake, package, load interfaces from vyra_base, etc.)
    python3 tools/setup_interfaces.py

    if [ $? -eq 0 ]; then
        echo "✅ Interface setup completed"
    else
        echo "❌ Interface setup failed"
        exit 1
    fi

    # Clean build
    rm -rf log/build_* # build/ 
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

    if [ $? -eq 0 ]; then
        echo "✅ Build completed"
    else
        echo "❌ Build failed"
        exit 1
    fi

    rm -rf build/

    # Deactivate startup flag to avoid repeated builds
    sed -i 's/^VYRA_STARTUP_ACTIVE=.*/VYRA_STARTUP_ACTIVE=false/' .env    
else
    echo "=== STARTUP NOT ACTIVE ==="
    echo "✅ Skipping interface configuration"
    echo "✅ Skipping ros2 build"
fi

if pip show vyra_base > /dev/null 2>&1; then
    echo "✅ vyra_base is installed"
else
    echo "❌ vyra_base is NOT installed. VYRA_STARTUP_ACTIVE=true will be set to base all settings."
    export VYRA_STARTUP_ACTIVE=true
    exit 1
fi

# Source package setup
source install/setup.bash

if [ $? -eq 0 ]; then
    echo "✅ Source package setup successful"
else
    echo "❌ Source package setup failed"
    exit 1
fi

# Debug: Show available packages
echo "=== AVAILABLE PACKAGES ==="
ros2 pkg list | grep -E "(v2_|vyra_)" || echo "No matching packages"

echo "=== EXECUTABLES ==="
ros2 pkg executables v2_modulemanager || echo "No executables for v2_modulemanager"

# SROS2 Setup
echo "=== SROS2 SETUP ==="
echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"

if [ ! -d "$ROS_SECURITY_KEYSTORE" ]; then
    echo "[SROS2] Creating keystore at $ROS_SECURITY_KEYSTORE"
    ros2 security create_keystore $ROS_SECURITY_KEYSTORE
fi

if [ ! -d "$ROS_SECURITY_KEYSTORE/enclaves" ]; then
    echo "[SROS2] Creating enclaves at $ROS_SECURITY_KEYSTORE"
    mkdir -p $ROS_SECURITY_KEYSTORE/enclaves
fi

# Enclave für v2_modulemanager erzeugen
echo "[SROS2] Creating enclave for /v2_modulemanager/core"
ros2 security create_enclave $ROS_SECURITY_KEYSTORE /v2_modulemanager/core

# Environment für Security setzen
# export ROS_SECURITY_ENABLE=false
# export ROS_SECURITY_STRATEGY=Enforce
# export ROS_SECURITY_ENCLAVE="/v2_modulemanager/core"

echo "=== FINAL ENVIRONMENT ==="
echo "ROS_SECURITY_ENABLE: $ROS_SECURITY_ENABLE"
echo "ROS_SECURITY_STRATEGY: $ROS_SECURITY_STRATEGY"
echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"

# Prüfe ob Supervisor-Konfiguration existiert und starte Supervisor
if [ -f "/etc/supervisor/conf.d/supervisord.conf" ]; then
    echo "=== STARTING SUPERVISORD ==="
    exec /usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf -n
elif [ -f "/workspace/supervisord.conf" ]; then
    echo "=== STARTING SUPERVISORD (Workspace) ==="
    exec /usr/bin/supervisord -c /workspace/supervisord.conf -n
else
    echo "=== NO SUPERVISORD CONFIG - STARTING DEFAULT COMMAND ==="
    echo "=== ENTRYPOINT READY - EXECUTING: $@ ==="
    exec "$@"
fi