// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HandType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TYPE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'NONE'.
/**
  * 0: 无状态, 1: 自研灵巧手模式, 2: 爪模式, 3: 雷赛灵巧手 255: 错误
  * 无状态
 */
enum
{
  aimdk_msgs__msg__HandType__NONE = 0
};

/// Constant 'NIMBLE_HANDS'.
/**
  * 灵巧手模式
 */
enum
{
  aimdk_msgs__msg__HandType__NIMBLE_HANDS = 1
};

/// Constant 'CLAW'.
/**
  * 假爪模式
 */
enum
{
  aimdk_msgs__msg__HandType__CLAW = 2
};

/// Constant 'LEISAI_NIMBLE_HANDS'.
/**
  * 灵巧手模式
 */
enum
{
  aimdk_msgs__msg__HandType__LEISAI_NIMBLE_HANDS = 3
};

/// Constant 'ERROR'.
/**
  * 错误
 */
enum
{
  aimdk_msgs__msg__HandType__ERROR = 255
};

/// Struct defined in msg/HandType in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__HandType
{
  uint8_t value;
} aimdk_msgs__msg__HandType;

// Struct for a sequence of aimdk_msgs__msg__HandType.
typedef struct aimdk_msgs__msg__HandType__Sequence
{
  aimdk_msgs__msg__HandType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HandType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TYPE__STRUCT_H_
