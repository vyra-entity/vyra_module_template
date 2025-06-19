// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vos_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice
#include "vos_module_interfaces/srv/detail/health_check__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vos_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vos_module_interfaces/srv/detail/health_check__struct.h"
#include "vos_module_interfaces/srv/detail/health_check__functions.h"
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


using _HealthCheck_Request__ros_msg_type = vos_module_interfaces__srv__HealthCheck_Request;

static bool _HealthCheck_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _HealthCheck_Request__ros_msg_type * ros_message = static_cast<const _HealthCheck_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr << ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

static bool _HealthCheck_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _HealthCheck_Request__ros_msg_type * ros_message = static_cast<_HealthCheck_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: structure_needs_at_least_one_member
  {
    cdr >> ros_message->structure_needs_at_least_one_member;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vos_module_interfaces
size_t get_serialized_size_vos_module_interfaces__srv__HealthCheck_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _HealthCheck_Request__ros_msg_type * ros_message = static_cast<const _HealthCheck_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name structure_needs_at_least_one_member
  {
    size_t item_size = sizeof(ros_message->structure_needs_at_least_one_member);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _HealthCheck_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vos_module_interfaces__srv__HealthCheck_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vos_module_interfaces
size_t max_serialized_size_vos_module_interfaces__srv__HealthCheck_Request(
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

  // member: structure_needs_at_least_one_member
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
    using DataType = vos_module_interfaces__srv__HealthCheck_Request;
    is_plain =
      (
      offsetof(DataType, structure_needs_at_least_one_member) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _HealthCheck_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vos_module_interfaces__srv__HealthCheck_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_HealthCheck_Request = {
  "vos_module_interfaces::srv",
  "HealthCheck_Request",
  _HealthCheck_Request__cdr_serialize,
  _HealthCheck_Request__cdr_deserialize,
  _HealthCheck_Request__get_serialized_size,
  _HealthCheck_Request__max_serialized_size
};

static rosidl_message_type_support_t _HealthCheck_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HealthCheck_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, HealthCheck_Request)() {
  return &_HealthCheck_Request__type_support;
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
// #include "vos_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vos_module_interfaces/srv/detail/health_check__struct.h"
// already included above
// #include "vos_module_interfaces/srv/detail/health_check__functions.h"
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

#include "rosidl_runtime_c/string.h"  // health_status, issues, state
#include "rosidl_runtime_c/string_functions.h"  // health_status, issues, state

// forward declare type support functions


using _HealthCheck_Response__ros_msg_type = vos_module_interfaces__srv__HealthCheck_Response;

static bool _HealthCheck_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _HealthCheck_Response__ros_msg_type * ros_message = static_cast<const _HealthCheck_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: alive
  {
    cdr << (ros_message->alive ? true : false);
  }

  // Field name: state
  {
    const rosidl_runtime_c__String * str = &ros_message->state;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: health_status
  {
    const rosidl_runtime_c__String * str = &ros_message->health_status;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: issues
  {
    size_t size = ros_message->issues.size;
    auto array_ptr = ros_message->issues.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  return true;
}

static bool _HealthCheck_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _HealthCheck_Response__ros_msg_type * ros_message = static_cast<_HealthCheck_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: alive
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->alive = tmp ? true : false;
  }

  // Field name: state
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->state.data) {
      rosidl_runtime_c__String__init(&ros_message->state);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->state,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'state'\n");
      return false;
    }
  }

  // Field name: health_status
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->health_status.data) {
      rosidl_runtime_c__String__init(&ros_message->health_status);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->health_status,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'health_status'\n");
      return false;
    }
  }

  // Field name: issues
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->issues.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->issues);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->issues, size)) {
      fprintf(stderr, "failed to create array for field 'issues'");
      return false;
    }
    auto array_ptr = ros_message->issues.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'issues'\n");
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vos_module_interfaces
size_t get_serialized_size_vos_module_interfaces__srv__HealthCheck_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _HealthCheck_Response__ros_msg_type * ros_message = static_cast<const _HealthCheck_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name alive
  {
    size_t item_size = sizeof(ros_message->alive);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name state
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->state.size + 1);
  // field.name health_status
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->health_status.size + 1);
  // field.name issues
  {
    size_t array_size = ros_message->issues.size;
    auto array_ptr = ros_message->issues.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _HealthCheck_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vos_module_interfaces__srv__HealthCheck_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vos_module_interfaces
size_t max_serialized_size_vos_module_interfaces__srv__HealthCheck_Response(
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

  // member: alive
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: state
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: health_status
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: issues
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vos_module_interfaces__srv__HealthCheck_Response;
    is_plain =
      (
      offsetof(DataType, issues) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _HealthCheck_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vos_module_interfaces__srv__HealthCheck_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_HealthCheck_Response = {
  "vos_module_interfaces::srv",
  "HealthCheck_Response",
  _HealthCheck_Response__cdr_serialize,
  _HealthCheck_Response__cdr_deserialize,
  _HealthCheck_Response__get_serialized_size,
  _HealthCheck_Response__max_serialized_size
};

static rosidl_message_type_support_t _HealthCheck_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HealthCheck_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, HealthCheck_Response)() {
  return &_HealthCheck_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "vos_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vos_module_interfaces/srv/health_check.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t HealthCheck__callbacks = {
  "vos_module_interfaces::srv",
  "HealthCheck",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, HealthCheck_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, HealthCheck_Response)(),
};

static rosidl_service_type_support_t HealthCheck__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &HealthCheck__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vos_module_interfaces, srv, HealthCheck)() {
  return &HealthCheck__handle;
}

#if defined(__cplusplus)
}
#endif
