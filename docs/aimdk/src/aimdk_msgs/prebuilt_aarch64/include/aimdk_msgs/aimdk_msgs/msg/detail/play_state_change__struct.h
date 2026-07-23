// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/PlayStateChange.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pkg_name'
#include "rosidl_runtime_c/string.h"
// Member 'state'
#include "aimdk_msgs/msg/detail/play_state_type__struct.h"

/// Struct defined in msg/PlayStateChange in the package aimdk_msgs.
/**
  * 播放来源
 */
typedef struct aimdk_msgs__msg__PlayStateChange
{
  rosidl_runtime_c__String pkg_name;
  /// 播放状态
  aimdk_msgs__msg__PlayStateType state;
} aimdk_msgs__msg__PlayStateChange;

// Struct for a sequence of aimdk_msgs__msg__PlayStateChange.
typedef struct aimdk_msgs__msg__PlayStateChange__Sequence
{
  aimdk_msgs__msg__PlayStateChange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__PlayStateChange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_H_
