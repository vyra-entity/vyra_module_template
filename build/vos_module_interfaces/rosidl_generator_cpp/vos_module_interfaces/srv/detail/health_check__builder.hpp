// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/srv/detail/health_check__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::HealthCheck_Request>()
{
  return ::vos_module_interfaces::srv::HealthCheck_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_HealthCheck_Response_issues
{
public:
  explicit Init_HealthCheck_Response_issues(::vos_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::srv::HealthCheck_Response issues(::vos_module_interfaces::srv::HealthCheck_Response::_issues_type arg)
  {
    msg_.issues = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_health_status
{
public:
  explicit Init_HealthCheck_Response_health_status(::vos_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  Init_HealthCheck_Response_issues health_status(::vos_module_interfaces::srv::HealthCheck_Response::_health_status_type arg)
  {
    msg_.health_status = std::move(arg);
    return Init_HealthCheck_Response_issues(msg_);
  }

private:
  ::vos_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_state
{
public:
  explicit Init_HealthCheck_Response_state(::vos_module_interfaces::srv::HealthCheck_Response & msg)
  : msg_(msg)
  {}
  Init_HealthCheck_Response_health_status state(::vos_module_interfaces::srv::HealthCheck_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_HealthCheck_Response_health_status(msg_);
  }

private:
  ::vos_module_interfaces::srv::HealthCheck_Response msg_;
};

class Init_HealthCheck_Response_alive
{
public:
  Init_HealthCheck_Response_alive()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HealthCheck_Response_state alive(::vos_module_interfaces::srv::HealthCheck_Response::_alive_type arg)
  {
    msg_.alive = std::move(arg);
    return Init_HealthCheck_Response_state(msg_);
  }

private:
  ::vos_module_interfaces::srv::HealthCheck_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::HealthCheck_Response>()
{
  return vos_module_interfaces::srv::builder::Init_HealthCheck_Response_alive();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__BUILDER_HPP_
