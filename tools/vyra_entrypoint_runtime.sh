#!/bin/bash
# Runtime Entrypoint for pre-built VYRA modules
# Supports both CI (pre-built) and local (build at runtime) modes
set -euo pipefail

echo "=== VYRA RUNTIME ENTRYPOINT STARTING ==="

# Load environment variables from .env
if [ -f ".env" ]; then
    chmod 777 .env
    export $(grep -v '^#' .env | sed 's/#.*$//' | grep -v '^$' | xargs)
    echo "✅ Loaded .env configuration"
fi

# Set defaults
: "${VYRA_BUILD_MODE:=ci}"
: "${MODULE_NAME:=v2_modulemanager}"
: "${RMW_IMPLEMENTATION:=rmw_cyclonedds_cpp}"
: "${ROS_DOMAIN_ID:=42}"
: "${SECURE_BY_SROS2:=false}"
: "${ROS_SECURITY_ENABLE:=true}"
: "${VYRA_DEV_MODE:=false}"

# Override ROS_SECURITY_ENABLE based on SECURE_BY_SROS2
if [ "$SECURE_BY_SROS2" = "false" ]; then
    export ROS_SECURITY_ENABLE=false
    echo "⚠️  SROS2 disabled via SECURE_BY_SROS2=false"
fi

echo "=== Configuration ==="
echo "  MODULE_NAME: $MODULE_NAME"
echo "  VYRA_BUILD_MODE: $VYRA_BUILD_MODE"
echo "  RMW_IMPLEMENTATION: $RMW_IMPLEMENTATION"
echo "  ROS_DOMAIN_ID: $ROS_DOMAIN_ID"
echo "  ROS_SECURITY_ENABLE: $ROS_SECURITY_ENABLE"
echo "===================="

# Create log directories
mkdir -p /workspace/log/vyra /workspace/log/uvicorn /workspace/log/nginx /workspace/log/ros2

# Check build mode
if [ "$VYRA_BUILD_MODE" = "local" ]; then
    echo "🔨 Local Build Mode: Running colcon build at runtime..."
    
    # Source ROS2 setup
    source /opt/ros/kilted/setup.bash
    
    # Setup interfaces
    if [ -f "tools/setup_interfaces.py" ]; then
        python3 tools/setup_interfaces.py
    fi
    
    # Clean and build
    rm -rf build/ install/ log/ros2/build* log/ros2/latest*
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
    
    # Move logs
    mv log/build_* log/latest_build log/latest log/ros2/ 2>/dev/null || true
    
    echo "✅ Local build completed"
    
elif [ "$VYRA_BUILD_MODE" = "ci" ]; then
    echo "✅ CI Build Mode: Using pre-built install/"
    
    if [ ! -d "/workspace/install" ]; then
        echo "❌ ERROR: Pre-built install/ directory not found!"
        echo "💡 This image was built for CI mode but install/ is missing"
        echo "   Either:"
        echo "   1. Use correct pre-built image"
        echo "   2. Set VYRA_BUILD_MODE=local in .env for runtime build"
        exit 1
    fi
    
    echo "✅ Found pre-built ROS2 workspace"
else
    echo "❌ ERROR: Invalid VYRA_BUILD_MODE: $VYRA_BUILD_MODE"
    echo "   Valid values: ci, local"
    exit 1
fi

# Source ROS2 setup
source /opt/ros/kilted/setup.bash

if [ -f "/workspace/install/setup.bash" ]; then
    source /workspace/install/setup.bash
    echo "✅ Sourced module setup.bash"
else
    echo "❌ ERROR: install/setup.bash not found"
    exit 1
fi

# Set RMW Implementation
export RMW_IMPLEMENTATION=${RMW_IMPLEMENTATION}
echo "✅ RMW Implementation: $RMW_IMPLEMENTATION"

# Configure CycloneDDS if selected
if [ "$RMW_IMPLEMENTATION" = "rmw_cyclonedds_cpp" ]; then
    if [ -f "/workspace/config/cyclonedds.xml" ]; then
        export CYCLONEDDS_URI="file:///workspace/config/cyclonedds.xml"
        echo "✅ CycloneDDS configured: $CYCLONEDDS_URI"
    else
        echo "⚠️  CycloneDDS config not found, using defaults"
    fi
