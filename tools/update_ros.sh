#!/bin/bash

pushd /workspace

pip uninstall vyra_base -y --break-system-packages
pip install wheels/vyra_base-0.1.5-py3-none-any.whl --break-system-packages

python3 tools/setup_interfaces.py

rm -rf log/build_*

colcon build
source install/setup.bash

export ROS_SECURITY_ENCLAVE=/workspace/sros2_keystore/enclaves/vyra_module_template

ros2 run vyra_module_template core

popd