// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/SlaveDevice.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'ip'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SlaveDevice in the package aimdk_msgs.
/**
  * ------------------------------------------------------------------------------------
  * 群控从节点ip
  * ------------------------------------------------------------------------------------
 */
typedef struct aimdk_msgs__msg__SlaveDevice
{
  rosidl_runtime_c__String ip;
} aimdk_msgs__msg__SlaveDevice;

// Struct for a sequence of aimdk_msgs__msg__SlaveDevice.
typedef struct aimdk_msgs__msg__SlaveDevice__Sequence
{
  aimdk_msgs__msg__SlaveDevice * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__SlaveDevice__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__STRUCT_H_
