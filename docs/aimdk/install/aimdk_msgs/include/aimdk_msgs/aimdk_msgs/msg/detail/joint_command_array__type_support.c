// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/JointCommandArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/joint_command_array__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/joint_command_array__functions.h"
#include "aimdk_msgs/msg/detail/joint_command_array__struct.h"


// Include directives for member types
// Member `header`
#include "aimdk_msgs/msg/message_header.h"
// Member `header`
#include "aimdk_msgs/msg/detail/message_header__rosidl_typesupport_introspection_c.h"
// Member `joints`
#include "aimdk_msgs/msg/joint_command.h"
// Member `joints`
#include "aimdk_msgs/msg/detail/joint_command__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__JointCommandArray__init(message_memory);
}

void aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_fini_function(void * message_memory)
{
  aimdk_msgs__msg__JointCommandArray__fini(message_memory);
}

size_t aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__size_function__JointCommandArray__joints(
  const void * untyped_member)
{
  const aimdk_msgs__msg__JointCommand__Sequence * member =
    (const aimdk_msgs__msg__JointCommand__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_const_function__JointCommandArray__joints(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__JointCommand__Sequence * member =
    (const aimdk_msgs__msg__JointCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_function__JointCommandArray__joints(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__JointCommand__Sequence * member =
    (aimdk_msgs__msg__JointCommand__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__fetch_function__JointCommandArray__joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__JointCommand * item =
    ((const aimdk_msgs__msg__JointCommand *)
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_const_function__JointCommandArray__joints(untyped_member, index));
  aimdk_msgs__msg__JointCommand * value =
    (aimdk_msgs__msg__JointCommand *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__assign_function__JointCommandArray__joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__JointCommand * item =
    ((aimdk_msgs__msg__JointCommand *)
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_function__JointCommandArray__joints(untyped_member, index));
  const aimdk_msgs__msg__JointCommand * value =
    (const aimdk_msgs__msg__JointCommand *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__resize_function__JointCommandArray__joints(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__JointCommand__Sequence * member =
    (aimdk_msgs__msg__JointCommand__Sequence *)(untyped_member);
  aimdk_msgs__msg__JointCommand__Sequence__fini(member);
  return aimdk_msgs__msg__JointCommand__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__JointCommandArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__JointCommandArray, joints),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__size_function__JointCommandArray__joints,  // size() function pointer
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_const_function__JointCommandArray__joints,  // get_const(index) function pointer
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__get_function__JointCommandArray__joints,  // get(index) function pointer
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__fetch_function__JointCommandArray__joints,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__assign_function__JointCommandArray__joints,  // assign(index, value) function pointer
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__resize_function__JointCommandArray__joints  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "JointCommandArray",  // message name
  2,  // number of fields
  sizeof(aimdk_msgs__msg__JointCommandArray),
  aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_member_array,  // message members
  aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointCommandArray)() {
  aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, MessageHeader)();
  aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointCommand)();
  if (!aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__JointCommandArray__rosidl_typesupport_introspection_c__JointCommandArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
