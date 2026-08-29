// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:srv/ExecuteActionResource.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/srv/detail/execute_action_resource__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/common_request__functions.h"
// Member `resource_key`
// Member `resource_version`
// Member `meta`
#include "rosidl_runtime_c/string_functions.h"
// Member `slaves`
#include "aimdk_msgs/msg/detail/slave_device__functions.h"

bool
aimdk_msgs__srv__ExecuteActionResource_Request__init(aimdk_msgs__srv__ExecuteActionResource_Request * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonRequest__init(&msg->header)) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
    return false;
  }
  // resource_key
  if (!rosidl_runtime_c__String__init(&msg->resource_key)) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
    return false;
  }
  // resource_version
  if (!rosidl_runtime_c__String__init(&msg->resource_version)) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
    return false;
  }
  // slaves
  if (!aimdk_msgs__msg__SlaveDevice__Sequence__init(&msg->slaves, 0)) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
    return false;
  }
  // meta
  if (!rosidl_runtime_c__String__init(&msg->meta)) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__srv__ExecuteActionResource_Request__fini(aimdk_msgs__srv__ExecuteActionResource_Request * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__CommonRequest__fini(&msg->header);
  // resource_key
  rosidl_runtime_c__String__fini(&msg->resource_key);
  // resource_version
  rosidl_runtime_c__String__fini(&msg->resource_version);
  // slaves
  aimdk_msgs__msg__SlaveDevice__Sequence__fini(&msg->slaves);
  // meta
  rosidl_runtime_c__String__fini(&msg->meta);
}

bool
aimdk_msgs__srv__ExecuteActionResource_Request__are_equal(const aimdk_msgs__srv__ExecuteActionResource_Request * lhs, const aimdk_msgs__srv__ExecuteActionResource_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonRequest__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // resource_key
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->resource_key), &(rhs->resource_key)))
  {
    return false;
  }
  // resource_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->resource_version), &(rhs->resource_version)))
  {
    return false;
  }
  // slaves
  if (!aimdk_msgs__msg__SlaveDevice__Sequence__are_equal(
      &(lhs->slaves), &(rhs->slaves)))
  {
    return false;
  }
  // meta
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->meta), &(rhs->meta)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__ExecuteActionResource_Request__copy(
  const aimdk_msgs__srv__ExecuteActionResource_Request * input,
  aimdk_msgs__srv__ExecuteActionResource_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonRequest__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // resource_key
  if (!rosidl_runtime_c__String__copy(
      &(input->resource_key), &(output->resource_key)))
  {
    return false;
  }
  // resource_version
  if (!rosidl_runtime_c__String__copy(
      &(input->resource_version), &(output->resource_version)))
  {
    return false;
  }
  // slaves
  if (!aimdk_msgs__msg__SlaveDevice__Sequence__copy(
      &(input->slaves), &(output->slaves)))
  {
    return false;
  }
  // meta
  if (!rosidl_runtime_c__String__copy(
      &(input->meta), &(output->meta)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__srv__ExecuteActionResource_Request *
aimdk_msgs__srv__ExecuteActionResource_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Request * msg = (aimdk_msgs__srv__ExecuteActionResource_Request *)allocator.allocate(sizeof(aimdk_msgs__srv__ExecuteActionResource_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__ExecuteActionResource_Request));
  bool success = aimdk_msgs__srv__ExecuteActionResource_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__ExecuteActionResource_Request__destroy(aimdk_msgs__srv__ExecuteActionResource_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__ExecuteActionResource_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__init(aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Request * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__ExecuteActionResource_Request *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__ExecuteActionResource_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__ExecuteActionResource_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__ExecuteActionResource_Request__fini(&data[i - 1]);
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
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__fini(aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * array)
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
      aimdk_msgs__srv__ExecuteActionResource_Request__fini(&array->data[i]);
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

aimdk_msgs__srv__ExecuteActionResource_Request__Sequence *
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * array = (aimdk_msgs__srv__ExecuteActionResource_Request__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__ExecuteActionResource_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__destroy(aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__are_equal(const aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * lhs, const aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__ExecuteActionResource_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__ExecuteActionResource_Request__Sequence__copy(
  const aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * input,
  aimdk_msgs__srv__ExecuteActionResource_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__ExecuteActionResource_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__ExecuteActionResource_Request * data =
      (aimdk_msgs__srv__ExecuteActionResource_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__ExecuteActionResource_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__ExecuteActionResource_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__ExecuteActionResource_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/detail/common_response__functions.h"

bool
aimdk_msgs__srv__ExecuteActionResource_Response__init(aimdk_msgs__srv__ExecuteActionResource_Response * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonResponse__init(&msg->header)) {
    aimdk_msgs__srv__ExecuteActionResource_Response__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__srv__ExecuteActionResource_Response__fini(aimdk_msgs__srv__ExecuteActionResource_Response * msg)
{
  if (!msg) {
    return;
  }
  // header
  aimdk_msgs__msg__CommonResponse__fini(&msg->header);
}

bool
aimdk_msgs__srv__ExecuteActionResource_Response__are_equal(const aimdk_msgs__srv__ExecuteActionResource_Response * lhs, const aimdk_msgs__srv__ExecuteActionResource_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonResponse__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__ExecuteActionResource_Response__copy(
  const aimdk_msgs__srv__ExecuteActionResource_Response * input,
  aimdk_msgs__srv__ExecuteActionResource_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!aimdk_msgs__msg__CommonResponse__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__srv__ExecuteActionResource_Response *
aimdk_msgs__srv__ExecuteActionResource_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Response * msg = (aimdk_msgs__srv__ExecuteActionResource_Response *)allocator.allocate(sizeof(aimdk_msgs__srv__ExecuteActionResource_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__ExecuteActionResource_Response));
  bool success = aimdk_msgs__srv__ExecuteActionResource_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__ExecuteActionResource_Response__destroy(aimdk_msgs__srv__ExecuteActionResource_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__ExecuteActionResource_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__init(aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Response * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__ExecuteActionResource_Response *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__ExecuteActionResource_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__ExecuteActionResource_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__ExecuteActionResource_Response__fini(&data[i - 1]);
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
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__fini(aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * array)
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
      aimdk_msgs__srv__ExecuteActionResource_Response__fini(&array->data[i]);
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

aimdk_msgs__srv__ExecuteActionResource_Response__Sequence *
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * array = (aimdk_msgs__srv__ExecuteActionResource_Response__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__ExecuteActionResource_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__destroy(aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__are_equal(const aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * lhs, const aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__ExecuteActionResource_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__ExecuteActionResource_Response__Sequence__copy(
  const aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * input,
  aimdk_msgs__srv__ExecuteActionResource_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__ExecuteActionResource_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__ExecuteActionResource_Response * data =
      (aimdk_msgs__srv__ExecuteActionResource_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__ExecuteActionResource_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__ExecuteActionResource_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__ExecuteActionResource_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
