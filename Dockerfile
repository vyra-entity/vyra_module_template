# ROS 2 Kilted Kaiju Base Image (inkl. ROS-Base vorinstalliert)
FROM ros:kilted-ros-base

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# User und Gruppe anlegen (z.B. vyrauser mit UID 1000)
RUN groupadd -r vyrauser && useradd -r -g vyrauser vyrauser
RUN mkdir /workspace && chown vyrauser:vyrauser /workspace
RUN usermod -aG sudo vyrauser
RUN echo "vyrauser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# System-Tools und ROS-Tools installieren
RUN apt update && apt install -y \
    software-properties-common \
    curl \
    gnupg \
    lsb-release \
    build-essential \
    git \
    locales \
    python3-tk \
    python3-pip \
    python3.12-venv \
    python3.12-dev \
    ros-kilted-sros2 \
    python3-colcon-common-extensions \
    redis-tools \
    && locale-gen en_US.UTF-8

# Python 3.12 als Standard setzen
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.12 1

RUN python3 -m pip install --upgrade typing_extensions cryptography --ignore-installed --break-system-packages

# Passende cryptography + pyopenssl installieren
RUN python3 -m pip install --upgrade setuptools --break-system-packages \
    && python3 -m pip install cryptography pyOpenSSL --break-system-packages

# pip für Python 3.12 installieren (falls nötig)
# RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
#     && python3.12 get-pip.py \
#     && rm get-pip.py

WORKDIR /workspace

# Projektdateien kopieren
# COPY . .
COPY src /workspace/src
COPY tools /workspace/tools
COPY wheels /workspace/wheels
COPY docs /workspace/docs
COPY LICENSE /workspace/LICENSE
COPY README.md /workspace/README.md
COPY pyproject.toml /workspace/pyproject.toml
COPY vyra_entrypoint.sh /workspace/vyra_entrypoint.sh

# Policies ins Image kopieren
# COPY security/policies /workspace/security/policies

# Alte ROS-Builds löschen
RUN rm -rf build/ install/ log/

SHELL ["/bin/bash", "-c"]

# Entrypoint-Skript ausführbar machen
RUN chmod +x /workspace/vyra_entrypoint.sh

# Interfaces vorbereiten
RUN python3 /workspace/tools/setup_interfaces.py

# ROS 2 Workspace bauen
RUN source /opt/ros/kilted/setup.bash && colcon build

# Umgebungsvariablen für ROS 2 Security (SROS2)
ENV ROS_DOMAIN_ID=0
# ENV ROS_SECURITY_KEYSTORE=/workspace/sros2_keystore
# ENV ROS_SECURITY_ENABLE=true
# ENV ROS_SECURITY_STRATEGY=Enforce
# ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore

# Einstiegspunkt
ENTRYPOINT ["/workspace/vyra_entrypoint.sh"]
CMD ["bash"]