// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:srv/GetMcAction.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/srv/detail/get_mc_action__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `request`
#include "aimdk_msgs/msg/detail/common_request__functions.h"

bool
aimdk_msgs__srv__GetMcAction_Request__init(aimdk_msgs__srv__GetMcAction_Request * msg)
{
  if (!msg) {
    return false;
  }
  // request
  if (!aimdk_msgs__msg__CommonRequest__init(&msg->request)) {
    aimdk_msgs__srv__GetMcAction_Request__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__srv__GetMcAction_Request__fini(aimdk_msgs__srv__GetMcAction_Request * msg)
{
  if (!msg) {
    return;
  }
  // request
  aimdk_msgs__msg__CommonRequest__fini(&msg->request);
}

bool
aimdk_msgs__srv__GetMcAction_Request__are_equal(const aimdk_msgs__srv__GetMcAction_Request * lhs, const aimdk_msgs__srv__GetMcAction_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // request
  if (!aimdk_msgs__msg__CommonRequest__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__GetMcAction_Request__copy(
  const aimdk_msgs__srv__GetMcAction_Request * input,
  aimdk_msgs__srv__GetMcAction_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // request
  if (!aimdk_msgs__msg__CommonRequest__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__srv__GetMcAction_Request *
aimdk_msgs__srv__GetMcAction_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Request * msg = (aimdk_msgs__srv__GetMcAction_Request *)allocator.allocate(sizeof(aimdk_msgs__srv__GetMcAction_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__GetMcAction_Request));
  bool success = aimdk_msgs__srv__GetMcAction_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__GetMcAction_Request__destroy(aimdk_msgs__srv__GetMcAction_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__GetMcAction_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__GetMcAction_Request__Sequence__init(aimdk_msgs__srv__GetMcAction_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Request * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__GetMcAction_Request *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__GetMcAction_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__GetMcAction_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__GetMcAction_Request__fini(&data[i - 1]);
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
aimdk_msgs__srv__GetMcAction_Request__Sequence__fini(aimdk_msgs__srv__GetMcAction_Request__Sequence * array)
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
      aimdk_msgs__srv__GetMcAction_Request__fini(&array->data[i]);
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

aimdk_msgs__srv__GetMcAction_Request__Sequence *
aimdk_msgs__srv__GetMcAction_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Request__Sequence * array = (aimdk_msgs__srv__GetMcAction_Request__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__GetMcAction_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__GetMcAction_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__GetMcAction_Request__Sequence__destroy(aimdk_msgs__srv__GetMcAction_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__GetMcAction_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__GetMcAction_Request__Sequence__are_equal(const aimdk_msgs__srv__GetMcAction_Request__Sequence * lhs, const aimdk_msgs__srv__GetMcAction_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__GetMcAction_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__GetMcAction_Request__Sequence__copy(
  const aimdk_msgs__srv__GetMcAction_Request__Sequence * input,
  aimdk_msgs__srv__GetMcAction_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__GetMcAction_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__GetMcAction_Request * data =
      (aimdk_msgs__srv__GetMcAction_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__GetMcAction_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__GetMcAction_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__GetMcAction_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/response_header__functions.h"
// Member `info`
#include "aimdk_msgs/msg/detail/mc_action_info__functions.h"

bool
aimdk_msgs__srv__GetMcAction_Response__init(aimdk_msgs__srv__GetMcAction_Response * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__init(&msg->header)) {
    aimdk_msgs__srv__GetMcAction_Response__fini(msg);
    return false;
  }
  // info
  if (!aimdk_msgs__msg__McActionInfo__init(&msg->info)) {
    aimdk_msgs__srv__GetMcAction_Response__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__srv__GetMcAction_Response__fini(aimdk_msgs__srv__GetMcAction_Response * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__ResponseHeader__fini(&msg->header);
  // info
  aimdk_msgs__msg__McActionInfo__fini(&msg->info);
}

bool
aimdk_msgs__srv__GetMcAction_Response__are_equal(const aimdk_msgs__srv__GetMcAction_Response * lhs, const aimdk_msgs__srv__GetMcAction_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // info
  if (!aimdk_msgs__msg__McActionInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__GetMcAction_Response__copy(
  const aimdk_msgs__srv__GetMcAction_Response * input,
  aimdk_msgs__srv__GetMcAction_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // info
  if (!aimdk_msgs__msg__McActionInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__srv__GetMcAction_Response *
aimdk_msgs__srv__GetMcAction_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Response * msg = (aimdk_msgs__srv__GetMcAction_Response *)allocator.allocate(sizeof(aimdk_msgs__srv__GetMcAction_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__GetMcAction_Response));
  bool success = aimdk_msgs__srv__GetMcAction_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__GetMcAction_Response__destroy(aimdk_msgs__srv__GetMcAction_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__GetMcAction_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__GetMcAction_Response__Sequence__init(aimdk_msgs__srv__GetMcAction_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Response * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__GetMcAction_Response *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__GetMcAction_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__GetMcAction_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__GetMcAction_Response__fini(&data[i - 1]);
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
aimdk_msgs__srv__GetMcAction_Response__Sequence__fini(aimdk_msgs__srv__GetMcAction_Response__Sequence * array)
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
      aimdk_msgs__srv__GetMcAction_Response__fini(&array->data[i]);
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

aimdk_msgs__srv__GetMcAction_Response__Sequence *
aimdk_msgs__srv__GetMcAction_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetMcAction_Response__Sequence * array = (aimdk_msgs__srv__GetMcAction_Response__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__GetMcAction_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__GetMcAction_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__GetMcAction_Response__Sequence__destroy(aimdk_msgs__srv__GetMcAction_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__GetMcAction_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__GetMcAction_Response__Sequence__are_equal(const aimdk_msgs__srv__GetMcAction_Response__Sequence * lhs, const aimdk_msgs__srv__GetMcAction_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__GetMcAction_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__GetMcAction_Response__Sequence__copy(
  const aimdk_msgs__srv__GetMcAction_Response__Sequence * input,
  aimdk_msgs__srv__GetMcAction_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__GetMcAction_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__GetMcAction_Response * data =
      (aimdk_msgs__srv__GetMcAction_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__GetMcAction_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__GetMcAction_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__GetMcAction_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
