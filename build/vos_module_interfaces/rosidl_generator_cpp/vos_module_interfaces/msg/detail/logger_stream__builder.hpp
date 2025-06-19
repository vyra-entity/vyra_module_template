// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vos_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__BUILDER_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vos_module_interfaces/msg/detail/logger_stream__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vos_module_interfaces
{

namespace msg
{

namespace builder
{

class Init_LoggerStream_timestamp
{
public:
  explicit Init_LoggerStream_timestamp(::vos_module_interfaces::msg::LoggerStream & msg)
  : msg_(msg)
  {}
  ::vos_module_interfaces::msg::LoggerStream timestamp(::vos_module_interfaces::msg::LoggerStream::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vos_module_interfaces::msg::LoggerStream msg_;
};

class Init_LoggerStream_log_message
{
public:
  explicit Init_LoggerStream_log_message(::vos_module_interfaces::msg::LoggerStream & msg)
  : msg_(msg)
  {}
  Init_LoggerStream_timestamp log_message(::vos_module_interfaces::msg::LoggerStream::_log_message_type arg)
  {
    msg_.log_message = std::move(arg);
    return Init_LoggerStream_timestamp(msg_);
  }

private:
  ::vos_module_interfaces::msg::LoggerStream msg_;
};

class Init_LoggerStream_log_level
{
public:
  Init_LoggerStream_log_level()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LoggerStream_log_message log_level(::vos_module_interfaces::msg::LoggerStream::_log_level_type arg)
  {
    msg_.log_level = std::move(arg);
    return Init_LoggerStream_log_message(msg_);
  }

private:
  ::vos_module_interfaces::msg::LoggerStream msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vos_module_interfaces::msg::LoggerStream>()
{
  return vos_module_interfaces::msg::builder::Init_LoggerStream_log_level();
}

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__BUILDER_HPP_
