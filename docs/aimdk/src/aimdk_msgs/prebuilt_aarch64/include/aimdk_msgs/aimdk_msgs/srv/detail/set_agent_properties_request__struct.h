// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetAgentPropertiesRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_H_

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
// Member 'contents'
#include "aimdk_msgs/msg/detail/agent_properties__struct.h"

/// Struct defined in srv/SetAgentPropertiesRequest in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetAgentPropertiesRequest_Request
{
  aimdk_msgs__msg__CommonRequest header;
  aimdk_msgs__msg__AgentProperties contents;
} aimdk_msgs__srv__SetAgentPropertiesRequest_Request;

// Struct for a sequence of aimdk_msgs__srv__SetAgentPropertiesRequest_Request.
typedef struct aimdk_msgs__srv__SetAgentPropertiesRequest_Request__Sequence
{
  aimdk_msgs__srv__SetAgentPropertiesRequest_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetAgentPropertiesRequest_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"

/// Struct defined in srv/SetAgentPropertiesRequest in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetAgentPropertiesRequest_Response
{
  aimdk_msgs__msg__CommonResponse header;
} aimdk_msgs__srv__SetAgentPropertiesRequest_Response;

// Struct for a sequence of aimdk_msgs__srv__SetAgentPropertiesRequest_Response.
typedef struct aimdk_msgs__srv__SetAgentPropertiesRequest_Response__Sequence
{
  aimdk_msgs__srv__SetAgentPropertiesRequest_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetAgentPropertiesRequest_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_H_
