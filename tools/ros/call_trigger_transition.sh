#!/bin/bash

ros2 service call /vyra_module_template_733256b82d6b48a48bc52b5ec73ebfff/callable/trigger_transition \
  vyra_module_interfaces/srv/VBASETriggerTransition \
  "{'trigger_name': '$1'}"
  