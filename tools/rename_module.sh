#!/bin/bash

# This script will take a name as input argument and rename every
# occurence in the subdirektories and files

if [ -z "$1" ]; then
    echo "⚠️ Usage: $0 <new_module_name given>"
    exit 1
fi

TEMPLATE_NAME="vyra_module_template"

# Prüfe alle Argumente auf --old_name=
for arg in "$@"; do
    if [[ "$arg" == "--old_name="* ]]; then
        TEMPLATE_NAME="${arg#--old_name=}"
        break
    fi
done

echo "Renaming module from '$TEMPLATE_NAME' to '$1'"

# safe filepath of this script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

NEW_NAME=$1


# Rename the node in the package directory
NODE_DIR="$SCRIPT_DIR/../src/$TEMPLATE_NAME/$TEMPLATE_NAME"
if [ -d "$NODE_DIR" ]; then
    echo "✅ Renaming node directory: $NODE_DIR to $NEW_NAME"
    mv "$NODE_DIR" "$SCRIPT_DIR/../src/$TEMPLATE_NAME/$NEW_NAME"
else
    echo "⚠️ Node directory $NODE_DIR not found."

fi


# Rename the ros2 package itself
ROS2_PACKAGE_DIR="$SCRIPT_DIR/../src/$TEMPLATE_NAME"
if [ -d "$ROS2_PACKAGE_DIR" ]; then
    echo "✅ Renaming ROS2 package directory: $ROS2_PACKAGE_DIR to $SCRIPT_DIR/../src/$NEW_NAME"
    mv "$ROS2_PACKAGE_DIR" "$SCRIPT_DIR/../src/$NEW_NAME"
else
    echo "⚠️ ROS2 package directory $ROS2_PACKAGE_DIR not found."
fi

# Rename the module in the config file
CONFIG_FILE="$SCRIPT_DIR/../src/$NEW_NAME/resource/module_config.yaml"
if [ -f "$CONFIG_FILE" ]; then
    echo "✅ Renaming module in config file: $CONFIG_FILE"
    sed -i "s/^package_name: .*/package_name: $NEW_NAME/" "$CONFIG_FILE"
else
    echo "⚠️ Config file $CONFIG_FILE not found."

fi

# Rename the module in the permission file
SETUP_FILE="$SCRIPT_DIR/../src/$NEW_NAME/setup.py"

if [ -f "$SETUP_FILE" ]; then
    echo "✅ Renaming module in setup file: $SETUP_FILE"
    sed -i "s/^package_name\s*=\s* .*/package_name = '$NEW_NAME'/" "$SETUP_FILE"
else
    echo "⚠️ Setup file $SETUP_FILE not found."
fi

# Rename the module in the package .xml file
PACKAGE_XML="$SCRIPT_DIR/../src/$NEW_NAME/package.xml"
if [ -f "$PACKAGE_XML" ]; then
    echo "✅ Renaming module in package.xml file: $PACKAGE_XML"
    sed -i "s/<name>.*<\/name>/<name>$NEW_NAME<\/name>/" "$PACKAGE_XML"
else
    echo "⚠️ Package XML file $PACKAGE_XML not found."

fi  

# Rename the module in the setup.cfg file
SETUP_CFG="$SCRIPT_DIR/../src/$NEW_NAME/setup.cfg"
if [ -f "$SETUP_CFG" ]; then
    echo "✅ Renaming module in setup.cfg file: $SETUP_CFG"
    sed -i "s/^script_dir\s*=\s*.*/script_dir = \$base\/lib\/$NEW_NAME/" "$SETUP_CFG"
    sed -i "s/^install_scripts\s*=\s*.*/install_scripts = \$base\/lib\/$NEW_NAME/" "$SETUP_CFG"
else
    echo "⚠️ Setup.cfg file $SETUP_CFG not found."
fi

# Rename in update_ros.sh
UPDATE_ROS_FILE="$SCRIPT_DIR/../tools/update_ros.sh"
if [ -f "$UPDATE_ROS_FILE" ]; then
    echo "✅ Renaming module in update_ros.sh: $UPDATE_ROS_FILE"
    sed -i "s/vyra_module_template/$NEW_NAME/g" "$UPDATE_ROS_FILE"
else
    echo "⚠️ Update ROS script $UPDATE_ROS_FILE not found."
fi

# Rename in vyra_entrypoint.sh
ENTRYPOINT_FILE="$SCRIPT_DIR/../vyra_entrypoint.sh"
if [ -f "$ENTRYPOINT_FILE" ]; then
    echo "✅ Renaming module in vyra_entrypoint.sh: $ENTRYPOINT_FILE"
    sed -i "s/vyra_module_template/$NEW_NAME/g" "$ENTRYPOINT_FILE"
else
    echo "⚠️ Entry point script $ENTRYPOINT_FILE not found."
fi

# Rename pyproject.toml
PYPROJECT_FILE="$SCRIPT_DIR/../pyproject.toml"
if [ -f "$PYPROJECT_FILE" ]; then
    echo "✅ Renaming module in pyproject.toml: $PYPROJECT_FILE"
    sed -i "s/^module_name\s*=\s*.*/module_name = \"$NEW_NAME\"/" "$PYPROJECT_FILE"
else
    echo "⚠️ Pyproject file $PYPROJECT_FILE not found."
fi

# Rename ros2 resource file
RESOURCE_FILE="$SCRIPT_DIR/../src/$NEW_NAME/resource/$TEMPLATE_NAME"

if [ -f "$RESOURCE_FILE" ]; then
    echo "✅ Renaming resource file: $RESOURCE_FILE to $SCRIPT_DIR/../src/$NEW_NAME/resource/$NEW_NAME"
    mv "$RESOURCE_FILE" "$SCRIPT_DIR/../src/$NEW_NAME/resource/$NEW_NAME"
else
    echo "⚠️ Resource file $RESOURCE_FILE not found."
fi