// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/AudioCapture.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/audio_capture__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamps`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `info`
#include "aimdk_msgs/msg/detail/audio_info__functions.h"
// Member `data`
#include "aimdk_msgs/msg/detail/audio_data__functions.h"
// Member `pkg_name`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__AudioCapture__init(aimdk_msgs__msg__AudioCapture * msg)
{
  if (!msg) {
    return false;
  }
  // stamps
  if (!builtin_interfaces__msg__Time__init(&msg->stamps)) {
    aimdk_msgs__msg__AudioCapture__fini(msg);
    return false;
  }
  // mic_channels
  // ref_channels
  // info
  if (!aimdk_msgs__msg__AudioInfo__init(&msg->info)) {
    aimdk_msgs__msg__AudioCapture__fini(msg);
    return false;
  }
  // data
  if (!aimdk_msgs__msg__AudioData__init(&msg->data)) {
    aimdk_msgs__msg__AudioCapture__fini(msg);
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__init(&msg->pkg_name)) {
    aimdk_msgs__msg__AudioCapture__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__msg__AudioCapture__fini(aimdk_msgs__msg__AudioCapture * msg)
{
  if (!msg) {
    return;
  }
  // stamps
  builtin_interfaces__msg__Time__fini(&msg->stamps);
  // mic_channels
  // ref_channels
  // info
  aimdk_msgs__msg__AudioInfo__fini(&msg->info);
  // data
  aimdk_msgs__msg__AudioData__fini(&msg->data);
  // pkg_name
  rosidl_runtime_c__String__fini(&msg->pkg_name);
}

bool
aimdk_msgs__msg__AudioCapture__are_equal(const aimdk_msgs__msg__AudioCapture * lhs, const aimdk_msgs__msg__AudioCapture * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamps
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamps), &(rhs->stamps)))
  {
    return false;
  }
  // mic_channels
  if (lhs->mic_channels != rhs->mic_channels) {
    return false;
  }
  // ref_channels
  if (lhs->ref_channels != rhs->ref_channels) {
    return false;
  }
  // info
  if (!aimdk_msgs__msg__AudioInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // data
  if (!aimdk_msgs__msg__AudioData__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pkg_name), &(rhs->pkg_name)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__AudioCapture__copy(
  const aimdk_msgs__msg__AudioCapture * input,
  aimdk_msgs__msg__AudioCapture * output)
{
  if (!input || !output) {
    return false;
  }
  // stamps
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamps), &(output->stamps)))
  {
    return false;
  }
  // mic_channels
  output->mic_channels = input->mic_channels;
  // ref_channels
  output->ref_channels = input->ref_channels;
  // info
  if (!aimdk_msgs__msg__AudioInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // data
  if (!aimdk_msgs__msg__AudioData__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  // pkg_name
  if (!rosidl_runtime_c__String__copy(
      &(input->pkg_name), &(output->pkg_name)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__msg__AudioCapture *
aimdk_msgs__msg__AudioCapture__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__AudioCapture * msg = (aimdk_msgs__msg__AudioCapture *)allocator.allocate(sizeof(aimdk_msgs__msg__AudioCapture), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__AudioCapture));
  bool success = aimdk_msgs__msg__AudioCapture__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__AudioCapture__destroy(aimdk_msgs__msg__AudioCapture * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__AudioCapture__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__AudioCapture__Sequence__init(aimdk_msgs__msg__AudioCapture__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__AudioCapture * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__AudioCapture *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__AudioCapture), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__AudioCapture__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__AudioCapture__fini(&data[i - 1]);
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
aimdk_msgs__msg__AudioCapture__Sequence__fini(aimdk_msgs__msg__AudioCapture__Sequence * array)
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
      aimdk_msgs__msg__AudioCapture__fini(&array->data[i]);
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

aimdk_msgs__msg__AudioCapture__Sequence *
aimdk_msgs__msg__AudioCapture__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__AudioCapture__Sequence * array = (aimdk_msgs__msg__AudioCapture__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__AudioCapture__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__AudioCapture__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__AudioCapture__Sequence__destroy(aimdk_msgs__msg__AudioCapture__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__AudioCapture__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__AudioCapture__Sequence__are_equal(const aimdk_msgs__msg__AudioCapture__Sequence * lhs, const aimdk_msgs__msg__AudioCapture__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__AudioCapture__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__AudioCapture__Sequence__copy(
  const aimdk_msgs__msg__AudioCapture__Sequence * input,
  aimdk_msgs__msg__AudioCapture__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__AudioCapture);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__AudioCapture * data =
      (aimdk_msgs__msg__AudioCapture *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__AudioCapture__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__AudioCapture__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__AudioCapture__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
