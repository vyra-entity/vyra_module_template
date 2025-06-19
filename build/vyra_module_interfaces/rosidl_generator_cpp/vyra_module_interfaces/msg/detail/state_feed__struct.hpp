// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:msg/StateFeed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/state_feed.hpp"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_HPP_

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
# define DEPRECATED__vyra_module_interfaces__msg__StateFeed __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__msg__StateFeed __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StateFeed_
{
  using Type = StateFeed_<ContainerAllocator>;

  explicit StateFeed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->prev_state = "";
      this->current_state = "";
    }
  }

  explicit StateFeed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : prev_state(_alloc),
    current_state(_alloc),
    timestamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->prev_state = "";
      this->current_state = "";
    }
  }

  // field types and members
  using _prev_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _prev_state_type prev_state;
  using _current_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_state_type current_state;
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__prev_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->prev_state = _arg;
    return *this;
  }
  Type & set__current_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_state = _arg;
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
    vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__msg__StateFeed
    std::shared_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__msg__StateFeed
    std::shared_ptr<vyra_module_interfaces::msg::StateFeed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StateFeed_ & other) const
  {
    if (this->prev_state != other.prev_state) {
      return false;
    }
    if (this->current_state != other.current_state) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const StateFeed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StateFeed_

// alias to use template instance with default allocator
using StateFeed =
  vyra_module_interfaces::msg::StateFeed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__STATE_FEED__STRUCT_HPP_
