# ROS 2 Kilted Kaiju Multi-Stage Build (dev/prod)
# Build Production: docker build --target production -t vyra_base_image:prod .
# Build Development: docker build --target development -t vyra_base_image:dev .

# ============================================================================
# BASE STAGE - Minimal dependencies for both dev and prod
# ============================================================================
FROM ros:kilted-ros-core AS base

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# User und Gruppe anlegen (z.B. vyrauser mit UID 1000)
RUN groupadd -r vyrauser && useradd -r -g vyrauser vyrauser
RUN mkdir /workspace
RUN mkdir /workspace/log
RUN mkdir /workspace/log/vyra
RUN mkdir /workspace/log/nginx
RUN mkdir /workspace/log/uvicorn

RUN mkdir /host
RUN usermod -aG sudo vyrauser
RUN echo "vyrauser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Python 3.11 aus deadsnakes PPA installieren (ERFORDERLICH für SROS2)
# Fix: "TypeError: curve must be an EllipticCurve instance" mit cryptography>=43 + Python 3.12
# WICHTIG: ROS2 Kilted nutzt Python 3.12, daher beide Versionen parallel
# Install ESSENTIAL packages (required for both dev and prod) in one layer
RUN apt-get update && apt-get install -y software-properties-common \
    && add-apt-repository -y ppa:deadsnakes/ppa \
    && apt-get update \
    && apt-get install -y \
    # === MINIMAL REQUIRED ===
    curl \
    iputils-ping \
    locales \
    python3-pip \
    redis-tools \
    supervisor \
    openssl \
    nginx \
    # === ROS2 SECURITY (SROS2) ===
    ros-kilted-sros2 \
    # === BUILD TOOLS (required for colcon build) ===
    python3-colcon-common-extensions \
    python3-colcon-core \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8

# Python packages and SROS2 fixes (common for all stages)

# Python 3.12 bleibt Standard (für ROS2 Kompatibilität)
# Python 3.11 wird für user-Module und SROS2 verwendet
# RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.12 1 \
#     && update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.11 2 \
#     && update-alternatives --set python3 /usr/bin/python3.12

# NumPy für beide Python-Versionen installieren (ERFORDERLICH für CMake rosidl_generator_py)
# System-NumPy ist für Python 3.12 kompiliert, muss für Python 3.11 separat installiert werden
# RUN rm -rf /usr/lib/python3/dist-packages/numpy* \
#     && python3.11 -m pip install --no-cache-dir numpy --break-system-packages \
#     && python3 -m pip install --no-cache-dir numpy --break-system-packages

# typing_extensions aktualisieren (für moderne Python Features)
RUN python3 -m pip install --upgrade typing_extensions --ignore-installed --break-system-packages

# SROS2 Fix: cryptography 42.0.8 installieren (< 43.0.0, behebt EllipticCurve TypeError)
# Upgrade von System python3-cryptography 41.0.7 auf pip-Version 42.0.8
# cryptography 42.x funktioniert mit Python 3.12 und SROS2
# WICHTIG: --ignore-installed verhindert Deinstallation des System-Pakets
RUN python3 -m pip install --no-cache-dir "cryptography==42.0.8" --ignore-installed --break-system-packages

# SROS2 Patch: Fix für cryptography 42.x API (ec.SECP256R1 -> ec.SECP256R1())
# Bug in /opt/ros/kilted/lib/python3.12/site-packages/sros2/_utilities.py:74
# generate_private_key() erwartet eine Kurven-Instanz, nicht die Klasse selbst
RUN sed -i 's/ec\.generate_private_key(ec\.SECP256R1,/ec.generate_private_key(ec.SECP256R1(),/g' \
    /opt/ros/kilted/lib/python3.12/site-packages/sros2/_utilities.py

WORKDIR /workspace

COPY supervisord.conf /etc/supervisor/conf.d/supervisord.conf
COPY rotate_logs.sh /opt/vyra/rotate_logs.sh
RUN chmod +x /opt/vyra/rotate_logs.sh

SHELL ["/bin/bash", "-c"]

RUN mkdir /workspace/.module
COPY requirements.txt /workspace/.module/requirements.txt
RUN pip install --no-cache-dir -r .module/requirements.txt --break-system-packages

# Umgebungsvariablen für ROS 2 Security (SROS2)
ENV ROS_DOMAIN_ID=0
ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore

# ============================================================================
# PRODUCTION STAGE - Minimal runtime (no dev tools)
# ============================================================================
FROM base AS production

LABEL maintainer="VYRA Development Team"
LABEL stage="production"
LABEL description="Minimal production image without development tools"

CMD ["/bin/bash"]

# ============================================================================
# DEVELOPMENT STAGE - Full dev tools for debugging and development
# ============================================================================
FROM base AS development

LABEL maintainer="VYRA Development Team"
LABEL stage="development"
LABEL description="Development image with debugging tools, Node.js, and build utilities"

# Install development tools
RUN apt-get update && apt-get install -y \
    vim \
    git \
    htop \
    build-essential \
    net-tools \
    wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Node.js installieren (für Frontend-Entwicklung mit Vite)
RUN curl -fsSL https://deb.nodesource.com/setup_22.x | bash - \
    && apt-get install -y nodejs \
    && npm install -g npm@latest \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash"]

# ============================================================================
# DEFAULT STAGE - Alias production as default target
# ============================================================================
FROM production AS default