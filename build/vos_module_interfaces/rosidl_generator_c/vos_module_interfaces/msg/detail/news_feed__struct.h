// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_H_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'type'
// Member 'message'
// Member 'module_id'
// Member 'module_name'
#include "rosidl_runtime_c/string.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/NewsFeed in the package vos_module_interfaces.
/**
  * NewsFeed.msg
 */
typedef struct vos_module_interfaces__msg__NewsFeed
{
  rosidl_runtime_c__String type;
  rosidl_runtime_c__String message;
  builtin_interfaces__msg__Time timestamp;
  rosidl_runtime_c__String module_id;
  rosidl_runtime_c__String module_name;
} vos_module_interfaces__msg__NewsFeed;

// Struct for a sequence of vos_module_interfaces__msg__NewsFeed.
typedef struct vos_module_interfaces__msg__NewsFeed__Sequence
{
  vos_module_interfaces__msg__NewsFeed * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__msg__NewsFeed__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_H_
