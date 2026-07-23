// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/srv/detail/get_all_joint_state__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/srv/detail/get_all_joint_state__functions.h"
#include "aimdk_msgs/srv/detail/get_all_joint_state__struct.h"


// Include directives for member types
// Member `request`
#include "aimdk_msgs/msg/common_request.h"
// Member `request`
#include "aimdk_msgs/msg/detail/common_request__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__srv__GetAllJointState_Request__init(message_memory);
}

void aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_fini_function(void * message_memory)
{
  aimdk_msgs__srv__GetAllJointState_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_member_array[1] = {
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Request, request),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_members = {
  "aimdk_msgs__srv",  // message namespace
  "GetAllJointState_Request",  // message name
  1,  // number of fields
  sizeof(aimdk_msgs__srv__GetAllJointState_Request),
  aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_member_array,  // message members
  aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_type_support_handle = {
  0,
  &aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Request)() {
  aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, CommonRequest)();
  if (!aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__srv__GetAllJointState_Request__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "aimdk_msgs/srv/detail/get_all_joint_state__rosidl_typesupport_introspection_c.h"
// already included above
// #include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_all_joint_state__functions.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_all_joint_state__struct.h"


// Include directives for member types
// Member `reponse`
#include "aimdk_msgs/msg/common_response.h"
// Member `reponse`
#include "aimdk_msgs/msg/detail/common_response__rosidl_typesupport_introspection_c.h"
// Member `head_joints`
// Member `arm_joints`
// Member `waist_joints`
// Member `leg_joints`
#include "aimdk_msgs/msg/joint_state.h"
// Member `head_joints`
// Member `arm_joints`
// Member `waist_joints`
// Member `leg_joints`
#include "aimdk_msgs/msg/detail/joint_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__srv__GetAllJointState_Response__init(message_memory);
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_fini_function(void * message_memory)
{
  aimdk_msgs__srv__GetAllJointState_Response__fini(message_memory);
}

size_t aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__head_joints(
  const void * untyped_member)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__head_joints(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__head_joints(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__head_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__JointState * item =
    ((const aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__head_joints(untyped_member, index));
  aimdk_msgs__msg__JointState * value =
    (aimdk_msgs__msg__JointState *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__head_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__JointState * item =
    ((aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__head_joints(untyped_member, index));
  const aimdk_msgs__msg__JointState * value =
    (const aimdk_msgs__msg__JointState *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__head_joints(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  aimdk_msgs__msg__JointState__Sequence__fini(member);
  return aimdk_msgs__msg__JointState__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__arm_joints(
  const void * untyped_member)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__arm_joints(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__arm_joints(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__arm_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__JointState * item =
    ((const aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__arm_joints(untyped_member, index));
  aimdk_msgs__msg__JointState * value =
    (aimdk_msgs__msg__JointState *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__arm_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__JointState * item =
    ((aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__arm_joints(untyped_member, index));
  const aimdk_msgs__msg__JointState * value =
    (const aimdk_msgs__msg__JointState *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__arm_joints(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  aimdk_msgs__msg__JointState__Sequence__fini(member);
  return aimdk_msgs__msg__JointState__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__waist_joints(
  const void * untyped_member)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__waist_joints(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__waist_joints(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__waist_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__JointState * item =
    ((const aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__waist_joints(untyped_member, index));
  aimdk_msgs__msg__JointState * value =
    (aimdk_msgs__msg__JointState *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__waist_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__JointState * item =
    ((aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__waist_joints(untyped_member, index));
  const aimdk_msgs__msg__JointState * value =
    (const aimdk_msgs__msg__JointState *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__waist_joints(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  aimdk_msgs__msg__JointState__Sequence__fini(member);
  return aimdk_msgs__msg__JointState__Sequence__init(member, size);
}

size_t aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__leg_joints(
  const void * untyped_member)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__leg_joints(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__JointState__Sequence * member =
    (const aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__leg_joints(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__leg_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__JointState * item =
    ((const aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__leg_joints(untyped_member, index));
  aimdk_msgs__msg__JointState * value =
    (aimdk_msgs__msg__JointState *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__leg_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__JointState * item =
    ((aimdk_msgs__msg__JointState *)
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__leg_joints(untyped_member, index));
  const aimdk_msgs__msg__JointState * value =
    (const aimdk_msgs__msg__JointState *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__leg_joints(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__JointState__Sequence * member =
    (aimdk_msgs__msg__JointState__Sequence *)(untyped_member);
  aimdk_msgs__msg__JointState__Sequence__fini(member);
  return aimdk_msgs__msg__JointState__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[5] = {
  {
    "reponse",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Response, reponse),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "head_joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Response, head_joints),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__head_joints,  // size() function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__head_joints,  // get_const(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__head_joints,  // get(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__head_joints,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__head_joints,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__head_joints  // resize(index) function pointer
  },
  {
    "arm_joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Response, arm_joints),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__arm_joints,  // size() function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__arm_joints,  // get_const(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__arm_joints,  // get(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__arm_joints,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__arm_joints,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__arm_joints  // resize(index) function pointer
  },
  {
    "waist_joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Response, waist_joints),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__waist_joints,  // size() function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__waist_joints,  // get_const(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__waist_joints,  // get(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__waist_joints,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__waist_joints,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__waist_joints  // resize(index) function pointer
  },
  {
    "leg_joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__srv__GetAllJointState_Response, leg_joints),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__size_function__GetAllJointState_Response__leg_joints,  // size() function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_const_function__GetAllJointState_Response__leg_joints,  // get_const(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__get_function__GetAllJointState_Response__leg_joints,  // get(index) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__fetch_function__GetAllJointState_Response__leg_joints,  // fetch(index, &value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__assign_function__GetAllJointState_Response__leg_joints,  // assign(index, value) function pointer
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__resize_function__GetAllJointState_Response__leg_joints  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_members = {
  "aimdk_msgs__srv",  // message namespace
  "GetAllJointState_Response",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs__srv__GetAllJointState_Response),
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array,  // message members
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_type_support_handle = {
  0,
  &aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Response)() {
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, CommonResponse)();
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointState)();
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointState)();
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointState)();
  aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, JointState)();
  if (!aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__srv__GetAllJointState_Response__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_all_joint_state__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_members = {
  "aimdk_msgs__srv",  // service namespace
  "GetAllJointState",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_Request_message_type_support_handle,
  NULL  // response message
  // aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_Response_message_type_support_handle
};

static rosidl_service_type_support_t aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_type_support_handle = {
  0,
  &aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState)() {
  if (!aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_type_support_handle.typesupport_identifier) {
    aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, srv, GetAllJointState_Response)()->data;
  }

  return &aimdk_msgs__srv__detail__get_all_joint_state__rosidl_typesupport_introspection_c__GetAllJointState_service_type_support_handle;
}
