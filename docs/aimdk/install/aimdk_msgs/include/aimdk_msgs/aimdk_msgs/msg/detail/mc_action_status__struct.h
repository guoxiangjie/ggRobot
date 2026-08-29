// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McActionStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'IDLE'.
/**
  * 未知状态
 */
enum
{
  aimdk_msgs__msg__McActionStatus__IDLE = 0l
};

/// Constant 'RUNNING'.
/**
  * 运行中
 */
enum
{
  aimdk_msgs__msg__McActionStatus__RUNNING = 100l
};

/// Constant 'TRANSITION'.
/**
  * 切换中
 */
enum
{
  aimdk_msgs__msg__McActionStatus__TRANSITION = 200l
};

/// Struct defined in msg/McActionStatus in the package aimdk_msgs.
/**
  * 定义枚举字段
 */
typedef struct aimdk_msgs__msg__McActionStatus
{
  int32_t value;
} aimdk_msgs__msg__McActionStatus;

// Struct for a sequence of aimdk_msgs__msg__McActionStatus.
typedef struct aimdk_msgs__msg__McActionStatus__Sequence
{
  aimdk_msgs__msg__McActionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McActionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__STRUCT_H_
