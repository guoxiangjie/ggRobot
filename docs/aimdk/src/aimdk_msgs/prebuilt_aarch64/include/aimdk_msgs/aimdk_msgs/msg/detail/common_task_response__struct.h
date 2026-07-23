// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/CommonTaskResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_H_

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
#include "aimdk_msgs/msg/detail/response_header__struct.h"
// Member 'state'
#include "aimdk_msgs/msg/detail/common_state__struct.h"

/// Struct defined in msg/CommonTaskResponse in the package aimdk_msgs.
/**
  * 响应头
 */
typedef struct aimdk_msgs__msg__CommonTaskResponse
{
  aimdk_msgs__msg__ResponseHeader header;
  /// 任务ID
  uint64_t task_id;
  /// 状态
  aimdk_msgs__msg__CommonState state;
} aimdk_msgs__msg__CommonTaskResponse;

// Struct for a sequence of aimdk_msgs__msg__CommonTaskResponse.
typedef struct aimdk_msgs__msg__CommonTaskResponse__Sequence
{
  aimdk_msgs__msg__CommonTaskResponse * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__CommonTaskResponse__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_H_
