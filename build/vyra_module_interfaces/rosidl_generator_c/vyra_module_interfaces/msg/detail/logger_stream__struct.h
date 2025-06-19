// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/logger_stream.h"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_

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

/// Struct defined in msg/LoggerStream in the package vyra_module_interfaces.
/**
  * LoggerStream.msg
 */
typedef struct vyra_module_interfaces__msg__LoggerStream
{
  rosidl_runtime_c__String log_level;
  rosidl_runtime_c__String log_message;
  builtin_interfaces__msg__Time timestamp;
} vyra_module_interfaces__msg__LoggerStream;

// Struct for a sequence of vyra_module_interfaces__msg__LoggerStream.
typedef struct vyra_module_interfaces__msg__LoggerStream__Sequence
{
  vyra_module_interfaces__msg__LoggerStream * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__msg__LoggerStream__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_H_
