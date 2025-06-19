// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vyra_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/action/initiate_update.hpp"


#ifndef VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__TRAITS_HPP_
#define VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vyra_module_interfaces/action/detail/initiate_update__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: module_name
  {
    out << "module_name: ";
    rosidl_generator_traits::value_to_yaml(msg.module_name, out);
    out << ", ";
  }

  // member: update_url
  {
    out << "update_url: ";
    rosidl_generator_traits::value_to_yaml(msg.update_url, out);
    out << ", ";
  }

  // member: target_version
  {
    out << "target_version: ";
    rosidl_generator_traits::value_to_yaml(msg.target_version, out);
    out << ", ";
  }

  // member: force
  {
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
    out << ", ";
  }

  // member: expected_hash
  {
    out << "expected_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_hash, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: module_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "module_name: ";
    rosidl_generator_traits::value_to_yaml(msg.module_name, out);
    out << "\n";
  }

  // member: update_url
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "update_url: ";
    rosidl_generator_traits::value_to_yaml(msg.update_url, out);
    out << "\n";
  }

  // member: target_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_version: ";
    rosidl_generator_traits::value_to_yaml(msg.target_version, out);
    out << "\n";
  }

  // member: force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
    out << "\n";
  }

  // member: expected_hash
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "expected_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_hash, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_Goal & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_Goal>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_Goal";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_Goal>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_Goal";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: report
  {
    out << "report: ";
    rosidl_generator_traits::value_to_yaml(msg.report, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_Result & msg,
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

  // member: report
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "report: ";
    rosidl_generator_traits::value_to_yaml(msg.report, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_Result & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_Result>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_Result";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_Result>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_Result";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: status_message
  {
    out << "status_message: ";
    rosidl_generator_traits::value_to_yaml(msg.status_message, out);
    out << ", ";
  }

  // member: progress_percentage
  {
    out << "progress_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percentage, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status_message: ";
    rosidl_generator_traits::value_to_yaml(msg.status_message, out);
    out << "\n";
  }

  // member: progress_percentage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress_percentage: ";
    rosidl_generator_traits::value_to_yaml(msg.progress_percentage, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_Feedback & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_Feedback>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_Feedback";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_Feedback>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_Feedback";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "vyra_module_interfaces/action/detail/initiate_update__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_SendGoal_Request";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Goal>::value> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Goal>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_SendGoal_Response";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_SendGoal_Event & msg,
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
  const InitiateUpdate_SendGoal_Event & msg,
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

inline std::string to_yaml(const InitiateUpdate_SendGoal_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_SendGoal_Event";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_SendGoal>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_SendGoal";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_SendGoal>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_SendGoal";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>::value &&
    has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>::value &&
    has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<vyra_module_interfaces::action::InitiateUpdate_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vyra_module_interfaces::action::InitiateUpdate_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_GetResult_Request & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_GetResult_Request";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_GetResult_Request";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_GetResult_Response & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_GetResult_Response";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_GetResult_Response";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Result>::value> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Result>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_GetResult_Event & msg,
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
  const InitiateUpdate_GetResult_Event & msg,
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

inline std::string to_yaml(const InitiateUpdate_GetResult_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_GetResult_Event & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_GetResult_Event>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_GetResult_Event";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_GetResult_Event>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_GetResult_Event";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_GetResult_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_GetResult>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_GetResult";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_GetResult>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_GetResult";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>::value &&
    has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>::value &&
    has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>::value
  >
{
};

template<>
struct is_service<vyra_module_interfaces::action::InitiateUpdate_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<vyra_module_interfaces::action::InitiateUpdate_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<vyra_module_interfaces::action::InitiateUpdate_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__traits.hpp"

namespace vyra_module_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const InitiateUpdate_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitiateUpdate_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitiateUpdate_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace vyra_module_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use vyra_module_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  vyra_module_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vyra_module_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage & msg)
{
  return vyra_module_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage>()
{
  return "vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage>()
{
  return "vyra_module_interfaces/action/InitiateUpdate_FeedbackMessage";
}

template<>
struct has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value && has_fixed_size<vyra_module_interfaces::action::InitiateUpdate_Feedback>::value> {};

template<>
struct has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value && has_bounded_size<vyra_module_interfaces::action::InitiateUpdate_Feedback>::value> {};

template<>
struct is_message<vyra_module_interfaces::action::InitiateUpdate_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
inline const char * data_type<vyra_module_interfaces::action::InitiateUpdate>()
{
  return "vyra_module_interfaces::action::InitiateUpdate";
}

template<>
inline const char * name<vyra_module_interfaces::action::InitiateUpdate>()
{
  return "vyra_module_interfaces/action/InitiateUpdate";
}

template<>
struct is_action<vyra_module_interfaces::action::InitiateUpdate>
  : std::true_type
{
};

template<>
struct is_action_goal<vyra_module_interfaces::action::InitiateUpdate_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<vyra_module_interfaces::action::InitiateUpdate_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<vyra_module_interfaces::action::InitiateUpdate_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // VYRA_MODULE_INTERFACES__ACTION__DETAIL__INITIATE_UPDATE__TRAITS_HPP_
