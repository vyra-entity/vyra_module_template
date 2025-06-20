// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vyra_module_interfaces:msg/LoggerStream.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/msg/detail/logger_stream__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `log_level`
// Member `log_message`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
vyra_module_interfaces__msg__LoggerStream__init(vyra_module_interfaces__msg__LoggerStream * msg)
{
  if (!msg) {
    return false;
  }
  // log_level
  if (!rosidl_runtime_c__String__init(&msg->log_level)) {
    vyra_module_interfaces__msg__LoggerStream__fini(msg);
    return false;
  }
  // log_message
  if (!rosidl_runtime_c__String__init(&msg->log_message)) {
    vyra_module_interfaces__msg__LoggerStream__fini(msg);
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    vyra_module_interfaces__msg__LoggerStream__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__msg__LoggerStream__fini(vyra_module_interfaces__msg__LoggerStream * msg)
{
  if (!msg) {
    return;
  }
  // log_level
  rosidl_runtime_c__String__fini(&msg->log_level);
  // log_message
  rosidl_runtime_c__String__fini(&msg->log_message);
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
}

bool
vyra_module_interfaces__msg__LoggerStream__are_equal(const vyra_module_interfaces__msg__LoggerStream * lhs, const vyra_module_interfaces__msg__LoggerStream * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // log_level
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->log_level), &(rhs->log_level)))
  {
    return false;
  }
  // log_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->log_message), &(rhs->log_message)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->timestamp), &(rhs->timestamp)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__msg__LoggerStream__copy(
  const vyra_module_interfaces__msg__LoggerStream * input,
  vyra_module_interfaces__msg__LoggerStream * output)
{
  if (!input || !output) {
    return false;
  }
  // log_level
  if (!rosidl_runtime_c__String__copy(
      &(input->log_level), &(output->log_level)))
  {
    return false;
  }
  // log_message
  if (!rosidl_runtime_c__String__copy(
      &(input->log_message), &(output->log_message)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->timestamp), &(output->timestamp)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__msg__LoggerStream *
vyra_module_interfaces__msg__LoggerStream__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__LoggerStream * msg = (vyra_module_interfaces__msg__LoggerStream *)allocator.allocate(sizeof(vyra_module_interfaces__msg__LoggerStream), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__msg__LoggerStream));
  bool success = vyra_module_interfaces__msg__LoggerStream__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__msg__LoggerStream__destroy(vyra_module_interfaces__msg__LoggerStream * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__msg__LoggerStream__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__msg__LoggerStream__Sequence__init(vyra_module_interfaces__msg__LoggerStream__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__LoggerStream * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__msg__LoggerStream *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__msg__LoggerStream), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__msg__LoggerStream__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__msg__LoggerStream__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vyra_module_interfaces__msg__LoggerStream__Sequence__fini(vyra_module_interfaces__msg__LoggerStream__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vyra_module_interfaces__msg__LoggerStream__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vyra_module_interfaces__msg__LoggerStream__Sequence *
vyra_module_interfaces__msg__LoggerStream__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__LoggerStream__Sequence * array = (vyra_module_interfaces__msg__LoggerStream__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__msg__LoggerStream__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__msg__LoggerStream__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__msg__LoggerStream__Sequence__destroy(vyra_module_interfaces__msg__LoggerStream__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__msg__LoggerStream__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__msg__LoggerStream__Sequence__are_equal(const vyra_module_interfaces__msg__LoggerStream__Sequence * lhs, const vyra_module_interfaces__msg__LoggerStream__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__msg__LoggerStream__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__msg__LoggerStream__Sequence__copy(
  const vyra_module_interfaces__msg__LoggerStream__Sequence * input,
  vyra_module_interfaces__msg__LoggerStream__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__msg__LoggerStream);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__msg__LoggerStream * data =
      (vyra_module_interfaces__msg__LoggerStream *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__msg__LoggerStream__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__msg__LoggerStream__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__msg__LoggerStream__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
