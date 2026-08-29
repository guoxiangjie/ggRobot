// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McActionInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'current_action'
#include "aimdk_msgs/msg/detail/mc_action__struct.h"
// Member 'action_desc'
#include "rosidl_runtime_c/string.h"
// Member 'status'
#include "aimdk_msgs/msg/detail/mc_action_status__struct.h"

/// Struct defined in msg/McActionInfo in the package aimdk_msgs.
/**
  * 当前运行的Action
 */
typedef struct aimdk_msgs__msg__McActionInfo
{
  aimdk_msgs__msg__McAction current_action;
  /// 描述
  rosidl_runtime_c__String action_desc;
  /// Action状态
  aimdk_msgs__msg__McActionStatus status;
} aimdk_msgs__msg__McActionInfo;

// Struct for a sequence of aimdk_msgs__msg__McActionInfo.
typedef struct aimdk_msgs__msg__McActionInfo__Sequence
{
  aimdk_msgs__msg__McActionInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McActionInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__STRUCT_H_
