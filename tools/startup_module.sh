#!/bin/bash

pushd /workspace

export $(grep -v '^#' .env | xargs)

source install/setup.bash

echo "SECURITY ENCLAVE: $ROS_SECURITY_ENCLAVE"

exec ros2 run vyra_module_template core --ros-args --enclave $ROS_SECURITY_ENCLAVE

if [ $? -eq 0 ]; then
    echo "✅ Module run successfully"
else
    echo "❌ Module runtime failed"
    exit 1
fi

popd