// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HandStateArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.h"
// Member 'left_hand_type'
// Member 'right_hand_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.h"
// Member 'left_hands'
// Member 'right_hands'
#include "aimdk_msgs/msg/detail/hand_state__struct.h"
// Member 'left_touch_sensors'
// Member 'right_touch_sensors'
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.h"

/// Struct defined in msg/HandStateArray in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__HandStateArray
{
  aimdk_msgs__msg__MessageHeader header;
  aimdk_msgs__msg__HandType left_hand_type;
  aimdk_msgs__msg__HandState__Sequence left_hands;
  aimdk_msgs__msg__HandTouchSensorData left_touch_sensors;
  aimdk_msgs__msg__HandType right_hand_type;
  aimdk_msgs__msg__HandState__Sequence right_hands;
  aimdk_msgs__msg__HandTouchSensorData right_touch_sensors;
} aimdk_msgs__msg__HandStateArray;

// Struct for a sequence of aimdk_msgs__msg__HandStateArray.
typedef struct aimdk_msgs__msg__HandStateArray__Sequence
{
  aimdk_msgs__msg__HandStateArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HandStateArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_H_
