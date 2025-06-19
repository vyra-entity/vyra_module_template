// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vyra_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vyra_module_interfaces/srv/get_capabilities.hpp"


#ifndef VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_HPP_
#define VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Request __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Request __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCapabilities_Request_
{
  using Type = GetCapabilities_Request_<ContainerAllocator>;

  explicit GetCapabilities_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit GetCapabilities_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Request
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Request
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCapabilities_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCapabilities_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCapabilities_Request_

// alias to use template instance with default allocator
using GetCapabilities_Request =
  vyra_module_interfaces::srv::GetCapabilities_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces


#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Response __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Response __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCapabilities_Response_
{
  using Type = GetCapabilities_Response_<ContainerAllocator>;

  explicit GetCapabilities_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit GetCapabilities_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _capabilities_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _capabilities_type capabilities;

  // setters for named parameter idiom
  Type & set__capabilities(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->capabilities = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Response
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Response
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCapabilities_Response_ & other) const
  {
    if (this->capabilities != other.capabilities) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCapabilities_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCapabilities_Response_

// alias to use template instance with default allocator
using GetCapabilities_Response =
  vyra_module_interfaces::srv::GetCapabilities_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Event __attribute__((deprecated))
#else
# define DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Event __declspec(deprecated)
#endif

namespace vyra_module_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCapabilities_Event_
{
  using Type = GetCapabilities_Event_<ContainerAllocator>;

  explicit GetCapabilities_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit GetCapabilities_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::srv::GetCapabilities_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vyra_module_interfaces::srv::GetCapabilities_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Event
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vyra_module_interfaces__srv__GetCapabilities_Event
    std::shared_ptr<vyra_module_interfaces::srv::GetCapabilities_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCapabilities_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCapabilities_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCapabilities_Event_

// alias to use template instance with default allocator
using GetCapabilities_Event =
  vyra_module_interfaces::srv::GetCapabilities_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace vyra_module_interfaces
{

namespace srv
{

struct GetCapabilities
{
  using Request = vyra_module_interfaces::srv::GetCapabilities_Request;
  using Response = vyra_module_interfaces::srv::GetCapabilities_Response;
  using Event = vyra_module_interfaces::srv::GetCapabilities_Event;
};

}  // namespace srv

}  // namespace vyra_module_interfaces

#endif  // VYRA_MODULE_INTERFACES__SRV__DETAIL__GET_CAPABILITIES__STRUCT_HPP_
