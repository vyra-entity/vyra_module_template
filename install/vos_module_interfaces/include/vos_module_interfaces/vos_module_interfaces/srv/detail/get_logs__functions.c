// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vos_module_interfaces:srv/GetLogs.idl
// generated code does not contain a copyright notice
#include "vos_module_interfaces/srv/detail/get_logs__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
vos_module_interfaces__srv__GetLogs_Request__init(vos_module_interfaces__srv__GetLogs_Request * msg)
{
  if (!msg) {
    return false;
  }
  // log_lines
  // log_level
  return true;
}

void
vos_module_interfaces__srv__GetLogs_Request__fini(vos_module_interfaces__srv__GetLogs_Request * msg)
{
  if (!msg) {
    return;
  }
  // log_lines
  // log_level
}

bool
vos_module_interfaces__srv__GetLogs_Request__are_equal(const vos_module_interfaces__srv__GetLogs_Request * lhs, const vos_module_interfaces__srv__GetLogs_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // log_lines
  if (lhs->log_lines != rhs->log_lines) {
    return false;
  }
  // log_level
  if (lhs->log_level != rhs->log_level) {
    return false;
  }
  return true;
}

bool
vos_module_interfaces__srv__GetLogs_Request__copy(
  const vos_module_interfaces__srv__GetLogs_Request * input,
  vos_module_interfaces__srv__GetLogs_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // log_lines
  output->log_lines = input->log_lines;
  // log_level
  output->log_level = input->log_level;
  return true;
}

