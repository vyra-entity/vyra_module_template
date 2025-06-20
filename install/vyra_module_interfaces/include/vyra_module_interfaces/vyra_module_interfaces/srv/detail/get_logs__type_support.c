// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vyra_module_interfaces/srv/detail/get_logs__rosidl_typesupport_introspection_c.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vyra_module_interfaces/srv/detail/get_logs__functions.h"
#include "vyra_module_interfaces/srv/detail/get_logs__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__srv__GetLogs_Request__init(message_memory);
}

void vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_fini_function(void * message_memory)
{
  vyra_module_interfaces__srv__GetLogs_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_member_array[2] = {
  {
    "log_lines",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetLogs_Request, log_lines),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "log_level",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetLogs_Request, log_level),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_members = {
  "vyra_module_interfaces__srv",  // message namespace
  "GetLogs_Request",  // message name
  2,  // number of fields
  sizeof(vyra_module_interfaces__srv__GetLogs_Request),
  vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_member_array,  // message members
  vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Request)() {
  if (!vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__srv__GetLogs_Request__rosidl_typesupport_introspection_c__GetLogs_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__functions.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__struct.h"


// Include directives for member types
// Member `log_messages`
#include "vyra_module_interfaces/msg/logger_stream.h"
// Member `log_messages`
#include "vyra_module_interfaces/msg/detail/logger_stream__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__srv__GetLogs_Response__init(message_memory);
}

void vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_fini_function(void * message_memory)
{
  vyra_module_interfaces__srv__GetLogs_Response__fini(message_memory);
}

size_t vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__size_function__GetLogs_Response__log_messages(
  const void * untyped_member)
{
  const vyra_module_interfaces__msg__LoggerStream__Sequence * member =
    (const vyra_module_interfaces__msg__LoggerStream__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_const_function__GetLogs_Response__log_messages(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__msg__LoggerStream__Sequence * member =
    (const vyra_module_interfaces__msg__LoggerStream__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_function__GetLogs_Response__log_messages(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__msg__LoggerStream__Sequence * member =
    (vyra_module_interfaces__msg__LoggerStream__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__fetch_function__GetLogs_Response__log_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__msg__LoggerStream * item =
    ((const vyra_module_interfaces__msg__LoggerStream *)
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_const_function__GetLogs_Response__log_messages(untyped_member, index));
  vyra_module_interfaces__msg__LoggerStream * value =
    (vyra_module_interfaces__msg__LoggerStream *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__assign_function__GetLogs_Response__log_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__msg__LoggerStream * item =
    ((vyra_module_interfaces__msg__LoggerStream *)
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_function__GetLogs_Response__log_messages(untyped_member, index));
  const vyra_module_interfaces__msg__LoggerStream * value =
    (const vyra_module_interfaces__msg__LoggerStream *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__resize_function__GetLogs_Response__log_messages(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__msg__LoggerStream__Sequence * member =
    (vyra_module_interfaces__msg__LoggerStream__Sequence *)(untyped_member);
  vyra_module_interfaces__msg__LoggerStream__Sequence__fini(member);
  return vyra_module_interfaces__msg__LoggerStream__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_member_array[1] = {
  {
    "log_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetLogs_Response, log_messages),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__size_function__GetLogs_Response__log_messages,  // size() function pointer
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_const_function__GetLogs_Response__log_messages,  // get_const(index) function pointer
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__get_function__GetLogs_Response__log_messages,  // get(index) function pointer
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__fetch_function__GetLogs_Response__log_messages,  // fetch(index, &value) function pointer
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__assign_function__GetLogs_Response__log_messages,  // assign(index, value) function pointer
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__resize_function__GetLogs_Response__log_messages  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_members = {
  "vyra_module_interfaces__srv",  // message namespace
  "GetLogs_Response",  // message name
  1,  // number of fields
  sizeof(vyra_module_interfaces__srv__GetLogs_Response),
  vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_member_array,  // message members
  vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Response)() {
  vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, msg, LoggerStream)();
  if (!vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__srv__GetLogs_Response__rosidl_typesupport_introspection_c__GetLogs_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_members = {
  "vyra_module_interfaces__srv",  // service namespace
  "GetLogs",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_Request_message_type_support_handle,
  NULL  // response message
  // vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_Response_message_type_support_handle
};

static rosidl_service_type_support_t vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs)() {
  if (!vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetLogs_Response)()->data;
  }

  return &vyra_module_interfaces__srv__detail__get_logs__rosidl_typesupport_introspection_c__GetLogs_service_type_support_handle;
}
