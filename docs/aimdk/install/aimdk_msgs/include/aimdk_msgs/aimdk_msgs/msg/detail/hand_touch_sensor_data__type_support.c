// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__functions.h"
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__HandTouchSensorData__init(message_memory);
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_fini_function(void * message_memory)
{
  aimdk_msgs__msg__HandTouchSensorData__fini(message_memory);
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__palm_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__palm_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__palm_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__palm_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__palm_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__palm_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__palm_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__back_of_hand_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__back_of_hand_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__back_of_hand_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__back_of_hand_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__back_of_hand_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__back_of_hand_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__back_of_hand_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__thumb_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__thumb_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__thumb_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__thumb_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__thumb_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__thumb_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__thumb_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__index_finger_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__index_finger_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__index_finger_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__index_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__index_finger_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__index_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__index_finger_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__middle_finger_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__middle_finger_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__middle_finger_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__middle_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__middle_finger_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__middle_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__middle_finger_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__ring_finger_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__ring_finger_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__ring_finger_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__ring_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__ring_finger_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__ring_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__ring_finger_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__little_finger_touch_data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__little_finger_touch_data(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__little_finger_touch_data(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__little_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__little_finger_touch_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__little_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__little_finger_touch_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_member_array[7] = {
  {
    "palm_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, palm_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__palm_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__palm_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__palm_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__palm_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__palm_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "back_of_hand_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, back_of_hand_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__back_of_hand_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__back_of_hand_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__back_of_hand_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__back_of_hand_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__back_of_hand_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "thumb_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, thumb_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__thumb_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__thumb_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__thumb_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__thumb_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__thumb_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "index_finger_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, index_finger_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__index_finger_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__index_finger_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__index_finger_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__index_finger_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__index_finger_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "middle_finger_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, middle_finger_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__middle_finger_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__middle_finger_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__middle_finger_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__middle_finger_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__middle_finger_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ring_finger_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, ring_finger_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__ring_finger_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__ring_finger_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__ring_finger_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__ring_finger_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__ring_finger_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "little_finger_touch_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandTouchSensorData, little_finger_touch_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__size_function__HandTouchSensorData__little_finger_touch_data,  // size() function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_const_function__HandTouchSensorData__little_finger_touch_data,  // get_const(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__get_function__HandTouchSensorData__little_finger_touch_data,  // get(index) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__fetch_function__HandTouchSensorData__little_finger_touch_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__assign_function__HandTouchSensorData__little_finger_touch_data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "HandTouchSensorData",  // message name
  7,  // number of fields
  sizeof(aimdk_msgs__msg__HandTouchSensorData),
  aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_member_array,  // message members
  aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandTouchSensorData)() {
  if (!aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__HandTouchSensorData__rosidl_typesupport_introspection_c__HandTouchSensorData_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