fi

# Debug: Show available packages
echo "=== AVAILABLE ROS2 PACKAGES ==="
ros2 pkg list | grep -E "(v2_|vyra_)" || echo "No matching packages"

echo "=== EXECUTABLES ==="
ros2 pkg executables $MODULE_NAME || echo "No executables for $MODULE_NAME"

# SROS2 Setup (only if SECURE_BY_SROS2=true)
if [ "$SECURE_BY_SROS2" = "true" ] && [ "$ROS_SECURITY_ENABLE" = "true" ]; then
    echo "=== SROS2 SECURITY SETUP ==="
    echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"
    
    if [ -d "$ROS_SECURITY_KEYSTORE" ]; then
        export ROS_SECURITY_ENABLE=true
        export ROS_SECURITY_STRATEGY=Enforce
        export ROS_SECURITY_ENCLAVE="/${MODULE_NAME}/core"
        echo "✅ SROS2 enabled with enclave: $ROS_SECURITY_ENCLAVE"
    else
        echo "⚠️  SROS2 keystore not found, disabling security"
        export ROS_SECURITY_ENABLE=false
    fi
else
    echo "⚠️  SROS2 disabled via configuration"
    export ROS_SECURITY_ENABLE=false
fi

# SSL Certificate Check (same as before)
echo "=== SSL CERTIFICATE CHECK ==="

check_and_create_certificates() {
    local cert_name="${1:-webserver}"
    local cert_path="/workspace/storage/certificates/${cert_name}.crt"
    local key_path="/workspace/storage/certificates/${cert_name}.key"
    local cert_script="/workspace/tools/create_ssl_certificates.sh"
    
    if [ -f "$cert_path" ] && [ -f "$key_path" ]; then
        if openssl x509 -checkend 86400 -noout -in "$cert_path" >/dev/null 2>&1; then
            echo "✅ SSL certificates valid for $cert_name"
            return 0
        fi
    fi
    
    mkdir -p "/workspace/storage/certificates"
    
    if [ -f "$cert_script" ]; then
        "$cert_script" --name "$cert_name" --domain localhost --days 365
    else
        openssl req -x509 -newkey rsa:4096 \
            -keyout "$key_path" -out "$cert_path" \
            -days 365 -nodes \
            -subj "/CN=localhost/O=VYRA/OU=${cert_name}/C=DE" >/dev/null 2>&1
        chmod 600 "$key_path"
        chmod 644 "$cert_path"
    fi
}

# Check certificates based on enabled services
if [ "${ENABLE_BACKEND_WEBSERVER:-true}" = "true" ]; then
    check_and_create_certificates "webserver"
fi

if [ "${ENABLE_FRONTEND_WEBSERVER:-true}" = "true" ]; then
    check_and_create_certificates "frontend"
fi

# Configure supervisord services
echo "=== CONFIGURING SERVICES ==="

if [ "$VYRA_DEV_MODE" = "true" ]; then
    echo "🚀 Development Mode Enabled"
    # Development mode logic (Vite, Hot-Reload, etc.) same as before
else
    echo "🏭 Production Mode"
    
    # Check if frontend is built
    if [ -d "/workspace/frontend/dist" ]; then
        ASSET_COUNT=$(find /workspace/frontend/dist -type f \( -name "*.js" -o -name "*.css" \) 2>/dev/null | wc -l)
        
        if [ "$ASSET_COUNT" -eq 0 ]; then
            echo "⚠️  Frontend dist/ is empty"
            
            if command -v npm >/dev/null 2>&1; then
                echo "🔨 Building frontend..."
                cd /workspace/frontend
                [ ! -d "node_modules" ] && npm install
                npm run build
                cd /workspace
            else
                echo "❌ ERROR: Frontend not built and Node.js unavailable"
                exit 1
            fi
        else
            echo "✅ Frontend built ($ASSET_COUNT assets)"
        fi
    fi
fi

# Start supervisord
if [ -f "/etc/supervisor/conf.d/supervisord.conf" ]; then
    echo "=== STARTING SUPERVISORD ==="
    exec /usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf -n
else
    echo "❌ ERROR: supervisord.conf not found"
    exit 1
fi
