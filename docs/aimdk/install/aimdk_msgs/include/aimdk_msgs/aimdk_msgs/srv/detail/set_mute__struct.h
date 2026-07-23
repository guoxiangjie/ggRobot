// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetMute.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MUTE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_MUTE__STRUCT_H_

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

/// Struct defined in srv/SetMute in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMute_Request
{
  /// 请求头
  aimdk_msgs__msg__CommonRequest request;
  /// 请求静音状态
  /// true(mute)
  /// false(unmute)
  bool is_mute;
} aimdk_msgs__srv__SetMute_Request;

// Struct for a sequence of aimdk_msgs__srv__SetMute_Request.
typedef struct aimdk_msgs__srv__SetMute_Request__Sequence
{
  aimdk_msgs__srv__SetMute_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMute_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.h"

/// Struct defined in srv/SetMute in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMute_Response
{
  /// ----------------------------------------------------
  /// response
  /// 响应头
  aimdk_msgs__msg__CommonResponse reponse;
  /// 当前静音状态
  bool is_mute;
} aimdk_msgs__srv__SetMute_Response;

// Struct for a sequence of aimdk_msgs__srv__SetMute_Response.
typedef struct aimdk_msgs__srv__SetMute_Response__Sequence
{
  aimdk_msgs__srv__SetMute_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMute_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MUTE__STRUCT_H_
