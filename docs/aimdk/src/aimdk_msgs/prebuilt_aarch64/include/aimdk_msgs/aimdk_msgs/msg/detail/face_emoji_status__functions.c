// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/face_emoji_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__functions.h"
// Member `e_path`
// Member `e_path_list`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__FaceEmojiStatus__init(aimdk_msgs__msg__FaceEmojiStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__MessageHeader__init(&msg->header)) {
    aimdk_msgs__msg__FaceEmojiStatus__fini(msg);
    return false;
  }
  // e_path
  if (!rosidl_runtime_c__String__init(&msg->e_path)) {
    aimdk_msgs__msg__FaceEmojiStatus__fini(msg);
    return false;
  }
  // e_path_list
  if (!rosidl_runtime_c__String__Sequence__init(&msg->e_path_list, 0)) {
    aimdk_msgs__msg__FaceEmojiStatus__fini(msg);
    return false;
  }
  // e_id
  // mode
  // priority
  // status
  // time_to_end_ms
  return true;
}

void
aimdk_msgs__msg__FaceEmojiStatus__fini(aimdk_msgs__msg__FaceEmojiStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__MessageHeader__fini(&msg->header);
  // e_path
  rosidl_runtime_c__String__fini(&msg->e_path);
  // e_path_list
  rosidl_runtime_c__String__Sequence__fini(&msg->e_path_list);
  // e_id
  // mode
  // priority
  // status
  // time_to_end_ms
}

bool
aimdk_msgs__msg__FaceEmojiStatus__are_equal(const aimdk_msgs__msg__FaceEmojiStatus * lhs, const aimdk_msgs__msg__FaceEmojiStatus * rhs)
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
  // e_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->e_path), &(rhs->e_path)))
  {
    return false;
  }
  // e_path_list
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->e_path_list), &(rhs->e_path_list)))
  {
    return false;
  }
  // e_id
  if (lhs->e_id != rhs->e_id) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // priority
  if (lhs->priority != rhs->priority) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // time_to_end_ms
  if (lhs->time_to_end_ms != rhs->time_to_end_ms) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__FaceEmojiStatus__copy(
  const aimdk_msgs__msg__FaceEmojiStatus * input,
  aimdk_msgs__msg__FaceEmojiStatus * output)
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
  // e_path
  if (!rosidl_runtime_c__String__copy(
      &(input->e_path), &(output->e_path)))
  {
    return false;
  }
  // e_path_list
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->e_path_list), &(output->e_path_list)))
  {
    return false;
  }
  // e_id
  output->e_id = input->e_id;
  // mode
  output->mode = input->mode;
  // priority
  output->priority = input->priority;
  // status
  output->status = input->status;
  // time_to_end_ms
  output->time_to_end_ms = input->time_to_end_ms;
  return true;
}

aimdk_msgs__msg__FaceEmojiStatus *
aimdk_msgs__msg__FaceEmojiStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FaceEmojiStatus * msg = (aimdk_msgs__msg__FaceEmojiStatus *)allocator.allocate(sizeof(aimdk_msgs__msg__FaceEmojiStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__FaceEmojiStatus));
  bool success = aimdk_msgs__msg__FaceEmojiStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__FaceEmojiStatus__destroy(aimdk_msgs__msg__FaceEmojiStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__FaceEmojiStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__FaceEmojiStatus__Sequence__init(aimdk_msgs__msg__FaceEmojiStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FaceEmojiStatus * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__FaceEmojiStatus *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__FaceEmojiStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__FaceEmojiStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__FaceEmojiStatus__fini(&data[i - 1]);
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
aimdk_msgs__msg__FaceEmojiStatus__Sequence__fini(aimdk_msgs__msg__FaceEmojiStatus__Sequence * array)
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
      aimdk_msgs__msg__FaceEmojiStatus__fini(&array->data[i]);
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

aimdk_msgs__msg__FaceEmojiStatus__Sequence *
aimdk_msgs__msg__FaceEmojiStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__FaceEmojiStatus__Sequence * array = (aimdk_msgs__msg__FaceEmojiStatus__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__FaceEmojiStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__FaceEmojiStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__FaceEmojiStatus__Sequence__destroy(aimdk_msgs__msg__FaceEmojiStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__FaceEmojiStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__FaceEmojiStatus__Sequence__are_equal(const aimdk_msgs__msg__FaceEmojiStatus__Sequence * lhs, const aimdk_msgs__msg__FaceEmojiStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__FaceEmojiStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__FaceEmojiStatus__Sequence__copy(
  const aimdk_msgs__msg__FaceEmojiStatus__Sequence * input,
  aimdk_msgs__msg__FaceEmojiStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__FaceEmojiStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__FaceEmojiStatus * data =
      (aimdk_msgs__msg__FaceEmojiStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__FaceEmojiStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__FaceEmojiStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__FaceEmojiStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
