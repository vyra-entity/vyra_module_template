#!/bin/bash

ros2 service call /trigger_transition \
  vyra_module_interfaces/srv/TriggerTransition \
  "{'trigger_name': '$1'}"
  