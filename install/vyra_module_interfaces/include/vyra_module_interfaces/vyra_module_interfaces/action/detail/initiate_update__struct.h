// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vyra_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/action/initiate_update.h"


#ifndef VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_
#define VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_

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

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Goal
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
} vyra_module_interfaces__action__InitiateUpdate_Goal;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_Goal.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'report'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Result
{
  bool success;
  /// Report on the update process, e.g., "Update successful", "Update failed", etc.
  rosidl_runtime_c__String report;
} vyra_module_interfaces__action__InitiateUpdate_Result;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_Result.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Result__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'status_message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Feedback
{
  rosidl_runtime_c__String status_message;
  /// 0.0 - 100.0
  float progress_percentage;
} vyra_module_interfaces__action__InitiateUpdate_Feedback;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_Feedback.
typedef struct vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "vyra_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  vyra_module_interfaces__action__InitiateUpdate_Goal goal;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence request;
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence response;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event.
typedef struct vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Request;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_GetResult_Request.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Response
{
  int8_t status;
  vyra_module_interfaces__action__InitiateUpdate_Result result;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Response;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_GetResult_Response.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence request;
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence response;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Event;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_GetResult_Event.
typedef struct vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"

/// Struct defined in action/InitiateUpdate in the package vyra_module_interfaces.
typedef struct vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  vyra_module_interfaces__action__InitiateUpdate_Feedback feedback;
} vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage;

// Struct for a sequence of vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage.
typedef struct vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence
{
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__STRUCT_H_
