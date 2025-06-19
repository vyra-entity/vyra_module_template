// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vyra_module_interfaces/srv/detail/health_check__functions.h"
#include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _HealthCheck_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _HealthCheck_Request_type_support_ids_t;

static const _HealthCheck_Request_type_support_ids_t _HealthCheck_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _HealthCheck_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _HealthCheck_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _HealthCheck_Request_type_support_symbol_names_t _HealthCheck_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, HealthCheck_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vyra_module_interfaces, srv, HealthCheck_Request)),
  }
};

typedef struct _HealthCheck_Request_type_support_data_t
{
  void * data[2];
} _HealthCheck_Request_type_support_data_t;

static _HealthCheck_Request_type_support_data_t _HealthCheck_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _HealthCheck_Request_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_HealthCheck_Request_message_typesupport_ids.typesupport_identifier[0],
  &_HealthCheck_Request_message_typesupport_symbol_names.symbol_name[0],
  &_HealthCheck_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t HealthCheck_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_HealthCheck_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Request>()
{
  return &::vyra_module_interfaces::srv::rosidl_typesupport_cpp::HealthCheck_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vyra_module_interfaces, srv, HealthCheck_Request)() {
  return get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Request>();
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
// #include "vyra_module_interfaces/srv/detail/health_check__functions.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
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

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _HealthCheck_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _HealthCheck_Response_type_support_ids_t;

static const _HealthCheck_Response_type_support_ids_t _HealthCheck_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _HealthCheck_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _HealthCheck_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _HealthCheck_Response_type_support_symbol_names_t _HealthCheck_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, HealthCheck_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vyra_module_interfaces, srv, HealthCheck_Response)),
  }
};

typedef struct _HealthCheck_Response_type_support_data_t
{
  void * data[2];
} _HealthCheck_Response_type_support_data_t;

static _HealthCheck_Response_type_support_data_t _HealthCheck_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _HealthCheck_Response_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_HealthCheck_Response_message_typesupport_ids.typesupport_identifier[0],
  &_HealthCheck_Response_message_typesupport_symbol_names.symbol_name[0],
  &_HealthCheck_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t HealthCheck_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_HealthCheck_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Response>()
{
  return &::vyra_module_interfaces::srv::rosidl_typesupport_cpp::HealthCheck_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vyra_module_interfaces, srv, HealthCheck_Response)() {
  return get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Response>();
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
// #include "vyra_module_interfaces/srv/detail/health_check__functions.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
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

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _HealthCheck_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _HealthCheck_Event_type_support_ids_t;

static const _HealthCheck_Event_type_support_ids_t _HealthCheck_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _HealthCheck_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _HealthCheck_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _HealthCheck_Event_type_support_symbol_names_t _HealthCheck_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, HealthCheck_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vyra_module_interfaces, srv, HealthCheck_Event)),
  }
};

typedef struct _HealthCheck_Event_type_support_data_t
{
  void * data[2];
} _HealthCheck_Event_type_support_data_t;

static _HealthCheck_Event_type_support_data_t _HealthCheck_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _HealthCheck_Event_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_HealthCheck_Event_message_typesupport_ids.typesupport_identifier[0],
  &_HealthCheck_Event_message_typesupport_symbol_names.symbol_name[0],
  &_HealthCheck_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t HealthCheck_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_HealthCheck_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Event>()
{
  return &::vyra_module_interfaces::srv::rosidl_typesupport_cpp::HealthCheck_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vyra_module_interfaces, srv, HealthCheck_Event)() {
  return get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _HealthCheck_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _HealthCheck_type_support_ids_t;

static const _HealthCheck_type_support_ids_t _HealthCheck_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _HealthCheck_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _HealthCheck_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _HealthCheck_type_support_symbol_names_t _HealthCheck_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, HealthCheck)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vyra_module_interfaces, srv, HealthCheck)),
  }
};

typedef struct _HealthCheck_type_support_data_t
{
  void * data[2];
} _HealthCheck_type_support_data_t;

static _HealthCheck_type_support_data_t _HealthCheck_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _HealthCheck_service_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_HealthCheck_service_typesupport_ids.typesupport_identifier[0],
  &_HealthCheck_service_typesupport_symbol_names.symbol_name[0],
  &_HealthCheck_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t HealthCheck_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_HealthCheck_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<vyra_module_interfaces::srv::HealthCheck_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<vyra_module_interfaces::srv::HealthCheck>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<vyra_module_interfaces::srv::HealthCheck>,
  &vyra_module_interfaces__srv__HealthCheck__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<vyra_module_interfaces::srv::HealthCheck>()
{
  return &::vyra_module_interfaces::srv::rosidl_typesupport_cpp::HealthCheck_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, vyra_module_interfaces, srv, HealthCheck)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<vyra_module_interfaces::srv::HealthCheck>();
}

#ifdef __cplusplus
}
#endif
