#!/bin/bash

ros2 service call /{{ module_name }}_733256b82d6b48a48bc52b5ec73ebfff/callable/trigger_transition \
  {{ module_name }}_interfaces/srv/VBASETriggerTransition \
  "{'trigger_name': '$1'}"
  