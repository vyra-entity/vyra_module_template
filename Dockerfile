# Direktes ROS 2 Humble Base Image (inkl. ROS-Base vorinstalliert)
FROM ros:humble-ros-base

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# System-Tools installieren
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
    python3.10 \
    python3.10-venv \
    python3.10-dev \
    python3.10-distutils \
    ros-humble-sros2 \
    python3-colcon-common-extensions \
    && locale-gen en_US.UTF-8

# Python 3.10 als Standard setzen
RUN update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.10 1

# pip für Python 3.10 installieren
RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
    && python3.10 get-pip.py \
    && rm get-pip.py

# Poetry installieren
# RUN curl -sSL https://install.python-poetry.org | python3.10 - \
#     && ln -s ~/.local/bin/poetry /usr/local/bin/poetry

# Arbeitsverzeichnis
WORKDIR /workspace

# Projektdateien kopieren
COPY . .

# Policies ins Image kopieren
# COPY security/policies /workspace/security/policies

# Poetry ohne virtuelle Umgebung
# RUN poetry config virtualenvs.create false

# Python-Tools aktualisieren
RUN python3 -m pip install --upgrade pip setuptools packaging

# Alte ROS-Builds löschen
RUN rm -rf build/ install/ log/

# Bash als Standardshell
SHELL ["/bin/bash", "-c"]

# Entrypoint-Skript ausführbar machen
RUN chmod +x /workspace/ros_entrypoint.sh

# Interfaces vorbereiten
RUN python3 /workspace/tools/setup_interfaces.py

# ROS 2 Workspace bauen
RUN source /opt/ros/humble/setup.bash && colcon build


# Umgebungsvariablen für ROS 2
ENV ROS_DOMAIN_ID=0
ENV ROS_SECURITY_KEYSTORE=/workspace/sros2_keystore
ENV ROS_SECURITY_ENABLE=true
ENV ROS_SECURITY_STRATEGY=Enforce
ENV ROS_SECURITY_ROOT_DIRECTORY=/workspace/sros2_keystore

# Einstiegspunkt
ENTRYPOINT ["/workspace/ros_entrypoint.sh"]
CMD ["bash"]
