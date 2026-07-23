// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/PlayMediaFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__STRUCT_H_

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
// Member 'media_file_req'
#include "aimdk_msgs/msg/detail/play_media_file_request__struct.h"

/// Struct defined in srv/PlayMediaFile in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayMediaFile_Request
{
  aimdk_msgs__msg__CommonRequest header;
  aimdk_msgs__msg__PlayMediaFileRequest media_file_req;
} aimdk_msgs__srv__PlayMediaFile_Request;

// Struct for a sequence of aimdk_msgs__srv__PlayMediaFile_Request.
typedef struct aimdk_msgs__srv__PlayMediaFile_Request__Sequence
{
  aimdk_msgs__srv__PlayMediaFile_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayMediaFile_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'tts_resp'
#include "aimdk_msgs/msg/detail/play_tts_response__struct.h"

/// Struct defined in srv/PlayMediaFile in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayMediaFile_Response
{
  aimdk_msgs__msg__CommonResponse header;
  aimdk_msgs__msg__PlayTtsResponse tts_resp;
} aimdk_msgs__srv__PlayMediaFile_Response;

// Struct for a sequence of aimdk_msgs__srv__PlayMediaFile_Response.
typedef struct aimdk_msgs__srv__PlayMediaFile_Response__Sequence
{
  aimdk_msgs__srv__PlayMediaFile_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayMediaFile_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__STRUCT_H_
