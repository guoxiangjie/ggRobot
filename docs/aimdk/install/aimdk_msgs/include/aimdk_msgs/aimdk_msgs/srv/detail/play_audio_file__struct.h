// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/PlayAudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__struct.h"
// Member 'file'
#include "aimdk_msgs/msg/detail/audio_file__struct.h"
// Member 'play_stamps'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in srv/PlayAudioFile in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayAudioFile_Request
{
  /// 请求头
  aimdk_msgs__msg__CommonRequest request;
  /// 必要项，文件信息
  aimdk_msgs__msg__AudioFile file;
  /// 可选项，指定时刻播放，默认立即播放
  builtin_interfaces__msg__Time play_stamps;
} aimdk_msgs__srv__PlayAudioFile_Request;

// Struct for a sequence of aimdk_msgs__srv__PlayAudioFile_Request.
typedef struct aimdk_msgs__srv__PlayAudioFile_Request__Sequence
{
  aimdk_msgs__srv__PlayAudioFile_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayAudioFile_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.h"

/// Struct defined in srv/PlayAudioFile in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayAudioFile_Response
{
  /// ----------------------------------------------------
  /// response
  /// 响应头
  aimdk_msgs__msg__CommonResponse reponse;
} aimdk_msgs__srv__PlayAudioFile_Response;

// Struct for a sequence of aimdk_msgs__srv__PlayAudioFile_Response.
typedef struct aimdk_msgs__srv__PlayAudioFile_Response__Sequence
{
  aimdk_msgs__srv__PlayAudioFile_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayAudioFile_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_H_
