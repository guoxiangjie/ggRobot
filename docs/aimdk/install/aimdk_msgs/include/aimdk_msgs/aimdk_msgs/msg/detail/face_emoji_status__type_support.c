// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/face_emoji_status__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/face_emoji_status__functions.h"
#include "aimdk_msgs/msg/detail/face_emoji_status__struct.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/message_header.h"
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__rosidl_typesupport_introspection_c.h"
// Member `e_path`
// Member `e_path_list`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__FaceEmojiStatus__init(message_memory);
}

void aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_fini_function(void * message_memory)
{
  aimdk_msgs__msg__FaceEmojiStatus__fini(message_memory);
}

size_t aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__size_function__FaceEmojiStatus__e_path_list(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_const_function__FaceEmojiStatus__e_path_list(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_function__FaceEmojiStatus__e_path_list(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__fetch_function__FaceEmojiStatus__e_path_list(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_const_function__FaceEmojiStatus__e_path_list(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__assign_function__FaceEmojiStatus__e_path_list(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_function__FaceEmojiStatus__e_path_list(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__resize_function__FaceEmojiStatus__e_path_list(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_member_array[8] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "e_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, e_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "e_path_list",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, e_path_list),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__size_function__FaceEmojiStatus__e_path_list,  // size() function pointer
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_const_function__FaceEmojiStatus__e_path_list,  // get_const(index) function pointer
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__get_function__FaceEmojiStatus__e_path_list,  // get(index) function pointer
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__fetch_function__FaceEmojiStatus__e_path_list,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__assign_function__FaceEmojiStatus__e_path_list,  // assign(index, value) function pointer
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__resize_function__FaceEmojiStatus__e_path_list  // resize(index) function pointer
  },
  {
    "e_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, e_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "priority",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, priority),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "time_to_end_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__FaceEmojiStatus, time_to_end_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "FaceEmojiStatus",  // message name
  8,  // number of fields
  sizeof(aimdk_msgs__msg__FaceEmojiStatus),
  aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_member_array,  // message members
  aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, FaceEmojiStatus)() {
  aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, MessageHeader)();
  if (!aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__FaceEmojiStatus__rosidl_typesupport_introspection_c__FaceEmojiStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
