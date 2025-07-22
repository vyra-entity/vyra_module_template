# ROS 2 Kilted Kaiju Base Image (inkl. ROS-Base vorinstalliert)
FROM ros:kilted-ros-base

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

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
COPY . .

# Policies ins Image kopieren
# COPY security/policies /workspace/security/policies

# Alte ROS-Builds löschen
RUN rm -rf build/ install/ log/

SHELL ["/bin/bash", "-c"]

# Entrypoint-Skript ausführbar machen
RUN chmod +x /workspace/ros_entrypoint.sh

# Interfaces vorbereiten
RUN python3 /workspace/tools/setup_interfaces.py

# ROS 2 Workspace bauen
RUN source /opt/ros/kilted/setup.bash && colcon build

# Umgebungsvariablen für ROS 2 Security (SROS2)
ENV ROS_DOMAIN_ID=0
ENV ROS_SECURITY_KEYSTORE=/workspace/sros2_keystore
ENV ROS_SECURITY_ENABLE=true
ENV ROS_SECURITY_STRATEGY=Enforce
ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore

# Einstiegspunkt
ENTRYPOINT ["/workspace/ros_entrypoint.sh"]
CMD ["bash"]