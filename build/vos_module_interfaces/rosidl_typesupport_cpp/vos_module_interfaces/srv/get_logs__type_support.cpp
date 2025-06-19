// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from vos_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vos_module_interfaces/srv/detail/get_logs__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetLogs_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetLogs_Request_type_support_ids_t;

static const _GetLogs_Request_type_support_ids_t _GetLogs_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GetLogs_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetLogs_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetLogs_Request_type_support_symbol_names_t _GetLogs_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vos_module_interfaces, srv, GetLogs_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vos_module_interfaces, srv, GetLogs_Request)),
  }
};

typedef struct _GetLogs_Request_type_support_data_t
{
  void * data[2];
} _GetLogs_Request_type_support_data_t;

static _GetLogs_Request_type_support_data_t _GetLogs_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetLogs_Request_message_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetLogs_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GetLogs_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GetLogs_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetLogs_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetLogs_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vos_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vos_module_interfaces::srv::GetLogs_Request>()
{
  return &::vos_module_interfaces::srv::rosidl_typesupport_cpp::GetLogs_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vos_module_interfaces, srv, GetLogs_Request)() {
  return get_message_type_support_handle<vos_module_interfaces::srv::GetLogs_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/get_logs__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetLogs_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetLogs_Response_type_support_ids_t;

static const _GetLogs_Response_type_support_ids_t _GetLogs_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GetLogs_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetLogs_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetLogs_Response_type_support_symbol_names_t _GetLogs_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vos_module_interfaces, srv, GetLogs_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vos_module_interfaces, srv, GetLogs_Response)),
  }
};

typedef struct _GetLogs_Response_type_support_data_t
{
  void * data[2];
} _GetLogs_Response_type_support_data_t;

static _GetLogs_Response_type_support_data_t _GetLogs_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetLogs_Response_message_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetLogs_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GetLogs_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GetLogs_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GetLogs_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetLogs_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vos_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vos_module_interfaces::srv::GetLogs_Response>()
{
  return &::vos_module_interfaces::srv::rosidl_typesupport_cpp::GetLogs_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vos_module_interfaces, srv, GetLogs_Response)() {
  return get_message_type_support_handle<vos_module_interfaces::srv::GetLogs_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/get_logs__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vos_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _GetLogs_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GetLogs_type_support_ids_t;

static const _GetLogs_type_support_ids_t _GetLogs_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GetLogs_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GetLogs_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GetLogs_type_support_symbol_names_t _GetLogs_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vos_module_interfaces, srv, GetLogs)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vos_module_interfaces, srv, GetLogs)),
  }
};

typedef struct _GetLogs_type_support_data_t
{
  void * data[2];
} _GetLogs_type_support_data_t;

static _GetLogs_type_support_data_t _GetLogs_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GetLogs_service_typesupport_map = {
  2,
  "vos_module_interfaces",
  &_GetLogs_service_typesupport_ids.typesupport_identifier[0],
  &_GetLogs_service_typesupport_symbol_names.symbol_name[0],
  &_GetLogs_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GetLogs_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GetLogs_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vos_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<vos_module_interfaces::srv::GetLogs>()
{
  return &::vos_module_interfaces::srv::rosidl_typesupport_cpp::GetLogs_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, vos_module_interfaces, srv, GetLogs)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<vos_module_interfaces::srv::GetLogs>();
}

#ifdef __cplusplus
}
#endif
