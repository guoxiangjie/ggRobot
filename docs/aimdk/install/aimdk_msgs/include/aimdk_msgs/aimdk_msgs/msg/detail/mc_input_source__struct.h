// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/McInputSource in the package aimdk_msgs.
/**
  * -----------------------------------------------------------------------------------
  * 机器人运控状态 - 输入源信息
  * -----------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__McInputSource
{
  /// 输入源名称（rc/vr/app_proxy/interaction/pnc）
  rosidl_runtime_c__String name;
  /// 输入源优先级(0-100)
  int32_t priority;
  /// 超时时间(ms), 默认 1000 ms
  int32_t timeout;
} aimdk_msgs__msg__McInputSource;

// Struct for a sequence of aimdk_msgs__msg__McInputSource.
typedef struct aimdk_msgs__msg__McInputSource__Sequence
{
  aimdk_msgs__msg__McInputSource * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McInputSource__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__STRUCT_H_
