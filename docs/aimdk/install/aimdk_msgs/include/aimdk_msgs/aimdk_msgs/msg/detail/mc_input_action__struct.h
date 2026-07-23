// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McInputAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_INPUT_ACTION__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_INPUT_ACTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'INPUTACTION_ADD'.
/**
  * 添加新的输入源
 */
enum
{
  aimdk_msgs__msg__McInputAction__INPUTACTION_ADD = 1001l
};

/// Constant 'INPUTACTION_MODIFY'.
/**
  * 修改输入源配置
 */
enum
{
  aimdk_msgs__msg__McInputAction__INPUTACTION_MODIFY = 1002l
};

/// Constant 'INPUTACTION_DELETE'.
/**
  * 删除输入源
 */
enum
{
  aimdk_msgs__msg__McInputAction__INPUTACTION_DELETE = 1003l
};

/// Constant 'INPUTACTION_ENABLE'.
/**
  * 使能输入源
 */
enum
{
  aimdk_msgs__msg__McInputAction__INPUTACTION_ENABLE = 2001l
};

/// Constant 'INPUTACTION_DISABLE'.
/**
  * 下使能输入源
 */
enum
{
  aimdk_msgs__msg__McInputAction__INPUTACTION_DISABLE = 2002l
};

/// Struct defined in msg/McInputAction in the package aimdk_msgs.
/**
  * 输入源操作
 */
typedef struct aimdk_msgs__msg__McInputAction
{
  int32_t value;
} aimdk_msgs__msg__McInputAction;

// Struct for a sequence of aimdk_msgs__msg__McInputAction.
typedef struct aimdk_msgs__msg__McInputAction__Sequence
{
  aimdk_msgs__msg__McInputAction * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McInputAction__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_INPUT_ACTION__STRUCT_H_
