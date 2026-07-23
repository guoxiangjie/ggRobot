// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/PlayVideo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'EMOTION_MODE_ONCE'.
/**
  * 仅播放一次
 */
enum
{
  aimdk_msgs__srv__PlayVideo_Request__EMOTION_MODE_ONCE = 1
};

/// Constant 'EMOTION_MODE_LOOP'.
/**
  * 循环播放
 */
enum
{
  aimdk_msgs__srv__PlayVideo_Request__EMOTION_MODE_LOOP = 2
};

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__struct.h"
// Member 'video_path'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/PlayVideo in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayVideo_Request
{
  aimdk_msgs__msg__CommonRequest header;
  /// ----------------------------------------------------
  /// 视频路径
  /// ----------------------------------------------------
  rosidl_runtime_c__String video_path;
  /// ----------------------------------------------------
  /// 播放模式枚举
  uint8_t mode;
  /// ----------------------------------------------------
  /// 播放优先级
  int32_t priority;
} aimdk_msgs__srv__PlayVideo_Request;

// Struct for a sequence of aimdk_msgs__srv__PlayVideo_Request.
typedef struct aimdk_msgs__srv__PlayVideo_Request__Sequence
{
  aimdk_msgs__srv__PlayVideo_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayVideo_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/PlayVideo in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayVideo_Response
{
  aimdk_msgs__msg__CommonResponse header;
  bool success;
  rosidl_runtime_c__String message;
} aimdk_msgs__srv__PlayVideo_Response;

// Struct for a sequence of aimdk_msgs__srv__PlayVideo_Response.
typedef struct aimdk_msgs__srv__PlayVideo_Response__Sequence
{
  aimdk_msgs__srv__PlayVideo_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayVideo_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO__STRUCT_H_
