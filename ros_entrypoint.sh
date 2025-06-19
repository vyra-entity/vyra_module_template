#!/bin/bash
python3 /workspace/tools/setup_interfaces.py

source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

exec "$@"
