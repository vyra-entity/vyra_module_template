#!/bin/bash
# python3 /workspace/tools/setup_interfaces.py

source /opt/ros/kilted/setup.bash
source /workspace/install/setup.bash

# SROS2 Keystore erzeugen, falls nicht vorhanden
if [ ! -d "$ROS_SECURITY_ROOT_DIRECTORY" ]; then
    echo "[SROS2] Erzeuge Keystore on $ROS_SECURITY_ROOT_DIRECTORY"
    ros2 security create_keystore $ROS_SECURITY_ROOT_DIRECTORY
    ros2 security create_enclave $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_interfaces
    ros2 security create_enclave $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_template

    echo "[SROS2] Lade Permissions aus Datei..."
    # ros2 security create_permission \
    #     $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_interfaces \
    #     /workspace/sros2_keystore/enclaves/vyra_module_interfaces/permissions.xml
    # ros2 security create_permission \
    #     $ROS_SECURITY_ROOT_DIRECTORY /vyra_module_template \
    #     /workspace/sros2_keystore/enclaves/vyra_module_template/permissions.xml
fi

exec "$@"
