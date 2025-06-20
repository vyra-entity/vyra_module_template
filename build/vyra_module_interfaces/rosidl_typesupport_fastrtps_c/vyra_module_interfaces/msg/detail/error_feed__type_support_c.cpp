// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from vyra_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/msg/detail/error_feed__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "vyra_module_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "vyra_module_interfaces/msg/detail/error_feed__struct.h"
#include "vyra_module_interfaces/msg/detail/error_feed__functions.h"
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

#include "builtin_interfaces/msg/detail/time__functions.h"  // timestamp
#include "rosidl_runtime_c/string.h"  // description, miscellaneous, module_id, solution
#include "rosidl_runtime_c/string_functions.h"  // description, miscellaneous, module_id, solution

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t get_serialized_size_builtin_interfaces__msg__Time(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
size_t max_serialized_size_builtin_interfaces__msg__Time(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_vyra_module_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time)();


using _ErrorFeed__ros_msg_type = vyra_module_interfaces__msg__ErrorFeed;

static bool _ErrorFeed__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ErrorFeed__ros_msg_type * ros_message = static_cast<const _ErrorFeed__ros_msg_type *>(untyped_ros_message);
  // Field name: error_code
  {
    cdr << ros_message->error_code;
  }

  // Field name: module_id
  {
    const rosidl_runtime_c__String * str = &ros_message->module_id;
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

  // Field name: description
  {
    const rosidl_runtime_c__String * str = &ros_message->description;
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

  // Field name: solution
  {
    const rosidl_runtime_c__String * str = &ros_message->solution;
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

  // Field name: miscellaneous
  {
    const rosidl_runtime_c__String * str = &ros_message->miscellaneous;
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

  // Field name: timestamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->timestamp, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _ErrorFeed__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ErrorFeed__ros_msg_type * ros_message = static_cast<_ErrorFeed__ros_msg_type *>(untyped_ros_message);
  // Field name: error_code
  {
    cdr >> ros_message->error_code;
  }

  // Field name: module_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->module_id.data) {
      rosidl_runtime_c__String__init(&ros_message->module_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->module_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'module_id'\n");
      return false;
    }
  }

  // Field name: description
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->description.data) {
      rosidl_runtime_c__String__init(&ros_message->description);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->description,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'description'\n");
      return false;
    }
  }

  // Field name: solution
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->solution.data) {
      rosidl_runtime_c__String__init(&ros_message->solution);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->solution,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'solution'\n");
      return false;
    }
  }

  // Field name: miscellaneous
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->miscellaneous.data) {
      rosidl_runtime_c__String__init(&ros_message->miscellaneous);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->miscellaneous,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'miscellaneous'\n");
      return false;
    }
  }

  // Field name: timestamp
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, builtin_interfaces, msg, Time
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->timestamp))
    {
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t get_serialized_size_vyra_module_interfaces__msg__ErrorFeed(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ErrorFeed__ros_msg_type * ros_message = static_cast<const _ErrorFeed__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name error_code
  {
    size_t item_size = sizeof(ros_message->error_code);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name module_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->module_id.size + 1);
  // field.name description
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->description.size + 1);
  // field.name solution
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->solution.size + 1);
  // field.name miscellaneous
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->miscellaneous.size + 1);
  // field.name timestamp

  current_alignment += get_serialized_size_builtin_interfaces__msg__Time(
    &(ros_message->timestamp), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _ErrorFeed__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_vyra_module_interfaces__msg__ErrorFeed(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_vyra_module_interfaces
size_t max_serialized_size_vyra_module_interfaces__msg__ErrorFeed(
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

  // member: error_code
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: module_id
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
  // member: description
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
  // member: solution
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
  // member: miscellaneous
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
  // member: timestamp
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_builtin_interfaces__msg__Time(
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
    using DataType = vyra_module_interfaces__msg__ErrorFeed;
    is_plain =
      (
      offsetof(DataType, timestamp) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ErrorFeed__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_vyra_module_interfaces__msg__ErrorFeed(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ErrorFeed = {
  "vyra_module_interfaces::msg",
  "ErrorFeed",
  _ErrorFeed__cdr_serialize,
  _ErrorFeed__cdr_deserialize,
  _ErrorFeed__get_serialized_size,
  _ErrorFeed__max_serialized_size
};

static rosidl_message_type_support_t _ErrorFeed__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ErrorFeed,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, vyra_module_interfaces, msg, ErrorFeed)() {
  return &_ErrorFeed__type_support;
}

#if defined(__cplusplus)
}
#endif
