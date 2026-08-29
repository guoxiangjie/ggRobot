// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetMcPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_H_

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
#include "aimdk_msgs/msg/detail/request_header__struct.h"
// Member 'area'
#include "aimdk_msgs/msg/detail/mc_control_area__struct.h"
// Member 'motion'
#include "aimdk_msgs/msg/detail/mc_preset_motion__struct.h"
// Member 'ani_path'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetMcPresetMotion in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMcPresetMotion_Request
{
  aimdk_msgs__msg__RequestHeader header;
  /// 控制区域
  aimdk_msgs__msg__McControlArea area;
  /// 预设动作
  aimdk_msgs__msg__McPresetMotion motion;
  /// 是否打断前一个动作
  bool interrupt;
  /// 自定义动作地址
  rosidl_runtime_c__String ani_path;
  /// 动作运行时间，0代表立刻运行，单位: ms (UNIX时间)
  uint64_t play_timestamp;
} aimdk_msgs__srv__SetMcPresetMotion_Request;

// Struct for a sequence of aimdk_msgs__srv__SetMcPresetMotion_Request.
typedef struct aimdk_msgs__srv__SetMcPresetMotion_Request__Sequence
{
  aimdk_msgs__srv__SetMcPresetMotion_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMcPresetMotion_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__struct.h"

/// Struct defined in srv/SetMcPresetMotion in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMcPresetMotion_Response
{
  aimdk_msgs__msg__CommonTaskResponse response;
} aimdk_msgs__srv__SetMcPresetMotion_Response;

// Struct for a sequence of aimdk_msgs__srv__SetMcPresetMotion_Response.
typedef struct aimdk_msgs__srv__SetMcPresetMotion_Response__Sequence
{
  aimdk_msgs__srv__SetMcPresetMotion_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMcPresetMotion_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_H_
