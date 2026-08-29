// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/NaviPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'navi_point'
#include "geometry_msgs/msg/detail/pose2_d__struct.h"

/// Struct defined in msg/NaviPoint in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 导航点的数据结构
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__NaviPoint
{
  /// -------------------------------------------------------------
  /// 点位id
  int32_t point_id;
  /// -------------------------------------------------------------
  /// 导航点，二维坐标位姿
  geometry_msgs__msg__Pose2D navi_point;
} aimdk_msgs__msg__NaviPoint;

// Struct for a sequence of aimdk_msgs__msg__NaviPoint.
typedef struct aimdk_msgs__msg__NaviPoint__Sequence
{
  aimdk_msgs__msg__NaviPoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__NaviPoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_H_
