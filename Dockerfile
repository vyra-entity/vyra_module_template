# Multi-Stage Dockerfile
# Stage 1: Builder (ROS2 Build + SROS2 + Frontend)
# Stage 2: Runtime (Production-ready with pre-built artifacts)

# =============================================================================
# Stage 1: Builder
# =============================================================================
FROM vyra_base_image:dev AS builder

# Accept MODULE_NAME as build argument (provided by GitHub Actions or docker-compose)
ARG MODULE_NAME
ENV MODULE_NAME=${MODULE_NAME}

WORKDIR /build

# Copy source code and configuration
COPY src/ ./src/
COPY config/ ./config/
COPY tools/ ./tools/
COPY .module/ ./.module/
COPY frontend/ ./frontend/
COPY wheels/ ./wheels/

# Install Python dependencies
RUN if [ -f ".module/requirements.txt" ]; then \
        pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; \
    fi

# Install system packages if needed
RUN if [ -f ".module/system-packages.txt" ]; then \
        apt-get update -qq && \
        while read -r package; do \
            [ -n "$package" ] && [ "${package:0:1}" != "#" ] && apt-get install -y "$package" || exit 0; \
        done < .module/system-packages.txt; \
        apt-get clean && rm -rf /var/lib/apt/lists/*; \
    fi

# Install wheel dependencies (required for setup_interfaces.py)
RUN if [ -d "wheels" ]; then \
        pip install wheels/*.whl --break-system-packages --ignore-installed cryptography || true; \
    fi

# Setup ROS2 interfaces (script expects /workspace directory structure)
# Create temporary symlink from /workspace -> /build for setup_interfaces.py
RUN mkdir -p /workspace && \
    cp -r src /workspace/ && \
    cp -r tools /workspace/ && \
    cd /workspace && \
    python3 tools/setup_interfaces.py && \
    cp -r /workspace/src/* /build/src/ && \
    rm -rf /workspace

# Build ROS2 packages
RUN source /opt/ros/kilted/setup.bash && \
    colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release

# Generate SROS2 keystore and enclave
RUN source /opt/ros/kilted/setup.bash && \
    ros2 security create_keystore ./sros2_keystore && \
    ros2 security create_enclave ./sros2_keystore /${MODULE_NAME}/core

# Generate merged SROS2 policy
RUN python3 tools/generate_sros2_policy.py \
    --static config/sros2_policy_static.xml \
    --dynamic config/sros2_policy_dynamic.xml \
    --output sros2_keystore/enclaves/${MODULE_NAME}/core

# Build Frontend (if exists and has required files)
# Note: Using 'npm install' for template flexibility (generates package-lock.json)
# Production modules should use 'npm ci' with committed package-lock.json
RUN if [ -d "frontend" ] && [ -f "frontend/package.json" ] && [ -d "frontend/src/views" ] && [ "$(ls -A frontend/src/views)" ]; then \
        cd frontend && \
        npm install && \
        npm run build && \
        cd ..; \
    else \
        echo "⚠️  Skipping frontend build (template or incomplete frontend structure)"; \
        mkdir -p frontend/dist && \
        echo '<!DOCTYPE html><html><body><h1>Frontend Template</h1></body></html>' > frontend/dist/index.html; \
    fi

# Extract SROS2 CA for sharing with other modules
# SROS2 v2 uses different file names - try both old and new naming conventions
RUN if [ -f "./sros2_keystore/ca.cert.pem" ]; then \
        cp ./sros2_keystore/ca.cert.pem ./sros2_ca_public.pem; \
    elif [ -f "./sros2_keystore/public/ca.cert.pem" ]; then \
        cp ./sros2_keystore/public/ca.cert.pem ./sros2_ca_public.pem; \
    else \
        find ./sros2_keystore -name "*.pem" -o -name "ca.*" && \
        echo "ERROR: Could not find SROS2 CA certificate" && exit 1; \
    fi

# =============================================================================
# Stage 2: Runtime
# =============================================================================
FROM vyra_base_image:prod AS runtime

ENV MODULE_NAME=${MODULE_NAME}

WORKDIR /workspace

# Copy built artifacts from builder
COPY --from=builder /build/install/ ./install/
COPY --from=builder /build/sros2_keystore/ ./sros2_keystore/
COPY --from=builder /build/sros2_ca_public.pem ./sros2_ca_public.pem
COPY --from=builder /build/config/ ./config/
COPY --from=builder /build/tools/ ./tools/
COPY --from=builder /build/.module/ ./.module/
COPY --from=builder /build/frontend/dist ./frontend/dist
COPY --from=builder /build/src/rest_api ./src/rest_api

# Create runtime directories
RUN mkdir -p log/ros2 log/nginx log/uvicorn log/vyra storage

# Install runtime dependencies only
RUN if [ -f ".module/requirements.txt" ]; then \
        pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; \
    fi

# Set ROS2 environment
ENV ROS_DOMAIN_ID=42
ENV ROS_SECURITY_KEYSTORE=/workspace/sros2_keystore
ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore

# Default to production build mode
ENV VYRA_BUILD_MODE=ci

LABEL maintainer="VYRA Development Team"
LABEL module="${MODULE_NAME}"
LABEL stage="runtime"

CMD ["/workspace/tools/vyra_entrypoint_runtime.sh"]
