// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/srv/health_check.hpp"


#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__TRAITS_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vyra_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const HealthCheck_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HealthCheck_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HealthCheck_Request & msg, bool use_flow_style = false)
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
  const vyra_module_interfaces::srv::HealthCheck_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::srv::HealthCheck_Request & msg)
{
  return vyra_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::srv::HealthCheck_Request>()
{
  return "vyra_module_interfaces::srv::HealthCheck_Request";
}

template<>
inline const char * name<vyra_module_interfaces::srv::HealthCheck_Request>()
{
  return "vyra_module_interfaces/srv/HealthCheck_Request";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::HealthCheck_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vyra_module_interfaces::srv::HealthCheck_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vyra_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const HealthCheck_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: alive
  {
    out << "alive: ";
    rosidl_generator_traits::value_to_yaml(msg.alive, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: health_status
  {
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << ", ";
  }

  // member: issues
  {
    if (msg.issues.size() == 0) {
      out << "issues: []";
    } else {
      out << "issues: [";
      size_t pending_items = msg.issues.size();
      for (auto item : msg.issues) {
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
  const HealthCheck_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: alive
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alive: ";
    rosidl_generator_traits::value_to_yaml(msg.alive, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: health_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << "\n";
  }

  // member: issues
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.issues.size() == 0) {
      out << "issues: []\n";
    } else {
      out << "issues:\n";
      for (auto item : msg.issues) {
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

inline std::string to_yaml(const HealthCheck_Response & msg, bool use_flow_style = false)
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
  const vyra_module_interfaces::srv::HealthCheck_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::srv::HealthCheck_Response & msg)
{
  return vyra_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::srv::HealthCheck_Response>()
{
  return "vyra_module_interfaces::srv::HealthCheck_Response";
}

template<>
inline const char * name<vyra_module_interfaces::srv::HealthCheck_Response>()
{
  return "vyra_module_interfaces/srv/HealthCheck_Response";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::HealthCheck_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::srv::HealthCheck_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace vyra_module_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const HealthCheck_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
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
  const HealthCheck_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HealthCheck_Event & msg, bool use_flow_style = false)
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
  const vyra_module_interfaces::srv::HealthCheck_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::srv::HealthCheck_Event & msg)
{
  return vyra_module_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::srv::HealthCheck_Event>()
{
  return "vyra_module_interfaces::srv::HealthCheck_Event";
}

template<>
inline const char * name<vyra_module_interfaces::srv::HealthCheck_Event>()
{
  return "vyra_module_interfaces/srv/HealthCheck_Event";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::HealthCheck_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Request>::value && has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Response>::value> {};

template<>
struct is_message<vyra_module_interfaces::srv::HealthCheck_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vyra_module_interfaces::srv::HealthCheck>()
{
  return "vyra_module_interfaces::srv::HealthCheck";
}

template<>
inline const char * name<vyra_module_interfaces::srv::HealthCheck>()
{
  return "vyra_module_interfaces/srv/HealthCheck";
}

template<>
struct has_fixed_size<vyra_module_interfaces::srv::HealthCheck>
  : std::integral_constant<
    bool,
    has_fixed_size<vyra_module_interfaces::srv::HealthCheck_Request>::value &&
    has_fixed_size<vyra_module_interfaces::srv::HealthCheck_Response>::value
  >
{
};

template<>
struct has_bounded_size<vyra_module_interfaces::srv::HealthCheck>
  : std::integral_constant<
    bool,
    has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Request>::value &&
    has_bounded_size<vyra_module_interfaces::srv::HealthCheck_Response>::value
  >
{
};

template<>
struct is_service<vyra_module_interfaces::srv::HealthCheck>
  : std::true_type
{
};

template<>
struct is_service_request<vyra_module_interfaces::srv::HealthCheck_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vyra_module_interfaces::srv::HealthCheck_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__TRAITS_HPP_
