// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McActionCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'action'
#include "aimdk_msgs/msg/detail/mc_action__struct.h"
// Member 'action_desc'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/McActionCommand in the package aimdk_msgs.
/**
  * Action
 */
typedef struct aimdk_msgs__msg__McActionCommand
{
  aimdk_msgs__msg__McAction action;
  /// 描述
  rosidl_runtime_c__String action_desc;
} aimdk_msgs__msg__McActionCommand;

// Struct for a sequence of aimdk_msgs__msg__McActionCommand.
typedef struct aimdk_msgs__msg__McActionCommand__Sequence
{
  aimdk_msgs__msg__McActionCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McActionCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_H_
