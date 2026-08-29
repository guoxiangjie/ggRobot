// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetMcInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__STRUCT_H_

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
// Member 'action'
#include "aimdk_msgs/msg/detail/mc_input_action__struct.h"
// Member 'input_source'
#include "aimdk_msgs/msg/detail/mc_input_source__struct.h"

/// Struct defined in srv/SetMcInputSource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMcInputSource_Request
{
  aimdk_msgs__msg__CommonRequest request;
  /// ADD MODIFY DELETE DISABLE ENABLE
  aimdk_msgs__msg__McInputAction action;
  aimdk_msgs__msg__McInputSource input_source;
} aimdk_msgs__srv__SetMcInputSource_Request;

// Struct for a sequence of aimdk_msgs__srv__SetMcInputSource_Request.
typedef struct aimdk_msgs__srv__SetMcInputSource_Request__Sequence
{
  aimdk_msgs__srv__SetMcInputSource_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMcInputSource_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__struct.h"

/// Struct defined in srv/SetMcInputSource in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetMcInputSource_Response
{
  aimdk_msgs__msg__CommonTaskResponse response;
} aimdk_msgs__srv__SetMcInputSource_Response;

// Struct for a sequence of aimdk_msgs__srv__SetMcInputSource_Response.
typedef struct aimdk_msgs__srv__SetMcInputSource_Response__Sequence
{
  aimdk_msgs__srv__SetMcInputSource_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetMcInputSource_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__STRUCT_H_
