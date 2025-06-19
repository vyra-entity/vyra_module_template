// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/msg/detail/news_feed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_NewsFeed_module_name
{
public:
  explicit Init_NewsFeed_module_name(::vos_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::msg::NewsFeed module_name(::vos_module_interfaces::msg::NewsFeed::_module_name_type arg)
  {
    msg_.module_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_module_id
{
public:
  explicit Init_NewsFeed_module_id(::vos_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_module_name module_id(::vos_module_interfaces::msg::NewsFeed::_module_id_type arg)
  {
    msg_.module_id = std::move(arg);
    return Init_NewsFeed_module_name(msg_);
  }

private:
  ::vos_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_timestamp
{
public:
  explicit Init_NewsFeed_timestamp(::vos_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_module_id timestamp(::vos_module_interfaces::msg::NewsFeed::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_NewsFeed_module_id(msg_);
  }

private:
  ::vos_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_message
{
public:
  explicit Init_NewsFeed_message(::vos_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_timestamp message(::vos_module_interfaces::msg::NewsFeed::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_NewsFeed_timestamp(msg_);
  }

private:
  ::vos_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_type
{
public:
  Init_NewsFeed_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NewsFeed_message type(::vos_module_interfaces::msg::NewsFeed::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_NewsFeed_message(msg_);
  }

private:
  ::vos_module_interfaces::msg::NewsFeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::msg::NewsFeed>()
{
  return vos_module_interfaces::msg::builder::Init_NewsFeed_type();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_
