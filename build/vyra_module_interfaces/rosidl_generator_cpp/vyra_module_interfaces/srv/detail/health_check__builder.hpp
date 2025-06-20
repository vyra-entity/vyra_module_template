// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vyra_module_interfaces/srv/detail/health_check__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vyra_module_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::HealthCheck_Request>()
{
  return ::vyra_module_interfaces::srv::HealthCheck_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace vyra_module_interfaces


namespace vyra_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_HealthCheck_Response_issues
{
public:
  explicit Init_HealthCheck_Response_issues(::vyra_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  ::vyra_module_interfaces::srv::HealthCheck_Response issues(::vyra_module_interfaces::srv::HealthCheck_Response::_issues_type arg)
  {
    msg_.issues = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_health_status
{
public:
  explicit Init_HealthCheck_Response_health_status(::vyra_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  Init_HealthCheck_Response_issues health_status(::vyra_module_interfaces::srv::HealthCheck_Response::_health_status_type arg)
  {
    msg_.health_status = std::move(arg);
    return Init_HealthCheck_Response_issues(msg_);
  }

private:
  ::vyra_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_state
{
public:
  explicit Init_HealthCheck_Response_state(::vyra_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  Init_HealthCheck_Response_health_status state(::vyra_module_interfaces::srv::HealthCheck_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_HealthCheck_Response_health_status(msg_);
  }

private:
  ::vyra_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_alive
{
public:
  Init_HealthCheck_Response_alive()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HealthCheck_Response_state alive(::vyra_module_interfaces::srv::HealthCheck_Response::_alive_type arg)
  {
    msg_.alive = std::move(arg);
    return Init_HealthCheck_Response_state(msg_);
  }

private:
  ::vyra_module_interfaces::srv::HealthCheck_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::HealthCheck_Response>()
{
  return vyra_module_interfaces::srv::builder::Init_HealthCheck_Response_alive();
}

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_
