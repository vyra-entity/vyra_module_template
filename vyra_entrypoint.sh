#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/$MODULE_NAME/vyra_entrypoint.sh
set -euo pipefail

echo "=== VYRA ENTRYPOINT STARTING ==="

# =============================================================================
# Redis Availability Check
# =============================================================================
echo "=== CHECKING REDIS AVAILABILITY ==="

# Wait for Redis to be ready (Docker Swarm compatible)
if [ -f "/workspace/tools/wait-for-redis.sh" ]; then
    echo "🔄 Checking Redis availability..."
    /workspace/tools/wait-for-redis.sh
elif [ -f "/host/tools/wait-for-redis.sh" ]; then
    echo "🔄 Checking Redis availability..."
    /host/tools/wait-for-redis.sh
else
    echo "⚠️ wait-for-redis.sh not found, skipping Redis check"
fi

# Warte kurz für vollständige Installation
# sleep 2

chmod 777 .env

# =============================================================================
# Environment Variable Setup
# =============================================================================
echo "=== SETTING UP ENVIRONMENT VARIABLES ==="

# Read MODULE_NAME from module_data.yaml BEFORE loading .env
# This allows module name to be available for ENV variable setup
MODULE_DATA_FILE=".module/module_data.yaml"
if [ -f "$MODULE_DATA_FILE" ]; then
    MODULE_NAME=$(grep "^name:" "$MODULE_DATA_FILE" | sed 's/^name:[[:space:]]*//')
    if [ -n "$MODULE_NAME" ]; then
        echo "✅ Using name from module_data.yaml: $MODULE_NAME"
        export MODULE_NAME  # Export as environment variable for ROS2 processes
        
        # Set ROS2 rcl_logging filename based on module name
        export RCL_LOGGING_LOG_FILE_NAME="${MODULE_NAME}_ros2_core.log"
        
        # Disable RCL/RCUTILS file logging to prevent per-thread log files
        # Log to console instead (stdout/stderr which supervisord captures)
        export RCUTILS_CONSOLE_OUTPUT_FORMAT="[{severity}] [{name}]: {message}"
        export RCUTILS_COLORIZED_OUTPUT=0
        export RCL_LOGGING_USE_CONSOLE=1
        export RCL_LOGGING_TO_FILES=0
        
        echo "✅ RCL logging configured to console only (no per-thread files)"
    else
        echo "⚠️ Could not read name from $MODULE_DATA_FILE"
        echo "⚠️ ! Check the structure of the module_data.yaml file !"
        exit 1
    fi
else
    echo "⚠️ Module data file $MODULE_DATA_FILE not found. Cannot start module"
    exit 1
fi

# Add module name to .env before loading
if [ -f ".env" ]; then
    if ! grep -q '^MODULE_NAME=' ".env"; then
        echo "MODULE_NAME=$MODULE_NAME" >> ".env"
    else
        # Update the existing line
        sed -i "s/^MODULE_NAME=.*/MODULE_NAME=$MODULE_NAME/" ".env"
    fi
    
    echo "=== UPDATING RCL_LOGGING_LOG_FILE_NAME IN .env ==="

    # -> Not working yet, ignore for now. Could be regarded as a TODO. <-

    # RCL_LOG_FILENAME="${MODULE_NAME}_ros2_core.log"
    # if ! grep -q '^RCL_LOGGING_LOG_FILE_NAME=' ".env"; then
    #     echo "RCL_LOGGING_LOG_FILE_NAME=$RCL_LOG_FILENAME" >> ".env"
    #     echo "✅ Added RCL_LOGGING_LOG_FILE_NAME=$RCL_LOG_FILENAME to .env"
    # else
    #     sed -i "s/^RCL_LOGGING_LOG_FILE_NAME=.*/RCL_LOGGING_LOG_FILE_NAME=$RCL_LOG_FILENAME/" ".env"
    #     echo "✅ Updated RCL_LOGGING_LOG_FILE_NAME=$RCL_LOG_FILENAME in .env"
    # fi
fi

# Load environment variables from .env (filter comments and empty lines)
# MODULE_NAME is now already exported, but this will reload it from .env
export $(grep -v '^#' .env | sed 's/#.*$//' | grep -v '^$' | xargs)

