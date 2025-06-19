// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vos_module_interfaces:srv/GetCapabilities.idl
// generated code does not contain a copyright notice
#include "vos_module_interfaces/srv/detail/get_capabilities__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
vos_module_interfaces__srv__GetCapabilities_Request__init(vos_module_interfaces__srv__GetCapabilities_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
vos_module_interfaces__srv__GetCapabilities_Request__fini(vos_module_interfaces__srv__GetCapabilities_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
vos_module_interfaces__srv__GetCapabilities_Request__are_equal(const vos_module_interfaces__srv__GetCapabilities_Request * lhs, const vos_module_interfaces__srv__GetCapabilities_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
vos_module_interfaces__srv__GetCapabilities_Request__copy(
  const vos_module_interfaces__srv__GetCapabilities_Request * input,
  vos_module_interfaces__srv__GetCapabilities_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

vos_module_interfaces__srv__GetCapabilities_Request *
vos_module_interfaces__srv__GetCapabilities_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Request * msg = (vos_module_interfaces__srv__GetCapabilities_Request *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetCapabilities_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vos_module_interfaces__srv__GetCapabilities_Request));
  bool success = vos_module_interfaces__srv__GetCapabilities_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vos_module_interfaces__srv__GetCapabilities_Request__destroy(vos_module_interfaces__srv__GetCapabilities_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vos_module_interfaces__srv__GetCapabilities_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__init(vos_module_interfaces__srv__GetCapabilities_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Request * data = NULL;

  if (size) {
    data = (vos_module_interfaces__srv__GetCapabilities_Request *)allocator.zero_allocate(size, sizeof(vos_module_interfaces__srv__GetCapabilities_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vos_module_interfaces__srv__GetCapabilities_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vos_module_interfaces__srv__GetCapabilities_Request__fini(&data[i - 1]);
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
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__fini(vos_module_interfaces__srv__GetCapabilities_Request__Sequence * array)
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
      vos_module_interfaces__srv__GetCapabilities_Request__fini(&array->data[i]);
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

vos_module_interfaces__srv__GetCapabilities_Request__Sequence *
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Request__Sequence * array = (vos_module_interfaces__srv__GetCapabilities_Request__Sequence *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetCapabilities_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vos_module_interfaces__srv__GetCapabilities_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__destroy(vos_module_interfaces__srv__GetCapabilities_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vos_module_interfaces__srv__GetCapabilities_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__are_equal(const vos_module_interfaces__srv__GetCapabilities_Request__Sequence * lhs, const vos_module_interfaces__srv__GetCapabilities_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vos_module_interfaces__srv__GetCapabilities_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vos_module_interfaces__srv__GetCapabilities_Request__Sequence__copy(
  const vos_module_interfaces__srv__GetCapabilities_Request__Sequence * input,
  vos_module_interfaces__srv__GetCapabilities_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vos_module_interfaces__srv__GetCapabilities_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vos_module_interfaces__srv__GetCapabilities_Request * data =
      (vos_module_interfaces__srv__GetCapabilities_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vos_module_interfaces__srv__GetCapabilities_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vos_module_interfaces__srv__GetCapabilities_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vos_module_interfaces__srv__GetCapabilities_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `capabilities`
#include "rosidl_runtime_c/string_functions.h"

bool
vos_module_interfaces__srv__GetCapabilities_Response__init(vos_module_interfaces__srv__GetCapabilities_Response * msg)
{
  if (!msg) {
    return false;
  }
  // capabilities
  if (!rosidl_runtime_c__String__Sequence__init(&msg->capabilities, 0)) {
    vos_module_interfaces__srv__GetCapabilities_Response__fini(msg);
    return false;
  }
  return true;
}

void
vos_module_interfaces__srv__GetCapabilities_Response__fini(vos_module_interfaces__srv__GetCapabilities_Response * msg)
{
  if (!msg) {
    return;
  }
  // capabilities
  rosidl_runtime_c__String__Sequence__fini(&msg->capabilities);
}

bool
vos_module_interfaces__srv__GetCapabilities_Response__are_equal(const vos_module_interfaces__srv__GetCapabilities_Response * lhs, const vos_module_interfaces__srv__GetCapabilities_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // capabilities
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->capabilities), &(rhs->capabilities)))
  {
    return false;
  }
  return true;
}

bool
vos_module_interfaces__srv__GetCapabilities_Response__copy(
  const vos_module_interfaces__srv__GetCapabilities_Response * input,
  vos_module_interfaces__srv__GetCapabilities_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // capabilities
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->capabilities), &(output->capabilities)))
  {
    return false;
  }
  return true;
}

vos_module_interfaces__srv__GetCapabilities_Response *
vos_module_interfaces__srv__GetCapabilities_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Response * msg = (vos_module_interfaces__srv__GetCapabilities_Response *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetCapabilities_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vos_module_interfaces__srv__GetCapabilities_Response));
  bool success = vos_module_interfaces__srv__GetCapabilities_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vos_module_interfaces__srv__GetCapabilities_Response__destroy(vos_module_interfaces__srv__GetCapabilities_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vos_module_interfaces__srv__GetCapabilities_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__init(vos_module_interfaces__srv__GetCapabilities_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Response * data = NULL;

  if (size) {
    data = (vos_module_interfaces__srv__GetCapabilities_Response *)allocator.zero_allocate(size, sizeof(vos_module_interfaces__srv__GetCapabilities_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vos_module_interfaces__srv__GetCapabilities_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vos_module_interfaces__srv__GetCapabilities_Response__fini(&data[i - 1]);
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
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__fini(vos_module_interfaces__srv__GetCapabilities_Response__Sequence * array)
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
      vos_module_interfaces__srv__GetCapabilities_Response__fini(&array->data[i]);
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

vos_module_interfaces__srv__GetCapabilities_Response__Sequence *
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetCapabilities_Response__Sequence * array = (vos_module_interfaces__srv__GetCapabilities_Response__Sequence *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetCapabilities_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vos_module_interfaces__srv__GetCapabilities_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__destroy(vos_module_interfaces__srv__GetCapabilities_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vos_module_interfaces__srv__GetCapabilities_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__are_equal(const vos_module_interfaces__srv__GetCapabilities_Response__Sequence * lhs, const vos_module_interfaces__srv__GetCapabilities_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vos_module_interfaces__srv__GetCapabilities_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vos_module_interfaces__srv__GetCapabilities_Response__Sequence__copy(
  const vos_module_interfaces__srv__GetCapabilities_Response__Sequence * input,
  vos_module_interfaces__srv__GetCapabilities_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vos_module_interfaces__srv__GetCapabilities_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vos_module_interfaces__srv__GetCapabilities_Response * data =
      (vos_module_interfaces__srv__GetCapabilities_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vos_module_interfaces__srv__GetCapabilities_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vos_module_interfaces__srv__GetCapabilities_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vos_module_interfaces__srv__GetCapabilities_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
