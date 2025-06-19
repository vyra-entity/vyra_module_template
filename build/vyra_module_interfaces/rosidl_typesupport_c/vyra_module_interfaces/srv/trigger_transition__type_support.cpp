// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vyra_module_interfaces/srv/detail/trigger_transition__struct.h"
#include "vyra_module_interfaces/srv/detail/trigger_transition__type_support.h"
#include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _TriggerTransition_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _TriggerTransition_Request_type_support_ids_t;

static const _TriggerTransition_Request_type_support_ids_t _TriggerTransition_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _TriggerTransition_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _TriggerTransition_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _TriggerTransition_Request_type_support_symbol_names_t _TriggerTransition_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, TriggerTransition_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, TriggerTransition_Request)),
  }
};

typedef struct _TriggerTransition_Request_type_support_data_t
{
  void * data[2];
} _TriggerTransition_Request_type_support_data_t;

static _TriggerTransition_Request_type_support_data_t _TriggerTransition_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _TriggerTransition_Request_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_TriggerTransition_Request_message_typesupport_ids.typesupport_identifier[0],
  &_TriggerTransition_Request_message_typesupport_symbol_names.symbol_name[0],
  &_TriggerTransition_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t TriggerTransition_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_TriggerTransition_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__TriggerTransition_Request__get_type_hash,
  &vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description,
  &vyra_module_interfaces__srv__TriggerTransition_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vyra_module_interfaces, srv, TriggerTransition_Request)() {
  return &::vyra_module_interfaces::srv::rosidl_typesupport_c::TriggerTransition_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__type_support.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _TriggerTransition_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _TriggerTransition_Response_type_support_ids_t;

static const _TriggerTransition_Response_type_support_ids_t _TriggerTransition_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _TriggerTransition_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _TriggerTransition_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _TriggerTransition_Response_type_support_symbol_names_t _TriggerTransition_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, TriggerTransition_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, TriggerTransition_Response)),
  }
};

typedef struct _TriggerTransition_Response_type_support_data_t
{
  void * data[2];
} _TriggerTransition_Response_type_support_data_t;

static _TriggerTransition_Response_type_support_data_t _TriggerTransition_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _TriggerTransition_Response_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_TriggerTransition_Response_message_typesupport_ids.typesupport_identifier[0],
  &_TriggerTransition_Response_message_typesupport_symbol_names.symbol_name[0],
  &_TriggerTransition_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t TriggerTransition_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_TriggerTransition_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__TriggerTransition_Response__get_type_hash,
  &vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description,
  &vyra_module_interfaces__srv__TriggerTransition_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vyra_module_interfaces, srv, TriggerTransition_Response)() {
  return &::vyra_module_interfaces::srv::rosidl_typesupport_c::TriggerTransition_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__type_support.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _TriggerTransition_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _TriggerTransition_Event_type_support_ids_t;

static const _TriggerTransition_Event_type_support_ids_t _TriggerTransition_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _TriggerTransition_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _TriggerTransition_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _TriggerTransition_Event_type_support_symbol_names_t _TriggerTransition_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, TriggerTransition_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, TriggerTransition_Event)),
  }
};

typedef struct _TriggerTransition_Event_type_support_data_t
{
  void * data[2];
} _TriggerTransition_Event_type_support_data_t;

static _TriggerTransition_Event_type_support_data_t _TriggerTransition_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _TriggerTransition_Event_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_TriggerTransition_Event_message_typesupport_ids.typesupport_identifier[0],
  &_TriggerTransition_Event_message_typesupport_symbol_names.symbol_name[0],
  &_TriggerTransition_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t TriggerTransition_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_TriggerTransition_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__TriggerTransition_Event__get_type_hash,
  &vyra_module_interfaces__srv__TriggerTransition_Event__get_type_description,
  &vyra_module_interfaces__srv__TriggerTransition_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vyra_module_interfaces, srv, TriggerTransition_Event)() {
  return &::vyra_module_interfaces::srv::rosidl_typesupport_c::TriggerTransition_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _TriggerTransition_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _TriggerTransition_type_support_ids_t;

static const _TriggerTransition_type_support_ids_t _TriggerTransition_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _TriggerTransition_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _TriggerTransition_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _TriggerTransition_type_support_symbol_names_t _TriggerTransition_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, TriggerTransition)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, srv, TriggerTransition)),
  }
};

typedef struct _TriggerTransition_type_support_data_t
{
  void * data[2];
} _TriggerTransition_type_support_data_t;

static _TriggerTransition_type_support_data_t _TriggerTransition_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _TriggerTransition_service_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_TriggerTransition_service_typesupport_ids.typesupport_identifier[0],
  &_TriggerTransition_service_typesupport_symbol_names.symbol_name[0],
  &_TriggerTransition_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t TriggerTransition_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_TriggerTransition_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &TriggerTransition_Request_message_type_support_handle,
  &TriggerTransition_Response_message_type_support_handle,
  &TriggerTransition_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    TriggerTransition
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    TriggerTransition
  ),
  &vyra_module_interfaces__srv__TriggerTransition__get_type_hash,
  &vyra_module_interfaces__srv__TriggerTransition__get_type_description,
  &vyra_module_interfaces__srv__TriggerTransition__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, vyra_module_interfaces, srv, TriggerTransition)() {
  return &::vyra_module_interfaces::srv::rosidl_typesupport_c::TriggerTransition_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
