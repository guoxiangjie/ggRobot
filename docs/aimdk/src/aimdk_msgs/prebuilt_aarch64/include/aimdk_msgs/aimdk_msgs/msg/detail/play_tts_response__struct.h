// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/PlayTtsResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'text'
// Member 'domain'
// Member 'trace_id'
// Member 'error_message'
#include "rosidl_runtime_c/string.h"
// Member 'priority_level'
#include "aimdk_msgs/msg/detail/tts_priority_level__struct.h"

/// Struct defined in msg/PlayTtsResponse in the package aimdk_msgs.
/**
  * PlayMediaFileRequest 同样复用此 rsp，file_name 放在 text 中
 */
typedef struct aimdk_msgs__msg__PlayTtsResponse
{
  rosidl_runtime_c__String text;
  aimdk_msgs__msg__TtsPriorityLevel priority_level;
  /// 加权参数(0-10)，最小单位为 1
  uint32_t priority_weight;
  /// 标识调用方来源
  rosidl_runtime_c__String domain;
  rosidl_runtime_c__String trace_id;
  /// 是否成功播放
  bool is_success;
  /// 错误信息
  rosidl_runtime_c__String error_message;
  /// 当前文本预计耗时（单位：毫秒）
  uint32_t estimated_duration;
} aimdk_msgs__msg__PlayTtsResponse;

// Struct for a sequence of aimdk_msgs__msg__PlayTtsResponse.
typedef struct aimdk_msgs__msg__PlayTtsResponse__Sequence
{
  aimdk_msgs__msg__PlayTtsResponse * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__PlayTtsResponse__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__STRUCT_H_
