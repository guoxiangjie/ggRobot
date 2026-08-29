// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/Region.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'REGION_UNDEFINED'.
enum
{
  aimdk_msgs__msg__Region__REGION_UNDEFINED = 0
};

/// Constant 'REGION_WORKING_SPACE'.
enum
{
  aimdk_msgs__msg__Region__REGION_WORKING_SPACE = 1
};

/// Constant 'REGION_VIRTUAL_WALL'.
enum
{
  aimdk_msgs__msg__Region__REGION_VIRTUAL_WALL = 2
};

/// Constant 'REGION_DRAWING_UNDEFINED'.
enum
{
  aimdk_msgs__msg__Region__REGION_DRAWING_UNDEFINED = 0
};

/// Constant 'REGION_DRAWING_CLOSURE'.
enum
{
  aimdk_msgs__msg__Region__REGION_DRAWING_CLOSURE = 1
};

/// Constant 'REGION_DRAWING_LINES'.
enum
{
  aimdk_msgs__msg__Region__REGION_DRAWING_LINES = 2
};

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"
// Member 'polygon'
#include "geometry_msgs/msg/detail/polygon__struct.h"

/// Struct defined in msg/Region in the package aimdk_msgs.
/**
  * --------------------------------------------------------------------------------------------------------------
  * 拓扑结构的区域状态
  * --------------------------------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__Region
{
  /// -------------------------------------------------------------
  /// 区域类型
  uint8_t type;
  /// -------------------------------------------------------------
  /// 区域绘制类型, closure代表封闭区域， lines代表折线
  uint8_t drawing_type;
  /// -------------------------------------------------------------
  /// 区域名字
  rosidl_runtime_c__String name;
  /// -------------------------------------------------------------
  /// 闭合多边形区域的有序顶点，首尾数据不重合
  geometry_msgs__msg__Polygon polygon;
} aimdk_msgs__msg__Region;

// Struct for a sequence of aimdk_msgs__msg__Region.
typedef struct aimdk_msgs__msg__Region__Sequence
{
  aimdk_msgs__msg__Region * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__Region__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_H_
