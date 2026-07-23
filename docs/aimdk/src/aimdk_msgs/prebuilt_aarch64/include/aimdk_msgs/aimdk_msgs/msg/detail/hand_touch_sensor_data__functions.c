// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
aimdk_msgs__msg__HandTouchSensorData__init(aimdk_msgs__msg__HandTouchSensorData * msg)
{
  if (!msg) {
    return false;
  }
  // palm_touch_data
  // back_of_hand_touch_data
  // thumb_touch_data
  // index_finger_touch_data
  // middle_finger_touch_data
  // ring_finger_touch_data
  // little_finger_touch_data
  return true;
}

void
aimdk_msgs__msg__HandTouchSensorData__fini(aimdk_msgs__msg__HandTouchSensorData * msg)
{
  if (!msg) {
    return;
  }
  // palm_touch_data
  // back_of_hand_touch_data
  // thumb_touch_data
  // index_finger_touch_data
  // middle_finger_touch_data
  // ring_finger_touch_data
  // little_finger_touch_data
}

bool
aimdk_msgs__msg__HandTouchSensorData__are_equal(const aimdk_msgs__msg__HandTouchSensorData * lhs, const aimdk_msgs__msg__HandTouchSensorData * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // palm_touch_data
  for (size_t i = 0; i < 36; ++i) {
    if (lhs->palm_touch_data[i] != rhs->palm_touch_data[i]) {
      return false;
    }
  }
  // back_of_hand_touch_data
  for (size_t i = 0; i < 36; ++i) {
    if (lhs->back_of_hand_touch_data[i] != rhs->back_of_hand_touch_data[i]) {
      return false;
    }
  }
  // thumb_touch_data
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->thumb_touch_data[i] != rhs->thumb_touch_data[i]) {
      return false;
    }
  }
  // index_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->index_finger_touch_data[i] != rhs->index_finger_touch_data[i]) {
      return false;
    }
  }
  // middle_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->middle_finger_touch_data[i] != rhs->middle_finger_touch_data[i]) {
      return false;
    }
  }
  // ring_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->ring_finger_touch_data[i] != rhs->ring_finger_touch_data[i]) {
      return false;
    }
  }
  // little_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->little_finger_touch_data[i] != rhs->little_finger_touch_data[i]) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__HandTouchSensorData__copy(
  const aimdk_msgs__msg__HandTouchSensorData * input,
  aimdk_msgs__msg__HandTouchSensorData * output)
{
  if (!input || !output) {
    return false;
  }
  // palm_touch_data
  for (size_t i = 0; i < 36; ++i) {
    output->palm_touch_data[i] = input->palm_touch_data[i];
  }
  // back_of_hand_touch_data
  for (size_t i = 0; i < 36; ++i) {
    output->back_of_hand_touch_data[i] = input->back_of_hand_touch_data[i];
  }
  // thumb_touch_data
  for (size_t i = 0; i < 16; ++i) {
    output->thumb_touch_data[i] = input->thumb_touch_data[i];
  }
  // index_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    output->index_finger_touch_data[i] = input->index_finger_touch_data[i];
  }
  // middle_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    output->middle_finger_touch_data[i] = input->middle_finger_touch_data[i];
  }
  // ring_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    output->ring_finger_touch_data[i] = input->ring_finger_touch_data[i];
  }
  // little_finger_touch_data
  for (size_t i = 0; i < 16; ++i) {
    output->little_finger_touch_data[i] = input->little_finger_touch_data[i];
  }
  return true;
}

aimdk_msgs__msg__HandTouchSensorData *
aimdk_msgs__msg__HandTouchSensorData__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandTouchSensorData * msg = (aimdk_msgs__msg__HandTouchSensorData *)allocator.allocate(sizeof(aimdk_msgs__msg__HandTouchSensorData), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__HandTouchSensorData));
  bool success = aimdk_msgs__msg__HandTouchSensorData__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__HandTouchSensorData__destroy(aimdk_msgs__msg__HandTouchSensorData * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__HandTouchSensorData__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__init(aimdk_msgs__msg__HandTouchSensorData__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandTouchSensorData * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__HandTouchSensorData *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__HandTouchSensorData), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__HandTouchSensorData__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__HandTouchSensorData__fini(&data[i - 1]);
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
aimdk_msgs__msg__HandTouchSensorData__Sequence__fini(aimdk_msgs__msg__HandTouchSensorData__Sequence * array)
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
      aimdk_msgs__msg__HandTouchSensorData__fini(&array->data[i]);
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

aimdk_msgs__msg__HandTouchSensorData__Sequence *
aimdk_msgs__msg__HandTouchSensorData__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandTouchSensorData__Sequence * array = (aimdk_msgs__msg__HandTouchSensorData__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__HandTouchSensorData__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__HandTouchSensorData__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__HandTouchSensorData__Sequence__destroy(aimdk_msgs__msg__HandTouchSensorData__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__HandTouchSensorData__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__are_equal(const aimdk_msgs__msg__HandTouchSensorData__Sequence * lhs, const aimdk_msgs__msg__HandTouchSensorData__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__HandTouchSensorData__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__copy(
  const aimdk_msgs__msg__HandTouchSensorData__Sequence * input,
  aimdk_msgs__msg__HandTouchSensorData__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__HandTouchSensorData);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__HandTouchSensorData * data =
      (aimdk_msgs__msg__HandTouchSensorData *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__HandTouchSensorData__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__HandTouchSensorData__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__HandTouchSensorData__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
