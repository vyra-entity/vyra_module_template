// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vyra_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
#include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


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

void vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_Goal__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_member_array[5] = {
  {
    "module_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Goal, module_name),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Goal, update_url),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Goal, target_version),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Goal, force),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Goal, expected_hash),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_Goal",  // message name
  5,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_Goal__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_Goal__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_Goal__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Goal)() {
  if (!vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_Goal__rosidl_typesupport_introspection_c__InitiateUpdate_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `report`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_Result__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Result, success),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Result, report),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_Result",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_Result),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_Result__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_Result__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_Result__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Result)() {
  if (!vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_Result__rosidl_typesupport_introspection_c__InitiateUpdate_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `status_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_Feedback__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_member_array[2] = {
  {
    "status_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Feedback, status_message),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_Feedback, progress_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_Feedback",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_Feedback__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_Feedback__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_Feedback__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Feedback)() {
  if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_Feedback__rosidl_typesupport_introspection_c__InitiateUpdate_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "vyra_module_interfaces/action/initiate_update.h"
// Member `goal`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request, goal_id),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Request)() {
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Goal)();
  if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response, accepted),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Response)() {
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/action/initiate_update.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__fini(message_memory);
}

size_t vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_SendGoal_Event__request(
  const void * untyped_member)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__request(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__request(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_SendGoal_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * item =
    ((const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__request(untyped_member, index));
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * value =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_SendGoal_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * item =
    ((vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__request(untyped_member, index));
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * value =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_SendGoal_Event__request(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *)(untyped_member);
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__fini(member);
  return vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__init(member, size);
}

size_t vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_SendGoal_Event__response(
  const void * untyped_member)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__response(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__response(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_SendGoal_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * item =
    ((const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__response(untyped_member, index));
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * value =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_SendGoal_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * item =
    ((vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__response(untyped_member, index));
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * value =
    (const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_SendGoal_Event__response(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *)(untyped_member);
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__fini(member);
  return vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event, request),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_SendGoal_Event__request,  // size() function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__request,  // get_const(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__request,  // get(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_SendGoal_Event__request,  // fetch(index, &value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_SendGoal_Event__request,  // assign(index, value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_SendGoal_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event, response),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_SendGoal_Event__response,  // size() function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_SendGoal_Event__response,  // get_const(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_SendGoal_Event__response,  // get(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_SendGoal_Event__response,  // fetch(index, &value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_SendGoal_Event__response,  // assign(index, value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_SendGoal_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_SendGoal_Event",  // message name
  3,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Event)() {
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Request)();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Response)();
  if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_members = {
  "vyra_module_interfaces__action",  // service namespace
  "InitiateUpdate_SendGoal",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle,
  NULL,  // response message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle
  NULL  // event_message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle
};


static rosidl_service_type_support_t vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle = {
  0,
  &vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_members,
  get_service_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Request_message_type_support_handle,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Response_message_type_support_handle,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal_Event__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    action,
    InitiateUpdate_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    action,
    InitiateUpdate_SendGoal
  ),
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_SendGoal__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal)(void) {
  if (!vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_SendGoal_Event)()->data;
  }

  return &vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


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

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Request)() {
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "vyra_module_interfaces/action/initiate_update.h"
// Member `result`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response, status),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Response)() {
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Result)();
  if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/service_event_info.h"
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/action/initiate_update.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__fini(message_memory);
}

size_t vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_GetResult_Event__request(
  const void * untyped_member)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__request(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__request(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_GetResult_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * item =
    ((const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__request(untyped_member, index));
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * value =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_GetResult_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * item =
    ((vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__request(untyped_member, index));
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * value =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_GetResult_Event__request(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *)(untyped_member);
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__fini(member);
  return vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__init(member, size);
}

size_t vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_GetResult_Event__response(
  const void * untyped_member)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__response(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * member =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__response(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_GetResult_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * item =
    ((const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__response(untyped_member, index));
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * value =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_GetResult_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * item =
    ((vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__response(untyped_member, index));
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * value =
    (const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_GetResult_Event__response(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * member =
    (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *)(untyped_member);
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__fini(member);
  return vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Event, request),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_GetResult_Event__request,  // size() function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__request,  // get_const(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__request,  // get(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_GetResult_Event__request,  // fetch(index, &value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_GetResult_Event__request,  // assign(index, value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_GetResult_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Event, response),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__size_function__InitiateUpdate_GetResult_Event__response,  // size() function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__InitiateUpdate_GetResult_Event__response,  // get_const(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__get_function__InitiateUpdate_GetResult_Event__response,  // get(index) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__InitiateUpdate_GetResult_Event__response,  // fetch(index, &value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__InitiateUpdate_GetResult_Event__response,  // assign(index, value) function pointer
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__InitiateUpdate_GetResult_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_GetResult_Event",  // message name
  3,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Event),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Event)() {
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Request)();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Response)();
  if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_members = {
  "vyra_module_interfaces__action",  // service namespace
  "InitiateUpdate_GetResult",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle,
  NULL,  // response message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle
  NULL  // event_message
  // vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle
};


static rosidl_service_type_support_t vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle = {
  0,
  &vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_members,
  get_service_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Request_message_type_support_handle,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Response_message_type_support_handle,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult_Event__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    action,
    InitiateUpdate_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    action,
    InitiateUpdate_GetResult
  ),
  &vyra_module_interfaces__action__InitiateUpdate_GetResult__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_GetResult__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult)(void) {
  if (!vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_GetResult_Event)()->data;
  }

  return &vyra_module_interfaces__action__detail__initiate_update__rosidl_typesupport_introspection_c__InitiateUpdate_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "vyra_module_interfaces/action/initiate_update.h"
// Member `feedback`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(message_memory);
}

void vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_fini_function(void * message_memory)
{
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage, goal_id),  // bytes offset in struct
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
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_members = {
  "vyra_module_interfaces__action",  // message namespace
  "InitiateUpdate_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage),
  false,  // has_any_key_member_
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array,  // message members
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle = {
  0,
  &vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__get_type_hash,
  &vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__get_type_description,
  &vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_FeedbackMessage)() {
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, action, InitiateUpdate_Feedback)();
  if (!vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__rosidl_typesupport_introspection_c__InitiateUpdate_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
