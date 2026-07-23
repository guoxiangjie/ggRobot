// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'points'
#include "geometry_msgs/msg/detail/pose2_d__struct.h"

/// Struct defined in msg/Path in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 路径的数据结构
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__Path
{
  /// -------------------------------------------------------------
  /// 路径id
  int32_t path_id;
  /// -------------------------------------------------------------
  /// 导航点，二维坐标位姿
  geometry_msgs__msg__Pose2D__Sequence points;
} aimdk_msgs__msg__Path;

// Struct for a sequence of aimdk_msgs__msg__Path.
typedef struct aimdk_msgs__msg__Path__Sequence
{
  aimdk_msgs__msg__Path * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__Path__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_H_
