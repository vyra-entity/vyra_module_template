// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_

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

/// Struct defined in srv/TriggerTransition in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__TriggerTransition_Request
{
  /// Request
  /// Name of the transition to set to change the current state
  rosidl_runtime_c__String transition_name;
} vos_module_interfaces__srv__TriggerTransition_Request;

// Struct for a sequence of vos_module_interfaces__srv__TriggerTransition_Request.
typedef struct vos_module_interfaces__srv__TriggerTransition_Request__Sequence
{
  vos_module_interfaces__srv__TriggerTransition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__TriggerTransition_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TriggerTransition in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__TriggerTransition_Response
{
  /// Indicates whether the operation was successful thus the state was set
  bool success;
  /// Additional information about the operation, e.g., "Transition started successfully", "Transition failed due to error", etc.
  rosidl_runtime_c__String message;
} vos_module_interfaces__srv__TriggerTransition_Response;

// Struct for a sequence of vos_module_interfaces__srv__TriggerTransition_Response.
typedef struct vos_module_interfaces__srv__TriggerTransition_Response__Sequence
{
  vos_module_interfaces__srv__TriggerTransition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__TriggerTransition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_H_
