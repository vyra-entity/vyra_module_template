// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vos_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_
#define VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'module_name'
// Member 'update_url'
// Member 'target_version'
// Member 'expected_hash'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_Goal
{
  /// Goal
  rosidl_runtime_c__String module_name;
  /// URL to the update package (will be uploaded by the webserver)
  rosidl_runtime_c__String update_url;
  /// version to update to, can be a specific version or "latest"
  rosidl_runtime_c__String target_version;
  /// whether to force the update even if the version is not newer
  bool force;
  /// optional SHA256-Hash
  rosidl_runtime_c__String expected_hash;
} vos_module_interfaces__action__InitiateUpdate_Goal;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_Goal.
typedef struct vos_module_interfaces__action__InitiateUpdate_Goal__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'report'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_Result
{
  bool success;
  /// Report on the update process, e.g., "Update successful", "Update failed", etc.
  rosidl_runtime_c__String report;
} vos_module_interfaces__action__InitiateUpdate_Result;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_Result.
typedef struct vos_module_interfaces__action__InitiateUpdate_Result__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status_message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_Feedback
{
  rosidl_runtime_c__String status_message;
  /// 0.0 - 100.0
  float progress_percentage;
} vos_module_interfaces__action__InitiateUpdate_Feedback;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_Feedback.
typedef struct vos_module_interfaces__action__InitiateUpdate_Feedback__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "vos_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  vos_module_interfaces__action__InitiateUpdate_Goal goal;
} vos_module_interfaces__action__InitiateUpdate_SendGoal_Request;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_SendGoal_Request.
typedef struct vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} vos_module_interfaces__action__InitiateUpdate_SendGoal_Response;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_SendGoal_Response.
typedef struct vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} vos_module_interfaces__action__InitiateUpdate_GetResult_Request;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_GetResult_Request.
typedef struct vos_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_GetResult_Response
{
  int8_t status;
  vos_module_interfaces__action__InitiateUpdate_Result result;
} vos_module_interfaces__action__InitiateUpdate_GetResult_Response;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_GetResult_Response.
typedef struct vos_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vos_module_interfaces.
typedef struct vos_module_interfaces__action__InitiateUpdate_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  vos_module_interfaces__action__InitiateUpdate_Feedback feedback;
} vos_module_interfaces__action__InitiateUpdate_FeedbackMessage;

// Struct for a sequence of vos_module_interfaces__action__InitiateUpdate_FeedbackMessage.
typedef struct vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence
{
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VOS_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_
