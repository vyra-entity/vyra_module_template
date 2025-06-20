// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_

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

/// Struct defined in msg/ErrorFeed in the package vyra_module_interfaces.
/**
  * ErrorFeed.msg
 */
typedef struct vyra_module_interfaces__msg__ErrorFeed
{
  uint32_t error_code;
  rosidl_runtime_c__String module_id;
  rosidl_runtime_c__String description;
  rosidl_runtime_c__String solution;
  rosidl_runtime_c__String miscellaneous;
  builtin_interfaces__msg__Time timestamp;
} vyra_module_interfaces__msg__ErrorFeed;

// Struct for a sequence of vyra_module_interfaces__msg__ErrorFeed.
typedef struct vyra_module_interfaces__msg__ErrorFeed__Sequence
{
  vyra_module_interfaces__msg__ErrorFeed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__msg__ErrorFeed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_H_
