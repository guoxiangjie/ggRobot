// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetSystemState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_H_

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
#include "aimdk_msgs/msg/detail/common_request__struct.h"

/// Struct defined in srv/GetSystemState in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetSystemState_Request
{
  /// --------------------------------------------------------------------------------------------------------------
  /// 获取系统状态
  /// --------------------------------------------------------------------------------------------------------------
  /// ----------------------------------------------------
  /// 请求头
  aimdk_msgs__msg__CommonRequest header;
} aimdk_msgs__srv__GetSystemState_Request;

// Struct for a sequence of aimdk_msgs__srv__GetSystemState_Request.
typedef struct aimdk_msgs__srv__GetSystemState_Request__Sequence
{
  aimdk_msgs__srv__GetSystemState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetSystemState_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'cur_state'
#include "rosidl_runtime_c/string.h"
// Member 'curr_status'
#include "aimdk_msgs/msg/detail/system_status__struct.h"

/// Struct defined in srv/GetSystemState in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetSystemState_Response
{
  /// ---------------------------------------------------- resp
  /// 响应头
  aimdk_msgs__msg__CommonResponse header;
  /// -----------------------------------------------------
  /// 当前系统状态名
  rosidl_runtime_c__String cur_state;
  /// ----------------------------------------------------
  /// 系统当前情况
  aimdk_msgs__msg__SystemStatus curr_status;
} aimdk_msgs__srv__GetSystemState_Response;

// Struct for a sequence of aimdk_msgs__srv__GetSystemState_Response.
typedef struct aimdk_msgs__srv__GetSystemState_Response__Sequence
{
  aimdk_msgs__srv__GetSystemState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetSystemState_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_H_
