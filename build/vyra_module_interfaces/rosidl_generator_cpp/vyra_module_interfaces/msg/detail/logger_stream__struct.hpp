// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__msg__LoggerStream __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__msg__LoggerStream __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LoggerStream_
{
  using Type = LoggerStream_<ContainerAllocator>;

  explicit LoggerStream_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->log_level = "";
      this->log_message = "";
    }
  }

  explicit LoggerStream_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : log_level(_alloc),
    log_message(_alloc),
    timestamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->log_level = "";
      this->log_message = "";
    }
  }

  // field types and members
  using _log_level_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _log_level_type log_level;
  using _log_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _log_message_type log_message;
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__log_level(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->log_level = _arg;
    return *this;
  }
  Type & set__log_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->log_message = _arg;
    return *this;
  }
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__msg__LoggerStream
    std::shared_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__msg__LoggerStream
    std::shared_ptr<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LoggerStream_ & other) const
  {
    if (this->log_level != other.log_level) {
      return false;
    }
    if (this->log_message != other.log_message) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const LoggerStream_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LoggerStream_

// alias to use template instance with default allocator
using LoggerStream =
  vyra_module_interfaces::msg::LoggerStream_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__LOGGER_STREAM__STRUCT_HPP_
