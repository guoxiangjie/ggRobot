// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_H_

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
// Member 'qr_list'
#include "aimdk_msgs/msg/detail/qr_code__struct.h"

/// Struct defined in msg/HRPoint in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 高精度点的数据结构
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__HRPoint
{
  /// -------------------------------------------------------------
  /// 点位id
  int32_t point_id;
  /// -------------------------------------------------------------
  /// 高精度点的实时位姿
  geometry_msgs__msg__Pose pose;
  /// -------------------------------------------------------------
  /// 高精度点关联的二维码点坐标
  aimdk_msgs__msg__QRCode__Sequence qr_list;
  /// -------------------------------------------------------------
  /// 是否是头部相机
  bool use_head;
} aimdk_msgs__msg__HRPoint;

// Struct for a sequence of aimdk_msgs__msg__HRPoint.
typedef struct aimdk_msgs__msg__HRPoint__Sequence
{
  aimdk_msgs__msg__HRPoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HRPoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_H_
