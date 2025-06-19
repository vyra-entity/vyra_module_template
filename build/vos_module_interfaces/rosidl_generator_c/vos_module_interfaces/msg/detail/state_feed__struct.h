// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'prev_state'
// Member 'current_state'
#include "rosidl_runtime_c/string.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/StateFeed in the package vos_module_interfaces.
/**
  * StateFeeder.msg
 */
typedef struct vos_module_interfaces__msg__StateFeed
{
  rosidl_runtime_c__String prev_state;
  rosidl_runtime_c__String current_state;
  builtin_interfaces__msg__Time timestamp;
} vos_module_interfaces__msg__StateFeed;

// Struct for a sequence of vos_module_interfaces__msg__StateFeed.
typedef struct vos_module_interfaces__msg__StateFeed__Sequence
{
  vos_module_interfaces__msg__StateFeed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__msg__StateFeed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_
