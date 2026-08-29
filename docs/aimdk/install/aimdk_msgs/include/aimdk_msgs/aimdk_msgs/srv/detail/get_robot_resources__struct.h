// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetRobotResources.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__STRUCT_H_

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

/// Struct defined in srv/GetRobotResources in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetRobotResources_Request
{
  /// ----------------------------------------------------
  /// 请求头
  aimdk_msgs__msg__CommonRequest header;
} aimdk_msgs__srv__GetRobotResources_Request;

// Struct for a sequence of aimdk_msgs__srv__GetRobotResources_Request.
typedef struct aimdk_msgs__srv__GetRobotResources_Request__Sequence
{
  aimdk_msgs__srv__GetRobotResources_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetRobotResources_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'robot_resources'
#include "aimdk_msgs/msg/detail/robot_resource__struct.h"

/// Struct defined in srv/GetRobotResources in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetRobotResources_Response
{
  /// ----------------------------------------------------
  /// 响应头
  aimdk_msgs__msg__CommonResponse header;
  /// ----------------------------------------------------
  /// 机上资源信息
  aimdk_msgs__msg__RobotResource__Sequence robot_resources;
} aimdk_msgs__srv__GetRobotResources_Response;

// Struct for a sequence of aimdk_msgs__srv__GetRobotResources_Response.
typedef struct aimdk_msgs__srv__GetRobotResources_Response__Sequence
{
  aimdk_msgs__srv__GetRobotResources_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetRobotResources_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__STRUCT_H_
