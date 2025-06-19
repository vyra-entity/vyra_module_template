#!/bin/bash

pushd /workspace

pip uninstall vyra_base -y
pip install wheels/vyra_base-0.1.5-py3-none-any.whl

colcon build
source install/setup.bash

ros2 run vyra_module_template core

popd