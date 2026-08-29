// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/QRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__QR_POINT__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__QR_POINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'qr_code'
#include "aimdk_msgs/msg/detail/qr_code__struct.h"

/// Struct defined in msg/QRPoint in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 二维码点的数据结构
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__QRPoint
{
  /// -------------------------------------------------------------
  /// 点位id
  int32_t point_id;
  /// -------------------------------------------------------------
  /// 二维码
  aimdk_msgs__msg__QRCode qr_code;
} aimdk_msgs__msg__QRPoint;

// Struct for a sequence of aimdk_msgs__msg__QRPoint.
typedef struct aimdk_msgs__msg__QRPoint__Sequence
{
  aimdk_msgs__msg__QRPoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__QRPoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__QR_POINT__STRUCT_H_
