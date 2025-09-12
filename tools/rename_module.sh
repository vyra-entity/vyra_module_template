#!/bin/bash

# This script will take a name as input argument and rename every
# occurence in the subdirektories and files

# Check if $1 is provided, otherwise get name from .module/module_data.yaml
if [ -z "$1" ]; then
    # Try to read the name from .module/module_data.yaml
    MODULE_DATA_FILE="$(dirname "$(readlink -f "$0")")/../.module/module_data.yaml"
    if [ -f "$MODULE_DATA_FILE" ]; then
        NEW_MODULE_NAME=$(grep "^name:" "$MODULE_DATA_FILE" | sed 's/^name:[[:space:]]*//')
        if [ -n "$NEW_MODULE_NAME" ]; then
            echo "ℹ️ No module name provided as argument, using name from module_data.yaml: $NEW_MODULE_NAME"
            set -- "$NEW_MODULE_NAME" "${@:2}"  # Set $1 to the name from yaml
        else
            echo "⚠️ Could not read name from $MODULE_DATA_FILE"
            echo "⚠️ Usage: $0 <new_module_name> or ensure name is set in .module/module_data.yaml"
            exit 1
        fi
    else
        echo "⚠️ Module data file $MODULE_DATA_FILE not found"
        echo "⚠️ Usage: $0 <new_module_name>"
        exit 1
    fi
else
    echo "ℹ️ Using provided module name: $1"
    NEW_MODULE_NAME=$1
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
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
echo "Script directory: $SCRIPT_DIR"

# Rename the node in the package directory
NODE_DIR="$SCRIPT_DIR/../src/$TEMPLATE_NAME/$TEMPLATE_NAME"
if [ -d "$NODE_DIR" ]; then
    echo "✅ Renaming node directory: $NODE_DIR to $NEW_MODULE_NAME"
    mv "$NODE_DIR" "$SCRIPT_DIR/../src/$TEMPLATE_NAME/$NEW_MODULE_NAME"
else
    echo "⚠️ Node directory $NODE_DIR not found."

fi


# Rename the ros2 package itself
ROS2_PACKAGE_DIR="$SCRIPT_DIR/../src/$TEMPLATE_NAME"
if [ -d "$ROS2_PACKAGE_DIR" ]; then
    echo "✅ Renaming ROS2 package directory: $ROS2_PACKAGE_DIR to $SCRIPT_DIR/../src/$NEW_MODULE_NAME"
    mv "$ROS2_PACKAGE_DIR" "$SCRIPT_DIR/../src/$NEW_MODULE_NAME"
else
    echo "⚠️ ROS2 package directory $ROS2_PACKAGE_DIR not found."
fi

# Rename the module in the config file
CONFIG_FILE="$SCRIPT_DIR/../src/$NEW_MODULE_NAME/resource/module_config.yaml"
if [ -f "$CONFIG_FILE" ]; then
    echo "✅ Renaming module in config file: $CONFIG_FILE"
    sed -i "s/^package_name: .*/package_name: $NEW_MODULE_NAME/" "$CONFIG_FILE"
else
    echo "⚠️ Config file $CONFIG_FILE not found."

fi

# Rename the module in the permission file
SETUP_FILE="$SCRIPT_DIR/../src/$NEW_MODULE_NAME/setup.py"

if [ -f "$SETUP_FILE" ]; then
    echo "✅ Renaming module in setup file: $SETUP_FILE"
    sed -i "s/^package_name\s*=\s* .*/package_name = '$NEW_MODULE_NAME'/" "$SETUP_FILE"
else
    echo "⚠️ Setup file $SETUP_FILE not found."
fi

# Rename the module in the package .xml file
PACKAGE_XML="$SCRIPT_DIR/../src/$NEW_MODULE_NAME/package.xml"
if [ -f "$PACKAGE_XML" ]; then
    echo "✅ Renaming module in package.xml file: $PACKAGE_XML"
    sed -i "s/<name>.*<\/name>/<name>$NEW_MODULE_NAME<\/name>/" "$PACKAGE_XML"
