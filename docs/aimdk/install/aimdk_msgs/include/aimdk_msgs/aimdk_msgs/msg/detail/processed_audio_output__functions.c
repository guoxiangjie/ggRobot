// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/processed_audio_output__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__functions.h"
// Member `audio_vad_state`
#include "aimdk_msgs/msg/detail/audio_vad_state_type__functions.h"
// Member `audio_data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
aimdk_msgs__msg__ProcessedAudioOutput__init(aimdk_msgs__msg__ProcessedAudioOutput * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__MessageHeader__init(&msg->header)) {
    aimdk_msgs__msg__ProcessedAudioOutput__fini(msg);
    return false;
  }
  // stream_id
  // audio_vad_state
  if (!aimdk_msgs__msg__AudioVadStateType__init(&msg->audio_vad_state)) {
    aimdk_msgs__msg__ProcessedAudioOutput__fini(msg);
    return false;
  }
  // audio_data
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->audio_data, 0)) {
    aimdk_msgs__msg__ProcessedAudioOutput__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__msg__ProcessedAudioOutput__fini(aimdk_msgs__msg__ProcessedAudioOutput * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__MessageHeader__fini(&msg->header);
  // stream_id
  // audio_vad_state
  aimdk_msgs__msg__AudioVadStateType__fini(&msg->audio_vad_state);
  // audio_data
  rosidl_runtime_c__uint8__Sequence__fini(&msg->audio_data);
}

bool
aimdk_msgs__msg__ProcessedAudioOutput__are_equal(const aimdk_msgs__msg__ProcessedAudioOutput * lhs, const aimdk_msgs__msg__ProcessedAudioOutput * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__MessageHeader__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // stream_id
  if (lhs->stream_id != rhs->stream_id) {
    return false;
  }
  // audio_vad_state
  if (!aimdk_msgs__msg__AudioVadStateType__are_equal(
      &(lhs->audio_vad_state), &(rhs->audio_vad_state)))
  {
    return false;
  }
  // audio_data
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->audio_data), &(rhs->audio_data)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__ProcessedAudioOutput__copy(
  const aimdk_msgs__msg__ProcessedAudioOutput * input,
  aimdk_msgs__msg__ProcessedAudioOutput * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__MessageHeader__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // stream_id
  output->stream_id = input->stream_id;
  // audio_vad_state
  if (!aimdk_msgs__msg__AudioVadStateType__copy(
      &(input->audio_vad_state), &(output->audio_vad_state)))
  {
    return false;
  }
  // audio_data
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->audio_data), &(output->audio_data)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__msg__ProcessedAudioOutput *
aimdk_msgs__msg__ProcessedAudioOutput__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__ProcessedAudioOutput * msg = (aimdk_msgs__msg__ProcessedAudioOutput *)allocator.allocate(sizeof(aimdk_msgs__msg__ProcessedAudioOutput), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__ProcessedAudioOutput));
  bool success = aimdk_msgs__msg__ProcessedAudioOutput__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__ProcessedAudioOutput__destroy(aimdk_msgs__msg__ProcessedAudioOutput * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__ProcessedAudioOutput__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__init(aimdk_msgs__msg__ProcessedAudioOutput__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__ProcessedAudioOutput * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__ProcessedAudioOutput *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__ProcessedAudioOutput), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__ProcessedAudioOutput__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__ProcessedAudioOutput__fini(&data[i - 1]);
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
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__fini(aimdk_msgs__msg__ProcessedAudioOutput__Sequence * array)
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
      aimdk_msgs__msg__ProcessedAudioOutput__fini(&array->data[i]);
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

aimdk_msgs__msg__ProcessedAudioOutput__Sequence *
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__ProcessedAudioOutput__Sequence * array = (aimdk_msgs__msg__ProcessedAudioOutput__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__ProcessedAudioOutput__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__ProcessedAudioOutput__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__destroy(aimdk_msgs__msg__ProcessedAudioOutput__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__ProcessedAudioOutput__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__are_equal(const aimdk_msgs__msg__ProcessedAudioOutput__Sequence * lhs, const aimdk_msgs__msg__ProcessedAudioOutput__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__ProcessedAudioOutput__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__ProcessedAudioOutput__Sequence__copy(
  const aimdk_msgs__msg__ProcessedAudioOutput__Sequence * input,
  aimdk_msgs__msg__ProcessedAudioOutput__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__ProcessedAudioOutput);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__ProcessedAudioOutput * data =
      (aimdk_msgs__msg__ProcessedAudioOutput *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__ProcessedAudioOutput__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__ProcessedAudioOutput__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__ProcessedAudioOutput__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
