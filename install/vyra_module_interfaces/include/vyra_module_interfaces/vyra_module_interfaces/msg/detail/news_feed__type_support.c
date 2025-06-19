// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vyra_module_interfaces/msg/detail/news_feed__rosidl_typesupport_introspection_c.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vyra_module_interfaces/msg/detail/news_feed__functions.h"
#include "vyra_module_interfaces/msg/detail/news_feed__struct.h"


// Include directives for member types
// Member `type`
// Member `message`
// Member `module_id`
// Member `module_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__msg__NewsFeed__init(message_memory);
}

void vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_fini_function(void * message_memory)
{
  vyra_module_interfaces__msg__NewsFeed__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_member_array[5] = {
  {
    "type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__msg__NewsFeed, type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__msg__NewsFeed, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timestamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__msg__NewsFeed, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "module_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__msg__NewsFeed, module_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "module_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__msg__NewsFeed, module_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_members = {
  "vyra_module_interfaces__msg",  // message namespace
  "NewsFeed",  // message name
  5,  // number of fields
  sizeof(vyra_module_interfaces__msg__NewsFeed),
  false,  // has_any_key_member_
  vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_member_array,  // message members
  vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_type_support_handle = {
  0,
  &vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__msg__NewsFeed__get_type_hash,
  &vyra_module_interfaces__msg__NewsFeed__get_type_description,
  &vyra_module_interfaces__msg__NewsFeed__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, msg, NewsFeed)() {
  vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__msg__NewsFeed__rosidl_typesupport_introspection_c__NewsFeed_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
