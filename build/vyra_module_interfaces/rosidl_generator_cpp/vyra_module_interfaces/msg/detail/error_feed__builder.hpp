// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vyra_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/error_feed.hpp"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vyra_module_interfaces/msg/detail/error_feed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vyra_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_ErrorFeed_timestamp
{
public:
  explicit Init_ErrorFeed_timestamp(::vyra_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  ::vyra_module_interfaces::msg::ErrorFeed timestamp(::vyra_module_interfaces::msg::ErrorFeed::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_miscellaneous
{
public:
  explicit Init_ErrorFeed_miscellaneous(::vyra_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_timestamp miscellaneous(::vyra_module_interfaces::msg::ErrorFeed::_miscellaneous_type arg)
  {
    msg_.miscellaneous = std::move(arg);
    return Init_ErrorFeed_timestamp(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_solution
{
public:
  explicit Init_ErrorFeed_solution(::vyra_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_miscellaneous solution(::vyra_module_interfaces::msg::ErrorFeed::_solution_type arg)
  {
    msg_.solution = std::move(arg);
    return Init_ErrorFeed_miscellaneous(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_description
{
public:
  explicit Init_ErrorFeed_description(::vyra_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_solution description(::vyra_module_interfaces::msg::ErrorFeed::_description_type arg)
  {
    msg_.description = std::move(arg);
    return Init_ErrorFeed_solution(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_module_id
{
public:
  explicit Init_ErrorFeed_module_id(::vyra_module_interfaces::msg::ErrorFeed & msg)
  : msg_(msg)
  {}
  Init_ErrorFeed_description module_id(::vyra_module_interfaces::msg::ErrorFeed::_module_id_type arg)
  {
    msg_.module_id = std::move(arg);
    return Init_ErrorFeed_description(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

class Init_ErrorFeed_error_code
{
public:
  Init_ErrorFeed_error_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ErrorFeed_module_id error_code(::vyra_module_interfaces::msg::ErrorFeed::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ErrorFeed_module_id(msg_);
  }

private:
  ::vyra_module_interfaces::msg::ErrorFeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::msg::ErrorFeed>()
{
  return vyra_module_interfaces::msg::builder::Init_ErrorFeed_error_code();
}

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__BUILDER_HPP_
