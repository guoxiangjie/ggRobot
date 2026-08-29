// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetMcAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_H_

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

/// Struct defined in srv/GetMcAction in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetMcAction_Request
{
  aimdk_msgs__msg__CommonRequest request;
} aimdk_msgs__srv__GetMcAction_Request;

// Struct for a sequence of aimdk_msgs__srv__GetMcAction_Request.
typedef struct aimdk_msgs__srv__GetMcAction_Request__Sequence
{
  aimdk_msgs__srv__GetMcAction_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetMcAction_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__struct.h"
// Member 'info'
#include "aimdk_msgs/msg/detail/mc_action_info__struct.h"

/// Struct defined in srv/GetMcAction in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetMcAction_Response
{
  /// 响应头
  aimdk_msgs__msg__ResponseHeader header;
  /// Action信息
  aimdk_msgs__msg__McActionInfo info;
} aimdk_msgs__srv__GetMcAction_Response;

// Struct for a sequence of aimdk_msgs__srv__GetMcAction_Response.
typedef struct aimdk_msgs__srv__GetMcAction_Response__Sequence
{
  aimdk_msgs__srv__GetMcAction_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetMcAction_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_H_
