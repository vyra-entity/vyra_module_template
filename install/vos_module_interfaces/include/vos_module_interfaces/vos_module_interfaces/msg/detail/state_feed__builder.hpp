// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/msg/detail/state_feed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_StateFeed_timestamp
{
public:
  explicit Init_StateFeed_timestamp(::vos_module_interfaces::msg::StateFeed & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::msg::StateFeed timestamp(::vos_module_interfaces::msg::StateFeed::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::msg::StateFeed msg_;
};

class Init_StateFeed_current_state
{
public:
  explicit Init_StateFeed_current_state(::vos_module_interfaces::msg::StateFeed & msg)
  : msg_(msg)
  {}
  Init_StateFeed_timestamp current_state(::vos_module_interfaces::msg::StateFeed::_current_state_type arg)
  {
    msg_.current_state = std::move(arg);
    return Init_StateFeed_timestamp(msg_);
  }

private:
  ::vos_module_interfaces::msg::StateFeed msg_;
};

class Init_StateFeed_prev_state
{
public:
  Init_StateFeed_prev_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StateFeed_current_state prev_state(::vos_module_interfaces::msg::StateFeed::_prev_state_type arg)
  {
    msg_.prev_state = std::move(arg);
    return Init_StateFeed_current_state(msg_);
  }

private:
  ::vos_module_interfaces::msg::StateFeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::msg::StateFeed>()
{
  return vos_module_interfaces::msg::builder::Init_StateFeed_prev_state();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__BUILDER_HPP_
