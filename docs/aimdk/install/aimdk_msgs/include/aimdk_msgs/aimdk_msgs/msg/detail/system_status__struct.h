// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'IN_INITIAL'.
/**
  * 起始态
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_INITIAL = 0
};

/// Constant 'IN_READY'.
/**
  * 就绪态，可执行业务
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_READY = 1
};

/// Constant 'IN_MOVE'.
/**
  * 迁移态，不可执行业务，拒绝迁移请求
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_MOVE = 2
};

/// Constant 'IN_ROLLBACK'.
/**
  * 回滚态，不可执行业务，拒绝迁移请求
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_ROLLBACK = 3
};

/// Constant 'IN_FALLBACK'.
/**
  * 异常态，接收迁移请求
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_FALLBACK = 4
};

/// Constant 'IN_FALLBACK_MOVE'.
/**
  * 异常迁移态，不可执行业务，拒绝迁移请求
 */
enum
{
  aimdk_msgs__msg__SystemStatus__IN_FALLBACK_MOVE = 5
};

/// Struct defined in msg/SystemStatus in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__SystemStatus
{
  uint8_t value;
} aimdk_msgs__msg__SystemStatus;

// Struct for a sequence of aimdk_msgs__msg__SystemStatus.
typedef struct aimdk_msgs__msg__SystemStatus__Sequence
{
  aimdk_msgs__msg__SystemStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__SystemStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__SYSTEM_STATUS__STRUCT_H_
