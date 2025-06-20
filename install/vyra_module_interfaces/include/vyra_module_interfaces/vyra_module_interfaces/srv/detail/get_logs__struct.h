// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetLogs in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__GetLogs_Request
{
  int32_t log_lines;
  uint8_t log_level;
} vyra_module_interfaces__srv__GetLogs_Request;

// Struct for a sequence of vyra_module_interfaces__srv__GetLogs_Request.
typedef struct vyra_module_interfaces__srv__GetLogs_Request__Sequence
{
  vyra_module_interfaces__srv__GetLogs_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__GetLogs_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'log_messages'
#include "vyra_module_interfaces/msg/detail/logger_stream__struct.h"

/// Struct defined in srv/GetLogs in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__GetLogs_Response
{
  vyra_module_interfaces__msg__LoggerStream__Sequence log_messages;
} vyra_module_interfaces__srv__GetLogs_Response;

// Struct for a sequence of vyra_module_interfaces__srv__GetLogs_Response.
typedef struct vyra_module_interfaces__srv__GetLogs_Response__Sequence
{
  vyra_module_interfaces__srv__GetLogs_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__GetLogs_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_
