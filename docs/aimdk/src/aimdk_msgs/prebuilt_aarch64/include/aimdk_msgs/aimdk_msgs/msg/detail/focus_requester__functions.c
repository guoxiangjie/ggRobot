// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/FocusRequester.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/focus_requester__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `pkg_name`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__FocusRequester__init(aimdk_msgs__msg__FocusRequester * msg)
{
  if (!msg) {
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__init(&msg->pkg_name)) {
    aimdk_msgs__msg__FocusRequester__fini(msg);
    return false;
  }
  // priority
  // priority_weight
  return true;
}

void
aimdk_msgs__msg__FocusRequester__fini(aimdk_msgs__msg__FocusRequester * msg)
{
  if (!msg) {
    return;
  }
  // pkg_name
  rosidl_runtime_c__String__fini(&msg->pkg_name);
  // priority
  // priority_weight
}

bool
aimdk_msgs__msg__FocusRequester__are_equal(const aimdk_msgs__msg__FocusRequester * lhs, const aimdk_msgs__msg__FocusRequester * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pkg_name), &(rhs->pkg_name)))
  {
    return false;
  }
  // priority
  if (lhs->priority != rhs->priority) {
    return false;
  }
  // priority_weight
  if (lhs->priority_weight != rhs->priority_weight) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__FocusRequester__copy(
  const aimdk_msgs__msg__FocusRequester * input,
  aimdk_msgs__msg__FocusRequester * output)
{
  if (!input || !output) {
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__copy(
      &(input->pkg_name), &(output->pkg_name)))
  {
    return false;
  }
  // priority
  output->priority = input->priority;
  // priority_weight
  output->priority_weight = input->priority_weight;
  return true;
}

aimdk_msgs__msg__FocusRequester *
aimdk_msgs__msg__FocusRequester__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FocusRequester * msg = (aimdk_msgs__msg__FocusRequester *)allocator.allocate(sizeof(aimdk_msgs__msg__FocusRequester), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__FocusRequester));
  bool success = aimdk_msgs__msg__FocusRequester__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__FocusRequester__destroy(aimdk_msgs__msg__FocusRequester * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__FocusRequester__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__FocusRequester__Sequence__init(aimdk_msgs__msg__FocusRequester__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FocusRequester * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__FocusRequester *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__FocusRequester), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__FocusRequester__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__FocusRequester__fini(&data[i - 1]);
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
aimdk_msgs__msg__FocusRequester__Sequence__fini(aimdk_msgs__msg__FocusRequester__Sequence * array)
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
      aimdk_msgs__msg__FocusRequester__fini(&array->data[i]);
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

aimdk_msgs__msg__FocusRequester__Sequence *
aimdk_msgs__msg__FocusRequester__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FocusRequester__Sequence * array = (aimdk_msgs__msg__FocusRequester__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__FocusRequester__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__FocusRequester__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__FocusRequester__Sequence__destroy(aimdk_msgs__msg__FocusRequester__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__FocusRequester__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__FocusRequester__Sequence__are_equal(const aimdk_msgs__msg__FocusRequester__Sequence * lhs, const aimdk_msgs__msg__FocusRequester__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__FocusRequester__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__FocusRequester__Sequence__copy(
  const aimdk_msgs__msg__FocusRequester__Sequence * input,
  aimdk_msgs__msg__FocusRequester__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__FocusRequester);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__FocusRequester * data =
      (aimdk_msgs__msg__FocusRequester *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__FocusRequester__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__FocusRequester__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__FocusRequester__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
