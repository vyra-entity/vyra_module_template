// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vyra_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/srv/get_capabilities.hpp"


#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vyra_module_interfaces/srv/detail/get_capabilities__struct.hpp"
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
auto build<::vyra_module_interfaces::srv::GetCapabilities_Request>()
{
  return ::vyra_module_interfaces::srv::GetCapabilities_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace vyra_module_interfaces


namespace vyra_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetCapabilities_Response_capabilities
{
public:
  Init_GetCapabilities_Response_capabilities()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::vyra_module_interfaces::srv::GetCapabilities_Response capabilities(::vyra_module_interfaces::srv::GetCapabilities_Response::_capabilities_type arg)
  {
    msg_.capabilities = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::srv::GetCapabilities_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::GetCapabilities_Response>()
{
  return vyra_module_interfaces::srv::builder::Init_GetCapabilities_Response_capabilities();
}

}  // namespace vyra_module_interfaces


namespace vyra_module_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetCapabilities_Event_response
{
public:
  explicit Init_GetCapabilities_Event_response(::vyra_module_interfaces::srv::GetCapabilities_Event & msg)
  : msg_(msg)
  {}
  ::vyra_module_interfaces::srv::GetCapabilities_Event response(::vyra_module_interfaces::srv::GetCapabilities_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::srv::GetCapabilities_Event msg_;
};

class Init_GetCapabilities_Event_request
{
public:
  explicit Init_GetCapabilities_Event_request(::vyra_module_interfaces::srv::GetCapabilities_Event & msg)
  : msg_(msg)
  {}
  Init_GetCapabilities_Event_response request(::vyra_module_interfaces::srv::GetCapabilities_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetCapabilities_Event_response(msg_);
  }

private:
  ::vyra_module_interfaces::srv::GetCapabilities_Event msg_;
};

class Init_GetCapabilities_Event_info
{
public:
  Init_GetCapabilities_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetCapabilities_Event_request info(::vyra_module_interfaces::srv::GetCapabilities_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetCapabilities_Event_request(msg_);
  }

private:
  ::vyra_module_interfaces::srv::GetCapabilities_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::srv::GetCapabilities_Event>()
{
  return vyra_module_interfaces::srv::builder::Init_GetCapabilities_Event_info();
}

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_
