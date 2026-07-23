// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AudioData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_DATA__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/AudioData in the package aimdk_msgs.
/**
  * 音频数据
 */
typedef struct aimdk_msgs__msg__AudioData
{
  rosidl_runtime_c__uint8__Sequence data;
} aimdk_msgs__msg__AudioData;

// Struct for a sequence of aimdk_msgs__msg__AudioData.
typedef struct aimdk_msgs__msg__AudioData__Sequence
{
  aimdk_msgs__msg__AudioData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AudioData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_DATA__STRUCT_H_