else
    echo "⚠️ Package XML file $PACKAGE_XML not found."

fi  

# Rename the module in the setup.cfg file
SETUP_CFG="$SCRIPT_DIR/../src/$NEW_MODULE_NAME/setup.cfg"
if [ -f "$SETUP_CFG" ]; then
    echo "✅ Renaming module in setup.cfg file: $SETUP_CFG"
    sed -i "s/$TEMPLATE_NAME/$NEW_MODULE_NAME/g" "$SETUP_CFG"
else
    echo "⚠️ Setup.cfg file $SETUP_CFG not found."
fi

# Rename in update_ros.sh
STARTUP_MODULE="$SCRIPT_DIR/../tools/startup_module.sh"
if [ -f "$STARTUP_MODULE" ]; then
    echo "✅ Renaming module in startup_module.sh: $STARTUP_MODULE"
    sed -i "s/$TEMPLATE_NAME/$NEW_MODULE_NAME/g" "$STARTUP_MODULE"
else
    echo "⚠️ Update ROS script $STARTUP_MODULE not found."
fi

# Rename in vyra_entrypoint.sh
ENTRYPOINT_FILE="$SCRIPT_DIR/../vyra_entrypoint.sh"
if [ -f "$ENTRYPOINT_FILE" ]; then
    echo "✅ Renaming module in vyra_entrypoint.sh: $ENTRYPOINT_FILE"
    sed -i "s/$TEMPLATE_NAME/$NEW_MODULE_NAME/g" "$ENTRYPOINT_FILE"
else
    echo "⚠️ Entry point script $ENTRYPOINT_FILE not found."
fi

# Rename pyproject.toml
PYPROJECT_FILE="$SCRIPT_DIR/../pyproject.toml"
if [ -f "$PYPROJECT_FILE" ]; then
    echo "✅ Renaming module in pyproject.toml: $PYPROJECT_FILE"
    # Update module_name in [tool.vyra] section
    sed -i "s/^module_name\s*=\s*.*/module_name = \"$NEW_MODULE_NAME\"/" "$PYPROJECT_FILE"
    
    # Update name in [tool.poetry] section only
    echo "✅ Updating name in [tool.poetry] section"
    sed -i '/^\[tool\.poetry\]/,/^\[/{s/^name\s*=\s*.*/name = "'"$NEW_MODULE_NAME"'"/}' "$PYPROJECT_FILE"

else
    echo "⚠️ Pyproject file $PYPROJECT_FILE not found."
fi

# Rename ros2 resource file
RESOURCE_FILE="$SCRIPT_DIR/../src/$NEW_MODULE_NAME/resource/$TEMPLATE_NAME"

if [ -f "$RESOURCE_FILE" ]; then
    echo "✅ Renaming resource file: $RESOURCE_FILE to $SCRIPT_DIR/../src/$NEW_MODULE_NAME/resource/$NEW_MODULE_NAME"
    mv "$RESOURCE_FILE" "$SCRIPT_DIR/../src/$NEW_MODULE_NAME/resource/$NEW_MODULE_NAME"
else
    echo "⚠️ Resource file $RESOURCE_FILE not found."
fi

# Adding new module name to .env if not already present
RESOURCE_FILE="$SCRIPT_DIR/../.env"
if [ -f "$RESOURCE_FILE" ]; then
    echo "✅ Adding module to .env file: $RESOURCE_FILE"
    if ! grep -q '^MODULE_NAME=' "$RESOURCE_FILE"; then
        echo "MODULE_NAME=$NEW_MODULE_NAME" >> "$RESOURCE_FILE"
    else
        echo "⚠️ MODULE_NAME already set in $RESOURCE_FILE"
        # Update the existing line
        sed -i "s/^MODULE_NAME=.*/MODULE_NAME=$NEW_MODULE_NAME/" "$RESOURCE_FILE"
    fi