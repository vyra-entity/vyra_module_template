// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vos_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vos_module_interfaces/msg/detail/state_feed__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vos_module_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void StateFeed_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vos_module_interfaces::msg::StateFeed(_init);
}

void StateFeed_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vos_module_interfaces::msg::StateFeed *>(message_memory);
  typed_message->~StateFeed();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember StateFeed_message_member_array[3] = {
  {
    "prev_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces::msg::StateFeed, prev_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "current_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces::msg::StateFeed, current_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "timestamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vos_module_interfaces::msg::StateFeed, timestamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers StateFeed_message_members = {
  "vos_module_interfaces::msg",  // message namespace
  "StateFeed",  // message name
  3,  // number of fields
  sizeof(vos_module_interfaces::msg::StateFeed),
  StateFeed_message_member_array,  // message members
  StateFeed_init_function,  // function to initialize message memory (memory has to be allocated)
  StateFeed_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t StateFeed_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &StateFeed_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vos_module_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vos_module_interfaces::msg::StateFeed>()
{
  return &::vos_module_interfaces::msg::rosidl_typesupport_introspection_cpp::StateFeed_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vos_module_interfaces, msg, StateFeed)() {
  return &::vos_module_interfaces::msg::rosidl_typesupport_introspection_cpp::StateFeed_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
