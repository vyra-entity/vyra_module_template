// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vos_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__TRAITS_HPP_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vos_module_interfaces/srv/detail/get_capabilities__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vos_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCapabilities_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCapabilities_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCapabilities_Request & msg, bool use_flow_style = false)
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

}  // namespace vos_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vos_module_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vos_module_interfaces::srv::GetCapabilities_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vos_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vos_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vos_module_interfaces::srv::GetCapabilities_Request & msg)
{
  return vos_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vos_module_interfaces::srv::GetCapabilities_Request>()
{
  return "vos_module_interfaces::srv::GetCapabilities_Request";
}

template<>
inline const char * name<vos_module_interfaces::srv::GetCapabilities_Request>()
{
  return "vos_module_interfaces/srv/GetCapabilities_Request";
}

template<>
struct has_fixed_size<vos_module_interfaces::srv::GetCapabilities_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vos_module_interfaces::srv::GetCapabilities_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vos_module_interfaces::srv::GetCapabilities_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vos_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCapabilities_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: capabilities
  {
    if (msg.capabilities.size() == 0) {
      out << "capabilities: []";
    } else {
      out << "capabilities: [";
      size_t pending_items = msg.capabilities.size();
      for (auto item : msg.capabilities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCapabilities_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: capabilities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.capabilities.size() == 0) {
      out << "capabilities: []\n";
    } else {
      out << "capabilities:\n";
      for (auto item : msg.capabilities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCapabilities_Response & msg, bool use_flow_style = false)
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

}  // namespace vos_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vos_module_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vos_module_interfaces::srv::GetCapabilities_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vos_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vos_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vos_module_interfaces::srv::GetCapabilities_Response & msg)
{
  return vos_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vos_module_interfaces::srv::GetCapabilities_Response>()
{
  return "vos_module_interfaces::srv::GetCapabilities_Response";
}

template<>
inline const char * name<vos_module_interfaces::srv::GetCapabilities_Response>()
{
  return "vos_module_interfaces/srv/GetCapabilities_Response";
}

template<>
struct has_fixed_size<vos_module_interfaces::srv::GetCapabilities_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vos_module_interfaces::srv::GetCapabilities_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vos_module_interfaces::srv::GetCapabilities_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vos_module_interfaces::srv::GetCapabilities>()
{
  return "vos_module_interfaces::srv::GetCapabilities";
}

template<>
inline const char * name<vos_module_interfaces::srv::GetCapabilities>()
{
  return "vos_module_interfaces/srv/GetCapabilities";
}

template<>
struct has_fixed_size<vos_module_interfaces::srv::GetCapabilities>
  : std::integral_constant<
    bool,
    has_fixed_size<vos_module_interfaces::srv::GetCapabilities_Request>::value &&
    has_fixed_size<vos_module_interfaces::srv::GetCapabilities_Response>::value
  >
{
};

template<>
struct has_bounded_size<vos_module_interfaces::srv::GetCapabilities>
  : std::integral_constant<
    bool,
    has_bounded_size<vos_module_interfaces::srv::GetCapabilities_Request>::value &&
    has_bounded_size<vos_module_interfaces::srv::GetCapabilities_Response>::value
  >
{
};

template<>
struct is_service<vos_module_interfaces::srv::GetCapabilities>
  : std::true_type
{
};

template<>
struct is_service_request<vos_module_interfaces::srv::GetCapabilities_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vos_module_interfaces::srv::GetCapabilities_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__TRAITS_HPP_
