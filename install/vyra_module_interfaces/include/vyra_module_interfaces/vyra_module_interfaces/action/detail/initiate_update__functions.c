// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vyra_module_interfaces:action/InitiateUpdate.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/action/detail/initiate_update__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `module_name`
// Member `update_url`
// Member `target_version`
// Member `expected_hash`
#include "rosidl_runtime_c/string_functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_Goal__init(vyra_module_interfaces__action__InitiateUpdate_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__init(&msg->module_name)) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__fini(msg);
    return false;
  }
  // update_url
  if (!rosidl_runtime_c__String__init(&msg->update_url)) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__fini(msg);
    return false;
  }
  // target_version
  if (!rosidl_runtime_c__String__init(&msg->target_version)) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__fini(msg);
    return false;
  }
  // force
  // expected_hash
  if (!rosidl_runtime_c__String__init(&msg->expected_hash)) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_Goal__fini(vyra_module_interfaces__action__InitiateUpdate_Goal * msg)
{
  if (!msg) {
    return;
  }
  // module_name
  rosidl_runtime_c__String__fini(&msg->module_name);
  // update_url
  rosidl_runtime_c__String__fini(&msg->update_url);
  // target_version
  rosidl_runtime_c__String__fini(&msg->target_version);
  // force
  // expected_hash
  rosidl_runtime_c__String__fini(&msg->expected_hash);
}

bool
vyra_module_interfaces__action__InitiateUpdate_Goal__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Goal * lhs, const vyra_module_interfaces__action__InitiateUpdate_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->module_name), &(rhs->module_name)))
  {
    return false;
  }
  // update_url
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->update_url), &(rhs->update_url)))
  {
    return false;
  }
  // target_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->target_version), &(rhs->target_version)))
  {
    return false;
  }
  // force
  if (lhs->force != rhs->force) {
    return false;
  }
  // expected_hash
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->expected_hash), &(rhs->expected_hash)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Goal__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Goal * input,
  vyra_module_interfaces__action__InitiateUpdate_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // module_name
  if (!rosidl_runtime_c__String__copy(
      &(input->module_name), &(output->module_name)))
  {
    return false;
  }
  // update_url
  if (!rosidl_runtime_c__String__copy(
      &(input->update_url), &(output->update_url)))
  {
    return false;
  }
  // target_version
  if (!rosidl_runtime_c__String__copy(
      &(input->target_version), &(output->target_version)))
  {
    return false;
  }
  // force
  output->force = input->force;
  // expected_hash
  if (!rosidl_runtime_c__String__copy(
      &(input->expected_hash), &(output->expected_hash)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_Goal *
vyra_module_interfaces__action__InitiateUpdate_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Goal * msg = (vyra_module_interfaces__action__InitiateUpdate_Goal *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal));
  bool success = vyra_module_interfaces__action__InitiateUpdate_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_Goal__destroy(vyra_module_interfaces__action__InitiateUpdate_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Goal * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_Goal *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_Goal__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_Goal__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence *
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_Goal * data =
      (vyra_module_interfaces__action__InitiateUpdate_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `report`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_Result__init(vyra_module_interfaces__action__InitiateUpdate_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // report
  if (!rosidl_runtime_c__String__init(&msg->report)) {
    vyra_module_interfaces__action__InitiateUpdate_Result__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_Result__fini(vyra_module_interfaces__action__InitiateUpdate_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // report
  rosidl_runtime_c__String__fini(&msg->report);
}

bool
vyra_module_interfaces__action__InitiateUpdate_Result__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Result * lhs, const vyra_module_interfaces__action__InitiateUpdate_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // report
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->report), &(rhs->report)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Result__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Result * input,
  vyra_module_interfaces__action__InitiateUpdate_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // report
  if (!rosidl_runtime_c__String__copy(
      &(input->report), &(output->report)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_Result *
vyra_module_interfaces__action__InitiateUpdate_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Result * msg = (vyra_module_interfaces__action__InitiateUpdate_Result *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_Result));
  bool success = vyra_module_interfaces__action__InitiateUpdate_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_Result__destroy(vyra_module_interfaces__action__InitiateUpdate_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Result * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_Result *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_Result__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_Result__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_Result__Sequence *
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_Result__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Result__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_Result * data =
      (vyra_module_interfaces__action__InitiateUpdate_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `status_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__init(vyra_module_interfaces__action__InitiateUpdate_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // status_message
  if (!rosidl_runtime_c__String__init(&msg->status_message)) {
    vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(msg);
    return false;
  }
  // progress_percentage
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(vyra_module_interfaces__action__InitiateUpdate_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // status_message
  rosidl_runtime_c__String__fini(&msg->status_message);
  // progress_percentage
}

bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Feedback * lhs, const vyra_module_interfaces__action__InitiateUpdate_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status_message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->status_message), &(rhs->status_message)))
  {
    return false;
  }
  // progress_percentage
  if (lhs->progress_percentage != rhs->progress_percentage) {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Feedback * input,
  vyra_module_interfaces__action__InitiateUpdate_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // status_message
  if (!rosidl_runtime_c__String__copy(
      &(input->status_message), &(output->status_message)))
  {
    return false;
  }
  // progress_percentage
  output->progress_percentage = input->progress_percentage;
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_Feedback *
vyra_module_interfaces__action__InitiateUpdate_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Feedback * msg = (vyra_module_interfaces__action__InitiateUpdate_Feedback *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback));
  bool success = vyra_module_interfaces__action__InitiateUpdate_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_Feedback__destroy(vyra_module_interfaces__action__InitiateUpdate_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Feedback * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_Feedback *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence *
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_Feedback * data =
      (vyra_module_interfaces__action__InitiateUpdate_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!vyra_module_interfaces__action__InitiateUpdate_Goal__init(&msg->goal)) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  vyra_module_interfaces__action__InitiateUpdate_Goal__fini(&msg->goal);
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__are_equal(const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * lhs, const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!vyra_module_interfaces__action__InitiateUpdate_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__copy(
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * input,
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!vyra_module_interfaces__action__InitiateUpdate_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * msg = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request));
  bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__destroy(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request * data =
      (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__are_equal(const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * lhs, const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__copy(
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * input,
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * msg = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response));
  bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__destroy(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response * data =
      (vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__init(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__are_equal(const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * lhs, const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__copy(
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * input,
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * msg = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request));
  bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__destroy(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Request * data =
      (vyra_module_interfaces__action__InitiateUpdate_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__init(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!vyra_module_interfaces__action__InitiateUpdate_Result__init(&msg->result)) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  vyra_module_interfaces__action__InitiateUpdate_Result__fini(&msg->result);
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__are_equal(const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * lhs, const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!vyra_module_interfaces__action__InitiateUpdate_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__copy(
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * input,
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!vyra_module_interfaces__action__InitiateUpdate_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * msg = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response));
  bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__destroy(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_GetResult_Response * data =
      (vyra_module_interfaces__action__InitiateUpdate_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "vyra_module_interfaces/action/detail/initiate_update__functions.h"

bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__init(&msg->feedback)) {
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  vyra_module_interfaces__action__InitiateUpdate_Feedback__fini(&msg->feedback);
}

bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__are_equal(const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * lhs, const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__copy(
  const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * input,
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!vyra_module_interfaces__action__InitiateUpdate_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage *
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * msg = (vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage));
  bool success = vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__destroy(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__init(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(&data[i - 1]);
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
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__fini(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * array)
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
      vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(&array->data[i]);
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

vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence *
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * array = (vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__destroy(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__are_equal(const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * lhs, const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence__copy(
  const vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * input,
  vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage * data =
      (vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__action__InitiateUpdate_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
