// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vos_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
#include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vos_module_interfaces/action/detail/initiate_update__functions.h"
#include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `module_name`
// Member `update_url`
// Member `target_version`
// Member `expected_hash`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_Goal__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_member_array[5] = {
  {
    "module_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Goal, module_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "update_url",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Goal, update_url),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Goal, target_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "force",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Goal, force),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "expected_hash",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Goal, expected_hash),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_Goal",  // message name
  5,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_Goal),
  vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Goal)() {
  if (!vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `report`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_Result__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "report",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Result, report),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_Result",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_Result),
  vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Result)() {
  if (!vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `status_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_Feedback__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_member_array[2] = {
  {
    "status_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Feedback, status_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "progress_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_Feedback, progress_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_Feedback",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_Feedback),
  vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Feedback)() {
  if (!vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "vos_module_interfaces/action/initiate_update.h"
// Member `goal`
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Request),
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Request)() {
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Goal)();
  if (!vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_SendGoal_Response),
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Response)() {
  vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_members = {
  "vos_module_interfaces__action",  // service namespace
  "InitiateUpdate_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle = {
  0,
  &vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal)() {
  if (!vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_SendGoal_Response)()->data;
  }

  return &vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_GetResult_Request),
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Request)() {
  vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "vos_module_interfaces/action/initiate_update.h"
// Member `result`
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_GetResult_Response),
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Response)() {
  vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Result)();
  if (!vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_members = {
  "vos_module_interfaces__action",  // service namespace
  "InitiateUpdate_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle = {
  0,
  &vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult)() {
  if (!vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_GetResult_Response)()->data;
  }

  return &vos_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "vos_module_interfaces/action/initiate_update.h"
// Member `feedback`
// already included above
// #include "vos_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(message_memory);
}

void vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_fini_function(void * message_memory)
{
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__action__InitiateUpdate_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_members = {
  "vos_module_interfaces__action",  // message namespace
  "InitiateUpdate_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__action__InitiateUpdate_FeedbackMessage),
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array,  // message members
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle = {
  0,
  &vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_FeedbackMessage)() {
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, action, InitiateUpdate_Feedback)();
  if (!vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
