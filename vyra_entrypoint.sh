#!/bin/bash
# filepath: /home/holgder/VOS2_WORKSPACE/$MODULE_NAME/vyra_entrypoint.sh
set -euo pipefail

echo "=== VYRA ENTRYPOINT STARTING ==="

# Warte kurz für vollständige Installation
# sleep 2

chmod 777 .env

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
        echo "✅ RCL logging configured: ${MODULE_NAME}_ros2_core.log"
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

# Vyra Base installieren
# source /workspace/tools/setup_ros_global.sh
source /opt/ros/kilted/setup.bash

if [ $? -eq 0 ]; then
    echo "✅ Source ROS global setup successful"
else
    echo "❌ Source ROS global setup failed"
    exit 1
fi

# Create log directories required by supervisord
mkdir -p /workspace/log/vyra
mkdir -p /workspace/log/uvicorn
mkdir -p /workspace/log/nginx
mkdir -p /workspace/log/ros2

# Copy install/ directory from image if not present or incomplete (volume mount overrides image)
# This happens when using full workspace mount for development
if [ -d "/opt/vyra/install_backup" ]; then
    if [ ! -f "/workspace/install/setup.bash" ]; then
        echo "📦 Copying install/ directory from image backup..."
        rm -rf /workspace/install  # Remove incomplete directory if exists
        cp -r /opt/vyra/install_backup /workspace/install
        echo "✅ install/ directory restored"
    else
        echo "✅ install/ directory already complete (setup.bash found)"
    fi
else
    if [ ! -f "/workspace/install/setup.bash" ]; then
        echo "❌ ERROR: install/setup.bash not found and no backup available"
        echo "💡 Image may not have been built correctly"
        exit 1
    fi
fi

# Source package setup (install folder already built in image or restored)
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
        # Note: ros2_main is the supervisord program name for the ROS2 node
        nohup python3 /workspace/tools/ros2_hot_reload.py "$MODULE_NAME" core ros2_main \
            > /workspace/log/ros2/hot_reload.log 2>&1 &
        
        HOT_RELOAD_PID=$!
        echo "✅ ROS2 Hot Reload started (PID: $HOT_RELOAD_PID)"
        echo "   Watching: /workspace/src"
        echo "   Logs: /workspace/log/ros2/hot_reload.log"
    fi

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

    # Alter reload=True on uvicorn in /etc/supervisor/conf.d/supervisord.conf for developement
    echo "🔄 Enabling autoreload for Uvicorn (FastAPI)..."
    echo "   Watch directory: $BACKEND_DEV_FILEWATCH"
    
    BACKEND_DEV_FILEWATCH_SED=$(echo "$BACKEND_DEV_FILEWATCH" | sed 's/\//\\\//g')

    # Add --reload and --reload-dir for both SSL and non-SSL variants using the env variable
    sed -i "/exec uvicorn src.asgi:application.*--host 0.0.0.0 --port 8443/s/--log-level info/--log-level info --reload --reload-dir $BACKEND_DEV_FILEWATCH_SED --reload-exclude \/workspace\/log/" /etc/supervisor/conf.d/supervisord.conf
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
    sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf 2>/dev/null || \
    sed -i '/\[program:nginx\]/,/^\[/ s/autostart=false/autostart=true/' /workspace/supervisord.conf 2>/dev/null || true
else
    echo "⚠️ Nginx (Frontend Webserver) disabled"
fi

# Configure Uvicorn (Backend ASGI Server)
if [ "$ENABLE_BACKEND_WEBSERVER" = "true" ]; then
    echo "✅ Enabling Uvicorn (Backend ASGI Server)"
    sed -i '/\[program:uvicorn\]/,/^\[/ s/autostart=false/autostart=true/' /etc/supervisor/conf.d/supervisord.conf 2>/dev/null || \
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