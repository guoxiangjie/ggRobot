// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.h"
// Member 'left_hand_type'
// Member 'right_hand_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.h"
// Member 'left_hands'
// Member 'right_hands'
#include "aimdk_msgs/msg/detail/hand_command__struct.h"

/// Struct defined in msg/HandCommandArray in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__HandCommandArray
{
  aimdk_msgs__msg__MessageHeader header;
  aimdk_msgs__msg__HandType left_hand_type;
  aimdk_msgs__msg__HandCommand__Sequence left_hands;
  aimdk_msgs__msg__HandType right_hand_type;
  aimdk_msgs__msg__HandCommand__Sequence right_hands;
} aimdk_msgs__msg__HandCommandArray;

// Struct for a sequence of aimdk_msgs__msg__HandCommandArray.
typedef struct aimdk_msgs__msg__HandCommandArray__Sequence
{
  aimdk_msgs__msg__HandCommandArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__HandCommandArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_H_
