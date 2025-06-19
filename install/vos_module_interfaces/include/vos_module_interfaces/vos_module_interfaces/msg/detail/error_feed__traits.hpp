// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vos_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__TRAITS_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vos_module_interfaces/msg/detail/error_feed__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vos_module_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ErrorFeed & msg,
  std::ostream & out)
{
  out << "{";
  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: module_id
  {
    out << "module_id: ";
    rosidl_generator_traits::value_to_yaml(msg.module_id, out);
    out << ", ";
  }

  // member: description
  {
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << ", ";
  }

  // member: solution
  {
    out << "solution: ";
    rosidl_generator_traits::value_to_yaml(msg.solution, out);
    out << ", ";
  }

  // member: miscellaneous
  {
    out << "miscellaneous: ";
    rosidl_generator_traits::value_to_yaml(msg.miscellaneous, out);
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
  const ErrorFeed & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: error_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << "\n";
  }

  // member: module_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "module_id: ";
    rosidl_generator_traits::value_to_yaml(msg.module_id, out);
    out << "\n";
  }

  // member: description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "description: ";
    rosidl_generator_traits::value_to_yaml(msg.description, out);
    out << "\n";
  }

  // member: solution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "solution: ";
    rosidl_generator_traits::value_to_yaml(msg.solution, out);
    out << "\n";
  }

  // member: miscellaneous
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "miscellaneous: ";
    rosidl_generator_traits::value_to_yaml(msg.miscellaneous, out);
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

inline std::string to_yaml(const ErrorFeed & msg, bool use_flow_style = false)
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

}  // namespace vos_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vos_module_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vos_module_interfaces::msg::ErrorFeed & msg,
  std::ostream & out, size_t indentation = 0)
{
  vos_module_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vos_module_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const vos_module_interfaces::msg::ErrorFeed & msg)
{
  return vos_module_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vos_module_interfaces::msg::ErrorFeed>()
{
  return "vos_module_interfaces::msg::ErrorFeed";
}

template<>
inline const char * name<vos_module_interfaces::msg::ErrorFeed>()
{
  return "vos_module_interfaces/msg/ErrorFeed";
}

template<>
struct has_fixed_size<vos_module_interfaces::msg::ErrorFeed>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vos_module_interfaces::msg::ErrorFeed>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vos_module_interfaces::msg::ErrorFeed>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__TRAITS_HPP_
