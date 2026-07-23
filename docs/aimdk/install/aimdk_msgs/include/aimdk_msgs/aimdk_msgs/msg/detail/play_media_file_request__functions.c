// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/PlayMediaFileRequest.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/play_media_file_request__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `file_name`
// Member `domain`
// Member `trace_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `priority_level`
#include "aimdk_msgs/msg/detail/tts_priority_level__functions.h"

bool
aimdk_msgs__msg__PlayMediaFileRequest__init(aimdk_msgs__msg__PlayMediaFileRequest * msg)
{
  if (!msg) {
    return false;
  }
  // file_name
  if (!rosidl_runtime_c__String__init(&msg->file_name)) {
    aimdk_msgs__msg__PlayMediaFileRequest__fini(msg);
    return false;
  }
  // sample_rate
  // priority_level
  if (!aimdk_msgs__msg__TtsPriorityLevel__init(&msg->priority_level)) {
    aimdk_msgs__msg__PlayMediaFileRequest__fini(msg);
    return false;
  }
  // priority_weight
  // domain
  if (!rosidl_runtime_c__String__init(&msg->domain)) {
    aimdk_msgs__msg__PlayMediaFileRequest__fini(msg);
    return false;
  }
  // trace_id
  if (!rosidl_runtime_c__String__init(&msg->trace_id)) {
    aimdk_msgs__msg__PlayMediaFileRequest__fini(msg);
    return false;
  }
  // is_interrupted
  return true;
}

void
aimdk_msgs__msg__PlayMediaFileRequest__fini(aimdk_msgs__msg__PlayMediaFileRequest * msg)
{
  if (!msg) {
    return;
  }
  // file_name
  rosidl_runtime_c__String__fini(&msg->file_name);
  // sample_rate
  // priority_level
  aimdk_msgs__msg__TtsPriorityLevel__fini(&msg->priority_level);
  // priority_weight
  // domain
  rosidl_runtime_c__String__fini(&msg->domain);
  // trace_id
  rosidl_runtime_c__String__fini(&msg->trace_id);
  // is_interrupted
}

bool
aimdk_msgs__msg__PlayMediaFileRequest__are_equal(const aimdk_msgs__msg__PlayMediaFileRequest * lhs, const aimdk_msgs__msg__PlayMediaFileRequest * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // file_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->file_name), &(rhs->file_name)))
  {
    return false;
  }
  // sample_rate
  if (lhs->sample_rate != rhs->sample_rate) {
    return false;
  }
  // priority_level
  if (!aimdk_msgs__msg__TtsPriorityLevel__are_equal(
      &(lhs->priority_level), &(rhs->priority_level)))
  {
    return false;
  }
  // priority_weight
  if (lhs->priority_weight != rhs->priority_weight) {
    return false;
  }
  // domain
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->domain), &(rhs->domain)))
  {
    return false;
  }
  // trace_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->trace_id), &(rhs->trace_id)))
  {
    return false;
  }
  // is_interrupted
  if (lhs->is_interrupted != rhs->is_interrupted) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__PlayMediaFileRequest__copy(
  const aimdk_msgs__msg__PlayMediaFileRequest * input,
  aimdk_msgs__msg__PlayMediaFileRequest * output)
{
  if (!input || !output) {
    return false;
  }
  // file_name
  if (!rosidl_runtime_c__String__copy(
      &(input->file_name), &(output->file_name)))
  {
    return false;
  }
  // sample_rate
  output->sample_rate = input->sample_rate;
  // priority_level
  if (!aimdk_msgs__msg__TtsPriorityLevel__copy(
      &(input->priority_level), &(output->priority_level)))
  {
    return false;
  }
  // priority_weight
  output->priority_weight = input->priority_weight;
  // domain
  if (!rosidl_runtime_c__String__copy(
      &(input->domain), &(output->domain)))
  {
    return false;
  }
  // trace_id
  if (!rosidl_runtime_c__String__copy(
      &(input->trace_id), &(output->trace_id)))
  {
    return false;
  }
  // is_interrupted
  output->is_interrupted = input->is_interrupted;
  return true;
}

aimdk_msgs__msg__PlayMediaFileRequest *
aimdk_msgs__msg__PlayMediaFileRequest__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PlayMediaFileRequest * msg = (aimdk_msgs__msg__PlayMediaFileRequest *)allocator.allocate(sizeof(aimdk_msgs__msg__PlayMediaFileRequest), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__PlayMediaFileRequest));
  bool success = aimdk_msgs__msg__PlayMediaFileRequest__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__PlayMediaFileRequest__destroy(aimdk_msgs__msg__PlayMediaFileRequest * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__PlayMediaFileRequest__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__init(aimdk_msgs__msg__PlayMediaFileRequest__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PlayMediaFileRequest * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__PlayMediaFileRequest *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__PlayMediaFileRequest), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__PlayMediaFileRequest__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__PlayMediaFileRequest__fini(&data[i - 1]);
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
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__fini(aimdk_msgs__msg__PlayMediaFileRequest__Sequence * array)
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
      aimdk_msgs__msg__PlayMediaFileRequest__fini(&array->data[i]);
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

aimdk_msgs__msg__PlayMediaFileRequest__Sequence *
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__PlayMediaFileRequest__Sequence * array = (aimdk_msgs__msg__PlayMediaFileRequest__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__PlayMediaFileRequest__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__PlayMediaFileRequest__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__destroy(aimdk_msgs__msg__PlayMediaFileRequest__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__PlayMediaFileRequest__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__are_equal(const aimdk_msgs__msg__PlayMediaFileRequest__Sequence * lhs, const aimdk_msgs__msg__PlayMediaFileRequest__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__PlayMediaFileRequest__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__PlayMediaFileRequest__Sequence__copy(
  const aimdk_msgs__msg__PlayMediaFileRequest__Sequence * input,
  aimdk_msgs__msg__PlayMediaFileRequest__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__PlayMediaFileRequest);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__PlayMediaFileRequest * data =
      (aimdk_msgs__msg__PlayMediaFileRequest *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__PlayMediaFileRequest__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__PlayMediaFileRequest__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__PlayMediaFileRequest__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
