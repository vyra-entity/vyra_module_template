// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'module_id'
// Member 'description'
// Member 'solution'
// Member 'miscellaneous'
#include "rosidl_runtime_c/string.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/ErrorFeed in the package vos_module_interfaces.
/**
  * ErrorFeed.msg
 */
typedef struct vos_module_interfaces__msg__ErrorFeed
{
  uint32_t error_code;
  rosidl_runtime_c__String module_id;
  rosidl_runtime_c__String description;
  rosidl_runtime_c__String solution;
  rosidl_runtime_c__String miscellaneous;
  builtin_interfaces__msg__Time timestamp;
} vos_module_interfaces__msg__ErrorFeed;

// Struct for a sequence of vos_module_interfaces__msg__ErrorFeed.
typedef struct vos_module_interfaces__msg__ErrorFeed__Sequence
{
  vos_module_interfaces__msg__ErrorFeed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__msg__ErrorFeed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_
