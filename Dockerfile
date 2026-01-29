# ==============================================================================
# VYRA Module Dockerfile - Optimized Multi-Stage Build
# Module: ${MODULE_NAME}
# ==============================================================================
# Local Development: Uses vyra_base_image:development/production (built locally)
# CI/CD Production: Uses ghcr.io/vyra-entity/vyra_framework:development/slim
# ==============================================================================

# Base image configuration (override with --build-arg)
ARG BUILDER_BASE_IMAGE=vyra_base_image:development
ARG RUNTIME_BASE_IMAGE=vyra_base_image:production

# =============================================================================
# Stage 1: Builder - Build ROS2 packages, frontend, and SROS2 keys
# =============================================================================
FROM ${BUILDER_BASE_IMAGE} AS builder

# Module name from build argument
ARG MODULE_NAME
ENV MODULE_NAME=${MODULE_NAME}

# SROS2 security feature flag (default: false for backward compatibility)
ARG SECURE_BY_SROS2=false
ENV SECURE_BY_SROS2=${SECURE_BY_SROS2}

WORKDIR /workspace

# Clean workspace from base image to prevent stale packages
RUN rm -rf /workspace/src /workspace/build /workspace/install

# Copy module sources
COPY src/ ./src/
COPY config/ ./config/
COPY tools/ ./tools/
COPY vyra_entrypoint.sh ./vyra_entrypoint.sh
COPY .module/ ./.module/
COPY frontend/ ./frontend/
COPY wheels/ ./wheels/
COPY storage/ ./storage/

# Install module-specific Python dependencies
RUN if [ -f ".module/requirements.txt" ]; then \
        pip install --no-cache-dir -r .module/requirements.txt --break-system-packages; \
    fi

# Run pre-install script if exists (for custom repository setup, etc.)
RUN if [ -f ".module/pre-install.sh" ]; then \
        chmod +x .module/pre-install.sh && \
        ./.module/pre-install.sh; \
    fi

