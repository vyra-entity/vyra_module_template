// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vyra_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vyra_module_interfaces/srv/detail/get_capabilities__rosidl_typesupport_introspection_c.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vyra_module_interfaces/srv/detail/get_capabilities__functions.h"
#include "vyra_module_interfaces/srv/detail/get_capabilities__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__srv__GetCapabilities_Request__init(message_memory);
}

void vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_fini_function(void * message_memory)
{
  vyra_module_interfaces__srv__GetCapabilities_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetCapabilities_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_members = {
  "vyra_module_interfaces__srv",  // message namespace
  "GetCapabilities_Request",  // message name
  1,  // number of fields
  sizeof(vyra_module_interfaces__srv__GetCapabilities_Request),
  false,  // has_any_key_member_
  vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_member_array,  // message members
  vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__GetCapabilities_Request__get_type_hash,
  &vyra_module_interfaces__srv__GetCapabilities_Request__get_type_description,
  &vyra_module_interfaces__srv__GetCapabilities_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Request)() {
  if (!vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__functions.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__struct.h"


// Include directives for member types
// Member `capabilities`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__srv__GetCapabilities_Response__init(message_memory);
}

void vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_fini_function(void * message_memory)
{
  vyra_module_interfaces__srv__GetCapabilities_Response__fini(message_memory);
}

size_t vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Response__capabilities(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Response__capabilities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Response__capabilities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Response__capabilities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Response__capabilities(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Response__capabilities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Response__capabilities(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Response__capabilities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_member_array[1] = {
  {
    "capabilities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetCapabilities_Response, capabilities),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Response__capabilities,  // size() function pointer
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Response__capabilities,  // get_const(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Response__capabilities,  // get(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Response__capabilities,  // fetch(index, &value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Response__capabilities,  // assign(index, value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Response__capabilities  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_members = {
  "vyra_module_interfaces__srv",  // message namespace
  "GetCapabilities_Response",  // message name
  1,  // number of fields
  sizeof(vyra_module_interfaces__srv__GetCapabilities_Response),
  false,  // has_any_key_member_
  vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_member_array,  // message members
  vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__GetCapabilities_Response__get_type_hash,
  &vyra_module_interfaces__srv__GetCapabilities_Response__get_type_description,
  &vyra_module_interfaces__srv__GetCapabilities_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Response)() {
  if (!vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__functions.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "vyra_module_interfaces/srv/get_capabilities.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vyra_module_interfaces__srv__GetCapabilities_Event__init(message_memory);
}

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_fini_function(void * message_memory)
{
  vyra_module_interfaces__srv__GetCapabilities_Event__fini(message_memory);
}

size_t vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Event__request(
  const void * untyped_member)
{
  const vyra_module_interfaces__srv__GetCapabilities_Request__Sequence * member =
    (const vyra_module_interfaces__srv__GetCapabilities_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__request(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__srv__GetCapabilities_Request__Sequence * member =
    (const vyra_module_interfaces__srv__GetCapabilities_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__request(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__srv__GetCapabilities_Request__Sequence * member =
    (vyra_module_interfaces__srv__GetCapabilities_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__srv__GetCapabilities_Request * item =
    ((const vyra_module_interfaces__srv__GetCapabilities_Request *)
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__request(untyped_member, index));
  vyra_module_interfaces__srv__GetCapabilities_Request * value =
    (vyra_module_interfaces__srv__GetCapabilities_Request *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__srv__GetCapabilities_Request * item =
    ((vyra_module_interfaces__srv__GetCapabilities_Request *)
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__request(untyped_member, index));
  const vyra_module_interfaces__srv__GetCapabilities_Request * value =
    (const vyra_module_interfaces__srv__GetCapabilities_Request *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Event__request(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__srv__GetCapabilities_Request__Sequence * member =
    (vyra_module_interfaces__srv__GetCapabilities_Request__Sequence *)(untyped_member);
  vyra_module_interfaces__srv__GetCapabilities_Request__Sequence__fini(member);
  return vyra_module_interfaces__srv__GetCapabilities_Request__Sequence__init(member, size);
}

size_t vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Event__response(
  const void * untyped_member)
{
  const vyra_module_interfaces__srv__GetCapabilities_Response__Sequence * member =
    (const vyra_module_interfaces__srv__GetCapabilities_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__response(
  const void * untyped_member, size_t index)
{
  const vyra_module_interfaces__srv__GetCapabilities_Response__Sequence * member =
    (const vyra_module_interfaces__srv__GetCapabilities_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__response(
  void * untyped_member, size_t index)
{
  vyra_module_interfaces__srv__GetCapabilities_Response__Sequence * member =
    (vyra_module_interfaces__srv__GetCapabilities_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vyra_module_interfaces__srv__GetCapabilities_Response * item =
    ((const vyra_module_interfaces__srv__GetCapabilities_Response *)
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__response(untyped_member, index));
  vyra_module_interfaces__srv__GetCapabilities_Response * value =
    (vyra_module_interfaces__srv__GetCapabilities_Response *)(untyped_value);
  *value = *item;
}

void vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vyra_module_interfaces__srv__GetCapabilities_Response * item =
    ((vyra_module_interfaces__srv__GetCapabilities_Response *)
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__response(untyped_member, index));
  const vyra_module_interfaces__srv__GetCapabilities_Response * value =
    (const vyra_module_interfaces__srv__GetCapabilities_Response *)(untyped_value);
  *item = *value;
}

bool vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Event__response(
  void * untyped_member, size_t size)
{
  vyra_module_interfaces__srv__GetCapabilities_Response__Sequence * member =
    (vyra_module_interfaces__srv__GetCapabilities_Response__Sequence *)(untyped_member);
  vyra_module_interfaces__srv__GetCapabilities_Response__Sequence__fini(member);
  return vyra_module_interfaces__srv__GetCapabilities_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vyra_module_interfaces__srv__GetCapabilities_Event, info),  // bytes offset in struct
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
    offsetof(vyra_module_interfaces__srv__GetCapabilities_Event, request),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Event__request,  // size() function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__request,  // get_const(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__request,  // get(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Event__request,  // fetch(index, &value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Event__request,  // assign(index, value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Event__request  // resize(index) function pointer
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
    offsetof(vyra_module_interfaces__srv__GetCapabilities_Event, response),  // bytes offset in struct
    NULL,  // default value
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__size_function__GetCapabilities_Event__response,  // size() function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_const_function__GetCapabilities_Event__response,  // get_const(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__get_function__GetCapabilities_Event__response,  // get(index) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__fetch_function__GetCapabilities_Event__response,  // fetch(index, &value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__assign_function__GetCapabilities_Event__response,  // assign(index, value) function pointer
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__resize_function__GetCapabilities_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_members = {
  "vyra_module_interfaces__srv",  // message namespace
  "GetCapabilities_Event",  // message name
  3,  // number of fields
  sizeof(vyra_module_interfaces__srv__GetCapabilities_Event),
  false,  // has_any_key_member_
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_member_array,  // message members
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_members,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__GetCapabilities_Event__get_type_hash,
  &vyra_module_interfaces__srv__GetCapabilities_Event__get_type_description,
  &vyra_module_interfaces__srv__GetCapabilities_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Event)() {
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Request)();
  vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Response)();
  if (!vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_capabilities__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_members = {
  "vyra_module_interfaces__srv",  // service namespace
  "GetCapabilities",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle,
  NULL,  // response message
  // vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle
  NULL  // event_message
  // vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle
};


static rosidl_service_type_support_t vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_type_support_handle = {
  0,
  &vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_members,
  get_service_typesupport_handle_function,
  &vyra_module_interfaces__srv__GetCapabilities_Request__rosidl_typesupport_introspection_c__GetCapabilities_Request_message_type_support_handle,
  &vyra_module_interfaces__srv__GetCapabilities_Response__rosidl_typesupport_introspection_c__GetCapabilities_Response_message_type_support_handle,
  &vyra_module_interfaces__srv__GetCapabilities_Event__rosidl_typesupport_introspection_c__GetCapabilities_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    GetCapabilities
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    GetCapabilities
  ),
  &vyra_module_interfaces__srv__GetCapabilities__get_type_hash,
  &vyra_module_interfaces__srv__GetCapabilities__get_type_description,
  &vyra_module_interfaces__srv__GetCapabilities__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vyra_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities)(void) {
  if (!vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_type_support_handle.typesupport_identifier) {
    vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, GetCapabilities_Event)()->data;
  }

  return &vyra_module_interfaces__srv__detail__get_capabilities__rosidl_typesupport_introspection_c__GetCapabilities_service_type_support_handle;
}
