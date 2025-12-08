# ==============================================================================
# VYRA Module Dockerfile - Optimized Multi-Stage Build
# Module: ${MODULE_NAME}"
# Base Image: vyra_base_image:dev (builder), vyra_base_image:prod (runtime)
# ==============================================================================
# This Dockerfile builds ONLY the module layer on top of the shared base image
# Savings: ~2.3GB per module (99% base image redundancy eliminated)
# ==============================================================================

# =============================================================================
# Stage 1: Builder - Build ROS2 packages, frontend, and SROS2 keys
# =============================================================================
FROM ghcr.io/vyra-entity/vyra_framework:dev AS builder
# FROM vyra_base_image:dev AS builder

# Module name from build argument
ARG MODULE_NAME
ENV MODULE_NAME=${MODULE_NAME}

WORKDIR /build

# Copy module sources
COPY src/ ./src/
COPY config/ ./config/
COPY tools/ ./tools/
COPY .module/ ./.module/
COPY frontend/ ./frontend/
COPY wheels/ ./wheels/

# Install module-specific Python dependencies
RUN if [ -f ".module/requirements.txt" ]; then \
        pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; \
    fi

# Install module-specific system packages
RUN if [ -f ".module/system-packages.txt" ]; then \
        apt-get update -qq && \
        while read -r package; do \
            [ -n "$package" ] && [ "${package:0:1}" != "#" ] && apt-get install -y "$package" || exit 0; \
        done < .module/system-packages.txt; \
        apt-get clean && rm -rf /var/lib/apt/lists/*; \
    fi

# Install wheel dependencies
RUN if [ -d "wheels" ]; then \
        pip install wheels/*.whl --break-system-packages --ignore-installed cryptography || true; \
    fi

# Setup ROS2 interfaces
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

# Generate SROS2 keystore
RUN source /opt/ros/kilted/setup.bash && \
    ros2 security create_keystore ./sros2_keystore && \
    ros2 security create_enclave ./sros2_keystore /${MODULE_NAME}/core

# Generate merged SROS2 policy
RUN python3 tools/generate_sros2_policy.py \
    --static config/sros2_policy_static.xml \
    --dynamic config/sros2_policy_dynamic.xml \
    --output sros2_keystore/enclaves/${MODULE_NAME}/core

RUN if [ -d "frontend" ] && [ -f "frontend/package.json" ] && [ -d "frontend/src/views" ] && [ "$(ls -A frontend/src/views)" ]; then \
        cd frontend && \
        npm install && \
        npm run build && \
        cd ..; \
    else \
        echo "⚠️  Skipping frontend build (template or incomplete structure)"; \
        mkdir -p frontend/dist && \
        echo '<!DOCTYPE html><html><body><h1>Frontend Template</h1></body></html>' > frontend/dist/index.html; \
    fi

# Extract SROS2 CA certificate
RUN if [ -f "./sros2_keystore/ca.cert.pem" ]; then \
        cp ./sros2_keystore/ca.cert.pem ./sros2_ca_public.pem; \
    elif [ -f "./sros2_keystore/public/ca.cert.pem" ]; then \
        cp ./sros2_keystore/public/ca.cert.pem ./sros2_ca_public.pem; \
    else \
        find ./sros2_keystore -name "*.pem" -o -name "ca.*" && \
        echo "ERROR: Could not find SROS2 CA certificate" && exit 1; \
    fi

# =============================================================================
# Stage 2: Runtime - Minimal module layer (~150MB)
# =============================================================================
FROM ghcr.io/vyra-entity/vyra_framework:prod AS runtime
# FROM vyra_base_image:prod AS runtime

ARG MODULE_NAME
ENV MODULE_NAME=${MODULE_NAME}

WORKDIR /workspace

# Copy ONLY module artifacts (base image already has everything else)
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

# Install runtime dependencies
RUN if [ -f ".module/requirements.txt" ]; then \
        pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; \
    fi

# ROS2 environment configuration
ENV ROS_DOMAIN_ID=42
ENV ROS_SECURITY_KEYSTORE=/workspace/sros2_keystore
ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore
ENV VYRA_BUILD_MODE=ci

LABEL maintainer="VYRA Development Team" \
      org.opencontainers.image.source="https://github.com/variobotic-gmbh/${MODULE_NAME}" \
      module="${MODULE_NAME}" \
      stage="runtime"

CMD ["/workspace/tools/vyra_entrypoint_runtime.sh"]

