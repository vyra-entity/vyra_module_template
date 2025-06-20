// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__GetLogs_Request __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__GetLogs_Request __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetLogs_Request_
{
  using Type = GetLogs_Request_<ContainerAllocator>;

  explicit GetLogs_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->log_lines = 0l;
      this->log_level = 0;
    }
  }

  explicit GetLogs_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->log_lines = 0l;
      this->log_level = 0;
    }
  }

  // field types and members
  using _log_lines_type =
    int32_t;
  _log_lines_type log_lines;
  using _log_level_type =
    uint8_t;
  _log_level_type log_level;

  // setters for named parameter idiom
  Type & set__log_lines(
    const int32_t & _arg)
  {
    this->log_lines = _arg;
    return *this;
  }
  Type & set__log_level(
    const uint8_t & _arg)
  {
    this->log_level = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__GetLogs_Request
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__GetLogs_Request
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetLogs_Request_ & other) const
  {
    if (this->log_lines != other.log_lines) {
      return false;
    }
    if (this->log_level != other.log_level) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetLogs_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetLogs_Request_

// alias to use template instance with default allocator
using GetLogs_Request =
  vyra_module_interfaces::srv::GetLogs_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces


// Include directives for member types
// Member 'log_messages'
#include "vyra_module_interfaces/msg/detail/logger_stream__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__GetLogs_Response __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__GetLogs_Response __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetLogs_Response_
{
  using Type = GetLogs_Response_<ContainerAllocator>;

  explicit GetLogs_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit GetLogs_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _log_messages_type =
    std::vector<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>>;
  _log_messages_type log_messages;

  // setters for named parameter idiom
  Type & set__log_messages(
    const std::vector<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::msg::LoggerStream_<ContainerAllocator>>> & _arg)
  {
    this->log_messages = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__GetLogs_Response
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__GetLogs_Response
    std::shared_ptr<vyra_module_interfaces::srv::GetLogs_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetLogs_Response_ & other) const
  {
    if (this->log_messages != other.log_messages) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetLogs_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetLogs_Response_

// alias to use template instance with default allocator
using GetLogs_Response =
  vyra_module_interfaces::srv::GetLogs_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace vyra_module_interfaces
{

namespace srv
{

struct GetLogs
{
  using Request = vyra_module_interfaces::srv::GetLogs_Request;
  using Response = vyra_module_interfaces::srv::GetLogs_Response;
};

}  // namespace srv

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_LOGS__STRUCT_HPP_
