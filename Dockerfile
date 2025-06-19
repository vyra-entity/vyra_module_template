# Basis: Ubuntu 22.04 (Jammy) mit ROS 2 Humble
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# System-Tools + Universe Repo aktivieren
RUN apt update && apt install -y \
    software-properties-common \
    curl \
    gnupg \
    lsb-release \
    build-essential \
    git \
    locales \
    python3-tk \
    && add-apt-repository universe \
    && locale-gen en_US.UTF-8
    

# Deadsnakes PPA hinzufügen und Python 3.10 installieren
RUN add-apt-repository ppa:deadsnakes/ppa \
    && apt update \
    && apt install -y python3.10 python3.10-venv python3.10-dev python3.10-distutils \
    && update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.10 1

# pip für Python 3.11 installieren
RUN curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py \
    && python3.10 get-pip.py \
    && rm get-pip.py

# Poetry systemweit installieren
RUN curl -sSL https://install.python-poetry.org | python3.10 - \
    && ln -s ~/.local/bin/poetry /usr/local/bin/poetry

# ROS 2 Humble Setup
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=amd64 signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu jammy main" > /etc/apt/sources.list.d/ros2.list

# RUN apt update && apt install -y ros-humble-desktop python3-colcon-common-extensions
RUN apt update && apt install -y ros-humble-ros-base python3-colcon-common-extensions


# Arbeitsverzeichnis
WORKDIR /workspace

# Projektdateien kopieren
COPY . .

# Poetry so konfigurieren, dass keine virtuelle Umgebung erstellt wird
RUN poetry config virtualenvs.create false

# Abhängigkeiten installieren
# RUN poetry install

# ROS 2 Workspace bauen
RUN python3 -m pip install --upgrade pip setuptools packaging

RUN rm -rf build/ install/ log/ 
SHELL ["/bin/bash", "-c"]

# # Entrypoint-Skript kopieren und ausführbar machen
RUN chmod +x /workspace/ros_entrypoint.sh

# Quelle ROS2 Umgebung + Workspace Setup
RUN python3 /workspace/tools/setup_interfaces.py

# RUN source /opt/ros/humble/setup.bash && colcon build --event-handlers console_direct+
RUN source /opt/ros/humble/setup.bash && colcon build

ENTRYPOINT ["/workspace/ros_entrypoint.sh"]
CMD ["bash"]
