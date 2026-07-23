// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AudioVadStateType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'AUDIO_VAD_STATE_NONE'.
enum
{
  aimdk_msgs__msg__AudioVadStateType__AUDIO_VAD_STATE_NONE = 0
};

/// Constant 'AUDIO_VAD_STATE_BEGIN'.
enum
{
  aimdk_msgs__msg__AudioVadStateType__AUDIO_VAD_STATE_BEGIN = 1
};

/// Constant 'AUDIO_VAD_STATE_PROCESSING'.
enum
{
  aimdk_msgs__msg__AudioVadStateType__AUDIO_VAD_STATE_PROCESSING = 2
};

/// Constant 'AUDIO_VAD_STATE_END'.
enum
{
  aimdk_msgs__msg__AudioVadStateType__AUDIO_VAD_STATE_END = 3
};

/// Struct defined in msg/AudioVadStateType in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__AudioVadStateType
{
  uint8_t value;
} aimdk_msgs__msg__AudioVadStateType;

// Struct for a sequence of aimdk_msgs__msg__AudioVadStateType.
typedef struct aimdk_msgs__msg__AudioVadStateType__Sequence
{
  aimdk_msgs__msg__AudioVadStateType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AudioVadStateType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_H_
