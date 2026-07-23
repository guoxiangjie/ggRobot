// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:msg/RobotResourceMapping.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/msg/detail/robot_resource_mapping__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `robot_ip`
#include "rosidl_runtime_c/string_functions.h"
// Member `robot_resource_list`
#include "aimdk_msgs/msg/detail/robot_resource__functions.h"

bool
aimdk_msgs__msg__RobotResourceMapping__init(aimdk_msgs__msg__RobotResourceMapping * msg)
{
  if (!msg) {
    return false;
  }
  // is_master
  // robot_ip
  if (!rosidl_runtime_c__String__init(&msg->robot_ip)) {
    aimdk_msgs__msg__RobotResourceMapping__fini(msg);
    return false;
  }
  // robot_resource_list
  if (!aimdk_msgs__msg__RobotResource__Sequence__init(&msg->robot_resource_list, 0)) {
    aimdk_msgs__msg__RobotResourceMapping__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__msg__RobotResourceMapping__fini(aimdk_msgs__msg__RobotResourceMapping * msg)
{
  if (!msg) {
    return;
  }
  // is_master
  // robot_ip
  rosidl_runtime_c__String__fini(&msg->robot_ip);
  // robot_resource_list
  aimdk_msgs__msg__RobotResource__Sequence__fini(&msg->robot_resource_list);
}

bool
aimdk_msgs__msg__RobotResourceMapping__are_equal(const aimdk_msgs__msg__RobotResourceMapping * lhs, const aimdk_msgs__msg__RobotResourceMapping * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_master
  if (lhs->is_master != rhs->is_master) {
    return false;
  }
  // robot_ip
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_ip), &(rhs->robot_ip)))
  {
    return false;
  }
  // robot_resource_list
  if (!aimdk_msgs__msg__RobotResource__Sequence__are_equal(
      &(lhs->robot_resource_list), &(rhs->robot_resource_list)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__msg__RobotResourceMapping__copy(
  const aimdk_msgs__msg__RobotResourceMapping * input,
  aimdk_msgs__msg__RobotResourceMapping * output)
{
  if (!input || !output) {
    return false;
  }
  // is_master
  output->is_master = input->is_master;
  // robot_ip
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_ip), &(output->robot_ip)))
  {
    return false;
  }
  // robot_resource_list
  if (!aimdk_msgs__msg__RobotResource__Sequence__copy(
      &(input->robot_resource_list), &(output->robot_resource_list)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__msg__RobotResourceMapping *
aimdk_msgs__msg__RobotResourceMapping__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__RobotResourceMapping * msg = (aimdk_msgs__msg__RobotResourceMapping *)allocator.allocate(sizeof(aimdk_msgs__msg__RobotResourceMapping), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__msg__RobotResourceMapping));
  bool success = aimdk_msgs__msg__RobotResourceMapping__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__msg__RobotResourceMapping__destroy(aimdk_msgs__msg__RobotResourceMapping * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__msg__RobotResourceMapping__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__msg__RobotResourceMapping__Sequence__init(aimdk_msgs__msg__RobotResourceMapping__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__RobotResourceMapping * data = NULL;

  if (size) {
    data = (aimdk_msgs__msg__RobotResourceMapping *)allocator.zero_allocate(size, sizeof(aimdk_msgs__msg__RobotResourceMapping), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__msg__RobotResourceMapping__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__msg__RobotResourceMapping__fini(&data[i - 1]);
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
aimdk_msgs__msg__RobotResourceMapping__Sequence__fini(aimdk_msgs__msg__RobotResourceMapping__Sequence * array)
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
      aimdk_msgs__msg__RobotResourceMapping__fini(&array->data[i]);
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

aimdk_msgs__msg__RobotResourceMapping__Sequence *
aimdk_msgs__msg__RobotResourceMapping__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__msg__RobotResourceMapping__Sequence * array = (aimdk_msgs__msg__RobotResourceMapping__Sequence *)allocator.allocate(sizeof(aimdk_msgs__msg__RobotResourceMapping__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__msg__RobotResourceMapping__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__msg__RobotResourceMapping__Sequence__destroy(aimdk_msgs__msg__RobotResourceMapping__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__msg__RobotResourceMapping__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__msg__RobotResourceMapping__Sequence__are_equal(const aimdk_msgs__msg__RobotResourceMapping__Sequence * lhs, const aimdk_msgs__msg__RobotResourceMapping__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__msg__RobotResourceMapping__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__msg__RobotResourceMapping__Sequence__copy(
  const aimdk_msgs__msg__RobotResourceMapping__Sequence * input,
  aimdk_msgs__msg__RobotResourceMapping__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__msg__RobotResourceMapping);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__msg__RobotResourceMapping * data =
      (aimdk_msgs__msg__RobotResourceMapping *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__msg__RobotResourceMapping__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__msg__RobotResourceMapping__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__msg__RobotResourceMapping__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
