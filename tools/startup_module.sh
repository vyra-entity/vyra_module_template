#!/bin/bash

pushd /workspace

export $(grep -v '^#' .env | xargs)

source install/setup.bash

echo "SECURITY ENCLAVE: $ROS_SECURITY_ENCLAVE"

# exec ros2 run $MODULE_NAME core --ros-args --enclave $ROS_SECURITY_ENCLAVE
exec ros2 run $MODULE_NAME core


if [ $? -eq 0 ]; then
    echo "✅ Module $MODULE_NAME run successfully"
else
    echo "❌ Module $MODULE_NAME runtime failed"
    exit 1
fi

popd