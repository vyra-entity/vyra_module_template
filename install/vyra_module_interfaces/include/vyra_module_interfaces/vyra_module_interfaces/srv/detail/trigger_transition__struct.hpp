// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Request __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Request __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TriggerTransition_Request_
{
  using Type = TriggerTransition_Request_<ContainerAllocator>;

  explicit TriggerTransition_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->transition_name = "";
    }
  }

  explicit TriggerTransition_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : transition_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->transition_name = "";
    }
  }

  // field types and members
  using _transition_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _transition_name_type transition_name;

  // setters for named parameter idiom
  Type & set__transition_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->transition_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Request
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Request
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TriggerTransition_Request_ & other) const
  {
    if (this->transition_name != other.transition_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const TriggerTransition_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TriggerTransition_Request_

// alias to use template instance with default allocator
using TriggerTransition_Request =
  vyra_module_interfaces::srv::TriggerTransition_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Response __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Response __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TriggerTransition_Response_
{
  using Type = TriggerTransition_Response_<ContainerAllocator>;

  explicit TriggerTransition_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit TriggerTransition_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Response
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__TriggerTransition_Response
    std::shared_ptr<vyra_module_interfaces::srv::TriggerTransition_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TriggerTransition_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const TriggerTransition_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TriggerTransition_Response_

// alias to use template instance with default allocator
using TriggerTransition_Response =
  vyra_module_interfaces::srv::TriggerTransition_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace vyra_module_interfaces
{

namespace srv
{

struct TriggerTransition
{
  using Request = vyra_module_interfaces::srv::TriggerTransition_Request;
  using Response = vyra_module_interfaces::srv::TriggerTransition_Response;
};

}  // namespace srv

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__TRIGGER_TRANSITION__STRUCT_HPP_
