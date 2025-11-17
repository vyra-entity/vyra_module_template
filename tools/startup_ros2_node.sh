#!/bin/bash

pushd /workspace

# Load environment variables from .env (filter comments and empty lines)
export $(grep -v '^#' .env | sed 's/#.*$//' | grep -v '^$' | xargs)

# Set ROS_LOG_DIR for runtime logs
export ROS_LOG_DIR="/workspace/log/ros2"

source install/setup.bash

echo "----------------------------------------------------------------------------------"

echo "SECURITY ENCLAVE: $ROS_SECURITY_ENCLAVE"

# exec ros2 run $MODULE_NAME core --ros-args --enclave $ROS_SECURITY_ENCLAVE
# Run with log output to named file
exec ros2 run $MODULE_NAME core 2>&1 | tee /workspace/log/ros2/${MODULE_NAME}_runtime.log


if [ $? -eq 0 ]; then
    echo "✅ Module $MODULE_NAME run successfully"
else
    echo "❌ Module $MODULE_NAME runtime failed"
    exit 1
fi

popd