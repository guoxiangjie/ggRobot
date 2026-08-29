// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McLocomotionVelocity.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__STRUCT_H_

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
// Member 'source'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/McLocomotionVelocity in the package aimdk_msgs.
/**
  * 消息头
 */
typedef struct aimdk_msgs__msg__McLocomotionVelocity
{
  aimdk_msgs__msg__MessageHeader header;
  /// 输入源
  rosidl_runtime_c__String source;
  /// 前进速度 (m/s)
  /// 方向: +为前进, -为后退
  double forward_velocity;
  /// 侧移速度 (m/s)
  /// 方向: +为左移, -为右移
  double lateral_velocity;
  /// 旋转速度 (角速度) (m/s)
  /// 方向: +为左旋转, -为右旋转
  double angular_velocity;
} aimdk_msgs__msg__McLocomotionVelocity;

// Struct for a sequence of aimdk_msgs__msg__McLocomotionVelocity.
typedef struct aimdk_msgs__msg__McLocomotionVelocity__Sequence
{
  aimdk_msgs__msg__McLocomotionVelocity * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McLocomotionVelocity__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__STRUCT_H_
