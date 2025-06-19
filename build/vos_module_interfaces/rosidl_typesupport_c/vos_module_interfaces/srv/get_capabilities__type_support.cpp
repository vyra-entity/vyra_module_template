// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from vos_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vos_module_interfaces/srv/detail/get_capabilities__struct.h"
#include "vos_module_interfaces/srv/detail/get_capabilities__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetCapabilities_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetCapabilities_Request_type_support_ids_t;

static const _GetCapabilities_Request_type_support_ids_t _GetCapabilities_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetCapabilities_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetCapabilities_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetCapabilities_Request_type_support_symbol_names_t _GetCapabilities_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, GetCapabilities_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, GetCapabilities_Request)),
  }
};

typedef struct _GetCapabilities_Request_type_support_data_t
{
  void * data[2];
} _GetCapabilities_Request_type_support_data_t;

static _GetCapabilities_Request_type_support_data_t _GetCapabilities_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetCapabilities_Request_message_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetCapabilities_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GetCapabilities_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GetCapabilities_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetCapabilities_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetCapabilities_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vos_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vos_module_interfaces, srv, GetCapabilities_Request)() {
  return &::vos_module_interfaces::srv::rosidl_typesupport_c::GetCapabilities_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/get_capabilities__struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/get_capabilities__type_support.h"
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

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetCapabilities_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetCapabilities_Response_type_support_ids_t;

static const _GetCapabilities_Response_type_support_ids_t _GetCapabilities_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetCapabilities_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetCapabilities_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetCapabilities_Response_type_support_symbol_names_t _GetCapabilities_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, GetCapabilities_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, GetCapabilities_Response)),
  }
};

typedef struct _GetCapabilities_Response_type_support_data_t
{
  void * data[2];
} _GetCapabilities_Response_type_support_data_t;

static _GetCapabilities_Response_type_support_data_t _GetCapabilities_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetCapabilities_Response_message_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetCapabilities_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GetCapabilities_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GetCapabilities_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetCapabilities_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetCapabilities_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vos_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vos_module_interfaces, srv, GetCapabilities_Response)() {
  return &::vos_module_interfaces::srv::rosidl_typesupport_c::GetCapabilities_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/get_capabilities__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _GetCapabilities_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetCapabilities_type_support_ids_t;

static const _GetCapabilities_type_support_ids_t _GetCapabilities_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GetCapabilities_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetCapabilities_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetCapabilities_type_support_symbol_names_t _GetCapabilities_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, GetCapabilities)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vos_module_interfaces, srv, GetCapabilities)),
  }
};

typedef struct _GetCapabilities_type_support_data_t
{
  void * data[2];
} _GetCapabilities_type_support_data_t;

static _GetCapabilities_type_support_data_t _GetCapabilities_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetCapabilities_service_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetCapabilities_service_typesupport_ids.typesupport_identifier[0],
  &_GetCapabilities_service_typesupport_symbol_names.symbol_name[0],
  &_GetCapabilities_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GetCapabilities_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetCapabilities_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace vos_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, vos_module_interfaces, srv, GetCapabilities)() {
  return &::vos_module_interfaces::srv::rosidl_typesupport_c::GetCapabilities_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
