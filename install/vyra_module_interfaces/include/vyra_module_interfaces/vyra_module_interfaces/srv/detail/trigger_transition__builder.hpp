// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vyra_module_interfaces/srv/detail/trigger_transition__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vyra_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_TriggerTransition_Request_transition_name
{
public:
  Init_TriggerTransition_Request_transition_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vyra_module_interfaces::srv::TriggerTransition_Request transition_name(::vyra_module_interfaces::srv::TriggerTransition_Request::_transition_name_type arg)
  {
    msg_.transition_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::srv::TriggerTransition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::TriggerTransition_Request>()
{
  return vyra_module_interfaces::srv::builder::Init_TriggerTransition_Request_transition_name();
}

}  // namespace vyra_module_interfaces


namespace vyra_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_TriggerTransition_Response_message
{
public:
  explicit Init_TriggerTransition_Response_message(::vyra_module_interfaces::srv::TriggerTransition_Response & msg)
  : msg_(msg)
  {}
  ::vyra_module_interfaces::srv::TriggerTransition_Response message(::vyra_module_interfaces::srv::TriggerTransition_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::srv::TriggerTransition_Response msg_;
};

class Init_TriggerTransition_Response_success
{
public:
  Init_TriggerTransition_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TriggerTransition_Response_message success(::vyra_module_interfaces::srv::TriggerTransition_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_TriggerTransition_Response_message(msg_);
  }

private:
  ::vyra_module_interfaces::srv::TriggerTransition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::TriggerTransition_Response>()
{
  return vyra_module_interfaces::srv::builder::Init_TriggerTransition_Response_success();
}

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_
