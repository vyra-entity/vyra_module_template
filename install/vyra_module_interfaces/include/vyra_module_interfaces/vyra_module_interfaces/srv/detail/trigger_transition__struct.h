// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'transition_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TriggerTransition in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__TriggerTransition_Request
{
  /// Request
  /// Name of the transition to set to change the current state
  rosidl_runtime_c__String transition_name;
} vyra_module_interfaces__srv__TriggerTransition_Request;

// Struct for a sequence of vyra_module_interfaces__srv__TriggerTransition_Request.
typedef struct vyra_module_interfaces__srv__TriggerTransition_Request__Sequence
{
  vyra_module_interfaces__srv__TriggerTransition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__TriggerTransition_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TriggerTransition in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__TriggerTransition_Response
{
  /// Indicates whether the operation was successful thus the state was set
  bool success;
  /// Additional information about the operation, e.g., "Transition started successfully", "Transition failed due to error", etc.
  rosidl_runtime_c__String message;
} vyra_module_interfaces__srv__TriggerTransition_Response;

// Struct for a sequence of vyra_module_interfaces__srv__TriggerTransition_Response.
typedef struct vyra_module_interfaces__srv__TriggerTransition_Response__Sequence
{
  vyra_module_interfaces__srv__TriggerTransition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__TriggerTransition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_
