#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/$MODULE_NAME/vyra_entrypoint.sh

echo "=== VYRA ENTRYPOINT STARTING ==="

# Warte kurz für vollständige Installation
# sleep 2

chmod 777 .env

export $(grep -v '^#' .env | xargs)

# Vyra Base installieren
source /workspace/tools/setup_ros_global.sh

if [ $? -eq 0 ]; then
    echo "✅ Source ROS global setup successful"
else
    echo "❌ Source ROS global setup failed"
    exit 1
fi

# Try to read the name from .module/module_data.yaml
MODULE_DATA_FILE=".module/module_data.yaml"
if [ -f "$MODULE_DATA_FILE" ]; then
    MODULE_NAME=$(grep "^name:" "$MODULE_DATA_FILE" | sed 's/^name:[[:space:]]*//')
    if [ -n "$MODULE_NAME" ]; then
        echo "✅ Using name from module_data.yaml: $MODULE_NAME"
    else
        echo "⚠️ Could not read name from $MODULE_DATA_FILE"
        echo "⚠️ ! Check the structure of the module_data.yaml file !"
        exit 1
    fi
else
    echo "⚠️ Module data file $MODULE_DATA_FILE not found. Cannot start module"
    exit 1
fi

# Add module name to .env
if [ -f ".env" ]; then
    echo "✅ Adding MODULE_NAME=$MODULE_NAME to .env file"
    if ! grep -q '^MODULE_NAME=' ".env"; then
        echo "MODULE_NAME=$MODULE_NAME" >> ".env"
    else
        echo "⚠️ MODULE_NAME already set in .env"
        # Update the existing line
        sed -i "s/^MODULE_NAME=.*/MODULE_NAME=$MODULE_NAME/" ".env"
    fi
fi

# Create log directory
mkdir -p /workspace/log/vyra

if ! grep -q '^VYRA_STARTUP_ACTIVE=' .env; then
    echo "VYRA_STARTUP_ACTIVE=true" >> .env
fi

if pip show vyra_base > /dev/null 2>&1; then
    echo "✅ vyra_base is installed"
else
    echo "❌ vyra_base is NOT installed. VYRA_STARTUP_ACTIVE=true will be set to base all settings."
    export VYRA_STARTUP_ACTIVE=true
fi

# Only build on first start or if manually set (VYRA_STARTUP_ACTIVE=false)
if [ "$VYRA_STARTUP_ACTIVE" == "true" ]; then
    echo "=== STARTUP ACTIVE: INSTALL DEPS AND BUILDING WORKSPACE ==="

    # 1. Install system packages first
    # Optional: Run pre-install script for repository setup
    if [ -f ".module/pre-install.sh" ]; then
        echo "🔧 Running pre-install script..."
        chmod +x .module/pre-install.sh
        ./.module/pre-install.sh
        echo "✅ Pre-install script completed"
    fi
    
    # 2. Install system packages from .module/system-packages.txt
    if [ -f ".module/system-packages.txt" ]; then
        echo "🔧 Installing system packages from .module/system-packages.txt..."
        apt-get update -qq
        while read -r package; do
            if [ -n "$package" ] && [ "${package:0:1}" != "#" ]; then
                echo "  📦 Installing: $package"
                if apt-get install -y "$package"; then
                    echo "  ✅ $package installed successfully"
                else
                    echo "  ⚠️ Failed to install $package, continuing..."
                fi
            fi
        done < .module/system-packages.txt
        echo "✅ System packages installation completed"
    else
        echo "⚠️ No .module/system-packages.txt found, skipping system packages"
    fi

    # 3. Install Python requirements
    if [ -f ".module/requirements.txt" ]; then
        echo "🐍 Installing Python requirements from .module/requirements.txt..."
        if pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; then
            echo "✅ Python requirements installed successfully"
        else
            echo "❌ Python requirements installation failed"
            exit 1
        fi
    else
        echo "⚠️ No .module/requirements.txt found, skipping Python requirements"
    fi

    # Clear vyra_base
    if pip show vyra_base > /dev/null 2>&1; then
        pip uninstall vyra_base -y --break-system-packages
    else
        echo "vyra_base ist nicht installiert, überspringe Uninstall."
    fi

    # Interfaces setup
    # 3. Installing all wheels dependencies
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
ros2 pkg executables $MODULE_NAME || echo "No executables for $MODULE_NAME"

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

# Enclave für $MODULE_NAME erzeugen
echo "[SROS2] Creating enclave for /$MODULE_NAME/core"
ros2 security create_enclave $ROS_SECURITY_KEYSTORE /$MODULE_NAME/core

# Environment für Security setzen
# export ROS_SECURITY_ENABLE=false
# export ROS_SECURITY_STRATEGY=Enforce
# export ROS_SECURITY_ENCLAVE="/$MODULE_NAME/core"

echo "=== FINAL ENVIRONMENT ==="
echo "ROS_SECURITY_ENABLE: $ROS_SECURITY_ENABLE"
echo "ROS_SECURITY_STRATEGY: $ROS_SECURITY_STRATEGY"
echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"

# Prüfe ob Supervisor-Konfiguration existiert und starte Supervisor
if [ -f "/etc/supervisor/conf.d/supervisord.conf" ]; then
    echo "=== CONFIGURING SUPERVISORD SERVICES ==="
    
    # Configure Nginx (Frontend Webserver)
    if [ "$ENABLE_FRONTEND_WEBSERVER" = "true" ]; then
        echo "✅ Enabling Nginx (Frontend Webserver)"
        sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf
    else
        echo "⚠️ Nginx (Frontend Webserver) disabled"
    fi
    
    # Configure Gunicorn (Backend Webserver)
    if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
        echo "✅ Enabling Gunicorn (Backend Webserver)"
        sed -i '/\[program:gunicorn\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf
    else
        echo "⚠️ Gunicorn (Backend Webserver) disabled"
    fi
    
    echo "=== STARTING SUPERVISORD ==="
    exec /usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf -n
elif [ -f "/workspace/supervisord.conf" ]; then
    echo "=== CONFIGURING SUPERVISORD SERVICES (Workspace) ==="
    
    # Configure Nginx (Frontend Webserver)
    if [ "$ENABLE_FRONTEND_WEBSERVER" = "true" ]; then
        echo "✅ Enabling Nginx (Frontend Webserver)"
        sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /workspace/supervisord.conf
    else
        echo "⚠️ Nginx (Frontend Webserver) disabled"
    fi
    
    # Configure Gunicorn (Backend Webserver)
    if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
        echo "✅ Enabling Gunicorn (Backend Webserver)"
        sed -i '/\[program:gunicorn\]/,/^\[/ s/autostart=false/autostart=true/' /workspace/supervisord.conf
    else
        echo "⚠️ Gunicorn (Backend Webserver) disabled"
    fi
    
    echo "=== STARTING SUPERVISORD (Workspace) ==="
    exec /usr/bin/supervisord -c /workspace/supervisord.conf -n
else
    echo "=== NO SUPERVISORD CONFIG - STARTING DEFAULT COMMAND ==="
    echo "=== ENTRYPOINT READY - EXECUTING: $@ ==="
    exec "$@"
fi