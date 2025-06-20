// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "vyra_module_interfaces/msg/detail/logger_stream__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace vyra_module_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_serialize(
  const vyra_module_interfaces::msg::LoggerStream & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces::msg::LoggerStream & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
get_serialized_size(
  const vyra_module_interfaces::msg::LoggerStream & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
max_serialized_size_LoggerStream(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vyra_module_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, msg, LoggerStream)();

#ifdef __cplusplus
}
#endif

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
