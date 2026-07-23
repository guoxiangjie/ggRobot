// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetCurrentInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__struct.h"

/// Struct defined in srv/GetCurrentInputSource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetCurrentInputSource_Request
{
  /// Request 部分
  aimdk_msgs__msg__CommonRequest request;
} aimdk_msgs__srv__GetCurrentInputSource_Request;

// Struct for a sequence of aimdk_msgs__srv__GetCurrentInputSource_Request.
typedef struct aimdk_msgs__srv__GetCurrentInputSource_Request__Sequence
{
  aimdk_msgs__srv__GetCurrentInputSource_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetCurrentInputSource_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__struct.h"
// Member 'input_source'
#include "aimdk_msgs/msg/detail/mc_input_source__struct.h"

/// Struct defined in srv/GetCurrentInputSource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetCurrentInputSource_Response
{
  aimdk_msgs__msg__CommonTaskResponse response;
  aimdk_msgs__msg__McInputSource input_source;
} aimdk_msgs__srv__GetCurrentInputSource_Response;

// Struct for a sequence of aimdk_msgs__srv__GetCurrentInputSource_Response.
typedef struct aimdk_msgs__srv__GetCurrentInputSource_Response__Sequence
{
  aimdk_msgs__srv__GetCurrentInputSource_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetCurrentInputSource_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_H_
