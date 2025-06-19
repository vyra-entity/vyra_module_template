// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetLogs in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__GetLogs_Request
{
  int32_t log_lines;
  uint8_t log_level;
} vos_module_interfaces__srv__GetLogs_Request;

// Struct for a sequence of vos_module_interfaces__srv__GetLogs_Request.
typedef struct vos_module_interfaces__srv__GetLogs_Request__Sequence
{
  vos_module_interfaces__srv__GetLogs_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__GetLogs_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'log_messages'
#include "vos_module_interfaces/msg/detail/logger_stream__struct.h"

/// Struct defined in srv/GetLogs in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__GetLogs_Response
{
  vos_module_interfaces__msg__LoggerStream__Sequence log_messages;
} vos_module_interfaces__srv__GetLogs_Response;

// Struct for a sequence of vos_module_interfaces__srv__GetLogs_Response.
typedef struct vos_module_interfaces__srv__GetLogs_Response__Sequence
{
  vos_module_interfaces__srv__GetLogs_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__GetLogs_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_
