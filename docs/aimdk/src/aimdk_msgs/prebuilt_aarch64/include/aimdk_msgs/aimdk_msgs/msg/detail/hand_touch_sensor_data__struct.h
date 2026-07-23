// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/HandTouchSensorData in the package aimdk_msgs.
/**
  * 手心手背的触摸传感器数据 5*5, 数组长度一般是25, 雷赛是36，但是雷赛没有手背
 */
typedef struct aimdk_msgs__msg__HandTouchSensorData
{
  uint8_t palm_touch_data[36];
  uint8_t back_of_hand_touch_data[36];
  /// 指尖触摸传感器数据 4*4, 数组长度一般是16, Omnihands 长度是16，雷赛是12
  uint8_t thumb_touch_data[16];
  uint8_t index_finger_touch_data[16];
  uint8_t middle_finger_touch_data[16];
  uint8_t ring_finger_touch_data[16];
  uint8_t little_finger_touch_data[16];
} aimdk_msgs__msg__HandTouchSensorData;

// Struct for a sequence of aimdk_msgs__msg__HandTouchSensorData.
typedef struct aimdk_msgs__msg__HandTouchSensorData__Sequence
{
  aimdk_msgs__msg__HandTouchSensorData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HandTouchSensorData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_H_
