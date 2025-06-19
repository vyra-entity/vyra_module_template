// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/HealthCheck in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__HealthCheck_Request
{
  uint8_t structure_needs_at_least_one_member;
} vos_module_interfaces__srv__HealthCheck_Request;

// Struct for a sequence of vos_module_interfaces__srv__HealthCheck_Request.
typedef struct vos_module_interfaces__srv__HealthCheck_Request__Sequence
{
  vos_module_interfaces__srv__HealthCheck_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__HealthCheck_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
// Member 'health_status'
// Member 'issues'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/HealthCheck in the package vos_module_interfaces.
typedef struct vos_module_interfaces__srv__HealthCheck_Response
{
  /// Indicates if the system is alive/online and ready to process requests
  bool alive;
  /// Current state of the system, e.g., "active", ...
  rosidl_runtime_c__String state;
  /// Detailed health status of the system, e.g., "all systems operational", "minor issues detected", "major issues detected"
  rosidl_runtime_c__String health_status;
  /// List of issues detected, if any, e.g., ["disk space low", "network latency high"]
  rosidl_runtime_c__String__Sequence issues;
} vos_module_interfaces__srv__HealthCheck_Response;

// Struct for a sequence of vos_module_interfaces__srv__HealthCheck_Response.
typedef struct vos_module_interfaces__srv__HealthCheck_Response__Sequence
{
  vos_module_interfaces__srv__HealthCheck_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__srv__HealthCheck_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_H_
