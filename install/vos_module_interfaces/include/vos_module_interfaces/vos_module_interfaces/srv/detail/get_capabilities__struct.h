// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetCapabilities in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__GetCapabilities_Request
{
  uint8_t structure_needs_at_least_one_member;
} vos_module_interfaces__srv__GetCapabilities_Request;

// Struct for a sequence of vos_module_interfaces__srv__GetCapabilities_Request.
typedef struct vos_module_interfaces__srv__GetCapabilities_Request__Sequence
{
  vos_module_interfaces__srv__GetCapabilities_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__GetCapabilities_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'capabilities'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetCapabilities in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__GetCapabilities_Response
{
  rosidl_runtime_c__String__Sequence capabilities;
} vos_module_interfaces__srv__GetCapabilities_Response;

// Struct for a sequence of vos_module_interfaces__srv__GetCapabilities_Response.
typedef struct vos_module_interfaces__srv__GetCapabilities_Response__Sequence
{
  vos_module_interfaces__srv__GetCapabilities_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__GetCapabilities_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_H_
