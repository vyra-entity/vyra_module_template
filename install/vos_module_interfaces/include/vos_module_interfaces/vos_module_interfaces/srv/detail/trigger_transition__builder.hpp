// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/srv/detail/trigger_transition__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
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
  ::vos_module_interfaces::srv::TriggerTransition_Request transition_name(::vos_module_interfaces::srv::TriggerTransition_Request::_transition_name_type arg)
  {
    msg_.transition_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::TriggerTransition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::TriggerTransition_Request>()
{
  return vos_module_interfaces::srv::builder::Init_TriggerTransition_Request_transition_name();
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_TriggerTransition_Response_message
{
public:
  explicit Init_TriggerTransition_Response_message(::vos_module_interfaces::srv::TriggerTransition_Response & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::srv::TriggerTransition_Response message(::vos_module_interfaces::srv::TriggerTransition_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::TriggerTransition_Response msg_;
};

class Init_TriggerTransition_Response_success
{
public:
  Init_TriggerTransition_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TriggerTransition_Response_message success(::vos_module_interfaces::srv::TriggerTransition_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_TriggerTransition_Response_message(msg_);
  }

private:
  ::vos_module_interfaces::srv::TriggerTransition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::TriggerTransition_Response>()
{
  return vos_module_interfaces::srv::builder::Init_TriggerTransition_Response_success();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__BUILDER_HPP_
