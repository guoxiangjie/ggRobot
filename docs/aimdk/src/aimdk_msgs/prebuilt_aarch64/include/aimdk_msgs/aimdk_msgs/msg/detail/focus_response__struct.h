// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/FocusResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pkg_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/FocusResponse in the package aimdk_msgs.
/**
  * 必要项，标识调用方来源
 */
typedef struct aimdk_msgs__msg__FocusResponse
{
  rosidl_runtime_c__String pkg_name;
  /// 必要项，焦点结果
  /// true: 获取到焦点
  /// false: 丢失焦点
  bool focus_gain;
} aimdk_msgs__msg__FocusResponse;

// Struct for a sequence of aimdk_msgs__msg__FocusResponse.
typedef struct aimdk_msgs__msg__FocusResponse__Sequence
{
  aimdk_msgs__msg__FocusResponse * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__FocusResponse__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__STRUCT_H_
