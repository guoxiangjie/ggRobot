// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/hand_command_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__functions.h"
// Member `left_hand_type`
// Member `right_hand_type`
#include "aimdk_msgs/msg/detail/hand_type__functions.h"
// Member `left_hands`
// Member `right_hands`
#include "aimdk_msgs/msg/detail/hand_command__functions.h"

bool
aimdk_msgs__msg__HandCommandArray__init(aimdk_msgs__msg__HandCommandArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__MessageHeader__init(&msg->header)) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
    return false;
  }
  // left_hand_type
  if (!aimdk_msgs__msg__HandType__init(&msg->left_hand_type)) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
    return false;
  }
  // left_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__init(&msg->left_hands, 0)) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
    return false;
  }
  // right_hand_type
  if (!aimdk_msgs__msg__HandType__init(&msg->right_hand_type)) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
    return false;
  }
  // right_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__init(&msg->right_hands, 0)) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__msg__HandCommandArray__fini(aimdk_msgs__msg__HandCommandArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__MessageHeader__fini(&msg->header);
  // left_hand_type
  aimdk_msgs__msg__HandType__fini(&msg->left_hand_type);
  // left_hands
  aimdk_msgs__msg__HandCommand__Sequence__fini(&msg->left_hands);
  // right_hand_type
  aimdk_msgs__msg__HandType__fini(&msg->right_hand_type);
  // right_hands
  aimdk_msgs__msg__HandCommand__Sequence__fini(&msg->right_hands);
}

bool
aimdk_msgs__msg__HandCommandArray__are_equal(const aimdk_msgs__msg__HandCommandArray * lhs, const aimdk_msgs__msg__HandCommandArray * rhs)
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
  // left_hand_type
  if (!aimdk_msgs__msg__HandType__are_equal(
      &(lhs->left_hand_type), &(rhs->left_hand_type)))
  {
    return false;
  }
  // left_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__are_equal(
      &(lhs->left_hands), &(rhs->left_hands)))
  {
    return false;
  }
  // right_hand_type
  if (!aimdk_msgs__msg__HandType__are_equal(
      &(lhs->right_hand_type), &(rhs->right_hand_type)))
  {
    return false;
  }
  // right_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__are_equal(
      &(lhs->right_hands), &(rhs->right_hands)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__HandCommandArray__copy(
  const aimdk_msgs__msg__HandCommandArray * input,
  aimdk_msgs__msg__HandCommandArray * output)
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
  // left_hand_type
  if (!aimdk_msgs__msg__HandType__copy(
      &(input->left_hand_type), &(output->left_hand_type)))
  {
    return false;
  }
  // left_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__copy(
      &(input->left_hands), &(output->left_hands)))
  {
    return false;
  }
  // right_hand_type
  if (!aimdk_msgs__msg__HandType__copy(
      &(input->right_hand_type), &(output->right_hand_type)))
  {
    return false;
  }
  // right_hands
  if (!aimdk_msgs__msg__HandCommand__Sequence__copy(
      &(input->right_hands), &(output->right_hands)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__msg__HandCommandArray *
aimdk_msgs__msg__HandCommandArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommandArray * msg = (aimdk_msgs__msg__HandCommandArray *)allocator.allocate(sizeof(aimdk_msgs__msg__HandCommandArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__HandCommandArray));
  bool success = aimdk_msgs__msg__HandCommandArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__HandCommandArray__destroy(aimdk_msgs__msg__HandCommandArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__HandCommandArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__HandCommandArray__Sequence__init(aimdk_msgs__msg__HandCommandArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommandArray * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__HandCommandArray *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__HandCommandArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__HandCommandArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__HandCommandArray__fini(&data[i - 1]);
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
aimdk_msgs__msg__HandCommandArray__Sequence__fini(aimdk_msgs__msg__HandCommandArray__Sequence * array)
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
      aimdk_msgs__msg__HandCommandArray__fini(&array->data[i]);
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

aimdk_msgs__msg__HandCommandArray__Sequence *
aimdk_msgs__msg__HandCommandArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__HandCommandArray__Sequence * array = (aimdk_msgs__msg__HandCommandArray__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__HandCommandArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__HandCommandArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__HandCommandArray__Sequence__destroy(aimdk_msgs__msg__HandCommandArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__HandCommandArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__HandCommandArray__Sequence__are_equal(const aimdk_msgs__msg__HandCommandArray__Sequence * lhs, const aimdk_msgs__msg__HandCommandArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__HandCommandArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__HandCommandArray__Sequence__copy(
  const aimdk_msgs__msg__HandCommandArray__Sequence * input,
  aimdk_msgs__msg__HandCommandArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__HandCommandArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__HandCommandArray * data =
      (aimdk_msgs__msg__HandCommandArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__HandCommandArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__HandCommandArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__HandCommandArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
