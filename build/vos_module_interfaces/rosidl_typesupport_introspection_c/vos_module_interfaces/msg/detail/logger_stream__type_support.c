// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vos_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vos_module_interfaces/msg/detail/logger_stream__rosidl_typesupport_introspection_c.h"
#include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vos_module_interfaces/msg/detail/logger_stream__functions.h"
#include "vos_module_interfaces/msg/detail/logger_stream__struct.h"


// Include directives for member types
// Member `log_level`
// Member `log_message`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/time.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__msg__LoggerStream__init(message_memory);
}

void vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_fini_function(void * message_memory)
{
  vos_module_interfaces__msg__LoggerStream__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_member_array[3] = {
  {
    "log_level",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__msg__LoggerStream, log_level),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "log_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__msg__LoggerStream, log_message),  // bytes offset in struct
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
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__msg__LoggerStream, timestamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_members = {
  "vos_module_interfaces__msg",  // message namespace
  "LoggerStream",  // message name
  3,  // number of fields
  sizeof(vos_module_interfaces__msg__LoggerStream),
  vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_member_array,  // message members
  vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_type_support_handle = {
  0,
  &vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, msg, LoggerStream)() {
  vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__msg__LoggerStream__rosidl_typesupport_introspection_c__LoggerStream_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
