// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/PlayStateType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_TYPE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PLAYER_STATE_CLOSED'.
/**
  * 默认关闭状态
 */
enum
{
  aimdk_msgs__msg__PlayStateType__PLAYER_STATE_CLOSED = 0
};

/// Constant 'PLAYER_STATE_PLAYING'.
/**
  * 播放中
 */
enum
{
  aimdk_msgs__msg__PlayStateType__PLAYER_STATE_PLAYING = 1
};

/// Constant 'PLAYER_STATE_STOPED'.
/**
  * 播放结束
 */
enum
{
  aimdk_msgs__msg__PlayStateType__PLAYER_STATE_STOPED = 2
};

/// Struct defined in msg/PlayStateType in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__PlayStateType
{
  uint8_t value;
} aimdk_msgs__msg__PlayStateType;

// Struct for a sequence of aimdk_msgs__msg__PlayStateType.
typedef struct aimdk_msgs__msg__PlayStateType__Sequence
{
  aimdk_msgs__msg__PlayStateType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__PlayStateType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_TYPE__STRUCT_H_
