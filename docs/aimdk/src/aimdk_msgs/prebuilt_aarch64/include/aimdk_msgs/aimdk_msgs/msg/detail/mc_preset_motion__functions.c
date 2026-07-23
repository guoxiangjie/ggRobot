// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/McPresetMotion.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/mc_preset_motion__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
aimdk_msgs__msg__McPresetMotion__init(aimdk_msgs__msg__McPresetMotion * msg)
{
  if (!msg) {
    return false;
  }
  // value
  return true;
}

void
aimdk_msgs__msg__McPresetMotion__fini(aimdk_msgs__msg__McPresetMotion * msg)
{
  if (!msg) {
    return;
  }
  // value
}

bool
aimdk_msgs__msg__McPresetMotion__are_equal(const aimdk_msgs__msg__McPresetMotion * lhs, const aimdk_msgs__msg__McPresetMotion * rhs)
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
aimdk_msgs__msg__McPresetMotion__copy(
  const aimdk_msgs__msg__McPresetMotion * input,
  aimdk_msgs__msg__McPresetMotion * output)
{
  if (!input || !output) {
    return false;
  }
  // value
  output->value = input->value;
  return true;
}

aimdk_msgs__msg__McPresetMotion *
aimdk_msgs__msg__McPresetMotion__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__McPresetMotion * msg = (aimdk_msgs__msg__McPresetMotion *)allocator.allocate(sizeof(aimdk_msgs__msg__McPresetMotion), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__McPresetMotion));
  bool success = aimdk_msgs__msg__McPresetMotion__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__McPresetMotion__destroy(aimdk_msgs__msg__McPresetMotion * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__McPresetMotion__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__McPresetMotion__Sequence__init(aimdk_msgs__msg__McPresetMotion__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__McPresetMotion * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__McPresetMotion *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__McPresetMotion), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__McPresetMotion__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__McPresetMotion__fini(&data[i - 1]);
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
aimdk_msgs__msg__McPresetMotion__Sequence__fini(aimdk_msgs__msg__McPresetMotion__Sequence * array)
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
      aimdk_msgs__msg__McPresetMotion__fini(&array->data[i]);
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

aimdk_msgs__msg__McPresetMotion__Sequence *
aimdk_msgs__msg__McPresetMotion__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__McPresetMotion__Sequence * array = (aimdk_msgs__msg__McPresetMotion__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__McPresetMotion__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__McPresetMotion__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__McPresetMotion__Sequence__destroy(aimdk_msgs__msg__McPresetMotion__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__McPresetMotion__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__McPresetMotion__Sequence__are_equal(const aimdk_msgs__msg__McPresetMotion__Sequence * lhs, const aimdk_msgs__msg__McPresetMotion__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__McPresetMotion__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__McPresetMotion__Sequence__copy(
  const aimdk_msgs__msg__McPresetMotion__Sequence * input,
  aimdk_msgs__msg__McPresetMotion__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__McPresetMotion);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__McPresetMotion * data =
      (aimdk_msgs__msg__McPresetMotion *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__McPresetMotion__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__McPresetMotion__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__McPresetMotion__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
