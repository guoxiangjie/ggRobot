// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/QRCode.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__QR_CODE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__QR_CODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/QRCode in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 二维码的数据结构
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__QRCode
{
  /// -------------------------------------------------------------
  /// 二维码值
  int32_t code;
  /// -------------------------------------------------------------
  /// 二维码位姿
  geometry_msgs__msg__Pose pose;
} aimdk_msgs__msg__QRCode;

// Struct for a sequence of aimdk_msgs__msg__QRCode.
typedef struct aimdk_msgs__msg__QRCode__Sequence
{
  aimdk_msgs__msg__QRCode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__QRCode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__QR_CODE__STRUCT_H_
