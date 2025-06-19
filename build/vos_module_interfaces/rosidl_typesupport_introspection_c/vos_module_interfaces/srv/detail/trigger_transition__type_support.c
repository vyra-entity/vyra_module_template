// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vos_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vos_module_interfaces/srv/detail/trigger_transition__rosidl_typesupport_introspection_c.h"
#include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vos_module_interfaces/srv/detail/trigger_transition__functions.h"
#include "vos_module_interfaces/srv/detail/trigger_transition__struct.h"


// Include directives for member types
// Member `transition_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__srv__TriggerTransition_Request__init(message_memory);
}

void vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_fini_function(void * message_memory)
{
  vos_module_interfaces__srv__TriggerTransition_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_member_array[1] = {
  {
    "transition_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__srv__TriggerTransition_Request, transition_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_members = {
  "vos_module_interfaces__srv",  // message namespace
  "TriggerTransition_Request",  // message name
  1,  // number of fields
  sizeof(vos_module_interfaces__srv__TriggerTransition_Request),
  vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_member_array,  // message members
  vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_type_support_handle = {
  0,
  &vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Request)() {
  if (!vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__srv__TriggerTransition_Request__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "vos_module_interfaces/srv/detail/trigger_transition__rosidl_typesupport_introspection_c.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "vos_module_interfaces/srv/detail/trigger_transition__functions.h"
// already included above
// #include "vos_module_interfaces/srv/detail/trigger_transition__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vos_module_interfaces__srv__TriggerTransition_Response__init(message_memory);
}

void vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_fini_function(void * message_memory)
{
  vos_module_interfaces__srv__TriggerTransition_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__srv__TriggerTransition_Response, success),  // bytes offset in struct
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
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces__srv__TriggerTransition_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_members = {
  "vos_module_interfaces__srv",  // message namespace
  "TriggerTransition_Response",  // message name
  2,  // number of fields
  sizeof(vos_module_interfaces__srv__TriggerTransition_Response),
  vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_member_array,  // message members
  vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_type_support_handle = {
  0,
  &vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Response)() {
  if (!vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vos_module_interfaces__srv__TriggerTransition_Response__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "vos_module_interfaces/srv/detail/trigger_transition__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_members = {
  "vos_module_interfaces__srv",  // service namespace
  "TriggerTransition",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_Request_message_type_support_handle,
  NULL  // response message
  // vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_Response_message_type_support_handle
};

static rosidl_service_type_support_t vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_type_support_handle = {
  0,
  &vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vos_module_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition)() {
  if (!vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_type_support_handle.typesupport_identifier) {
    vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, TriggerTransition_Response)()->data;
  }

  return &vos_module_interfaces__srv__detail__trigger_transition__rosidl_typesupport_introspection_c__TriggerTransition_service_type_support_handle;
}
