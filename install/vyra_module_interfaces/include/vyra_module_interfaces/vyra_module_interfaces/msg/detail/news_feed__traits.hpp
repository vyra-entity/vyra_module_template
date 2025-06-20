// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__TRAITS_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vyra_module_interfaces/msg/detail/news_feed__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vyra_module_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const NewsFeed & msg,
  std::ostream & out)
{
  out << "{";
  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: timestamp
  {
    out << "timestamp: ";
    to_flow_style_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: module_id
  {
    out << "module_id: ";
    rosidl_generator_traits::value_to_yaml(msg.module_id, out);
    out << ", ";
  }

  // member: module_name
  {
    out << "module_name: ";
    rosidl_generator_traits::value_to_yaml(msg.module_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NewsFeed & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
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

  // member: module_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "module_id: ";
    rosidl_generator_traits::value_to_yaml(msg.module_id, out);
    out << "\n";
  }

  // member: module_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "module_name: ";
    rosidl_generator_traits::value_to_yaml(msg.module_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NewsFeed & msg, bool use_flow_style = false)
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
  const vyra_module_interfaces::msg::NewsFeed & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::msg::NewsFeed & msg)
{
  return vyra_module_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::msg::NewsFeed>()
{
  return "vyra_module_interfaces::msg::NewsFeed";
}

template<>
inline const char * name<vyra_module_interfaces::msg::NewsFeed>()
{
  return "vyra_module_interfaces/msg/NewsFeed";
}

template<>
struct has_fixed_size<vyra_module_interfaces::msg::NewsFeed>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::msg::NewsFeed>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::msg::NewsFeed>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__TRAITS_HPP_
