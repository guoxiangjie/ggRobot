// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/CommonResponse.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/common_response__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/response_header__functions.h"
// Member `status`
#include "aimdk_msgs/msg/detail/common_state__functions.h"
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__msg__CommonResponse__init(aimdk_msgs__msg__CommonResponse * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__init(&msg->header)) {
    aimdk_msgs__msg__CommonResponse__fini(msg);
    return false;
  }
  // status
  if (!aimdk_msgs__msg__CommonState__init(&msg->status)) {
    aimdk_msgs__msg__CommonResponse__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    aimdk_msgs__msg__CommonResponse__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__msg__CommonResponse__fini(aimdk_msgs__msg__CommonResponse * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__ResponseHeader__fini(&msg->header);
  // status
  aimdk_msgs__msg__CommonState__fini(&msg->status);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
aimdk_msgs__msg__CommonResponse__are_equal(const aimdk_msgs__msg__CommonResponse * lhs, const aimdk_msgs__msg__CommonResponse * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // status
  if (!aimdk_msgs__msg__CommonState__are_equal(
      &(lhs->status), &(rhs->status)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__CommonResponse__copy(
  const aimdk_msgs__msg__CommonResponse * input,
  aimdk_msgs__msg__CommonResponse * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__ResponseHeader__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // status
  if (!aimdk_msgs__msg__CommonState__copy(
      &(input->status), &(output->status)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__msg__CommonResponse *
aimdk_msgs__msg__CommonResponse__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__CommonResponse * msg = (aimdk_msgs__msg__CommonResponse *)allocator.allocate(sizeof(aimdk_msgs__msg__CommonResponse), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__CommonResponse));
  bool success = aimdk_msgs__msg__CommonResponse__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__CommonResponse__destroy(aimdk_msgs__msg__CommonResponse * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__CommonResponse__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__CommonResponse__Sequence__init(aimdk_msgs__msg__CommonResponse__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__CommonResponse * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__CommonResponse *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__CommonResponse), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__CommonResponse__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__CommonResponse__fini(&data[i - 1]);
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
aimdk_msgs__msg__CommonResponse__Sequence__fini(aimdk_msgs__msg__CommonResponse__Sequence * array)
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
      aimdk_msgs__msg__CommonResponse__fini(&array->data[i]);
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

aimdk_msgs__msg__CommonResponse__Sequence *
aimdk_msgs__msg__CommonResponse__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__CommonResponse__Sequence * array = (aimdk_msgs__msg__CommonResponse__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__CommonResponse__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__CommonResponse__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__CommonResponse__Sequence__destroy(aimdk_msgs__msg__CommonResponse__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__CommonResponse__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__CommonResponse__Sequence__are_equal(const aimdk_msgs__msg__CommonResponse__Sequence * lhs, const aimdk_msgs__msg__CommonResponse__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__CommonResponse__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__CommonResponse__Sequence__copy(
  const aimdk_msgs__msg__CommonResponse__Sequence * input,
  aimdk_msgs__msg__CommonResponse__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__CommonResponse);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__CommonResponse * data =
      (aimdk_msgs__msg__CommonResponse *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__CommonResponse__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__CommonResponse__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__CommonResponse__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
