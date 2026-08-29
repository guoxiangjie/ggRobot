// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/processed_audio_output__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/processed_audio_output__functions.h"
#include "aimdk_msgs/msg/detail/processed_audio_output__struct.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/message_header.h"
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__rosidl_typesupport_introspection_c.h"
// Member `audio_vad_state`
#include "aimdk_msgs/msg/audio_vad_state_type.h"
// Member `audio_vad_state`
#include "aimdk_msgs/msg/detail/audio_vad_state_type__rosidl_typesupport_introspection_c.h"
// Member `audio_data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__ProcessedAudioOutput__init(message_memory);
}

void aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_fini_function(void * message_memory)
{
  aimdk_msgs__msg__ProcessedAudioOutput__fini(message_memory);
}

size_t aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__size_function__ProcessedAudioOutput__audio_data(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_const_function__ProcessedAudioOutput__audio_data(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_function__ProcessedAudioOutput__audio_data(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__fetch_function__ProcessedAudioOutput__audio_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_const_function__ProcessedAudioOutput__audio_data(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__assign_function__ProcessedAudioOutput__audio_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_function__ProcessedAudioOutput__audio_data(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__resize_function__ProcessedAudioOutput__audio_data(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__ProcessedAudioOutput, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stream_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__ProcessedAudioOutput, stream_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "audio_vad_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__ProcessedAudioOutput, audio_vad_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "audio_data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__ProcessedAudioOutput, audio_data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__size_function__ProcessedAudioOutput__audio_data,  // size() function pointer
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_const_function__ProcessedAudioOutput__audio_data,  // get_const(index) function pointer
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__get_function__ProcessedAudioOutput__audio_data,  // get(index) function pointer
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__fetch_function__ProcessedAudioOutput__audio_data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__assign_function__ProcessedAudioOutput__audio_data,  // assign(index, value) function pointer
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__resize_function__ProcessedAudioOutput__audio_data  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "ProcessedAudioOutput",  // message name
  4,  // number of fields
  sizeof(aimdk_msgs__msg__ProcessedAudioOutput),
  aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_member_array,  // message members
  aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, ProcessedAudioOutput)() {
  aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, MessageHeader)();
  aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, AudioVadStateType)();
  if (!aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__ProcessedAudioOutput__rosidl_typesupport_introspection_c__ProcessedAudioOutput_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
