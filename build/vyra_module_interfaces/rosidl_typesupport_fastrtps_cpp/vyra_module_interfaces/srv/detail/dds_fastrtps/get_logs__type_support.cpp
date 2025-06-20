// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/srv/detail/get_logs__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vyra_module_interfaces/srv/detail/get_logs__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace vyra_module_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_serialize(
  const vyra_module_interfaces::srv::GetLogs_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: log_lines
  cdr << ros_message.log_lines;
  // Member: log_level
  cdr << ros_message.log_level;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces::srv::GetLogs_Request & ros_message)
{
  // Member: log_lines
  cdr >> ros_message.log_lines;

  // Member: log_level
  cdr >> ros_message.log_level;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
get_serialized_size(
  const vyra_module_interfaces::srv::GetLogs_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: log_lines
  {
    size_t item_size = sizeof(ros_message.log_lines);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: log_level
  {
    size_t item_size = sizeof(ros_message.log_level);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
max_serialized_size_GetLogs_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: log_lines
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: log_level
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vyra_module_interfaces::srv::GetLogs_Request;
    is_plain =
      (
      offsetof(DataType, log_level) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _GetLogs_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vyra_module_interfaces::srv::GetLogs_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _GetLogs_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vyra_module_interfaces::srv::GetLogs_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _GetLogs_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vyra_module_interfaces::srv::GetLogs_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _GetLogs_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_GetLogs_Request(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _GetLogs_Request__callbacks = {
  "vyra_module_interfaces::srv",
  "GetLogs_Request",
  _GetLogs_Request__cdr_serialize,
  _GetLogs_Request__cdr_deserialize,
  _GetLogs_Request__get_serialized_size,
  _GetLogs_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetLogs_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GetLogs_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<vyra_module_interfaces::srv::GetLogs_Request>()
{
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, GetLogs_Request)() {
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace vyra_module_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const vyra_module_interfaces::msg::LoggerStream &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  vyra_module_interfaces::msg::LoggerStream &);
size_t get_serialized_size(
  const vyra_module_interfaces::msg::LoggerStream &,
  size_t current_alignment);
size_t
max_serialized_size_LoggerStream(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace vyra_module_interfaces


namespace vyra_module_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_serialize(
  const vyra_module_interfaces::srv::GetLogs_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: log_messages
  {
    size_t size = ros_message.log_messages.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      vyra_module_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.log_messages[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces::srv::GetLogs_Response & ros_message)
{
  // Member: log_messages
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.log_messages.resize(size);
    for (size_t i = 0; i < size; i++) {
      vyra_module_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.log_messages[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
get_serialized_size(
  const vyra_module_interfaces::srv::GetLogs_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: log_messages
  {
    size_t array_size = ros_message.log_messages.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        vyra_module_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.log_messages[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vyra_module_interfaces
max_serialized_size_GetLogs_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: log_messages
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        vyra_module_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_LoggerStream(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vyra_module_interfaces::srv::GetLogs_Response;
    is_plain =
      (
      offsetof(DataType, log_messages) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _GetLogs_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vyra_module_interfaces::srv::GetLogs_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _GetLogs_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vyra_module_interfaces::srv::GetLogs_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _GetLogs_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vyra_module_interfaces::srv::GetLogs_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _GetLogs_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_GetLogs_Response(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _GetLogs_Response__callbacks = {
  "vyra_module_interfaces::srv",
  "GetLogs_Response",
  _GetLogs_Response__cdr_serialize,
  _GetLogs_Response__cdr_deserialize,
  _GetLogs_Response__get_serialized_size,
  _GetLogs_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetLogs_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GetLogs_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<vyra_module_interfaces::srv::GetLogs_Response>()
{
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, GetLogs_Response)() {
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace vyra_module_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _GetLogs__callbacks = {
  "vyra_module_interfaces::srv",
  "GetLogs",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, GetLogs_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, GetLogs_Response)(),
};

static rosidl_service_type_support_t _GetLogs__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_GetLogs__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace vyra_module_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vyra_module_interfaces
const rosidl_service_type_support_t *
get_service_type_support_handle<vyra_module_interfaces::srv::GetLogs>()
{
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vyra_module_interfaces, srv, GetLogs)() {
  return &vyra_module_interfaces::srv::typesupport_fastrtps_cpp::_GetLogs__handle;
}

#ifdef __cplusplus
}
#endif
