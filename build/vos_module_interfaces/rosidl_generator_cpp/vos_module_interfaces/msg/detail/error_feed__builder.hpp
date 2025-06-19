// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/msg/detail/error_feed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_ErrorFeed_timestamp
{
public:
  explicit Init_ErrorFeed_timestamp(::vos_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::msg::ErrorFeed timestamp(::vos_module_interfaces::msg::ErrorFeed::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_miscellaneous
{
public:
  explicit Init_ErrorFeed_miscellaneous(::vos_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_timestamp miscellaneous(::vos_module_interfaces::msg::ErrorFeed::_miscellaneous_type arg)
  {
    msg_.miscellaneous = std::move(arg);
    return Init_ErrorFeed_timestamp(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_solution
{
public:
  explicit Init_ErrorFeed_solution(::vos_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_miscellaneous solution(::vos_module_interfaces::msg::ErrorFeed::_solution_type arg)
  {
    msg_.solution = std::move(arg);
    return Init_ErrorFeed_miscellaneous(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_description
{
public:
  explicit Init_ErrorFeed_description(::vos_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_solution description(::vos_module_interfaces::msg::ErrorFeed::_description_type arg)
  {
    msg_.description = std::move(arg);
    return Init_ErrorFeed_solution(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_module_id
{
public:
  explicit Init_ErrorFeed_module_id(::vos_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_description module_id(::vos_module_interfaces::msg::ErrorFeed::_module_id_type arg)
  {
    msg_.module_id = std::move(arg);
    return Init_ErrorFeed_description(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_error_code
{
public:
  Init_ErrorFeed_error_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ErrorFeed_module_id error_code(::vos_module_interfaces::msg::ErrorFeed::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ErrorFeed_module_id(msg_);
  }

private:
  ::vos_module_interfaces::msg::ErrorFeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::msg::ErrorFeed>()
{
  return vos_module_interfaces::msg::builder::Init_ErrorFeed_error_code();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_
