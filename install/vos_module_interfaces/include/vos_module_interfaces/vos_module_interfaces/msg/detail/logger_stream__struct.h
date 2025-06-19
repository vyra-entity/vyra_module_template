// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'log_level'
// Member 'log_message'
#include "rosidl_runtime_c/string.h"
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/LoggerStream in the package vos_module_interfaces.
/**
  * LoggerStream.msg
 */
typedef struct vos_module_interfaces__msg__LoggerStream
{
  rosidl_runtime_c__String log_level;
  rosidl_runtime_c__String log_message;
  builtin_interfaces__msg__Time timestamp;
} vos_module_interfaces__msg__LoggerStream;

// Struct for a sequence of vos_module_interfaces__msg__LoggerStream.
typedef struct vos_module_interfaces__msg__LoggerStream__Sequence
{
  vos_module_interfaces__msg__LoggerStream * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__msg__LoggerStream__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_
