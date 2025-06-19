// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/news_feed.hpp"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vyra_module_interfaces/msg/detail/news_feed__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vyra_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_NewsFeed_module_name
{
public:
  explicit Init_NewsFeed_module_name(::vyra_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  ::vyra_module_interfaces::msg::NewsFeed module_name(::vyra_module_interfaces::msg::NewsFeed::_module_name_type arg)
  {
    msg_.module_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vyra_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_module_id
{
public:
  explicit Init_NewsFeed_module_id(::vyra_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_module_name module_id(::vyra_module_interfaces::msg::NewsFeed::_module_id_type arg)
  {
    msg_.module_id = std::move(arg);
    return Init_NewsFeed_module_name(msg_);
  }

private:
  ::vyra_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_timestamp
{
public:
  explicit Init_NewsFeed_timestamp(::vyra_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_module_id timestamp(::vyra_module_interfaces::msg::NewsFeed::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_NewsFeed_module_id(msg_);
  }

private:
  ::vyra_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_message
{
public:
  explicit Init_NewsFeed_message(::vyra_module_interfaces::msg::NewsFeed & msg)
  : msg_(msg)
  {}
  Init_NewsFeed_timestamp message(::vyra_module_interfaces::msg::NewsFeed::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_NewsFeed_timestamp(msg_);
  }

private:
  ::vyra_module_interfaces::msg::NewsFeed msg_;
};

class Init_NewsFeed_type
{
public:
  Init_NewsFeed_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NewsFeed_message type(::vyra_module_interfaces::msg::NewsFeed::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_NewsFeed_message(msg_);
  }

private:
  ::vyra_module_interfaces::msg::NewsFeed msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vyra_module_interfaces::msg::NewsFeed>()
{
  return vyra_module_interfaces::msg::builder::Init_NewsFeed_type();
}

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__BUILDER_HPP_
