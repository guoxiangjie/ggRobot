// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/RobotResourceMapping.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_ip'
#include "rosidl_runtime_c/string.h"
// Member 'robot_resource_list'
#include "aimdk_msgs/msg/detail/robot_resource__struct.h"

/// Struct defined in msg/RobotResourceMapping in the package aimdk_msgs.
/**
  * ------------------------------------------------------------------------------------
  * 机器人及其资源列表
  * ------------------------------------------------------------------------------------
  * 是否为主控机器人，若为主控机器人，则robot_ip字段为空字符串
 */
typedef struct aimdk_msgs__msg__RobotResourceMapping
{
  bool is_master;
  /// 机器人IP
  rosidl_runtime_c__String robot_ip;
  /// 资源列表
  aimdk_msgs__msg__RobotResource__Sequence robot_resource_list;
} aimdk_msgs__msg__RobotResourceMapping;

// Struct for a sequence of aimdk_msgs__msg__RobotResourceMapping.
typedef struct aimdk_msgs__msg__RobotResourceMapping__Sequence
{
  aimdk_msgs__msg__RobotResourceMapping * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__RobotResourceMapping__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_H_
