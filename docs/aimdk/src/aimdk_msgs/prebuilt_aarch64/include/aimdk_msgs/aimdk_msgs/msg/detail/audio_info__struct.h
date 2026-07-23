// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AudioInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'sample_format'
// Member 'coding_format'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AudioInfo in the package aimdk_msgs.
/**
  * 必要项，通道数
 */
typedef struct aimdk_msgs__msg__AudioInfo
{
  uint8_t channels;
  /// 必要项，采样率
  uint32_t sample_rate;
  /// 可选项，写入size
  uint32_t size;
  /// 可选项，Audio format (e.g. S16LE， S32_LE) 默认S16_LE
  rosidl_runtime_c__String sample_format;
  /// 可选项，Audio coding format (e.g. pcm, wave, opus)
  rosidl_runtime_c__String coding_format;
} aimdk_msgs__msg__AudioInfo;

// Struct for a sequence of aimdk_msgs__msg__AudioInfo.
typedef struct aimdk_msgs__msg__AudioInfo__Sequence
{
  aimdk_msgs__msg__AudioInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AudioInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__STRUCT_H_
