// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetCapabilities in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__GetCapabilities_Request
{
  uint8_t structure_needs_at_least_one_member;
} vyra_module_interfaces__srv__GetCapabilities_Request;

// Struct for a sequence of vyra_module_interfaces__srv__GetCapabilities_Request.
typedef struct vyra_module_interfaces__srv__GetCapabilities_Request__Sequence
{
  vyra_module_interfaces__srv__GetCapabilities_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__GetCapabilities_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'capabilities'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetCapabilities in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__GetCapabilities_Response
{
  rosidl_runtime_c__String__Sequence capabilities;
} vyra_module_interfaces__srv__GetCapabilities_Response;

// Struct for a sequence of vyra_module_interfaces__srv__GetCapabilities_Response.
typedef struct vyra_module_interfaces__srv__GetCapabilities_Response__Sequence
{
  vyra_module_interfaces__srv__GetCapabilities_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__GetCapabilities_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_
