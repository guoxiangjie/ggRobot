// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HandCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/HandCommand in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__HandCommand
{
  rosidl_runtime_c__String name;
  double position;
  double velocity;
  double acceleration;
  double deceleration;
  double effort;
} aimdk_msgs__msg__HandCommand;

// Struct for a sequence of aimdk_msgs__msg__HandCommand.
typedef struct aimdk_msgs__msg__HandCommand__Sequence
{
  aimdk_msgs__msg__HandCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HandCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__STRUCT_H_