# Debug: Show loaded environment variables
echo "=== Loaded Environment Variables ==="
env | grep -E "ENABLE_|VYRA_DEV_MODE|MODULE_NAME" || echo "No ENABLE_/VYRA variables found"
echo "===================================="

# Set empty variables to prevent unbound variable errors
: "${AMENT_TRACE_SETUP_FILES:=""}"
: "${COLCON_TRACE:=""}"
: "${AMENT_PYTHON_EXECUTABLE:="/usr/bin/python3"}"
: "${COLCON_PYTHON_EXECUTABLE:="/usr/bin/python3"}"
: "${CMAKE_PREFIX_PATH:="/opt/ros/kilted"}"

# =============================================================================
# Source Vyra Base and Package Setup
# =============================================================================
echo "=== SOURCING VYRA BASE SETUP ==="

# source /workspace/tools/setup_ros_global.sh
source /opt/ros/kilted/setup.bash

if [ $? -eq 0 ]; then
    echo "✅ Source ROS global setup successful"
else
    echo "❌ Source ROS global setup failed"
    exit 1
fi

# =============================================================================
# gRPC Interface Generation
# =============================================================================
echo "=== GRPC INTERFACE GENERATION CHECK ==="

if [ -d "/workspace/storage/interfaces" ] && [ -n "$(find /workspace/storage/interfaces -maxdepth 1 -name '*.proto' 2>/dev/null)" ]; then
    PROTO_COUNT=$(find /workspace/storage/interfaces -maxdepth 1 -name '*.proto' 2>/dev/null | wc -l)
    echo "📦 Found $PROTO_COUNT proto file(s), generating gRPC code..."
    
    # Create grpc_generated directory
    mkdir -p /workspace/storage/interfaces/grpc_generated
    
    # Always use grpc_tools.protoc directly (setup_interfaces.py doesn't support --generate-grpc)
    echo "🛠️ Generating gRPC code directly with grpc_tools.protoc..."
    
    # Generate Python code from proto files
    cd /workspace/storage/interfaces
    for proto_file in *.proto; do
        echo "   Generating from: $proto_file"
        python3 -m grpc_tools.protoc \
            --proto_path=. \
            --python_out=grpc_generated \
            --grpc_python_out=grpc_generated \
            "$proto_file"
    done
    
    # Fix imports in generated gRPC files (convert absolute to relative imports)
    echo "🔧 Fixing gRPC imports to use relative imports..."
    for grpc_file in grpc_generated/*_pb2_grpc.py; do
        if [ -f "$grpc_file" ]; then
            # Replace "import X_pb2 as" with "from . import X_pb2 as"
            sed -i 's/^import \(.*_pb2\) as /from . import \1 as /g' "$grpc_file"
            echo "   ✓ Fixed imports in $(basename $grpc_file)"
        fi
    done
    
    cd /workspace
    
    # Create __init__.py for the grpc_generated package
    touch /workspace/storage/interfaces/grpc_generated/__init__.py
    
    echo "✅ gRPC code generated successfully with relative imports"
else
    echo "ℹ️  No proto files found in storage/interfaces/, skipping gRPC generation"
fi

# =============================================================================
# Log Directory Setup
# =============================================================================
echo "=== SETTING UP LOG DIRECTORIES ==="

mkdir -p /workspace/log/vyra
mkdir -p /workspace/log/uvicorn
mkdir -p /workspace/log/nginx
mkdir -p /workspace/log/ros2

# Clean up old thread log files if cleanup script exists
if [ -f "/workspace/tools/cleanup_thread_logs.sh" ]; then
    /workspace/tools/cleanup_thread_logs.sh
fi

rm -rf /workspace/log/ros2/*.log

# =============================================================================
# Install Directory Restoration
# =============================================================================
echo "=== CHECKING install/ DIRECTORY ==="

# Get module name for checking install integrity
if [ -f ".module/module_data.yaml" ]; then
    MODULE_NAME=$(grep "^name:" .module/module_data.yaml | cut -d: -f2 | tr -d ' ' | tr -d "'" | tr -d '"')
else
    echo "⚠️  Warning: module_data.yaml not found, cannot verify module package installation"
    MODULE_NAME=""
fi

# This happens when using full workspace mount for development
if [ -d "/opt/vyra/install_backup" ]; then
    # Check if install directory is complete (has setup.bash AND module package)
    INSTALL_COMPLETE=true
    
    if [ ! -f "/workspace/install/setup.bash" ]; then
        echo "❌ install/setup.bash missing"
        INSTALL_COMPLETE=false
    elif [ -n "$MODULE_NAME" ] && [ ! -d "/workspace/install/$MODULE_NAME" ]; then
        echo "❌ install/$MODULE_NAME package missing"
        INSTALL_COMPLETE=false
    fi
    
    if [ "$INSTALL_COMPLETE" = false ]; then
        echo "📦 Restoring complete install/ directory from image backup..."
        rm -rf /workspace/install
        cp -r /opt/vyra/install_backup /workspace/install
        echo "✅ install/ directory restored (including $MODULE_NAME package)"
    else
        echo "✅ install/ directory complete (setup.bash + $MODULE_NAME found)"
    fi
else
    if [ ! -f "/workspace/install/setup.bash" ]; then
        echo "❌ ERROR: install/setup.bash not found and no backup available"
        echo "💡 Image may not have been built correctly"
        exit 1
    fi
fi

# =============================================================================
# Source Package Setup
# =============================================================================
echo "=== SOURCING PACKAGE SETUP ==="

# Source package setup (install folder already built in image or restored)
source install/setup.bash

if [ $? -eq 0 ]; then
    echo "✅ Source package setup successful"
else
    echo "❌ Source package setup failed"
    exit 1
fi

# =============================================================================
# Dynamic Wheel Installation
# =============================================================================
echo "=== CHECKING FOR NEW/UPDATED WHEELS ==="

if [ -d "wheels" ] && [ "$(ls -A wheels/*.whl 2>/dev/null)" ]; then
    echo "📦 Found wheels directory with .whl files"
    
    # Create temporary directory for latest wheels
    tmpdir=$(mktemp -d)
    
    # For each unique package, find the latest version
    for pkg in $(ls wheels/*.whl | sed -E 's#.*/([^/-]+)-.*#\1#' | sort -u); do
        latest=$(ls wheels/"$pkg"-*.whl | sort -V | tail -n 1)
        cp "$latest" "$tmpdir/"
        echo "  📦 Selected: $(basename "$latest")"
    done
    
    # Install all latest wheels
    echo "🔧 Installing/updating wheels..."
    if pip install "$tmpdir"/*.whl \
        --break-system-packages \
        --force-reinstall \
        --no-deps \
        --ignore-installed cryptography 2>&1 | grep -v "WARNING.*pip"; then
        echo "✅ Wheels installed successfully"
    else
        echo "⚠️  Some wheels may have failed to install (check logs)"
    fi
    
    # Cleanup
    rm -rf "$tmpdir"
else
    echo "ℹ️  No wheels directory or .whl files found - skipping wheel installation"
fi

echo "===================================="

# =============================================================================
# NFS Interface Management
# =============================================================================
echo "=== NFS INTERFACE MANAGEMENT ==="

# Read UUID from .module/module_data.yaml
MODULE_DATA_FILE="/workspace/.module/module_data.yaml"
if [ -f "$MODULE_DATA_FILE" ]; then
    INSTANCE_ID=$(grep '^uuid:' "$MODULE_DATA_FILE" | awk '{print $2}')
    echo "ℹ️  Module: $MODULE_NAME, Instance: $INSTANCE_ID (from module_data.yaml)"
else
    # Fallback: Extract instance_id from container name (format: <module_name>_<instance_id>)
    INSTANCE_ID="${HOSTNAME#${MODULE_NAME}_}"  # Remove module name prefix
    if [ "$INSTANCE_ID" = "$HOSTNAME" ]; then
        # Fallback: If HOSTNAME doesn't start with MODULE_NAME, use full HOSTNAME
        INSTANCE_ID="$HOSTNAME"
    fi
    echo "⚠️  Warning: module_data.yaml not found, Instance: $INSTANCE_ID (from HOSTNAME)"
fi

NFS_VOLUME_PATH="${NFS_VOLUME_PATH:-/nfs/vyra_interfaces}"
INTERFACE_DIR="${MODULE_NAME}_${INSTANCE_ID}_interfaces"
INTERFACE_SOURCE="/workspace/install/${MODULE_NAME}_interfaces"

# Check if NFS volume is mounted
if [ -d "$NFS_VOLUME_PATH" ]; then
    echo "✅ NFS volume found at $NFS_VOLUME_PATH"
    
    # Copy module's own interfaces to NFS (read-write)
    # We need to create a complete ROS2 install structure with setup.bash in root
    if [ -d "$INTERFACE_SOURCE" ]; then
        NFS_MODULE_DIR="$NFS_VOLUME_PATH/$INTERFACE_DIR"
        echo "📦 Copying interfaces to NFS as $INTERFACE_DIR..."
        mkdir -p "$NFS_MODULE_DIR"
        
        # Check if interfaces need to be copied or updated
        FORCE_UPDATE=false
        
        # Check if setup.bash exists (first-time setup)
        if [ ! -f "$NFS_MODULE_DIR/setup.bash" ]; then
            echo "ℹ️  First-time setup: Copying interfaces to NFS..."
            FORCE_UPDATE=true
        else
            # Check if config files differ (interface updates from vyra_base)
            # Compare checksums of critical config files
            for config_file in vyra_core_meta.json vyra_com_meta.json vyra_security_meta.json; do
                SOURCE_CONFIG="$INTERFACE_SOURCE/share/${MODULE_NAME}_interfaces/config/$config_file"
                NFS_CONFIG="$NFS_MODULE_DIR/share/${MODULE_NAME}_interfaces/config/$config_file"
                
                if [ -f "$SOURCE_CONFIG" ] && [ -f "$NFS_CONFIG" ]; then
                    SOURCE_MD5=$(md5sum "$SOURCE_CONFIG" | awk '{print $1}')
                    NFS_MD5=$(md5sum "$NFS_CONFIG" | awk '{print $1}')
                    
                    if [ "$SOURCE_MD5" != "$NFS_MD5" ]; then
                        echo "⚠️  Config update detected: $config_file differs"
                        echo "   Source:  $SOURCE_MD5"
                        echo "   NFS:     $NFS_MD5"
                        FORCE_UPDATE=true
                        break
                    fi
                fi
            done
            
            if [ "$FORCE_UPDATE" = false ]; then
                echo "✅ NFS interfaces up-to-date (checksums match)"
            fi
        fi
        
        # Copy/update interfaces if needed
        if [ "$FORCE_UPDATE" = true ]; then
            echo "🔄 Updating NFS interfaces..."
            # Copy the package artifacts (include, lib, share)
            if command -v rsync >/dev/null 2>&1; then
                rsync -av --delete "$INTERFACE_SOURCE/" "$NFS_MODULE_DIR/" 2>/dev/null || cp -r "$INTERFACE_SOURCE"/* "$NFS_MODULE_DIR"/
            else
                cp -r "$INTERFACE_SOURCE"/* "$NFS_MODULE_DIR"/
            fi
            
            # Copy minimal ROS2 setup infrastructure from workspace install
            # We need: setup.bash, local_setup.bash, _local_setup_util_sh.py
            if [ -f "/workspace/install/setup.bash" ]; then
                cp /workspace/install/setup.bash "$NFS_MODULE_DIR/"
                cp /workspace/install/local_setup.bash "$NFS_MODULE_DIR/" 2>/dev/null || true
                cp /workspace/install/_local_setup_util_sh.py "$NFS_MODULE_DIR/" 2>/dev/null || true
                cp /workspace/install/.colcon_install_layout "$NFS_MODULE_DIR/" 2>/dev/null || true
                
                # Modify setup.bash to only source this overlay's packages
                # Replace the prefix chain logic with simple local setup
                cat > "$NFS_MODULE_DIR/setup.bash" <<'EOF'
#!/usr/bin/env bash
# Simplified setup.bash for NFS interface sharing
COLCON_CURRENT_PREFIX="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null && pwd)"
export COLCON_CURRENT_PREFIX

# Add this prefix to AMENT_PREFIX_PATH
if [ -z "$AMENT_PREFIX_PATH" ]; then
    export AMENT_PREFIX_PATH="$COLCON_CURRENT_PREFIX"
else
    # Prepend if not already present
    if [[ ":$AMENT_PREFIX_PATH:" != *":$COLCON_CURRENT_PREFIX:"* ]]; then
        export AMENT_PREFIX_PATH="$COLCON_CURRENT_PREFIX:$AMENT_PREFIX_PATH"
    fi
fi

# Source local setup if available
if [ -f "$COLCON_CURRENT_PREFIX/local_setup.bash" ]; then
    . "$COLCON_CURRENT_PREFIX/local_setup.bash"
fi
EOF
                chmod +x "$NFS_MODULE_DIR/setup.bash"
            fi
            
            echo "✅ Interfaces updated on NFS successfully"
        fi
        
        if [ ! -f "$NFS_MODULE_DIR/setup.bash" ]; then
            echo "❌ Error: setup.bash not found after interface copy"
        fi
    else
        echo "⚠️  No interface source found at $INTERFACE_SOURCE"
    fi
    
    # Source all interfaces from NFS (read-only for other modules)
    echo "🔗 Sourcing ROS2 interfaces from NFS..."
    INTERFACES_SOURCED=0
    for interface_dir in "$NFS_VOLUME_PATH"/*_interfaces; do
        if [ -d "$interface_dir" ] && [ -f "$interface_dir/setup.bash" ]; then
            interface_name=$(basename "$interface_dir")
            echo "   Sourcing $interface_name..."
            source "$interface_dir/setup.bash" || echo "⚠️  Failed to source $interface_name"
            INTERFACES_SOURCED=$((INTERFACES_SOURCED + 1))
        fi
    done
    
    if [ $INTERFACES_SOURCED -gt 0 ]; then
        echo "✅ Sourced $INTERFACES_SOURCED interface packages from NFS"
    else
        echo "ℹ️  No interface packages found in NFS (first module?)"
    fi
else
    echo "⚠️  NFS volume not found at $NFS_VOLUME_PATH"
    echo "   Modules will only see their own interfaces"
fi

# Debug: Show available packages
echo "=== AVAILABLE PACKAGES ==="
ros2 pkg list | grep -E "(v2_|vyra_)" || echo "No matching packages"

echo "=== EXECUTABLES ==="
ros2 pkg executables $MODULE_NAME || echo "No executables for $MODULE_NAME"

# =============================================================================
# Proto Interface Setup & NFS Sharing (for gRPC/Redis communication)
# =============================================================================
echo "=== PROTO INTERFACE SETUP ==="

NFS_PROTO_PATH="${NFS_PROTO_PATH:-/nfs/proto_interfaces}"
PROTO_INTERFACE_DIR="${MODULE_NAME}_${INSTANCE_ID}_proto_interfaces"
PROTO_INTERFACE_SOURCE="/workspace/install/${MODULE_NAME}_proto_interfaces"

# Check if NFS Proto volume is mounted
if [ -d "$NFS_PROTO_PATH" ]; then
    echo "✅ Proto NFS volume found at $NFS_PROTO_PATH"
    
    # Copy module's own Proto interfaces to NFS
    if [ -d "$PROTO_INTERFACE_SOURCE" ]; then
        NFS_PROTO_MODULE_DIR="$NFS_PROTO_PATH/$PROTO_INTERFACE_DIR"
        echo "📦 Copying Proto interfaces to NFS as $PROTO_INTERFACE_DIR..."
        mkdir -p "$NFS_PROTO_MODULE_DIR"
        
        # Copy all files to NFS
        cp -r "$PROTO_INTERFACE_SOURCE"/* "$NFS_PROTO_MODULE_DIR"/ 2>/dev/null || echo "⚠️  No Proto interfaces to copy"
        
        if [ -f "$NFS_PROTO_MODULE_DIR/__init__.py" ]; then
            echo "✅ Proto interfaces deployed to NFS"
        else
            echo "⚠️  Warning: __init__.py not found after Proto interface copy"
        fi
    else
        echo "ℹ️  No Proto interfaces found at $PROTO_INTERFACE_SOURCE (optional)"
    fi
    
    # Add all Proto interfaces from NFS to PYTHONPATH
    echo "🔗 Loading Proto interfaces from NFS..."
    PROTO_INTERFACES_LOADED=0
    for proto_if_dir in "$NFS_PROTO_PATH"/*_proto_interfaces; do
        if [ -d "$proto_if_dir" ] && [ -f "$proto_if_dir/__init__.py" ]; then
            proto_if_name=$(basename "$proto_if_dir")
            echo "   Loading $proto_if_name..."
            export PYTHONPATH="$proto_if_dir:$PYTHONPATH"
            PROTO_INTERFACES_LOADED=$((PROTO_INTERFACES_LOADED + 1))
        fi
    done
    
    if [ $PROTO_INTERFACES_LOADED -gt 0 ]; then
        echo "✅ Loaded $PROTO_INTERFACES_LOADED Proto interface package(s) from NFS"
    else
        echo "ℹ️  No Proto interface packages found in NFS (first module?)"
    fi
else
    echo "⚠️  Proto NFS volume not found at $NFS_PROTO_PATH"
    echo "   Modules will only see their own Proto interfaces"
    
    # Still add local Proto interfaces to PYTHONPATH if they exist
    if [ -d "$PROTO_INTERFACE_SOURCE" ]; then
        export PYTHONPATH="$PROTO_INTERFACE_SOURCE:$PYTHONPATH"
        echo "✅ Added local Proto interfaces to PYTHONPATH"
    fi
fi

# SROS2 Setup
echo "=== SROS2 SETUP ==="
echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"

# if [ ! -d "$ROS_SECURITY_KEYSTORE" ]; then
#     echo "[SROS2] Creating keystore at $ROS_SECURITY_KEYSTORE"
#     ros2 security create_keystore $ROS_SECURITY_KEYSTORE
# fi

echo "[SROS2] Creating keystore at $ROS_SECURITY_KEYSTORE if not exists"
ros2 security create_keystore $ROS_SECURITY_KEYSTORE || true
ros2 security generate_policy sros2_keystore/ || true

if [ ! -d "$ROS_SECURITY_KEYSTORE/enclaves" ]; then
    echo "[SROS2] Creating enclaves at $ROS_SECURITY_KEYSTORE"
    mkdir -p $ROS_SECURITY_KEYSTORE/enclaves
fi

# Enclave für $MODULE_NAME erzeugen
echo "[SROS2] Creating enclave for /$MODULE_NAME/core"
ros2 security create_enclave $ROS_SECURITY_KEYSTORE /$MODULE_NAME/core || true

# Environment für Security setzen
# export ROS_SECURITY_ENABLE=false
# export ROS_SECURITY_STRATEGY=Enforce
# export ROS_SECURITY_ENCLAVE="/$MODULE_NAME/core"

echo "=== FINAL ENVIRONMENT ==="
echo "ROS_SECURITY_ENABLE: $ROS_SECURITY_ENABLE"
echo "ROS_SECURITY_STRATEGY: $ROS_SECURITY_STRATEGY"
echo "ROS_SECURITY_KEYSTORE: $ROS_SECURITY_KEYSTORE"

# =============================================================================
# SSL Certificate Auto-Generation
# =============================================================================
echo "=== SSL CERTIFICATE CHECK ==="

# Function to check and create SSL certificates
# Parameters: $1 = cert_name (e.g., "webserver", "frontend")
check_and_create_certificates() {
    local cert_name="${1:-webserver}"
    local cert_path="/workspace/storage/certificates/${cert_name}.crt"
    local key_path="/workspace/storage/certificates/${cert_name}.key"
    local cert_script="/workspace/tools/create_ssl_certificates.sh"
    
    echo "🔍 Checking SSL certificates for: $cert_name"
    echo "   Certificate: $cert_path"
    echo "   Private Key: $key_path"
    
    if [ -f "$cert_path" ] && [ -f "$key_path" ]; then
        echo "✅ SSL certificates found for $cert_name"
        
        # Check if certificates are still valid (not expired)
        if openssl x509 -checkend 86400 -noout -in "$cert_path" >/dev/null 2>&1; then
            echo "✅ SSL certificates for $cert_name are valid (>24h remaining)"
            return 0
        else
            echo "⚠️ SSL certificates for $cert_name are expiring soon or expired"
            echo "🔄 Regenerating certificates..."
        fi
    else
        echo "❌ SSL certificates not found for $cert_name"
        echo "🔨 Creating new SSL certificates..."
    fi
    
    # Create certificates directory if it doesn't exist
    mkdir -p "/workspace/storage/certificates"
    
    # Check if creation script exists
    if [ -f "$cert_script" ]; then
        echo "🛠️ Using certificate creation script for $cert_name..."
        if "$cert_script" --name "$cert_name" --domain localhost --days 365; then
            echo "✅ SSL certificates for $cert_name created successfully"
            return 0
        else
            echo "❌ Certificate creation script failed for $cert_name"
            return 1
        fi
    else
        echo "⚠️ Certificate script not found, creating $cert_name manually..."
        
        # Fallback: Create certificates directly
        if openssl req -x509 -newkey rsa:4096 \
            -keyout "$key_path" \
            -out "$cert_path" \
            -days 365 \
            -nodes \
            -subj "/CN=localhost/O=VYRA Dashboard/OU=${cert_name}/C=DE" >/dev/null 2>&1; then
            
            # Set secure permissions
            chmod 600 "$key_path"
            chmod 644 "$cert_path"
            
            echo "✅ SSL certificates for $cert_name created manually"
            return 0
        else
            echo "❌ Manual certificate creation failed for $cert_name"
            return 1
        fi
    fi
}

# Check/create backend certificates if backend webserver is enabled
if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
    echo "🔐 Backend webserver enabled - checking SSL certificates..."
    
    if check_and_create_certificates "webserver"; then
        echo "✅ Backend SSL certificate check completed successfully"
    else
        echo "⚠️ Backend SSL certificate setup failed - continuing without SSL"
        echo "   Backend will start in HTTP mode"
    fi
else
    echo "⏭️ Backend webserver disabled - skipping backend SSL certificate check"
fi

# Check/create frontend certificates if frontend webserver is enabled
if [ "$ENABLE_FRONTEND_WEBSERVER" = "true" ]; then
    echo "🔐 Frontend webserver enabled - checking SSL certificates..."
    
    if check_and_create_certificates "frontend"; then
        echo "✅ Frontend SSL certificate check completed successfully"
    else
        echo "⚠️ Frontend SSL certificate setup failed - continuing without SSL"
        echo "   Frontend will start in HTTP mode"
    fi
else
    echo "⏭️ Frontend webserver disabled - skipping frontend SSL certificate check"
fi

# =============================================================================
# Supervisord Service Configuration
# =============================================================================
echo "=== CONFIGURING SUPERVISORD SERVICES ==="

# Check Development Mode
if [ "$VYRA_DEV_MODE" = "true" ]; then
    echo "🚀 DEVELOPMENT MODE ENABLED"

    # Enable ROS2 Hot Reload if configured
    if [ "$ENABLE_ROS2_HOT_RELOAD" = "true" ]; then
        echo "🔥 Enabling ROS2 Hot Reload..."
        
        # Install watchdog if not present
        if ! pip show watchdog > /dev/null 2>&1; then
            echo "📦 Installing watchdog for hot reload..."
            pip install watchdog --break-system-packages
        fi
        
        # Start hot reload watcher in background
        # Note: ros2_core is the supervisord program name for the ROS2 core node
        nohup python3 /workspace/tools/ros2_hot_reload.py "$MODULE_NAME" core ros2_core \
            > /workspace/log/ros2/hot_reload.log 2>&1 &
        
        HOT_RELOAD_PID=$!
        echo "✅ ROS2 Hot Reload started (PID: $HOT_RELOAD_PID)"
        echo "   Watching: /workspace/src"
        echo "   Logs: /workspace/log/ros2/hot_reload.log"
    fi

    # Check if npm is available for Vite dev server
    if command -v npm >/dev/null 2>&1; then
        echo "   Starting Vite Dev Server instead of Nginx..."

        # Disable Nginx in dev mode
        ENABLE_FRONTEND_WEBSERVER=false
        
        # Install npm dependencies if needed
        if [ ! -d "/workspace/frontend/node_modules" ]; then
            echo "📦 Installing npm dependencies..."
            cd /workspace/frontend
            npm install
            cd /workspace
        fi
        
        # Start Vite Dev Server in background
        echo "🔥 Starting Vite Dev Server on port 3000..."
        cd /workspace/frontend
        nohup npm run dev -- --host 0.0.0.0 --port 3000 > /workspace/log/vite.log 2>&1 &
        VITE_PID=$!
        echo "✅ Vite Dev Server started (PID: $VITE_PID)"
        echo "   Frontend URL: http://localhost:3000"
        echo "   Log: /workspace/log/vite.log"
        cd /workspace
    else
        echo "⚠️  npm not available - falling back to Nginx with pre-built frontend"
        echo "   (Set VYRA_DEV_MODE=false or use development base image for Vite hot reload)"
        # Keep ENABLE_FRONTEND_WEBSERVER=true to use nginx with dist/
    fi

    # Alter reload=True on uvicorn in /etc/supervisor/conf.d/supervisord.conf for developement
    echo "🔄 Enabling autoreload for Uvicorn (FastAPI)..."
    echo "   Watch directory: $BACKEND_DEV_FILEWATCH"
    
    BACKEND_DEV_FILEWATCH_SED=$(echo "$BACKEND_DEV_FILEWATCH" | sed 's/\//\\\//g')

    # Add --reload and --reload-dir for both SSL and non-SSL variants using the env variable
    sudo sed -i "/exec uvicorn src.asgi:application.*--host 0.0.0.0 --port 8443/s/--log-level info/--log-level info --reload --reload-dir $BACKEND_DEV_FILEWATCH_SED --reload-exclude \/workspace\/log/" /etc/supervisor/conf.d/supervisord.conf
    # cat /etc/supervisor/conf.d/supervisord.conf
    # sed -i "/exec uvicorn src.asgi:application.*--host 0.0.0.0 --port 8443 --log-level info;/s/--log-level info/--log-level info --log-config \/workspace\/config\/logging.json --reload --reload-dir $BACKEND_DEV_FILEWATCH --reload-exclude \/workspace\/log/" /etc/supervisor/conf.d/supervisord.conf 2>/dev/null || true
else
    echo "🏭 PRODUCTION MODE — Using Nginx with pre-built frontend"
    
    # Check if frontend is built (dist folder should have JS/CSS files, not just index.html)
    if [ -d "/workspace/frontend/dist" ]; then
        ASSET_COUNT=$(find /workspace/frontend/dist -type f \( -name "*.js" -o -name "*.css" \) 2>/dev/null | wc -l)
        
        if [ "$ASSET_COUNT" -eq 0 ]; then
            echo "⚠️  Frontend dist/ folder exists but is empty (no JS/CSS assets)"
            
            # Check if we have Node.js available (dev image)
            if command -v npm >/dev/null 2>&1; then
                echo "🔨 Building frontend with Vite (npm run build)..."
                cd /workspace/frontend
                
                # Install dependencies if node_modules missing
                if [ ! -d "node_modules" ]; then
                    echo "📦 Installing npm dependencies first..."
                    npm install
                fi
                
                # Build the frontend
                if npm run build; then
                    echo "✅ Frontend build completed successfully"
                else
                    echo "❌ Frontend build failed"
                    exit 1
                fi
                
                cd /workspace
            else
                echo "❌ ERROR: Node.js not available in production image"
                echo "💡 Solution: Build frontend before deployment or use dev image"
                echo "   Run locally: cd modules/$MODULE_NAME/frontend && npm run build"
                exit 1
            fi
        else
            echo "✅ Frontend already built ($ASSET_COUNT JS/CSS assets found)"
        fi
    else
        echo "❌ ERROR: /workspace/frontend/dist directory not found"
        echo "💡 Frontend must be built before starting in production mode"
        exit 1
    fi
fi

# Configure Nginx (Frontend Webserver) - only in production mode
if [ "$ENABLE_FRONTEND_WEBSERVER" = "true" ]; then
    echo "✅ Enabling Nginx (Frontend Webserver)"
    sudo sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf 2>/dev/null || \
    sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /workspace/supervisord.conf 2>/dev/null || true
else
    echo "⚠️ Nginx (Frontend Webserver) disabled"
fi

# Configure Uvicorn (Backend ASGI Server)
if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
    echo "✅ Enabling Uvicorn (Backend ASGI Server)"
    sudo sed -i '/\[program:uvicorn\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf 2>/dev/null || \
    sed -i '/\[program:uvicorn\]/,/^\[/ s/autostart=false/autostart=true/' /workspace/supervisord.conf 2>/dev/null || true
else
    echo "⚠️ Uvicorn (Backend ASGI Server) disabled"
fi

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