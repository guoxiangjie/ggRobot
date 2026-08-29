// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATUS_IDLE'.
/**
  * 当前状态枚举：idle | start（仅广播一次）| running | finished（仅广播一次）| stopped（仅广播一次）
 */
enum
{
  aimdk_msgs__msg__FaceEmojiStatus__STATUS_IDLE = 0
};

/// Constant 'STATUS_START'.
enum
{
  aimdk_msgs__msg__FaceEmojiStatus__STATUS_START = 1
};

/// Constant 'STATUS_RUNNING'.
enum
{
  aimdk_msgs__msg__FaceEmojiStatus__STATUS_RUNNING = 2
};

/// Constant 'STATUS_FINISHED'.
enum
{
  aimdk_msgs__msg__FaceEmojiStatus__STATUS_FINISHED = 3
};

/// Constant 'STATUS_STOPPED'.
enum
{
  aimdk_msgs__msg__FaceEmojiStatus__STATUS_STOPPED = 4
};

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.h"
// Member 'e_path'
// Member 'e_path_list'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/FaceEmojiStatus in the package aimdk_msgs.
/**
  * Header 包含时间辍, trace_id、domain
 */
typedef struct aimdk_msgs__msg__FaceEmojiStatus
{
  aimdk_msgs__msg__MessageHeader header;
  /// 表情文件的路径
  rosidl_runtime_c__String e_path;
  /// 当前一组表情的路径列表
  rosidl_runtime_c__String__Sequence e_path_list;
  /// 表情id，可以为空
  uint8_t e_id;
  /// 播放模式，1-仅播放一次，2-循环播放
  uint8_t mode;
  /// 默认表情优先级为 0, 数值越大优先级越高
  int32_t priority;
  uint8_t status;
  /// 剩余时长，单位：秒；如果重复，会将剩余重复时间计算在内
  double time_to_end_ms;
} aimdk_msgs__msg__FaceEmojiStatus;

// Struct for a sequence of aimdk_msgs__msg__FaceEmojiStatus.
typedef struct aimdk_msgs__msg__FaceEmojiStatus__Sequence
{
  aimdk_msgs__msg__FaceEmojiStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__FaceEmojiStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_H_
