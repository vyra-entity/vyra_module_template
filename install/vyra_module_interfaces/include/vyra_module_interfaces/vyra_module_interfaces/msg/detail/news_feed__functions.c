// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vyra_module_interfaces:msg/NewsFeed.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/msg/detail/news_feed__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `type`
// Member `message`
// Member `module_id`
// Member `module_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
vyra_module_interfaces__msg__NewsFeed__init(vyra_module_interfaces__msg__NewsFeed * msg)
{
  if (!msg) {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__init(&msg->type)) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
    return false;
  }
  // module_id
  if (!rosidl_runtime_c__String__init(&msg->module_id)) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__init(&msg->module_name)) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__msg__NewsFeed__fini(vyra_module_interfaces__msg__NewsFeed * msg)
{
  if (!msg) {
    return;
  }
  // type
  rosidl_runtime_c__String__fini(&msg->type);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
  // module_id
  rosidl_runtime_c__String__fini(&msg->module_id);
  // module_name
  rosidl_runtime_c__String__fini(&msg->module_name);
}

bool
vyra_module_interfaces__msg__NewsFeed__are_equal(const vyra_module_interfaces__msg__NewsFeed * lhs, const vyra_module_interfaces__msg__NewsFeed * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type), &(rhs->type)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->timestamp), &(rhs->timestamp)))
  {
    return false;
  }
  // module_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->module_id), &(rhs->module_id)))
  {
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->module_name), &(rhs->module_name)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__msg__NewsFeed__copy(
  const vyra_module_interfaces__msg__NewsFeed * input,
  vyra_module_interfaces__msg__NewsFeed * output)
{
  if (!input || !output) {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__copy(
      &(input->type), &(output->type)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->timestamp), &(output->timestamp)))
  {
    return false;
  }
  // module_id
  if (!rosidl_runtime_c__String__copy(
      &(input->module_id), &(output->module_id)))
  {
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__copy(
      &(input->module_name), &(output->module_name)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__msg__NewsFeed *
vyra_module_interfaces__msg__NewsFeed__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__NewsFeed * msg = (vyra_module_interfaces__msg__NewsFeed *)allocator.allocate(sizeof(vyra_module_interfaces__msg__NewsFeed), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__msg__NewsFeed));
  bool success = vyra_module_interfaces__msg__NewsFeed__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__msg__NewsFeed__destroy(vyra_module_interfaces__msg__NewsFeed * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__msg__NewsFeed__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__msg__NewsFeed__Sequence__init(vyra_module_interfaces__msg__NewsFeed__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__NewsFeed * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__msg__NewsFeed *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__msg__NewsFeed), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__msg__NewsFeed__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__msg__NewsFeed__fini(&data[i - 1]);
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
vyra_module_interfaces__msg__NewsFeed__Sequence__fini(vyra_module_interfaces__msg__NewsFeed__Sequence * array)
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
      vyra_module_interfaces__msg__NewsFeed__fini(&array->data[i]);
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

vyra_module_interfaces__msg__NewsFeed__Sequence *
vyra_module_interfaces__msg__NewsFeed__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__msg__NewsFeed__Sequence * array = (vyra_module_interfaces__msg__NewsFeed__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__msg__NewsFeed__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__msg__NewsFeed__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__msg__NewsFeed__Sequence__destroy(vyra_module_interfaces__msg__NewsFeed__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__msg__NewsFeed__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__msg__NewsFeed__Sequence__are_equal(const vyra_module_interfaces__msg__NewsFeed__Sequence * lhs, const vyra_module_interfaces__msg__NewsFeed__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__msg__NewsFeed__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__msg__NewsFeed__Sequence__copy(
  const vyra_module_interfaces__msg__NewsFeed__Sequence * input,
  vyra_module_interfaces__msg__NewsFeed__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__msg__NewsFeed);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__msg__NewsFeed * data =
      (vyra_module_interfaces__msg__NewsFeed *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__msg__NewsFeed__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__msg__NewsFeed__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__msg__NewsFeed__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
