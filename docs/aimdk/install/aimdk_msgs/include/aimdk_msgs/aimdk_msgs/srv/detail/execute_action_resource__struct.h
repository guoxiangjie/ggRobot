// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/ExecuteActionResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_H_

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
// Member 'resource_key'
// Member 'resource_version'
// Member 'meta'
#include "rosidl_runtime_c/string.h"
// Member 'slaves'
#include "aimdk_msgs/msg/detail/slave_device__struct.h"

/// Struct defined in srv/ExecuteActionResource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__ExecuteActionResource_Request
{
  /// ----------------------------------------------------
  /// 请求头
  aimdk_msgs__msg__CommonRequest header;
  rosidl_runtime_c__String resource_key;
  rosidl_runtime_c__String resource_version;
  aimdk_msgs__msg__SlaveDevice__Sequence slaves;
  /// 直接使用json
  rosidl_runtime_c__String meta;
} aimdk_msgs__srv__ExecuteActionResource_Request;

// Struct for a sequence of aimdk_msgs__srv__ExecuteActionResource_Request.
typedef struct aimdk_msgs__srv__ExecuteActionResource_Request__Sequence
{
  aimdk_msgs__srv__ExecuteActionResource_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__ExecuteActionResource_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"

/// Struct defined in srv/ExecuteActionResource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__ExecuteActionResource_Response
{
  /// ----------------------------------------------------
  /// 响应头
  aimdk_msgs__msg__CommonResponse header;
} aimdk_msgs__srv__ExecuteActionResource_Response;

// Struct for a sequence of aimdk_msgs__srv__ExecuteActionResource_Response.
typedef struct aimdk_msgs__srv__ExecuteActionResource_Response__Sequence
{
  aimdk_msgs__srv__ExecuteActionResource_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__ExecuteActionResource_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_H_
