// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/hand_command_array__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/hand_command_array__functions.h"
#include "aimdk_msgs/msg/detail/hand_command_array__struct.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/message_header.h"
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__rosidl_typesupport_introspection_c.h"
// Member `left_hand_type`
// Member `right_hand_type`
#include "aimdk_msgs/msg/hand_type.h"
// Member `left_hand_type`
// Member `right_hand_type`
#include "aimdk_msgs/msg/detail/hand_type__rosidl_typesupport_introspection_c.h"
// Member `left_hands`
// Member `right_hands`
#include "aimdk_msgs/msg/hand_command.h"
// Member `left_hands`
// Member `right_hands`
#include "aimdk_msgs/msg/detail/hand_command__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__HandCommandArray__init(message_memory);
}

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_fini_function(void * message_memory)
{
  aimdk_msgs__msg__HandCommandArray__fini(message_memory);
}

size_t aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__size_function__HandCommandArray__left_hands(
  const void * untyped_member)
{
  const aimdk_msgs__msg__HandCommand__Sequence * member =
    (const aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__left_hands(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__HandCommand__Sequence * member =
    (const aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__left_hands(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__HandCommand__Sequence * member =
    (aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__fetch_function__HandCommandArray__left_hands(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__HandCommand * item =
    ((const aimdk_msgs__msg__HandCommand *)
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__left_hands(untyped_member, index));
  aimdk_msgs__msg__HandCommand * value =
    (aimdk_msgs__msg__HandCommand *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__assign_function__HandCommandArray__left_hands(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__HandCommand * item =
    ((aimdk_msgs__msg__HandCommand *)
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__left_hands(untyped_member, index));
  const aimdk_msgs__msg__HandCommand * value =
    (const aimdk_msgs__msg__HandCommand *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__resize_function__HandCommandArray__left_hands(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__HandCommand__Sequence * member =
    (aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  aimdk_msgs__msg__HandCommand__Sequence__fini(member);
  return aimdk_msgs__msg__HandCommand__Sequence__init(member, size);
}

size_t aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__size_function__HandCommandArray__right_hands(
  const void * untyped_member)
{
  const aimdk_msgs__msg__HandCommand__Sequence * member =
    (const aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__right_hands(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__HandCommand__Sequence * member =
    (const aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__right_hands(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__HandCommand__Sequence * member =
    (aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__fetch_function__HandCommandArray__right_hands(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__HandCommand * item =
    ((const aimdk_msgs__msg__HandCommand *)
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__right_hands(untyped_member, index));
  aimdk_msgs__msg__HandCommand * value =
    (aimdk_msgs__msg__HandCommand *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__assign_function__HandCommandArray__right_hands(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__HandCommand * item =
    ((aimdk_msgs__msg__HandCommand *)
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__right_hands(untyped_member, index));
  const aimdk_msgs__msg__HandCommand * value =
    (const aimdk_msgs__msg__HandCommand *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__resize_function__HandCommandArray__right_hands(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__HandCommand__Sequence * member =
    (aimdk_msgs__msg__HandCommand__Sequence *)(untyped_member);
  aimdk_msgs__msg__HandCommand__Sequence__fini(member);
  return aimdk_msgs__msg__HandCommand__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandCommandArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_hand_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandCommandArray, left_hand_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_hands",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandCommandArray, left_hands),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__size_function__HandCommandArray__left_hands,  // size() function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__left_hands,  // get_const(index) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__left_hands,  // get(index) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__fetch_function__HandCommandArray__left_hands,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__assign_function__HandCommandArray__left_hands,  // assign(index, value) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__resize_function__HandCommandArray__left_hands  // resize(index) function pointer
  },
  {
    "right_hand_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandCommandArray, right_hand_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_hands",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__HandCommandArray, right_hands),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__size_function__HandCommandArray__right_hands,  // size() function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_const_function__HandCommandArray__right_hands,  // get_const(index) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__get_function__HandCommandArray__right_hands,  // get(index) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__fetch_function__HandCommandArray__right_hands,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__assign_function__HandCommandArray__right_hands,  // assign(index, value) function pointer
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__resize_function__HandCommandArray__right_hands  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "HandCommandArray",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs__msg__HandCommandArray),
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array,  // message members
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandCommandArray)() {
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, MessageHeader)();
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandType)();
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandCommand)();
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandType)();
  aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, HandCommand)();
  if (!aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__HandCommandArray__rosidl_typesupport_introspection_c__HandCommandArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
