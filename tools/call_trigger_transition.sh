#!/bin/bash

ros2 service call /trigger_transition \
  vyra_module_interfaces/srv/TriggerTransition \
  "{'transition_name': 'StartUp'}"
  