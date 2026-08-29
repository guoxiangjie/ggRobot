// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/ResponseHeader.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/ResponseHeader in the package aimdk_msgs.
/**
  * World time stamp, which is expressed as seconds and nanoseconds.
 */
typedef struct aimdk_msgs__msg__ResponseHeader
{
  builtin_interfaces__msg__Time stamp;
  /// Return code, 0 for success, others for failure.
  int64_t code;
} aimdk_msgs__msg__ResponseHeader;

// Struct for a sequence of aimdk_msgs__msg__ResponseHeader.
typedef struct aimdk_msgs__msg__ResponseHeader__Sequence
{
  aimdk_msgs__msg__ResponseHeader * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__ResponseHeader__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_H_
