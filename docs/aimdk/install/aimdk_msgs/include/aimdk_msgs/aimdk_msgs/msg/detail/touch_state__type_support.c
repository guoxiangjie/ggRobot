// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/TouchState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/touch_state__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/touch_state__functions.h"
#include "aimdk_msgs/msg/detail/touch_state__struct.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/message_header.h"
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__TouchState__init(message_memory);
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_fini_function(void * message_memory)
{
  aimdk_msgs__msg__TouchState__fini(message_memory);
}

size_t aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__data(
  const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__data(
  const void * untyped_member, size_t index)
{
  const uint32_t * member =
    (const uint32_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__data(
  void * untyped_member, size_t index)
{
  uint32_t * member =
    (uint32_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__data(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__data(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__threshold(
  const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__threshold(
  const void * untyped_member, size_t index)
{
  const uint32_t * member =
    (const uint32_t *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__threshold(
  void * untyped_member, size_t index)
{
  uint32_t * member =
    (uint32_t *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__threshold(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__threshold(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__threshold(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__threshold(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

size_t aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__is_touched(
  const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__is_touched(
  const void * untyped_member, size_t index)
{
  const bool * member =
    (const bool *)(untyped_member);
  return &member[index];
}

void * aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__is_touched(
  void * untyped_member, size_t index)
{
  bool * member =
    (bool *)(untyped_member);
  return &member[index];
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__is_touched(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__is_touched(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__is_touched(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__is_touched(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__TouchState, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "event_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__TouchState, event_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__TouchState, data),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__data,  // size() function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__data,  // get_const(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__data,  // get(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__data,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__data,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "threshold",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__TouchState, threshold),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__threshold,  // size() function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__threshold,  // get_const(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__threshold,  // get(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__threshold,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__threshold,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_touched",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__TouchState, is_touched),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__size_function__TouchState__is_touched,  // size() function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_const_function__TouchState__is_touched,  // get_const(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__get_function__TouchState__is_touched,  // get(index) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__fetch_function__TouchState__is_touched,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__assign_function__TouchState__is_touched,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "TouchState",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs__msg__TouchState),
  aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_member_array,  // message members
  aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, TouchState)() {
  aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, MessageHeader)();
  if (!aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__TouchState__rosidl_typesupport_introspection_c__TouchState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
