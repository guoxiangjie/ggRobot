// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/SystemStatus.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/system_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
aimdk_msgs__msg__SystemStatus__init(aimdk_msgs__msg__SystemStatus * msg)
{
  if (!msg) {
    return false;
  }
  // value
  return true;
}

void
aimdk_msgs__msg__SystemStatus__fini(aimdk_msgs__msg__SystemStatus * msg)
{
  if (!msg) {
    return;
  }
  // value
}

bool
aimdk_msgs__msg__SystemStatus__are_equal(const aimdk_msgs__msg__SystemStatus * lhs, const aimdk_msgs__msg__SystemStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // value
  if (lhs->value != rhs->value) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__SystemStatus__copy(
  const aimdk_msgs__msg__SystemStatus * input,
  aimdk_msgs__msg__SystemStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // value
  output->value = input->value;
  return true;
}

aimdk_msgs__msg__SystemStatus *
aimdk_msgs__msg__SystemStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__SystemStatus * msg = (aimdk_msgs__msg__SystemStatus *)allocator.allocate(sizeof(aimdk_msgs__msg__SystemStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__SystemStatus));
  bool success = aimdk_msgs__msg__SystemStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__SystemStatus__destroy(aimdk_msgs__msg__SystemStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__SystemStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__SystemStatus__Sequence__init(aimdk_msgs__msg__SystemStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__SystemStatus * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__SystemStatus *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__SystemStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__SystemStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__SystemStatus__fini(&data[i - 1]);
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
aimdk_msgs__msg__SystemStatus__Sequence__fini(aimdk_msgs__msg__SystemStatus__Sequence * array)
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
      aimdk_msgs__msg__SystemStatus__fini(&array->data[i]);
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

aimdk_msgs__msg__SystemStatus__Sequence *
aimdk_msgs__msg__SystemStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__SystemStatus__Sequence * array = (aimdk_msgs__msg__SystemStatus__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__SystemStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__SystemStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__SystemStatus__Sequence__destroy(aimdk_msgs__msg__SystemStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__SystemStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__SystemStatus__Sequence__are_equal(const aimdk_msgs__msg__SystemStatus__Sequence * lhs, const aimdk_msgs__msg__SystemStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__SystemStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__SystemStatus__Sequence__copy(
  const aimdk_msgs__msg__SystemStatus__Sequence * input,
  aimdk_msgs__msg__SystemStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__SystemStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__SystemStatus * data =
      (aimdk_msgs__msg__SystemStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__SystemStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__SystemStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__SystemStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
