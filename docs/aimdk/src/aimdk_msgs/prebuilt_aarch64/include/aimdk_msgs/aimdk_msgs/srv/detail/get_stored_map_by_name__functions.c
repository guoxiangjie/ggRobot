// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `map_name`
#include "rosidl_runtime_c/string_functions.h"

bool
aimdk_msgs__srv__GetStoredMapByName_Request__init(aimdk_msgs__srv__GetStoredMapByName_Request * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    aimdk_msgs__srv__GetStoredMapByName_Request__fini(msg);
    return false;
  }
  // map_name
  if (!rosidl_runtime_c__String__init(&msg->map_name)) {
    aimdk_msgs__srv__GetStoredMapByName_Request__fini(msg);
    return false;
  }
  return true;
}

void
aimdk_msgs__srv__GetStoredMapByName_Request__fini(aimdk_msgs__srv__GetStoredMapByName_Request * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // map_name
  rosidl_runtime_c__String__fini(&msg->map_name);
}

bool
aimdk_msgs__srv__GetStoredMapByName_Request__are_equal(const aimdk_msgs__srv__GetStoredMapByName_Request * lhs, const aimdk_msgs__srv__GetStoredMapByName_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // map_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_name), &(rhs->map_name)))
  {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__GetStoredMapByName_Request__copy(
  const aimdk_msgs__srv__GetStoredMapByName_Request * input,
  aimdk_msgs__srv__GetStoredMapByName_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // map_name
  if (!rosidl_runtime_c__String__copy(
      &(input->map_name), &(output->map_name)))
  {
    return false;
  }
  return true;
}

aimdk_msgs__srv__GetStoredMapByName_Request *
aimdk_msgs__srv__GetStoredMapByName_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Request * msg = (aimdk_msgs__srv__GetStoredMapByName_Request *)allocator.allocate(sizeof(aimdk_msgs__srv__GetStoredMapByName_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__GetStoredMapByName_Request));
  bool success = aimdk_msgs__srv__GetStoredMapByName_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__GetStoredMapByName_Request__destroy(aimdk_msgs__srv__GetStoredMapByName_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__GetStoredMapByName_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__init(aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Request * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__GetStoredMapByName_Request *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__GetStoredMapByName_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__GetStoredMapByName_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__GetStoredMapByName_Request__fini(&data[i - 1]);
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
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__fini(aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * array)
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
      aimdk_msgs__srv__GetStoredMapByName_Request__fini(&array->data[i]);
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

aimdk_msgs__srv__GetStoredMapByName_Request__Sequence *
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * array = (aimdk_msgs__srv__GetStoredMapByName_Request__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__GetStoredMapByName_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__destroy(aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__are_equal(const aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * lhs, const aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__GetStoredMapByName_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__GetStoredMapByName_Request__Sequence__copy(
  const aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * input,
  aimdk_msgs__srv__GetStoredMapByName_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__GetStoredMapByName_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__GetStoredMapByName_Request * data =
      (aimdk_msgs__srv__GetStoredMapByName_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__GetStoredMapByName_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__GetStoredMapByName_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__GetStoredMapByName_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `header`
// already included above
// #include "std_msgs/msg/detail/header__functions.h"
// Member `map_info`
#include "nav_msgs/msg/detail/map_meta_data__functions.h"
// Member `map_path`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `navi_points`
#include "aimdk_msgs/msg/detail/navi_point__functions.h"
// Member `qr_points`
#include "aimdk_msgs/msg/detail/qr_point__functions.h"
// Member `hr_points`
#include "aimdk_msgs/msg/detail/hr_point__functions.h"
// Member `paths`
#include "aimdk_msgs/msg/detail/path__functions.h"
// Member `regions`
#include "aimdk_msgs/msg/detail/region__functions.h"

bool
aimdk_msgs__srv__GetStoredMapByName_Response__init(aimdk_msgs__srv__GetStoredMapByName_Response * msg)
{
  if (!msg) {
    return false;
  }
  // code
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // map_info
  if (!nav_msgs__msg__MapMetaData__init(&msg->map_info)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // map_version
  // map_path
  if (!rosidl_runtime_c__String__init(&msg->map_path)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // data
  if (!rosidl_runtime_c__int8__Sequence__init(&msg->data, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // navi_points
  if (!aimdk_msgs__msg__NaviPoint__Sequence__init(&msg->navi_points, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // qr_points
  if (!aimdk_msgs__msg__QRPoint__Sequence__init(&msg->qr_points, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // hr_points
  if (!aimdk_msgs__msg__HRPoint__Sequence__init(&msg->hr_points, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // paths
  if (!aimdk_msgs__msg__Path__Sequence__init(&msg->paths, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // regions
  if (!aimdk_msgs__msg__Region__Sequence__init(&msg->regions, 0)) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
    return false;
  }
  // map_id
  return true;
}

void
aimdk_msgs__srv__GetStoredMapByName_Response__fini(aimdk_msgs__srv__GetStoredMapByName_Response * msg)
{
  if (!msg) {
    return;
  }
  // code
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // map_info
  nav_msgs__msg__MapMetaData__fini(&msg->map_info);
  // map_version
  // map_path
  rosidl_runtime_c__String__fini(&msg->map_path);
  // data
  rosidl_runtime_c__int8__Sequence__fini(&msg->data);
  // navi_points
  aimdk_msgs__msg__NaviPoint__Sequence__fini(&msg->navi_points);
  // qr_points
  aimdk_msgs__msg__QRPoint__Sequence__fini(&msg->qr_points);
  // hr_points
  aimdk_msgs__msg__HRPoint__Sequence__fini(&msg->hr_points);
  // paths
  aimdk_msgs__msg__Path__Sequence__fini(&msg->paths);
  // regions
  aimdk_msgs__msg__Region__Sequence__fini(&msg->regions);
  // map_id
}

bool
aimdk_msgs__srv__GetStoredMapByName_Response__are_equal(const aimdk_msgs__srv__GetStoredMapByName_Response * lhs, const aimdk_msgs__srv__GetStoredMapByName_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // code
  if (lhs->code != rhs->code) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // map_info
  if (!nav_msgs__msg__MapMetaData__are_equal(
      &(lhs->map_info), &(rhs->map_info)))
  {
    return false;
  }
  // map_version
  if (lhs->map_version != rhs->map_version) {
    return false;
  }
  // map_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_path), &(rhs->map_path)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__int8__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  // navi_points
  if (!aimdk_msgs__msg__NaviPoint__Sequence__are_equal(
      &(lhs->navi_points), &(rhs->navi_points)))
  {
    return false;
  }
  // qr_points
  if (!aimdk_msgs__msg__QRPoint__Sequence__are_equal(
      &(lhs->qr_points), &(rhs->qr_points)))
  {
    return false;
  }
  // hr_points
  if (!aimdk_msgs__msg__HRPoint__Sequence__are_equal(
      &(lhs->hr_points), &(rhs->hr_points)))
  {
    return false;
  }
  // paths
  if (!aimdk_msgs__msg__Path__Sequence__are_equal(
      &(lhs->paths), &(rhs->paths)))
  {
    return false;
  }
  // regions
  if (!aimdk_msgs__msg__Region__Sequence__are_equal(
      &(lhs->regions), &(rhs->regions)))
  {
    return false;
  }
  // map_id
  if (lhs->map_id != rhs->map_id) {
    return false;
  }
  return true;
}

bool
aimdk_msgs__srv__GetStoredMapByName_Response__copy(
  const aimdk_msgs__srv__GetStoredMapByName_Response * input,
  aimdk_msgs__srv__GetStoredMapByName_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // code
  output->code = input->code;
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // map_info
  if (!nav_msgs__msg__MapMetaData__copy(
      &(input->map_info), &(output->map_info)))
  {
    return false;
  }
  // map_version
  output->map_version = input->map_version;
  // map_path
  if (!rosidl_runtime_c__String__copy(
      &(input->map_path), &(output->map_path)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__int8__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  // navi_points
  if (!aimdk_msgs__msg__NaviPoint__Sequence__copy(
      &(input->navi_points), &(output->navi_points)))
  {
    return false;
  }
  // qr_points
  if (!aimdk_msgs__msg__QRPoint__Sequence__copy(
      &(input->qr_points), &(output->qr_points)))
  {
    return false;
  }
  // hr_points
  if (!aimdk_msgs__msg__HRPoint__Sequence__copy(
      &(input->hr_points), &(output->hr_points)))
  {
    return false;
  }
  // paths
  if (!aimdk_msgs__msg__Path__Sequence__copy(
      &(input->paths), &(output->paths)))
  {
    return false;
  }
  // regions
  if (!aimdk_msgs__msg__Region__Sequence__copy(
      &(input->regions), &(output->regions)))
  {
    return false;
  }
  // map_id
  output->map_id = input->map_id;
  return true;
}

aimdk_msgs__srv__GetStoredMapByName_Response *
aimdk_msgs__srv__GetStoredMapByName_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Response * msg = (aimdk_msgs__srv__GetStoredMapByName_Response *)allocator.allocate(sizeof(aimdk_msgs__srv__GetStoredMapByName_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(aimdk_msgs__srv__GetStoredMapByName_Response));
  bool success = aimdk_msgs__srv__GetStoredMapByName_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
aimdk_msgs__srv__GetStoredMapByName_Response__destroy(aimdk_msgs__srv__GetStoredMapByName_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    aimdk_msgs__srv__GetStoredMapByName_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__init(aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Response * data = NULL;

  if (size) {
    data = (aimdk_msgs__srv__GetStoredMapByName_Response *)allocator.zero_allocate(size, sizeof(aimdk_msgs__srv__GetStoredMapByName_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = aimdk_msgs__srv__GetStoredMapByName_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        aimdk_msgs__srv__GetStoredMapByName_Response__fini(&data[i - 1]);
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
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__fini(aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * array)
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
      aimdk_msgs__srv__GetStoredMapByName_Response__fini(&array->data[i]);
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

aimdk_msgs__srv__GetStoredMapByName_Response__Sequence *
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * array = (aimdk_msgs__srv__GetStoredMapByName_Response__Sequence *)allocator.allocate(sizeof(aimdk_msgs__srv__GetStoredMapByName_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__destroy(aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__are_equal(const aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * lhs, const aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!aimdk_msgs__srv__GetStoredMapByName_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
aimdk_msgs__srv__GetStoredMapByName_Response__Sequence__copy(
  const aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * input,
  aimdk_msgs__srv__GetStoredMapByName_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(aimdk_msgs__srv__GetStoredMapByName_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    aimdk_msgs__srv__GetStoredMapByName_Response * data =
      (aimdk_msgs__srv__GetStoredMapByName_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!aimdk_msgs__srv__GetStoredMapByName_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          aimdk_msgs__srv__GetStoredMapByName_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!aimdk_msgs__srv__GetStoredMapByName_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
