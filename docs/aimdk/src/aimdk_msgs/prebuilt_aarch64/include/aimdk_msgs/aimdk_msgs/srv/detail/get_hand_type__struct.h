// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetHandType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_H_

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

/// Struct defined in srv/GetHandType in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetHandType_Request
{
  aimdk_msgs__msg__CommonRequest request;
} aimdk_msgs__srv__GetHandType_Request;

// Struct for a sequence of aimdk_msgs__srv__GetHandType_Request.
typedef struct aimdk_msgs__srv__GetHandType_Request__Sequence
{
  aimdk_msgs__srv__GetHandType_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetHandType_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'left_hands_type'
// Member 'right_hands_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.h"

/// Struct defined in srv/GetHandType in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetHandType_Response
{
  aimdk_msgs__msg__CommonResponse reponse;
  aimdk_msgs__msg__HandType left_hands_type;
  aimdk_msgs__msg__HandType right_hands_type;
} aimdk_msgs__srv__GetHandType_Response;

// Struct for a sequence of aimdk_msgs__srv__GetHandType_Response.
typedef struct aimdk_msgs__srv__GetHandType_Response__Sequence
{
  aimdk_msgs__srv__GetHandType_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetHandType_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_H_
