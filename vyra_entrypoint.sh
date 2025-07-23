#!/bin/bash
# python3 /workspace/tools/setup_interfaces.py

source /opt/ros/kilted/setup.bash
source /workspace/install/setup.bash

# SROS2 Keystore erzeugen, falls nicht vorhanden
if [ ! -d "$ROS_SECURITY_KEYSTORE" ]; then
    echo "[SROS2] Erzeuge Keystore on $ROS_SECURITY_KEYSTORE"
    ros2 security create_keystore $ROS_SECURITY_KEYSTORE
fi

if [ ! -d "$ROS_SECURITY_KEYSTORE/enclaves" ]; then
    echo "[SROS2] Erzeuge Enclaves on $ROS_SECURITY_KEYSTORE"
    mkdir -p $ROS_SECURITY_KEYSTORE/enclaves
fi

# Enclave fuer vyra_module_template erzeugen
ros2 security create_enclave $ROS_SECURITY_KEYSTORE /vyra_module_template/core


# if [ ! -d "$ROS_SECURITY_KEYSTORE/enclaves/vyra_module_interfaces" ]; then
#     echo "[SROS2] Erzeuge Keystore on $ROS_SECURITY_KEYSTORE"
#     mkdir -p $ROS_SECURITY_KEYSTORE/enclaves/vyra_module_interfaces
# fi

# if [ ! -d "$ROS_SECURITY_KEYSTORE/enclaves/vyra_module_template" ]; then
#     echo "[SROS2] Erzeuge Keystore on $ROS_SECURITY_KEYSTORE"
#     mkdir -p $ROS_SECURITY_KEYSTORE/enclaves/vyra_module_template
# fi

# cp -r ./sros2_keystore/enclaves/* $ROS_SECURITY_KEYSTORE/enclaves/

# echo "[SROS2] Lade Permissions aus Datei..."
# ros2 security create_permission \
#     $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_interfaces \
#     /workspace/sros2_keystore/enclaves/vyra_module_interfaces/permissions.xml
# ros2 security create_permission \
#     $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_template \
#     /workspace/sros2_keystore/enclaves/vyra_module_template/permissions.xml

exec "$@"
