// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McControlArea.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_CONTROL_AREA__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_CONTROL_AREA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'NONE'.
/**
  * 没有控制区域
 */
enum
{
  aimdk_msgs__msg__McControlArea__NONE = 0l
};

/// Constant 'LEFT_HAND'.
/**
  * 左手
 */
enum
{
  aimdk_msgs__msg__McControlArea__LEFT_HAND = 1l
};

/// Constant 'RIGHT_HAND'.
/**
  * 右手
 */
enum
{
  aimdk_msgs__msg__McControlArea__RIGHT_HAND = 2l
};

/// Constant 'HEAD'.
/**
  * 头部
 */
enum
{
  aimdk_msgs__msg__McControlArea__HEAD = 4l
};

/// Constant 'WAIST'.
/**
  * 腰部
 */
enum
{
  aimdk_msgs__msg__McControlArea__WAIST = 8l
};

/// Struct defined in msg/McControlArea in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__McControlArea
{
  int32_t value;
} aimdk_msgs__msg__McControlArea;

// Struct for a sequence of aimdk_msgs__msg__McControlArea.
typedef struct aimdk_msgs__msg__McControlArea__Sequence
{
  aimdk_msgs__msg__McControlArea * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McControlArea__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_CONTROL_AREA__STRUCT_H_
