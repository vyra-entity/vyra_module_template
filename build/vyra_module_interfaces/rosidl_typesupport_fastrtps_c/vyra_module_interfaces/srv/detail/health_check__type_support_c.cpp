// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vyra_module_interfaces:srv/HealthCheck.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/srv/detail/health_check__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vyra_module_interfaces/srv/detail/health_check__struct.h"
#include "vyra_module_interfaces/srv/detail/health_check__functions.h"
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


using _HealthCheck_Request__ros_msg_type = vyra_module_interfaces__srv__HealthCheck_Request;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Request(
  const vyra_module_interfaces__srv__HealthCheck_Request * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: structure_needs_at_least_one_member
  {
    cdr << ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Request(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces__srv__HealthCheck_Request * ros_message)
{
  // Field name: structure_needs_at_least_one_member
  {
    cdr >> ros_message->structure_needs_at_least_one_member;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
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

  // Field name: structure_needs_at_least_one_member
  {
    size_t item_size = sizeof(ros_message->structure_needs_at_least_one_member);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
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

  // Field name: structure_needs_at_least_one_member
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Request;
    is_plain =
      (
      offsetof(DataType, structure_needs_at_least_one_member) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Request(
  const vyra_module_interfaces__srv__HealthCheck_Request * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: structure_needs_at_least_one_member
  {
    cdr << ros_message->structure_needs_at_least_one_member;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
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

  // Field name: structure_needs_at_least_one_member
  {
    size_t item_size = sizeof(ros_message->structure_needs_at_least_one_member);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
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
  // Field name: structure_needs_at_least_one_member
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Request;
    is_plain =
      (
      offsetof(DataType, structure_needs_at_least_one_member) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _HealthCheck_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const vyra_module_interfaces__srv__HealthCheck_Request * ros_message = static_cast<const vyra_module_interfaces__srv__HealthCheck_Request *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Request(ros_message, cdr);
}

static bool _HealthCheck_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  vyra_module_interfaces__srv__HealthCheck_Request * ros_message = static_cast<vyra_module_interfaces__srv__HealthCheck_Request *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Request(cdr, ros_message);
}

static uint32_t _HealthCheck_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
      untyped_ros_message, 0));
}

static size_t _HealthCheck_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_HealthCheck_Request = {
  "vyra_module_interfaces::srv",
  "HealthCheck_Request",
  _HealthCheck_Request__cdr_serialize,
  _HealthCheck_Request__cdr_deserialize,
  _HealthCheck_Request__get_serialized_size,
  _HealthCheck_Request__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _HealthCheck_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HealthCheck_Request,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Request__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Request)() {
  return &_HealthCheck_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <cstddef>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__functions.h"
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


using _HealthCheck_Response__ros_msg_type = vyra_module_interfaces__srv__HealthCheck_Response;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Response(
  const vyra_module_interfaces__srv__HealthCheck_Response * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
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

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Response(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces__srv__HealthCheck_Response * ros_message)
{
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


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
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

  // Field name: alive
  {
    size_t item_size = sizeof(ros_message->alive);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: state
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->state.size + 1);

  // Field name: health_status
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->health_status.size + 1);

  // Field name: issues
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


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
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

  // Field name: alive
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: state
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

  // Field name: health_status
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

  // Field name: issues
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Response;
    is_plain =
      (
      offsetof(DataType, issues) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Response(
  const vyra_module_interfaces__srv__HealthCheck_Response * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
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

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
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

  // Field name: alive
  {
    size_t item_size = sizeof(ros_message->alive);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: state
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->state.size + 1);

  // Field name: health_status
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->health_status.size + 1);

  // Field name: issues
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

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
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
  // Field name: alive
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: state
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

  // Field name: health_status
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

  // Field name: issues
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Response;
    is_plain =
      (
      offsetof(DataType, issues) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _HealthCheck_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const vyra_module_interfaces__srv__HealthCheck_Response * ros_message = static_cast<const vyra_module_interfaces__srv__HealthCheck_Response *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Response(ros_message, cdr);
}

static bool _HealthCheck_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  vyra_module_interfaces__srv__HealthCheck_Response * ros_message = static_cast<vyra_module_interfaces__srv__HealthCheck_Response *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Response(cdr, ros_message);
}

static uint32_t _HealthCheck_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
      untyped_ros_message, 0));
}

static size_t _HealthCheck_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_HealthCheck_Response = {
  "vyra_module_interfaces::srv",
  "HealthCheck_Response",
  _HealthCheck_Response__cdr_serialize,
  _HealthCheck_Response__cdr_deserialize,
  _HealthCheck_Response__get_serialized_size,
  _HealthCheck_Response__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _HealthCheck_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HealthCheck_Response,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Response__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Response)() {
  return &_HealthCheck_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <cstddef>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__struct.h"
// already included above
// #include "vyra_module_interfaces/srv/detail/health_check__functions.h"
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

#include "service_msgs/msg/detail/service_event_info__functions.h"  // info

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
bool cdr_serialize_service_msgs__msg__ServiceEventInfo(
  const service_msgs__msg__ServiceEventInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
bool cdr_deserialize_service_msgs__msg__ServiceEventInfo(
  eprosima::fastcdr::Cdr & cdr,
  service_msgs__msg__ServiceEventInfo * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t get_serialized_size_service_msgs__msg__ServiceEventInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t max_serialized_size_service_msgs__msg__ServiceEventInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
bool cdr_serialize_key_service_msgs__msg__ServiceEventInfo(
  const service_msgs__msg__ServiceEventInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t get_serialized_size_key_service_msgs__msg__ServiceEventInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t max_serialized_size_key_service_msgs__msg__ServiceEventInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, service_msgs, msg, ServiceEventInfo)();

bool cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Request(
  const vyra_module_interfaces__srv__HealthCheck_Request * ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Request(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces__srv__HealthCheck_Request * ros_message);

size_t get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Request(
  const vyra_module_interfaces__srv__HealthCheck_Request * ros_message,
  eprosima::fastcdr::Cdr & cdr);

size_t get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Request)();

bool cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Response(
  const vyra_module_interfaces__srv__HealthCheck_Response * ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Response(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces__srv__HealthCheck_Response * ros_message);

size_t get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Response(
  const vyra_module_interfaces__srv__HealthCheck_Response * ros_message,
  eprosima::fastcdr::Cdr & cdr);

size_t get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Response)();


using _HealthCheck_Event__ros_msg_type = vyra_module_interfaces__srv__HealthCheck_Event;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Event(
  const vyra_module_interfaces__srv__HealthCheck_Event * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: info
  {
    cdr_serialize_service_msgs__msg__ServiceEventInfo(
      &ros_message->info, cdr);
  }

  // Field name: request
  {
    size_t size = ros_message->request.size;
    auto array_ptr = ros_message->request.data;
    if (size > 1) {
      fprintf(stderr, "array size exceeds upper bound\n");
      return false;
    }
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Request(
        &array_ptr[i], cdr);
    }
  }

  // Field name: response
  {
    size_t size = ros_message->response.size;
    auto array_ptr = ros_message->response.data;
    if (size > 1) {
      fprintf(stderr, "array size exceeds upper bound\n");
      return false;
    }
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Response(
        &array_ptr[i], cdr);
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Event(
  eprosima::fastcdr::Cdr & cdr,
  vyra_module_interfaces__srv__HealthCheck_Event * ros_message)
{
  // Field name: info
  {
    cdr_deserialize_service_msgs__msg__ServiceEventInfo(cdr, &ros_message->info);
  }

  // Field name: request
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->request.data) {
      vyra_module_interfaces__srv__HealthCheck_Request__Sequence__fini(&ros_message->request);
    }
    if (!vyra_module_interfaces__srv__HealthCheck_Request__Sequence__init(&ros_message->request, size)) {
      fprintf(stderr, "failed to create array for field 'request'");
      return false;
    }
    auto array_ptr = ros_message->request.data;
    for (size_t i = 0; i < size; ++i) {
      cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Request(cdr, &array_ptr[i]);
    }
  }

  // Field name: response
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->response.data) {
      vyra_module_interfaces__srv__HealthCheck_Response__Sequence__fini(&ros_message->response);
    }
    if (!vyra_module_interfaces__srv__HealthCheck_Response__Sequence__init(&ros_message->response, size)) {
      fprintf(stderr, "failed to create array for field 'response'");
      return false;
    }
    auto array_ptr = ros_message->response.data;
    for (size_t i = 0; i < size; ++i) {
      cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Response(cdr, &array_ptr[i]);
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Event(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _HealthCheck_Event__ros_msg_type * ros_message = static_cast<const _HealthCheck_Event__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: info
  current_alignment += get_serialized_size_service_msgs__msg__ServiceEventInfo(
    &(ros_message->info), current_alignment);

  // Field name: request
  {
    size_t array_size = ros_message->request.size;
    auto array_ptr = ros_message->request.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
        &array_ptr[index], current_alignment);
    }
  }

  // Field name: response
  {
    size_t array_size = ros_message->response.size;
    auto array_ptr = ros_message->response.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Event(
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

  // Field name: info
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_service_msgs__msg__ServiceEventInfo(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: request
  {
    size_t array_size = 1;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Request(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: response
  {
    size_t array_size = 1;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Response(
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Event;
    is_plain =
      (
      offsetof(DataType, response) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
bool cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Event(
  const vyra_module_interfaces__srv__HealthCheck_Event * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: info
  {
    cdr_serialize_key_service_msgs__msg__ServiceEventInfo(
      &ros_message->info, cdr);
  }

  // Field name: request
  {
    size_t size = ros_message->request.size;
    auto array_ptr = ros_message->request.data;
    if (size > 1) {
      fprintf(stderr, "array size exceeds upper bound\n");
      return false;
    }
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Request(
        &array_ptr[i], cdr);
    }
  }

  // Field name: response
  {
    size_t size = ros_message->response.size;
    auto array_ptr = ros_message->response.data;
    if (size > 1) {
      fprintf(stderr, "array size exceeds upper bound\n");
      return false;
    }
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      cdr_serialize_key_vyra_module_interfaces__srv__HealthCheck_Response(
        &array_ptr[i], cdr);
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Event(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _HealthCheck_Event__ros_msg_type * ros_message = static_cast<const _HealthCheck_Event__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: info
  current_alignment += get_serialized_size_key_service_msgs__msg__ServiceEventInfo(
    &(ros_message->info), current_alignment);

  // Field name: request
  {
    size_t array_size = ros_message->request.size;
    auto array_ptr = ros_message->request.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
        &array_ptr[index], current_alignment);
    }
  }

  // Field name: response
  {
    size_t array_size = ros_message->response.size;
    auto array_ptr = ros_message->response.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
        &array_ptr[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Event(
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
  // Field name: info
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_service_msgs__msg__ServiceEventInfo(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: request
  {
    size_t array_size = 1;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Request(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Field name: response
  {
    size_t array_size = 1;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_vyra_module_interfaces__srv__HealthCheck_Response(
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
    using DataType = vyra_module_interfaces__srv__HealthCheck_Event;
    is_plain =
      (
      offsetof(DataType, response) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _HealthCheck_Event__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const vyra_module_interfaces__srv__HealthCheck_Event * ros_message = static_cast<const vyra_module_interfaces__srv__HealthCheck_Event *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_vyra_module_interfaces__srv__HealthCheck_Event(ros_message, cdr);
}

static bool _HealthCheck_Event__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  vyra_module_interfaces__srv__HealthCheck_Event * ros_message = static_cast<vyra_module_interfaces__srv__HealthCheck_Event *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_vyra_module_interfaces__srv__HealthCheck_Event(cdr, ros_message);
}

static uint32_t _HealthCheck_Event__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__srv__HealthCheck_Event(
      untyped_ros_message, 0));
}

static size_t _HealthCheck_Event__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__srv__HealthCheck_Event(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_HealthCheck_Event = {
  "vyra_module_interfaces::srv",
  "HealthCheck_Event",
  _HealthCheck_Event__cdr_serialize,
  _HealthCheck_Event__cdr_deserialize,
  _HealthCheck_Event__get_serialized_size,
  _HealthCheck_Event__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _HealthCheck_Event__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HealthCheck_Event,
  get_message_typesupport_handle_function,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck_Event__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Event)() {
  return &_HealthCheck_Event__type_support;
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
#include "vyra_module_interfaces/srv/health_check.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t HealthCheck__callbacks = {
  "vyra_module_interfaces::srv",
  "HealthCheck",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck_Response)(),
};

static rosidl_service_type_support_t HealthCheck__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &HealthCheck__callbacks,
  get_service_typesupport_handle_function,
  &_HealthCheck_Request__type_support,
  &_HealthCheck_Response__type_support,
  &_HealthCheck_Event__type_support,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    HealthCheck
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    vyra_module_interfaces,
    srv,
    HealthCheck
  ),
  &vyra_module_interfaces__srv__HealthCheck__get_type_hash,
  &vyra_module_interfaces__srv__HealthCheck__get_type_description,
  &vyra_module_interfaces__srv__HealthCheck__get_type_description_sources,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, srv, HealthCheck)() {
  return &HealthCheck__handle;
}

#if defined(__cplusplus)
}
#endif
