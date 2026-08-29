// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/HandCommand.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/hand_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__HandCommand__init(aimdk_msgs__msg__HandCommand * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    aimdk_msgs__msg__HandCommand__fini(msg);
    return false;
  }
  // position
  // velocity
  // acceleration
  // deceleration
  // effort
  return true;
}

void
aimdk_msgs__msg__HandCommand__fini(aimdk_msgs__msg__HandCommand * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // position
  // velocity
  // acceleration
  // deceleration
  // effort
}

bool
aimdk_msgs__msg__HandCommand__are_equal(const aimdk_msgs__msg__HandCommand * lhs, const aimdk_msgs__msg__HandCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // acceleration
  if (lhs->acceleration != rhs->acceleration) {
    return false;
  }
  // deceleration
  if (lhs->deceleration != rhs->deceleration) {
    return false;
  }
  // effort
  if (lhs->effort != rhs->effort) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__HandCommand__copy(
  const aimdk_msgs__msg__HandCommand * input,
  aimdk_msgs__msg__HandCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  // acceleration
  output->acceleration = input->acceleration;
  // deceleration
  output->deceleration = input->deceleration;
  // effort
  output->effort = input->effort;
  return true;
}

aimdk_msgs__msg__HandCommand *
aimdk_msgs__msg__HandCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommand * msg = (aimdk_msgs__msg__HandCommand *)allocator.allocate(sizeof(aimdk_msgs__msg__HandCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__HandCommand));
  bool success = aimdk_msgs__msg__HandCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__HandCommand__destroy(aimdk_msgs__msg__HandCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__HandCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__HandCommand__Sequence__init(aimdk_msgs__msg__HandCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommand * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__HandCommand *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__HandCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__HandCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__HandCommand__fini(&data[i - 1]);
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
aimdk_msgs__msg__HandCommand__Sequence__fini(aimdk_msgs__msg__HandCommand__Sequence * array)
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
      aimdk_msgs__msg__HandCommand__fini(&array->data[i]);
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

aimdk_msgs__msg__HandCommand__Sequence *
aimdk_msgs__msg__HandCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommand__Sequence * array = (aimdk_msgs__msg__HandCommand__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__HandCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__HandCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__HandCommand__Sequence__destroy(aimdk_msgs__msg__HandCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__HandCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__HandCommand__Sequence__are_equal(const aimdk_msgs__msg__HandCommand__Sequence * lhs, const aimdk_msgs__msg__HandCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__HandCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__HandCommand__Sequence__copy(
  const aimdk_msgs__msg__HandCommand__Sequence * input,
  aimdk_msgs__msg__HandCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__HandCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__HandCommand * data =
      (aimdk_msgs__msg__HandCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__HandCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__HandCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__HandCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
