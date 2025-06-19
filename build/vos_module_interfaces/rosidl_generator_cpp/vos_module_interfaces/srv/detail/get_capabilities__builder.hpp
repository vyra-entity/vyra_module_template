// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/srv/detail/get_capabilities__struct.hpp"
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
auto build<::vos_module_interfaces::srv::GetCapabilities_Request>()
{
  return ::vos_module_interfaces::srv::GetCapabilities_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace vos_module_interfaces


namespace vos_module_interfaces
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
  ::vos_module_interfaces::srv::GetCapabilities_Response capabilities(::vos_module_interfaces::srv::GetCapabilities_Response::_capabilities_type arg)
  {
    msg_.capabilities = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::srv::GetCapabilities_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::srv::GetCapabilities_Response>()
{
  return vos_module_interfaces::srv::builder::Init_GetCapabilities_Response_capabilities();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__BUILDER_HPP_
