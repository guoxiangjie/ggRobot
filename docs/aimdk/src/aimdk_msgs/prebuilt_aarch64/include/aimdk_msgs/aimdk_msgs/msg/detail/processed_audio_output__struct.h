// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.h"
// Member 'audio_vad_state'
#include "aimdk_msgs/msg/detail/audio_vad_state_type__struct.h"
// Member 'audio_data'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/ProcessedAudioOutput in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__ProcessedAudioOutput
{
  aimdk_msgs__msg__MessageHeader header;
  uint32_t stream_id;
  aimdk_msgs__msg__AudioVadStateType audio_vad_state;
  rosidl_runtime_c__uint8__Sequence audio_data;
} aimdk_msgs__msg__ProcessedAudioOutput;

// Struct for a sequence of aimdk_msgs__msg__ProcessedAudioOutput.
typedef struct aimdk_msgs__msg__ProcessedAudioOutput__Sequence
{
  aimdk_msgs__msg__ProcessedAudioOutput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__ProcessedAudioOutput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_H_
