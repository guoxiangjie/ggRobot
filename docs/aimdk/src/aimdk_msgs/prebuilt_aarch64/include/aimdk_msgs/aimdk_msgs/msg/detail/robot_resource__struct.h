// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/RobotResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'resource_key'
#include "rosidl_runtime_c/string.h"
// Member 'current_version'
#include "aimdk_msgs/msg/detail/current_version__struct.h"

/// Struct defined in msg/RobotResource in the package aimdk_msgs.
/**
  * ------------------------------------------------------------------------------------
  * 机上资源的数据结构
  * ------------------------------------------------------------------------------------
  * 资源key
 */
typedef struct aimdk_msgs__msg__RobotResource
{
  rosidl_runtime_c__String resource_key;
  /// 当前资源版本
  aimdk_msgs__msg__CurrentVersion current_version;
} aimdk_msgs__msg__RobotResource;

// Struct for a sequence of aimdk_msgs__msg__RobotResource.
typedef struct aimdk_msgs__msg__RobotResource__Sequence
{
  aimdk_msgs__msg__RobotResource * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__RobotResource__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_H_
