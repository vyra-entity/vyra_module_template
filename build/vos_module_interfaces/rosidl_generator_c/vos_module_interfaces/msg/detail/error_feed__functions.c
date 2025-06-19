// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vos_module_interfaces:msg/ErrorFeed.idl
// generated code does not contain a copyright notice
#include "vos_module_interfaces/msg/detail/error_feed__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `module_id`
// Member `description`
// Member `solution`
// Member `miscellaneous`
#include "rosidl_runtime_c/string_functions.h"
// Member `timestamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
vos_module_interfaces__msg__ErrorFeed__init(vos_module_interfaces__msg__ErrorFeed * msg)
{
  if (!msg) {
    return false;
  }
  // error_code
  // module_id
  if (!rosidl_runtime_c__String__init(&msg->module_id)) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
    return false;
  }
  // description
  if (!rosidl_runtime_c__String__init(&msg->description)) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
    return false;
  }
  // solution
  if (!rosidl_runtime_c__String__init(&msg->solution)) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
    return false;
  }
  // miscellaneous
  if (!rosidl_runtime_c__String__init(&msg->miscellaneous)) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
    return false;
  }
  // timestamp
  if (!builtin_interfaces__msg__Time__init(&msg->timestamp)) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
    return false;
  }
  return true;
}

void
vos_module_interfaces__msg__ErrorFeed__fini(vos_module_interfaces__msg__ErrorFeed * msg)
{
  if (!msg) {
    return;
  }
  // error_code
  // module_id
  rosidl_runtime_c__String__fini(&msg->module_id);
  // description
  rosidl_runtime_c__String__fini(&msg->description);
  // solution
  rosidl_runtime_c__String__fini(&msg->solution);
  // miscellaneous
  rosidl_runtime_c__String__fini(&msg->miscellaneous);
  // timestamp
  builtin_interfaces__msg__Time__fini(&msg->timestamp);
}

bool
vos_module_interfaces__msg__ErrorFeed__are_equal(const vos_module_interfaces__msg__ErrorFeed * lhs, const vos_module_interfaces__msg__ErrorFeed * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // module_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->module_id), &(rhs->module_id)))
  {
    return false;
  }
  // description
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->description), &(rhs->description)))
  {
    return false;
  }
  // solution
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->solution), &(rhs->solution)))
  {
    return false;
  }
  // miscellaneous
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->miscellaneous), &(rhs->miscellaneous)))
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
vos_module_interfaces__msg__ErrorFeed__copy(
  const vos_module_interfaces__msg__ErrorFeed * input,
  vos_module_interfaces__msg__ErrorFeed * output)
{
  if (!input || !output) {
    return false;
  }
  // error_code
  output->error_code = input->error_code;
  // module_id
  if (!rosidl_runtime_c__String__copy(
      &(input->module_id), &(output->module_id)))
  {
    return false;
  }
  // description
  if (!rosidl_runtime_c__String__copy(
      &(input->description), &(output->description)))
  {
    return false;
  }
  // solution
  if (!rosidl_runtime_c__String__copy(
      &(input->solution), &(output->solution)))
  {
    return false;
  }
  // miscellaneous
  if (!rosidl_runtime_c__String__copy(
      &(input->miscellaneous), &(output->miscellaneous)))
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

vos_module_interfaces__msg__ErrorFeed *
vos_module_interfaces__msg__ErrorFeed__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__msg__ErrorFeed * msg = (vos_module_interfaces__msg__ErrorFeed *)allocator.allocate(sizeof(vos_module_interfaces__msg__ErrorFeed), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vos_module_interfaces__msg__ErrorFeed));
  bool success = vos_module_interfaces__msg__ErrorFeed__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vos_module_interfaces__msg__ErrorFeed__destroy(vos_module_interfaces__msg__ErrorFeed * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vos_module_interfaces__msg__ErrorFeed__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vos_module_interfaces__msg__ErrorFeed__Sequence__init(vos_module_interfaces__msg__ErrorFeed__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__msg__ErrorFeed * data = NULL;

  if (size) {
    data = (vos_module_interfaces__msg__ErrorFeed *)allocator.zero_allocate(size, sizeof(vos_module_interfaces__msg__ErrorFeed), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vos_module_interfaces__msg__ErrorFeed__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vos_module_interfaces__msg__ErrorFeed__fini(&data[i - 1]);
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
vos_module_interfaces__msg__ErrorFeed__Sequence__fini(vos_module_interfaces__msg__ErrorFeed__Sequence * array)
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
      vos_module_interfaces__msg__ErrorFeed__fini(&array->data[i]);
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

vos_module_interfaces__msg__ErrorFeed__Sequence *
vos_module_interfaces__msg__ErrorFeed__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__msg__ErrorFeed__Sequence * array = (vos_module_interfaces__msg__ErrorFeed__Sequence *)allocator.allocate(sizeof(vos_module_interfaces__msg__ErrorFeed__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vos_module_interfaces__msg__ErrorFeed__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vos_module_interfaces__msg__ErrorFeed__Sequence__destroy(vos_module_interfaces__msg__ErrorFeed__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vos_module_interfaces__msg__ErrorFeed__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vos_module_interfaces__msg__ErrorFeed__Sequence__are_equal(const vos_module_interfaces__msg__ErrorFeed__Sequence * lhs, const vos_module_interfaces__msg__ErrorFeed__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vos_module_interfaces__msg__ErrorFeed__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vos_module_interfaces__msg__ErrorFeed__Sequence__copy(
  const vos_module_interfaces__msg__ErrorFeed__Sequence * input,
  vos_module_interfaces__msg__ErrorFeed__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vos_module_interfaces__msg__ErrorFeed);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vos_module_interfaces__msg__ErrorFeed * data =
      (vos_module_interfaces__msg__ErrorFeed *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vos_module_interfaces__msg__ErrorFeed__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vos_module_interfaces__msg__ErrorFeed__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vos_module_interfaces__msg__ErrorFeed__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
