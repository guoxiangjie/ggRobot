// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/TtsPriorityLevel.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'UNKNOWN'.
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__UNKNOWN = 0
};

/// Constant 'BACKGROUND_L1'.
/**
  * 后台服务层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__BACKGROUND_L1 = 1
};

/// Constant 'SERVICE_L2'.
/**
  * 主动服务层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__SERVICE_L2 = 2
};

/// Constant 'MISSION_L4'.
/**
  * 任务执行层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__MISSION_L4 = 4
};

/// Constant 'INTERACTION_L6'.
/**
  * 交互相应层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__INTERACTION_L6 = 6
};

/// Constant 'SYSTEM_L7'.
/**
  * 系统提示层
  * 危险预警层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__SYSTEM_L7 = 7
};

/// Constant 'WARNING_L8'.
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__WARNING_L8 = 8
};

/// Constant 'SAFETY_L10'.
/**
  * 生命安全层
 */
enum
{
  aimdk_msgs__msg__TtsPriorityLevel__SAFETY_L10 = 10
};

/// Struct defined in msg/TtsPriorityLevel in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__TtsPriorityLevel
{
  uint8_t value;
} aimdk_msgs__msg__TtsPriorityLevel;

// Struct for a sequence of aimdk_msgs__msg__TtsPriorityLevel.
typedef struct aimdk_msgs__msg__TtsPriorityLevel__Sequence
{
  aimdk_msgs__msg__TtsPriorityLevel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__TtsPriorityLevel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_H_
