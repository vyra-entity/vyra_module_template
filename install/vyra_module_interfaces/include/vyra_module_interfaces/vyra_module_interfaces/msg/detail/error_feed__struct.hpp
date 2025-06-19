// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/msg/error_feed.hpp"


#ifndef VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_HPP_

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
# define DEPRECATED__vyra_module_interfaces__msg__ErrorFeed __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__msg__ErrorFeed __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ErrorFeed_
{
  using Type = ErrorFeed_<ContainerAllocator>;

  explicit ErrorFeed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_code = 0ul;
      this->module_id = "";
      this->description = "";
      this->solution = "";
      this->miscellaneous = "";
    }
  }

  explicit ErrorFeed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : module_id(_alloc),
    description(_alloc),
    solution(_alloc),
    miscellaneous(_alloc),
    timestamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->error_code = 0ul;
      this->module_id = "";
      this->description = "";
      this->solution = "";
      this->miscellaneous = "";
    }
  }

  // field types and members
  using _error_code_type =
    uint32_t;
  _error_code_type error_code;
  using _module_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _module_id_type module_id;
  using _description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _description_type description;
  using _solution_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _solution_type solution;
  using _miscellaneous_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _miscellaneous_type miscellaneous;
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;

  // setters for named parameter idiom
  Type & set__error_code(
    const uint32_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__module_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->module_id = _arg;
    return *this;
  }
  Type & set__description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->description = _arg;
    return *this;
  }
  Type & set__solution(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->solution = _arg;
    return *this;
  }
  Type & set__miscellaneous(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->miscellaneous = _arg;
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
    vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__msg__ErrorFeed
    std::shared_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__msg__ErrorFeed
    std::shared_ptr<vyra_module_interfaces::msg::ErrorFeed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ErrorFeed_ & other) const
  {
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->module_id != other.module_id) {
      return false;
    }
    if (this->description != other.description) {
      return false;
    }
    if (this->solution != other.solution) {
      return false;
    }
    if (this->miscellaneous != other.miscellaneous) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const ErrorFeed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ErrorFeed_

// alias to use template instance with default allocator
using ErrorFeed =
  vyra_module_interfaces::msg::ErrorFeed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__MSG__DETAIL__ERROR_FEED__STRUCT_HPP_
