// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/DomainErrorState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__STRUCT_H_

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
  * 0: 无状态, 1: 阻尼模式, 2: 下电模式, 3: 下使能模式, 4: CAN通信断连模式, 其他：等同于无状态
  * 无状态
 */
enum
{
  aimdk_msgs__msg__DomainErrorState__NONE = 0
};

/// Constant 'DAMPING'.
/**
  * 阻尼模式
 */
enum
{
  aimdk_msgs__msg__DomainErrorState__DAMPING = 1
};

/// Constant 'POWERDOWN'.
/**
  * 下电模式
 */
enum
{
  aimdk_msgs__msg__DomainErrorState__POWERDOWN = 2
};

/// Constant 'DISABLE'.
/**
  * 下使能模式
 */
enum
{
  aimdk_msgs__msg__DomainErrorState__DISABLE = 3
};

/// Constant 'DISCONNECT'.
/**
  * 通信断连模式
 */
enum
{
  aimdk_msgs__msg__DomainErrorState__DISCONNECT = 4
};

/// Struct defined in msg/DomainErrorState in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__DomainErrorState
{
  uint8_t value;
} aimdk_msgs__msg__DomainErrorState;

// Struct for a sequence of aimdk_msgs__msg__DomainErrorState.
typedef struct aimdk_msgs__msg__DomainErrorState__Sequence
{
  aimdk_msgs__msg__DomainErrorState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__DomainErrorState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__STRUCT_H_
