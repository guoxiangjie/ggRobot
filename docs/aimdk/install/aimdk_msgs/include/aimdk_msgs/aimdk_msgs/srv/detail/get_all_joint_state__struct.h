// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_H_

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

/// Struct defined in srv/GetAllJointState in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetAllJointState_Request
{
  aimdk_msgs__msg__CommonRequest request;
} aimdk_msgs__srv__GetAllJointState_Request;

// Struct for a sequence of aimdk_msgs__srv__GetAllJointState_Request.
typedef struct aimdk_msgs__srv__GetAllJointState_Request__Sequence
{
  aimdk_msgs__srv__GetAllJointState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetAllJointState_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'head_joints'
// Member 'arm_joints'
// Member 'waist_joints'
// Member 'leg_joints'
#include "aimdk_msgs/msg/detail/joint_state__struct.h"

/// Struct defined in srv/GetAllJointState in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetAllJointState_Response
{
  aimdk_msgs__msg__CommonResponse reponse;
  aimdk_msgs__msg__JointState__Sequence head_joints;
  aimdk_msgs__msg__JointState__Sequence arm_joints;
  aimdk_msgs__msg__JointState__Sequence waist_joints;
  aimdk_msgs__msg__JointState__Sequence leg_joints;
} aimdk_msgs__srv__GetAllJointState_Response;

// Struct for a sequence of aimdk_msgs__srv__GetAllJointState_Response.
typedef struct aimdk_msgs__srv__GetAllJointState_Response__Sequence
{
  aimdk_msgs__srv__GetAllJointState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetAllJointState_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_H_