# Install module-specific system packages
RUN if [ -f ".module/system-packages.txt" ]; then \
        apt-get update -qq && \
        while read -r package; do \
            [ -n "$package" ] && [ "${package:0:1}" != "#" ] && apt-get install -y "$package" || exit 0; \
        done < .module/system-packages.txt; \
        apt-get clean && rm -rf /var/lib/apt/lists/*; \
    fi

# Install wheel dependencies (vyra_base and module-specific wheels) [only latest versions]
RUN if [ -d "wheels" ]; then \
        set -e; \
        tmpdir=$(mktemp -d); \
        \
        for pkg in $(ls wheels/*.whl | sed -E 's#.*/([^/-]+)-.*#\1#' | sort -u); do \
            latest=$(ls wheels/"$pkg"-*.whl | sort -V | tail -n 1); \
            cp "$latest" "$tmpdir/"; \
        done; \
        \
        pip install "$tmpdir"/*.whl \
            --break-system-packages \
            --force-reinstall \
            --no-deps \
            --ignore-installed cryptography; \
        \
        rm -rf "$tmpdir"; \
        # pip install wheels/*.whl --break-system-packages --ignore-installed cryptography || true; \
    fi

# Setup ROS2 interfaces (already in /workspace)
RUN python3 tools/setup_interfaces.py

# Generate gRPC proto files from .proto definitions
RUN if [ -d "storage/interfaces" ] && [ "$(ls -A storage/interfaces/*.proto 2>/dev/null)" ]; then \
        echo "🔧 Generating gRPC proto files..."; \
        python3 tools/generate_grpc_protos.py \
            --proto-dir /workspace/storage/interfaces \
            --output-dir /workspace/src/rest_api/grpc_generated \
            --create-helpers; \
    else \
        echo "⚠️  No .proto files found in storage/interfaces, skipping gRPC generation"; \
    fi

# Clean any existing build artifacts for fresh build (prevents package name conflicts)
RUN rm -rf /workspace/install /workspace/build

# Build ROS2 packages (skip vyra_module_interfaces template from base image)
RUN source /opt/ros/kilted/setup.bash && \
    colcon build --packages-skip vyra_module_interfaces --cmake-args -DCMAKE_BUILD_TYPE=Release

# Extract MODULE_NAME from module_data.yaml if not provided
RUN if [ -z "$MODULE_NAME" ] && [ -f ".module/module_data.yaml" ]; then \
        export MODULE_NAME=$(grep "^name:" .module/module_data.yaml | cut -d: -f2 | tr -d ' ' | tr -d "'" | tr -d '"'); \
        echo "MODULE_NAME extracted from module_data.yaml: $MODULE_NAME"; \
    fi && \
    echo "MODULE_NAME=${MODULE_NAME}" > /tmp/module_name.env

# Copy module-specific interfaces to staging area for NFS volume
# This will be copied to NFS volume at runtime via entrypoint
RUN source /tmp/module_name.env && \
    mkdir -p /tmp/module_interfaces_staging/${MODULE_NAME}_interfaces && \
    if [ -d "install/${MODULE_NAME}_interfaces" ]; then \
        echo "📦 Staging ${MODULE_NAME}_interfaces for NFS volume..."; \
        cp -r install/${MODULE_NAME}_interfaces/* /tmp/module_interfaces_staging/${MODULE_NAME}_interfaces/; \
        echo "✓ Interfaces staged at /tmp/module_interfaces_staging/${MODULE_NAME}_interfaces"; \
    else \
        echo "⚠️  No ${MODULE_NAME}_interfaces found in install directory"; \
    fi

# Generate SROS2 keystore (only if SECURE_BY_SROS2=true)
RUN if [ "$SECURE_BY_SROS2" = "true" ]; then \
        echo "🔐 SROS2 Security enabled - generating keystore..."; \
        source /tmp/module_name.env && \
        source /opt/ros/kilted/setup.bash && \
        ros2 security create_keystore ./sros2_keystore && \
        ros2 security create_enclave ./sros2_keystore /${MODULE_NAME}/core; \
    else \
        echo "⚠️  SROS2 disabled - creating empty keystore directory"; \
        mkdir -p ./sros2_keystore; \
    fi

# Generate merged SROS2 policy (only if SECURE_BY_SROS2=true)
RUN if [ "$SECURE_BY_SROS2" = "true" ]; then \
        echo "🔐 Generating SROS2 policy..."; \
        python3 tools/generate_sros2_policy.py \
            --static config/sros2_policy_static.xml \
            --dynamic config/sros2_policy_dynamic.xml \
            --output sros2_keystore/enclaves/${MODULE_NAME}/core; \
    else \
        echo "⚠️  SROS2 disabled - skipping policy generation"; \
    fi

RUN if [ -d "frontend" ] && [ -f "frontend/package.json" ] && [ -d "frontend/src/views" ] && [ "$(ls -A frontend/src/views)" ]; then \
        cd frontend && \
        npm install && \
        npm run build && \
        rm -rf node_modules && \
        cd ..; \
    else \
        echo "⚠️  Skipping frontend build (template or incomplete structure)"; \
        mkdir -p frontend/dist && \
        echo '<!DOCTYPE html><html><body><h1>Frontend Template</h1></body></html>' > frontend/dist/index.html; \
    fi

# Extract SROS2 CA certificate (only if SROS2 is enabled)
RUN if [ "${SECURE_BY_SROS2}" = "true" ]; then \
        if [ -f "./sros2_keystore/ca.cert.pem" ]; then \
            cp ./sros2_keystore/ca.cert.pem ./sros2_ca_public.pem; \
        elif [ -f "./sros2_keystore/public/ca.cert.pem" ]; then \
            cp ./sros2_keystore/public/ca.cert.pem ./sros2_ca_public.pem; \
        else \
            echo "ERROR: SECURE_BY_SROS2=true but CA certificate not found" && exit 1; \
        fi; \
    else \
        echo "⚠️  SROS2 disabled - creating dummy certificate"; \
        echo "dummy-certificate" > ./sros2_ca_public.pem; \
    fi

# =============================================================================
# Stage 2: Runtime - Minimal module layer (~150MB)
# =============================================================================
FROM ${RUNTIME_BASE_IMAGE} AS runtime

ARG MODULE_NAME
ENV MODULE_NAME=${MODULE_NAME}

# Copy module name from builder stage if not set
COPY --from=builder /tmp/module_name.env /tmp/module_name.env
RUN if [ -z "$MODULE_NAME" ]; then \
        . /tmp/module_name.env; \
    fi

WORKDIR /workspace

# Copy ONLY module artifacts (base image already has everything else)
COPY --from=builder /workspace/install/ ./install/
# Note: build/ directory not needed in runtime (only for compilation)
COPY --from=builder /workspace/sros2_keystore/ ./sros2_keystore/
COPY --from=builder /workspace/sros2_ca_public.pem ./sros2_ca_public.pem
COPY --from=builder /workspace/config/ ./config/
COPY --from=builder /workspace/tools/ ./tools/
COPY --from=builder /workspace/vyra_entrypoint.sh ./vyra_entrypoint.sh
COPY --from=builder /workspace/.module/ ./.module/
COPY --from=builder /workspace/frontend/dist ./frontend/dist
COPY --from=builder /workspace/src/ ./src/
COPY --from=builder /workspace/storage/ ./storage/

# Copy staged interfaces for NFS volume initialization
COPY --from=builder /tmp/module_interfaces_staging/ /tmp/module_interfaces_staging/

# Backup install/ directory for volume mount scenarios
# When workspace is mounted as volume, install/ from image is hidden
RUN cp -r ./install /opt/vyra/install_backup

# Create runtime directories
RUN mkdir -p log/ros2 log/nginx log/uvicorn log/vyra storage

# Install Python dependencies for runtime (uvicorn, fastapi, etc.)
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

CMD ["/workspace/vyra_entrypoint.sh"]

