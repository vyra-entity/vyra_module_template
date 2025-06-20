// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__TRAITS_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vyra_module_interfaces/srv/detail/trigger_transition__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vyra_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const TriggerTransition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: transition_name
  {
    out << "transition_name: ";
    rosidl_generator_traits::value_to_yaml(msg.transition_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TriggerTransition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: transition_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "transition_name: ";
    rosidl_generator_traits::value_to_yaml(msg.transition_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TriggerTransition_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::srv::TriggerTransition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::srv::TriggerTransition_Request & msg)
{
  return vyra_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::srv::TriggerTransition_Request>()
{
  return "vyra_module_interfaces::srv::TriggerTransition_Request";
}

template<>
inline const char * name<vyra_module_interfaces::srv::TriggerTransition_Request>()
{
  return "vyra_module_interfaces/srv/TriggerTransition_Request";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::TriggerTransition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::TriggerTransition_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::srv::TriggerTransition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vyra_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const TriggerTransition_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TriggerTransition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TriggerTransition_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::srv::TriggerTransition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::srv::TriggerTransition_Response & msg)
{
  return vyra_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::srv::TriggerTransition_Response>()
{
  return "vyra_module_interfaces::srv::TriggerTransition_Response";
}

template<>
inline const char * name<vyra_module_interfaces::srv::TriggerTransition_Response>()
{
  return "vyra_module_interfaces/srv/TriggerTransition_Response";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::TriggerTransition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::TriggerTransition_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::srv::TriggerTransition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vyra_module_interfaces::srv::TriggerTransition>()
{
  return "vyra_module_interfaces::srv::TriggerTransition";
}

template<>
inline const char * name<vyra_module_interfaces::srv::TriggerTransition>()
{
  return "vyra_module_interfaces/srv/TriggerTransition";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::TriggerTransition>
  : std::integral_constant<
    bool,
    has_fixed_size<vyra_module_interfaces::srv::TriggerTransition_Request>::value &&
    has_fixed_size<vyra_module_interfaces::srv::TriggerTransition_Response>::value
  >
{
};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::TriggerTransition>
  : std::integral_constant<
    bool,
    has_bounded_size<vyra_module_interfaces::srv::TriggerTransition_Request>::value &&
    has_bounded_size<vyra_module_interfaces::srv::TriggerTransition_Response>::value
  >
{
};

template<>
struct is_service<vyra_module_interfaces::srv::TriggerTransition>
  : std::true_type
{
};

template<>
struct is_service_request<vyra_module_interfaces::srv::TriggerTransition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vyra_module_interfaces::srv::TriggerTransition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__TRAITS_HPP_
