// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/JointCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_

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

/// Struct defined in msg/JointCommand in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__JointCommand
{
  rosidl_runtime_c__String name;
  double position;
  double velocity;
  double effort;
  double stiffness;
  double damping;
} aimdk_msgs__msg__JointCommand;

// Struct for a sequence of aimdk_msgs__msg__JointCommand.
typedef struct aimdk_msgs__msg__JointCommand__Sequence
{
  aimdk_msgs__msg__JointCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__JointCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__JOINT_COMMAND__STRUCT_H_
