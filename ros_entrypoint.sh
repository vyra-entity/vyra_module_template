#!/bin/bash
# python3 /workspace/tools/setup_interfaces.py

source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# SROS2 Keystore erzeugen, falls nicht vorhanden
if [ ! -d "$ROS_SECURITY_ROOT_DIRECTORY" ]; then
    echo "[SROS2] Erzeuge Keystore..."
    sros2 security create_keystore $ROS_SECURITY_ROOT_DIRECTORY
    sros2 security create_key $ROS_SECURITY_ROOT_DIRECTORY vyra_secure_node

    echo "[SROS2] Lade Permissions aus Datei..."
    sros2 security create_permission \
        $ROS_SECURITY_ROOT_DIRECTORY \
        vyra_secure_node \
        /workspace/security/policies/vyra_secure_node/permissions.xml
fi

exec "$@"
