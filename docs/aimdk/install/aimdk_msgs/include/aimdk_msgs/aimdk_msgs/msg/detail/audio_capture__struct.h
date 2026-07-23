// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AudioCapture.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamps'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'info'
#include "aimdk_msgs/msg/detail/audio_info__struct.h"
// Member 'data'
#include "aimdk_msgs/msg/detail/audio_data__struct.h"
// Member 'pkg_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AudioCapture in the package aimdk_msgs.
/**
  * 必要项，时间戳
 */
typedef struct aimdk_msgs__msg__AudioCapture
{
  builtin_interfaces__msg__Time stamps;
  /// 必要项，麦克风通道数
  uint8_t mic_channels;
  /// 必要项，回采信号通道数
  uint8_t ref_channels;
  /// 必要项，音频格式
  aimdk_msgs__msg__AudioInfo info;
  /// 必要项，音频数据
  aimdk_msgs__msg__AudioData data;
  /// 可选项，标识发送方来源
  rosidl_runtime_c__String pkg_name;
} aimdk_msgs__msg__AudioCapture;

// Struct for a sequence of aimdk_msgs__msg__AudioCapture.
typedef struct aimdk_msgs__msg__AudioCapture__Sequence
{
  aimdk_msgs__msg__AudioCapture * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AudioCapture__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_H_
