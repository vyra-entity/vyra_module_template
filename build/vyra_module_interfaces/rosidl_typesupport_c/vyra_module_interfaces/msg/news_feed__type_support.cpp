// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vyra_module_interfaces/msg/detail/news_feed__struct.h"
#include "vyra_module_interfaces/msg/detail/news_feed__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vyra_module_interfaces
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _NewsFeed_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _NewsFeed_type_support_ids_t;

static const _NewsFeed_type_support_ids_t _NewsFeed_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _NewsFeed_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _NewsFeed_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _NewsFeed_type_support_symbol_names_t _NewsFeed_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, msg, NewsFeed)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vyra_module_interfaces, msg, NewsFeed)),
  }
};

typedef struct _NewsFeed_type_support_data_t
{
  void * data[2];
} _NewsFeed_type_support_data_t;

static _NewsFeed_type_support_data_t _NewsFeed_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _NewsFeed_message_typesupport_map = {
  2,
  "vyra_module_interfaces",
  &_NewsFeed_message_typesupport_ids.typesupport_identifier[0],
  &_NewsFeed_message_typesupport_symbol_names.symbol_name[0],
  &_NewsFeed_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t NewsFeed_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_NewsFeed_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, vyra_module_interfaces, msg, NewsFeed)() {
  return &::vyra_module_interfaces::msg::rosidl_typesupport_c::NewsFeed_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
