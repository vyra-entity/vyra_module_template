// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/srv/health_check.h"


#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/HealthCheck in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__HealthCheck_Request
{
  uint8_t structure_needs_at_least_one_member;
} vyra_module_interfaces__srv__HealthCheck_Request;

// Struct for a sequence of vyra_module_interfaces__srv__HealthCheck_Request.
typedef struct vyra_module_interfaces__srv__HealthCheck_Request__Sequence
{
  vyra_module_interfaces__srv__HealthCheck_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__HealthCheck_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'state'
// Member 'health_status'
// Member 'issues'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/HealthCheck in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__HealthCheck_Response
{
  /// Indicates if the system is alive/online and ready to process requests
  bool alive;
  /// Current state of the system, e.g., "active", ...
  rosidl_runtime_c__String state;
  /// Detailed health status of the system, e.g., "all systems operational", "minor issues detected", "major issues detected"
  rosidl_runtime_c__String health_status;
  /// List of issues detected, if any, e.g., ["disk space low", "network latency high"]
  rosidl_runtime_c__String__Sequence issues;
} vyra_module_interfaces__srv__HealthCheck_Response;

// Struct for a sequence of vyra_module_interfaces__srv__HealthCheck_Response.
typedef struct vyra_module_interfaces__srv__HealthCheck_Response__Sequence
{
  vyra_module_interfaces__srv__HealthCheck_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__HealthCheck_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  vyra_module_interfaces__srv__HealthCheck_Event__request__MAX_SIZE = 1
};
// response
enum
{
  vyra_module_interfaces__srv__HealthCheck_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/HealthCheck in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__srv__HealthCheck_Event
{
  service_msgs__msg__ServiceEventInfo info;
  vyra_module_interfaces__srv__HealthCheck_Request__Sequence request;
  vyra_module_interfaces__srv__HealthCheck_Response__Sequence response;
} vyra_module_interfaces__srv__HealthCheck_Event;

// Struct for a sequence of vyra_module_interfaces__srv__HealthCheck_Event.
typedef struct vyra_module_interfaces__srv__HealthCheck_Event__Sequence
{
  vyra_module_interfaces__srv__HealthCheck_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__srv__HealthCheck_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_
