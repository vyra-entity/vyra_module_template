// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/srv/detail/get_logs__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetLogs_Request_log_level
{
public:
  explicit Init_GetLogs_Request_log_level(::vos_module_interfaces::srv::GetLogs_Request & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::srv::GetLogs_Request log_level(::vos_module_interfaces::srv::GetLogs_Request::_log_level_type arg)
  {
    msg_.log_level = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::GetLogs_Request msg_;
};

class Init_GetLogs_Request_log_lines
{
public:
  Init_GetLogs_Request_log_lines()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetLogs_Request_log_level log_lines(::vos_module_interfaces::srv::GetLogs_Request::_log_lines_type arg)
  {
    msg_.log_lines = std::move(arg);
    return Init_GetLogs_Request_log_level(msg_);
  }

private:
  ::vos_module_interfaces::srv::GetLogs_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::GetLogs_Request>()
{
  return vos_module_interfaces::srv::builder::Init_GetLogs_Request_log_lines();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetLogs_Response_log_messages
{
public:
  Init_GetLogs_Response_log_messages()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vos_module_interfaces::srv::GetLogs_Response log_messages(::vos_module_interfaces::srv::GetLogs_Response::_log_messages_type arg)
  {
    msg_.log_messages = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::GetLogs_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::GetLogs_Response>()
{
  return vos_module_interfaces::srv::builder::Init_GetLogs_Response_log_messages();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__BUILDER_HPP_
