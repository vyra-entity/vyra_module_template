// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_

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

/// Struct defined in msg/StateFeed in the package vyra_module_interfaces.
/**
  * StateFeeder.msg
 */
typedef struct vyra_module_interfaces__msg__StateFeed
{
  rosidl_runtime_c__String prev_state;
  rosidl_runtime_c__String current_state;
  builtin_interfaces__msg__Time timestamp;
} vyra_module_interfaces__msg__StateFeed;

// Struct for a sequence of vyra_module_interfaces__msg__StateFeed.
typedef struct vyra_module_interfaces__msg__StateFeed__Sequence
{
  vyra_module_interfaces__msg__StateFeed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__msg__StateFeed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_H_
