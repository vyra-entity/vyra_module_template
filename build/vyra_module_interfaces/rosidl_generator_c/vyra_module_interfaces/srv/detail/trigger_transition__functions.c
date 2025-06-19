// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vyra_module_interfaces:srv/TriggerTransition.idl
// generated code does not contain a copyright notice
#include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `transition_name`
#include "rosidl_runtime_c/string_functions.h"

bool
vyra_module_interfaces__srv__TriggerTransition_Request__init(vyra_module_interfaces__srv__TriggerTransition_Request * msg)
{
  if (!msg) {
    return false;
  }
  // transition_name
  if (!rosidl_runtime_c__String__init(&msg->transition_name)) {
    vyra_module_interfaces__srv__TriggerTransition_Request__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__srv__TriggerTransition_Request__fini(vyra_module_interfaces__srv__TriggerTransition_Request * msg)
{
  if (!msg) {
    return;
  }
  // transition_name
  rosidl_runtime_c__String__fini(&msg->transition_name);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Request__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Request * lhs, const vyra_module_interfaces__srv__TriggerTransition_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // transition_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->transition_name), &(rhs->transition_name)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Request__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Request * input,
  vyra_module_interfaces__srv__TriggerTransition_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // transition_name
  if (!rosidl_runtime_c__String__copy(
      &(input->transition_name), &(output->transition_name)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__srv__TriggerTransition_Request *
vyra_module_interfaces__srv__TriggerTransition_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Request * msg = (vyra_module_interfaces__srv__TriggerTransition_Request *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__srv__TriggerTransition_Request));
  bool success = vyra_module_interfaces__srv__TriggerTransition_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__srv__TriggerTransition_Request__destroy(vyra_module_interfaces__srv__TriggerTransition_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__srv__TriggerTransition_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__init(vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Request * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__srv__TriggerTransition_Request *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__srv__TriggerTransition_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__srv__TriggerTransition_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__srv__TriggerTransition_Request__fini(&data[i - 1]);
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
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__fini(vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * array)
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
      vyra_module_interfaces__srv__TriggerTransition_Request__fini(&array->data[i]);
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

vyra_module_interfaces__srv__TriggerTransition_Request__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * array = (vyra_module_interfaces__srv__TriggerTransition_Request__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__destroy(vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * lhs, const vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * input,
  vyra_module_interfaces__srv__TriggerTransition_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__srv__TriggerTransition_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__srv__TriggerTransition_Request * data =
      (vyra_module_interfaces__srv__TriggerTransition_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__srv__TriggerTransition_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__srv__TriggerTransition_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
vyra_module_interfaces__srv__TriggerTransition_Response__init(vyra_module_interfaces__srv__TriggerTransition_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    vyra_module_interfaces__srv__TriggerTransition_Response__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__srv__TriggerTransition_Response__fini(vyra_module_interfaces__srv__TriggerTransition_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Response__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Response * lhs, const vyra_module_interfaces__srv__TriggerTransition_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Response__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Response * input,
  vyra_module_interfaces__srv__TriggerTransition_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__srv__TriggerTransition_Response *
vyra_module_interfaces__srv__TriggerTransition_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Response * msg = (vyra_module_interfaces__srv__TriggerTransition_Response *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__srv__TriggerTransition_Response));
  bool success = vyra_module_interfaces__srv__TriggerTransition_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__srv__TriggerTransition_Response__destroy(vyra_module_interfaces__srv__TriggerTransition_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__srv__TriggerTransition_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__init(vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Response * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__srv__TriggerTransition_Response *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__srv__TriggerTransition_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__srv__TriggerTransition_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__srv__TriggerTransition_Response__fini(&data[i - 1]);
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
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__fini(vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * array)
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
      vyra_module_interfaces__srv__TriggerTransition_Response__fini(&array->data[i]);
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

vyra_module_interfaces__srv__TriggerTransition_Response__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * array = (vyra_module_interfaces__srv__TriggerTransition_Response__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__destroy(vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * lhs, const vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * input,
  vyra_module_interfaces__srv__TriggerTransition_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__srv__TriggerTransition_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__srv__TriggerTransition_Response * data =
      (vyra_module_interfaces__srv__TriggerTransition_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__srv__TriggerTransition_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__srv__TriggerTransition_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "vyra_module_interfaces/srv/detail/trigger_transition__functions.h"

bool
vyra_module_interfaces__srv__TriggerTransition_Event__init(vyra_module_interfaces__srv__TriggerTransition_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    vyra_module_interfaces__srv__TriggerTransition_Event__fini(msg);
    return false;
  }
  // request
  if (!vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__init(&msg->request, 0)) {
    vyra_module_interfaces__srv__TriggerTransition_Event__fini(msg);
    return false;
  }
  // response
  if (!vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__init(&msg->response, 0)) {
    vyra_module_interfaces__srv__TriggerTransition_Event__fini(msg);
    return false;
  }
  return true;
}

void
vyra_module_interfaces__srv__TriggerTransition_Event__fini(vyra_module_interfaces__srv__TriggerTransition_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__fini(&msg->request);
  // response
  vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__fini(&msg->response);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Event__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Event * lhs, const vyra_module_interfaces__srv__TriggerTransition_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Event__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Event * input,
  vyra_module_interfaces__srv__TriggerTransition_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!vyra_module_interfaces__srv__TriggerTransition_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!vyra_module_interfaces__srv__TriggerTransition_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

vyra_module_interfaces__srv__TriggerTransition_Event *
vyra_module_interfaces__srv__TriggerTransition_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Event * msg = (vyra_module_interfaces__srv__TriggerTransition_Event *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vyra_module_interfaces__srv__TriggerTransition_Event));
  bool success = vyra_module_interfaces__srv__TriggerTransition_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vyra_module_interfaces__srv__TriggerTransition_Event__destroy(vyra_module_interfaces__srv__TriggerTransition_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vyra_module_interfaces__srv__TriggerTransition_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__init(vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Event * data = NULL;

  if (size) {
    data = (vyra_module_interfaces__srv__TriggerTransition_Event *)allocator.zero_allocate(size, sizeof(vyra_module_interfaces__srv__TriggerTransition_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vyra_module_interfaces__srv__TriggerTransition_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vyra_module_interfaces__srv__TriggerTransition_Event__fini(&data[i - 1]);
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
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__fini(vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * array)
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
      vyra_module_interfaces__srv__TriggerTransition_Event__fini(&array->data[i]);
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

vyra_module_interfaces__srv__TriggerTransition_Event__Sequence *
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * array = (vyra_module_interfaces__srv__TriggerTransition_Event__Sequence *)allocator.allocate(sizeof(vyra_module_interfaces__srv__TriggerTransition_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__destroy(vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__are_equal(const vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * lhs, const vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vyra_module_interfaces__srv__TriggerTransition_Event__Sequence__copy(
  const vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * input,
  vyra_module_interfaces__srv__TriggerTransition_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vyra_module_interfaces__srv__TriggerTransition_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vyra_module_interfaces__srv__TriggerTransition_Event * data =
      (vyra_module_interfaces__srv__TriggerTransition_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vyra_module_interfaces__srv__TriggerTransition_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vyra_module_interfaces__srv__TriggerTransition_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vyra_module_interfaces__srv__TriggerTransition_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
