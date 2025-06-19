#!/bin/bash

pushd /workspace

pip uninstall vos-base -y
pip install wheels/vos_base-0.1.5-py3-none-any.whl

colcon build
source install/setup.bash

ros2 run vos_module_template core

popd