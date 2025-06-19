// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/logger_stream.hpp"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__TRAITS_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vyra_module_interfaces/msg/detail/logger_stream__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vyra_module_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LoggerStream & msg,
  std::ostream & out)
{
  out << "{";
  // member: log_level
  {
    out << "log_level: ";
    rosidl_generator_traits::value_to_yaml(msg.log_level, out);
    out << ", ";
  }

  // member: log_message
  {
    out << "log_message: ";
    rosidl_generator_traits::value_to_yaml(msg.log_message, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoggerStream & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: log_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "log_level: ";
    rosidl_generator_traits::value_to_yaml(msg.log_level, out);
    out << "\n";
  }

  // member: log_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "log_message: ";
    rosidl_generator_traits::value_to_yaml(msg.log_message, out);
    out << "\n";
  }

  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp:\n";
    to_block_style_yaml(msg.timestamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoggerStream & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::msg::LoggerStream & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::msg::LoggerStream & msg)
{
  return vyra_module_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::msg::LoggerStream>()
{
  return "vyra_module_interfaces::msg::LoggerStream";
}

template<>
inline const char * name<vyra_module_interfaces::msg::LoggerStream>()
{
  return "vyra_module_interfaces/msg/LoggerStream";
}

template<>
struct has_fixed_size<vyra_module_interfaces::msg::LoggerStream>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::msg::LoggerStream>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::msg::LoggerStream>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__TRAITS_HPP_
