// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/TouchState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_H_

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
  * 触摸事件类型常量定义
  * 未知
 */
enum
{
  aimdk_msgs__msg__TouchState__UNKNOWN = 0
};

/// Constant 'IDLE'.
/**
  * 空闲
 */
enum
{
  aimdk_msgs__msg__TouchState__IDLE = 1
};

/// Constant 'TOUCH'.
/**
  * 触摸
 */
enum
{
  aimdk_msgs__msg__TouchState__TOUCH = 2
};

/// Constant 'SLIDE'.
/**
  * 滑动
 */
enum
{
  aimdk_msgs__msg__TouchState__SLIDE = 3
};

/// Constant 'PAT_ONCE'.
/**
  * 单击
 */
enum
{
  aimdk_msgs__msg__TouchState__PAT_ONCE = 4
};

/// Constant 'PAT_TWICE'.
/**
  * 双击
 */
enum
{
  aimdk_msgs__msg__TouchState__PAT_TWICE = 5
};

/// Constant 'PAT_TRIPLE'.
/**
  * 三击
 */
enum
{
  aimdk_msgs__msg__TouchState__PAT_TRIPLE = 6
};

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.h"

/// Struct defined in msg/TouchState in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 机器人触摸传感器状态
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__TouchState
{
  /// 触摸传感器状态消息
  aimdk_msgs__msg__MessageHeader header;
  /// 触摸事件类型
  uint8_t event_type;
  /// 8个通道的原始传感器数值
  uint32_t data[8];
  /// 8个通道对应的触摸阈值
  uint32_t threshold[8];
  /// 8个通道的触摸状态（true表示触摸）
  bool is_touched[8];
} aimdk_msgs__msg__TouchState;

// Struct for a sequence of aimdk_msgs__msg__TouchState.
typedef struct aimdk_msgs__msg__TouchState__Sequence
{
  aimdk_msgs__msg__TouchState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__TouchState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_H_
