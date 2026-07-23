// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetMicSourceRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__STRUCT_H_

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

/// Struct defined in srv/SetMicSourceRequest in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMicSourceRequest_Request
{
  aimdk_msgs__msg__CommonRequest header;
  uint32_t mic_source;
} aimdk_msgs__srv__SetMicSourceRequest_Request;

// Struct for a sequence of aimdk_msgs__srv__SetMicSourceRequest_Request.
typedef struct aimdk_msgs__srv__SetMicSourceRequest_Request__Sequence
{
  aimdk_msgs__srv__SetMicSourceRequest_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMicSourceRequest_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"

/// Struct defined in srv/SetMicSourceRequest in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMicSourceRequest_Response
{
  aimdk_msgs__msg__CommonResponse header;
} aimdk_msgs__srv__SetMicSourceRequest_Response;

// Struct for a sequence of aimdk_msgs__srv__SetMicSourceRequest_Response.
typedef struct aimdk_msgs__srv__SetMicSourceRequest_Response__Sequence
{
  aimdk_msgs__srv__SetMicSourceRequest_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMicSourceRequest_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__STRUCT_H_
