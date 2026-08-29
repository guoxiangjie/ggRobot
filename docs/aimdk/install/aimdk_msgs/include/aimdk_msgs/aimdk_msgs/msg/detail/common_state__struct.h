// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/CommonState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_STATE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'UNKNOWN'.
/**
  * 未知
 */
enum
{
  aimdk_msgs__msg__CommonState__UNKNOWN = 0l
};

/// Constant 'SUCCESS'.
/**
  * 成功
 */
enum
{
  aimdk_msgs__msg__CommonState__SUCCESS = 1l
};

/// Constant 'FAILURE'.
/**
  * 失败
 */
enum
{
  aimdk_msgs__msg__CommonState__FAILURE = 2l
};

/// Constant 'ABORTED'.
/**
  * 中止
 */
enum
{
  aimdk_msgs__msg__CommonState__ABORTED = 3l
};

/// Constant 'TIMEOUT'.
/**
  * 超时
 */
enum
{
  aimdk_msgs__msg__CommonState__TIMEOUT = 4l
};

/// Constant 'INVALID'.
/**
  * 无效
 */
enum
{
  aimdk_msgs__msg__CommonState__INVALID = 5l
};

/// Constant 'IN_MANUAL'.
/**
  * 手动
 */
enum
{
  aimdk_msgs__msg__CommonState__IN_MANUAL = 6l
};

/// Constant 'NOT_READY'.
/**
  * 未就绪
 */
enum
{
  aimdk_msgs__msg__CommonState__NOT_READY = 100l
};

/// Constant 'PENDING'.
/**
  * 等待中
 */
enum
{
  aimdk_msgs__msg__CommonState__PENDING = 200l
};

/// Constant 'CREATED'.
/**
  * 已创建
 */
enum
{
  aimdk_msgs__msg__CommonState__CREATED = 300l
};

/// Constant 'RUNNING'.
/**
  * 运行中
 */
enum
{
  aimdk_msgs__msg__CommonState__RUNNING = 400l
};

/// Struct defined in msg/CommonState in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__CommonState
{
  int32_t value;
} aimdk_msgs__msg__CommonState;

// Struct for a sequence of aimdk_msgs__msg__CommonState.
typedef struct aimdk_msgs__msg__CommonState__Sequence
{
  aimdk_msgs__msg__CommonState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__CommonState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_STATE__STRUCT_H_
