// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/PlayMediaFileRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'file_name'
// Member 'domain'
// Member 'trace_id'
#include "rosidl_runtime_c/string.h"
// Member 'priority_level'
#include "aimdk_msgs/msg/detail/tts_priority_level__struct.h"

/// Struct defined in msg/PlayMediaFileRequest in the package aimdk_msgs.
/**
  * 必要项
 */
typedef struct aimdk_msgs__msg__PlayMediaFileRequest
{
  rosidl_runtime_c__String file_name;
  /// 可选，当前不支持此能力。默认音频为 16k1ch
  uint32_t sample_rate;
  /// 必要项，默认使用 INTERACTION_L6
  aimdk_msgs__msg__TtsPriorityLevel priority_level;
  /// 可选，非产品要求勿用，优先级加权参数(0-99)，最小单位为 1
  uint32_t priority_weight;
  /// 必要项，标识调用方来源
  rosidl_runtime_c__String domain;
  /// 可选，用于标识播报的请求id
  rosidl_runtime_c__String trace_id;
  /// 必要项，是否打断同等优先级播报（ true：打断；false：不打断，进入队列播报）
  bool is_interrupted;
} aimdk_msgs__msg__PlayMediaFileRequest;

// Struct for a sequence of aimdk_msgs__msg__PlayMediaFileRequest.
typedef struct aimdk_msgs__msg__PlayMediaFileRequest__Sequence
{
  aimdk_msgs__msg__PlayMediaFileRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__PlayMediaFileRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__STRUCT_H_
