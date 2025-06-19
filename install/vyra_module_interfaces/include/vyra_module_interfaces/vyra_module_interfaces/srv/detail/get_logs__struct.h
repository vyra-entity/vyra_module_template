// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/srv/get_logs.h"


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

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  vyra_module_interfaces__srv__GetLogs_Event__request__MAX_SIZE = 1
};
// response
enum
{
  vyra_module_interfaces__srv__GetLogs_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/GetLogs in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__GetLogs_Event
{
  service_msgs__msg__ServiceEventInfo info;
  vyra_module_interfaces__srv__GetLogs_Request__Sequence request;
  vyra_module_interfaces__srv__GetLogs_Response__Sequence response;
} vyra_module_interfaces__srv__GetLogs_Event;

// Struct for a sequence of vyra_module_interfaces__srv__GetLogs_Event.
typedef struct vyra_module_interfaces__srv__GetLogs_Event__Sequence
{
  vyra_module_interfaces__srv__GetLogs_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__GetLogs_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_H_