vos_module_interfaces__srv__GetLogs_Request *
vos_module_interfaces__srv__GetLogs_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Request * msg = (vos_module_interfaces__srv__GetLogs_Request *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetLogs_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vos_module_interfaces__srv__GetLogs_Request));
  bool success = vos_module_interfaces__srv__GetLogs_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vos_module_interfaces__srv__GetLogs_Request__destroy(vos_module_interfaces__srv__GetLogs_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vos_module_interfaces__srv__GetLogs_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vos_module_interfaces__srv__GetLogs_Request__Sequence__init(vos_module_interfaces__srv__GetLogs_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Request * data = NULL;

  if (size) {
    data = (vos_module_interfaces__srv__GetLogs_Request *)allocator.zero_allocate(size, sizeof(vos_module_interfaces__srv__GetLogs_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vos_module_interfaces__srv__GetLogs_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vos_module_interfaces__srv__GetLogs_Request__fini(&data[i - 1]);
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
vos_module_interfaces__srv__GetLogs_Request__Sequence__fini(vos_module_interfaces__srv__GetLogs_Request__Sequence * array)
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
      vos_module_interfaces__srv__GetLogs_Request__fini(&array->data[i]);
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

vos_module_interfaces__srv__GetLogs_Request__Sequence *
vos_module_interfaces__srv__GetLogs_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Request__Sequence * array = (vos_module_interfaces__srv__GetLogs_Request__Sequence *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetLogs_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vos_module_interfaces__srv__GetLogs_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vos_module_interfaces__srv__GetLogs_Request__Sequence__destroy(vos_module_interfaces__srv__GetLogs_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vos_module_interfaces__srv__GetLogs_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vos_module_interfaces__srv__GetLogs_Request__Sequence__are_equal(const vos_module_interfaces__srv__GetLogs_Request__Sequence * lhs, const vos_module_interfaces__srv__GetLogs_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vos_module_interfaces__srv__GetLogs_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vos_module_interfaces__srv__GetLogs_Request__Sequence__copy(
  const vos_module_interfaces__srv__GetLogs_Request__Sequence * input,
  vos_module_interfaces__srv__GetLogs_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vos_module_interfaces__srv__GetLogs_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vos_module_interfaces__srv__GetLogs_Request * data =
      (vos_module_interfaces__srv__GetLogs_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vos_module_interfaces__srv__GetLogs_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vos_module_interfaces__srv__GetLogs_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vos_module_interfaces__srv__GetLogs_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `log_messages`
#include "vos_module_interfaces/msg/detail/logger_stream__functions.h"

bool
vos_module_interfaces__srv__GetLogs_Response__init(vos_module_interfaces__srv__GetLogs_Response * msg)
{
  if (!msg) {
    return false;
  }
  // log_messages
  if (!vos_module_interfaces__msg__LoggerStream__Sequence__init(&msg->log_messages, 0)) {
    vos_module_interfaces__srv__GetLogs_Response__fini(msg);
    return false;
  }
  return true;
}

void
vos_module_interfaces__srv__GetLogs_Response__fini(vos_module_interfaces__srv__GetLogs_Response * msg)
{
  if (!msg) {
    return;
  }
  // log_messages
  vos_module_interfaces__msg__LoggerStream__Sequence__fini(&msg->log_messages);
}

bool
vos_module_interfaces__srv__GetLogs_Response__are_equal(const vos_module_interfaces__srv__GetLogs_Response * lhs, const vos_module_interfaces__srv__GetLogs_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // log_messages
  if (!vos_module_interfaces__msg__LoggerStream__Sequence__are_equal(
      &(lhs->log_messages), &(rhs->log_messages)))
  {
    return false;
  }
  return true;
}

bool
vos_module_interfaces__srv__GetLogs_Response__copy(
  const vos_module_interfaces__srv__GetLogs_Response * input,
  vos_module_interfaces__srv__GetLogs_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // log_messages
  if (!vos_module_interfaces__msg__LoggerStream__Sequence__copy(
      &(input->log_messages), &(output->log_messages)))
  {
    return false;
  }
  return true;
}

vos_module_interfaces__srv__GetLogs_Response *
vos_module_interfaces__srv__GetLogs_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Response * msg = (vos_module_interfaces__srv__GetLogs_Response *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetLogs_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vos_module_interfaces__srv__GetLogs_Response));
  bool success = vos_module_interfaces__srv__GetLogs_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vos_module_interfaces__srv__GetLogs_Response__destroy(vos_module_interfaces__srv__GetLogs_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vos_module_interfaces__srv__GetLogs_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vos_module_interfaces__srv__GetLogs_Response__Sequence__init(vos_module_interfaces__srv__GetLogs_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Response * data = NULL;

  if (size) {
    data = (vos_module_interfaces__srv__GetLogs_Response *)allocator.zero_allocate(size, sizeof(vos_module_interfaces__srv__GetLogs_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vos_module_interfaces__srv__GetLogs_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vos_module_interfaces__srv__GetLogs_Response__fini(&data[i - 1]);
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
vos_module_interfaces__srv__GetLogs_Response__Sequence__fini(vos_module_interfaces__srv__GetLogs_Response__Sequence * array)
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
      vos_module_interfaces__srv__GetLogs_Response__fini(&array->data[i]);
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

vos_module_interfaces__srv__GetLogs_Response__Sequence *
vos_module_interfaces__srv__GetLogs_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vos_module_interfaces__srv__GetLogs_Response__Sequence * array = (vos_module_interfaces__srv__GetLogs_Response__Sequence *)allocator.allocate(sizeof(vos_module_interfaces__srv__GetLogs_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vos_module_interfaces__srv__GetLogs_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vos_module_interfaces__srv__GetLogs_Response__Sequence__destroy(vos_module_interfaces__srv__GetLogs_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vos_module_interfaces__srv__GetLogs_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vos_module_interfaces__srv__GetLogs_Response__Sequence__are_equal(const vos_module_interfaces__srv__GetLogs_Response__Sequence * lhs, const vos_module_interfaces__srv__GetLogs_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vos_module_interfaces__srv__GetLogs_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vos_module_interfaces__srv__GetLogs_Response__Sequence__copy(
  const vos_module_interfaces__srv__GetLogs_Response__Sequence * input,
  vos_module_interfaces__srv__GetLogs_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vos_module_interfaces__srv__GetLogs_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vos_module_interfaces__srv__GetLogs_Response * data =
      (vos_module_interfaces__srv__GetLogs_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vos_module_interfaces__srv__GetLogs_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vos_module_interfaces__srv__GetLogs_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vos_module_interfaces__srv__GetLogs_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
