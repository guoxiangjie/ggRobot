// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__STRUCT_H_

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
// Member 'file_name'
// Member 'file_path'
#include "rosidl_runtime_c/string.h"
// Member 'info'
#include "aimdk_msgs/msg/detail/audio_info__struct.h"

/// Struct defined in msg/AudioFile in the package aimdk_msgs.
/**
  * 必要项，标识调用方来源
 */
typedef struct aimdk_msgs__msg__AudioFile
{
  rosidl_runtime_c__String pkg_name;
  /// 必要项，文件名
  rosidl_runtime_c__String file_name;
  /// 必要项，不设置时使用系统默认路径
  rosidl_runtime_c__String file_path;
  /// pcm格式必要项，wav格式可选项，音频格式
  aimdk_msgs__msg__AudioInfo info;
  /// 必要项，优先级(1~10, 默认6)
  uint32_t priority;
  /// 可选项，(1~100) priority + priority_weight% is final priority
  uint32_t priority_weight;
} aimdk_msgs__msg__AudioFile;

// Struct for a sequence of aimdk_msgs__msg__AudioFile.
typedef struct aimdk_msgs__msg__AudioFile__Sequence
{
  aimdk_msgs__msg__AudioFile * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AudioFile__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__STRUCT_H_
