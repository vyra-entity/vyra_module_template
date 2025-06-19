// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vos_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice

#ifndef VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_HPP_
#define VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_HPP_

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
# define DEPRECATED__vos_module_interfaces__msg__NewsFeed __attribute__((deprecated))
#else
# define DEPRECATED__vos_module_interfaces__msg__NewsFeed __declspec(deprecated)
#endif

namespace vos_module_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NewsFeed_
{
  using Type = NewsFeed_<ContainerAllocator>;

  explicit NewsFeed_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : timestamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = "";
      this->message = "";
      this->module_id = "";
      this->module_name = "";
    }
  }

  explicit NewsFeed_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : type(_alloc),
    message(_alloc),
    timestamp(_alloc, _init),
    module_id(_alloc),
    module_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = "";
      this->message = "";
      this->module_id = "";
      this->module_name = "";
    }
  }

  // field types and members
  using _type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _type_type type;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _timestamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _timestamp_type timestamp;
  using _module_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _module_id_type module_id;
  using _module_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _module_name_type module_name;

  // setters for named parameter idiom
  Type & set__type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__timestamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__module_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->module_id = _arg;
    return *this;
  }
  Type & set__module_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->module_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> *;
  using ConstRawPtr =
    const vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vos_module_interfaces__msg__NewsFeed
    std::shared_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vos_module_interfaces__msg__NewsFeed
    std::shared_ptr<vos_module_interfaces::msg::NewsFeed_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NewsFeed_ & other) const
  {
    if (this->type != other.type) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->module_id != other.module_id) {
      return false;
    }
    if (this->module_name != other.module_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const NewsFeed_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NewsFeed_

// alias to use template instance with default allocator
using NewsFeed =
  vos_module_interfaces::msg::NewsFeed_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vos_module_interfaces

#endif  // VOS_MODULE_INTERFACES__MSG__DETAIL__NEWS_FEED__STRUCT_HPP_
