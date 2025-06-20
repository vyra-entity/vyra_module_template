// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice

#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Request __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Request __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct HealthCheck_Request_
{
  using Type = HealthCheck_Request_<ContainerAllocator>;

  explicit HealthCheck_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit HealthCheck_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Request
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Request
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HealthCheck_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const HealthCheck_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HealthCheck_Request_

// alias to use template instance with default allocator
using HealthCheck_Request =
  vyra_module_interfaces::srv::HealthCheck_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Response __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Response __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct HealthCheck_Response_
{
  using Type = HealthCheck_Response_<ContainerAllocator>;

  explicit HealthCheck_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->alive = false;
      this->state = "";
      this->health_status = "";
    }
  }

  explicit HealthCheck_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc),
    health_status(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->alive = false;
      this->state = "";
      this->health_status = "";
    }
  }

  // field types and members
  using _alive_type =
    bool;
  _alive_type alive;
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;
  using _health_status_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _health_status_type health_status;
  using _issues_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _issues_type issues;

  // setters for named parameter idiom
  Type & set__alive(
    const bool & _arg)
  {
    this->alive = _arg;
    return *this;
  }
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__health_status(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->health_status = _arg;
    return *this;
  }
  Type & set__issues(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->issues = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Response
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__HealthCheck_Response
    std::shared_ptr<vyra_module_interfaces::srv::HealthCheck_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HealthCheck_Response_ & other) const
  {
    if (this->alive != other.alive) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->health_status != other.health_status) {
      return false;
    }
    if (this->issues != other.issues) {
      return false;
    }
    return true;
  }
  bool operator!=(const HealthCheck_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HealthCheck_Response_

// alias to use template instance with default allocator
using HealthCheck_Response =
  vyra_module_interfaces::srv::HealthCheck_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace vyra_module_interfaces
{

namespace srv
{

struct HealthCheck
{
  using Request = vyra_module_interfaces::srv::HealthCheck_Request;
  using Response = vyra_module_interfaces::srv::HealthCheck_Response;
};

}  // namespace srv

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__HEALTH_CHECK__STRUCT_HPP_
