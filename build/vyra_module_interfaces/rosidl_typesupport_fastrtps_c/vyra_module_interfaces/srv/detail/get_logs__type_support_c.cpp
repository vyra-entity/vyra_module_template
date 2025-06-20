// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vyra_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/srv/detail/get_logs__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vyra_module_interfaces/srv/detail/get_logs__struct.h"
#include "vyra_module_interfaces/srv/detail/get_logs__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _GetLogs_Request__ros_msg_type = vyra_module_interfaces__srv__GetLogs_Request;

static bool _GetLogs_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetLogs_Request__ros_msg_type * ros_message = static_cast<const _GetLogs_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: log_lines
  {
    cdr << ros_message->log_lines;
  }

  // Field name: log_level
  {
    cdr << ros_message->log_level;
  }

  return true;
}

static bool _GetLogs_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetLogs_Request__ros_msg_type * ros_message = static_cast<_GetLogs_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: log_lines
  {
    cdr >> ros_message->log_lines;
  }

  // Field name: log_level
  {
    cdr >> ros_message->log_level;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__srv__GetLogs_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetLogs_Request__ros_msg_type * ros_message = static_cast<const _GetLogs_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name log_lines
  {
    size_t item_size = sizeof(ros_message->log_lines);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name log_level
  {
    size_t item_size = sizeof(ros_message->log_level);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GetLogs_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__srv__GetLogs_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__srv__GetLogs_Request(
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

  // member: log_lines
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: log_level
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
    using DataType = vyra_module_interfaces__srv__GetLogs_Request;
    is_plain =
      (
      offsetof(DataType, log_level) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetLogs_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__srv__GetLogs_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetLogs_Request = {
  "vyra_module_interfaces::srv",
  "GetLogs_Request",
  _GetLogs_Request__cdr_serialize,
  _GetLogs_Request__cdr_deserialize,
  _GetLogs_Request__get_serialized_size,
  _GetLogs_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetLogs_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetLogs_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, GetLogs_Request)() {
  return &_GetLogs_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/get_logs__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "vyra_module_interfaces/msg/detail/logger_stream__functions.h"  // log_messages

// forward declare type support functions
size_t get_serialized_size_vyra_module_interfaces__msg__LoggerStream(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vyra_module_interfaces__msg__LoggerStream(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, msg, LoggerStream)();


using _GetLogs_Response__ros_msg_type = vyra_module_interfaces__srv__GetLogs_Response;

static bool _GetLogs_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetLogs_Response__ros_msg_type * ros_message = static_cast<const _GetLogs_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: log_messages
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vyra_module_interfaces, msg, LoggerStream
      )()->data);
    size_t size = ros_message->log_messages.size;
    auto array_ptr = ros_message->log_messages.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  return true;
}

static bool _GetLogs_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetLogs_Response__ros_msg_type * ros_message = static_cast<_GetLogs_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: log_messages
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, vyra_module_interfaces, msg, LoggerStream
      )()->data);
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->log_messages.data) {
      vyra_module_interfaces__msg__LoggerStream__Sequence__fini(&ros_message->log_messages);
    }
    if (!vyra_module_interfaces__msg__LoggerStream__Sequence__init(&ros_message->log_messages, size)) {
      fprintf(stderr, "failed to create array for field 'log_messages'");
      return false;
    }
    auto array_ptr = ros_message->log_messages.data;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__srv__GetLogs_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetLogs_Response__ros_msg_type * ros_message = static_cast<const _GetLogs_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name log_messages
  {
    size_t array_size = ros_message->log_messages.size;
    auto array_ptr = ros_message->log_messages.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vyra_module_interfaces__msg__LoggerStream(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GetLogs_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__srv__GetLogs_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__srv__GetLogs_Response(
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

  // member: log_messages
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
      size_t inner_size;
      inner_size =
        max_serialized_size_vyra_module_interfaces__msg__LoggerStream(
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
    using DataType = vyra_module_interfaces__srv__GetLogs_Response;
    is_plain =
      (
      offsetof(DataType, log_messages) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetLogs_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__srv__GetLogs_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetLogs_Response = {
  "vyra_module_interfaces::srv",
  "GetLogs_Response",
  _GetLogs_Response__cdr_serialize,
  _GetLogs_Response__cdr_deserialize,
  _GetLogs_Response__get_serialized_size,
  _GetLogs_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetLogs_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetLogs_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, GetLogs_Response)() {
  return &_GetLogs_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vyra_module_interfaces/srv/get_logs.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetLogs__callbacks = {
  "vyra_module_interfaces::srv",
  "GetLogs",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, GetLogs_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, GetLogs_Response)(),
};

static rosidl_service_type_support_t GetLogs__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetLogs__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, GetLogs)() {
  return &GetLogs__handle;
}

#if defined(__cplusplus)
}
#endif
