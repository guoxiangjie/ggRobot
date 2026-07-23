// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from aimdk_msgs:msg/AgentProperties.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "aimdk_msgs/msg/detail/agent_properties__rosidl_typesupport_introspection_c.h"
#include "aimdk_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "aimdk_msgs/msg/detail/agent_properties__functions.h"
#include "aimdk_msgs/msg/detail/agent_properties__struct.h"


// Include directives for member types
// Member `properties`
#include "aimdk_msgs/msg/agent_properties_value.h"
// Member `properties`
#include "aimdk_msgs/msg/detail/agent_properties_value__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  aimdk_msgs__msg__AgentProperties__init(message_memory);
}

void aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_fini_function(void * message_memory)
{
  aimdk_msgs__msg__AgentProperties__fini(message_memory);
}

size_t aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__size_function__AgentProperties__properties(
  const void * untyped_member)
{
  const aimdk_msgs__msg__AgentPropertiesValue__Sequence * member =
    (const aimdk_msgs__msg__AgentPropertiesValue__Sequence *)(untyped_member);
  return member->size;
}

const void * aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_const_function__AgentProperties__properties(
  const void * untyped_member, size_t index)
{
  const aimdk_msgs__msg__AgentPropertiesValue__Sequence * member =
    (const aimdk_msgs__msg__AgentPropertiesValue__Sequence *)(untyped_member);
  return &member->data[index];
}

void * aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_function__AgentProperties__properties(
  void * untyped_member, size_t index)
{
  aimdk_msgs__msg__AgentPropertiesValue__Sequence * member =
    (aimdk_msgs__msg__AgentPropertiesValue__Sequence *)(untyped_member);
  return &member->data[index];
}

void aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__fetch_function__AgentProperties__properties(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const aimdk_msgs__msg__AgentPropertiesValue * item =
    ((const aimdk_msgs__msg__AgentPropertiesValue *)
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_const_function__AgentProperties__properties(untyped_member, index));
  aimdk_msgs__msg__AgentPropertiesValue * value =
    (aimdk_msgs__msg__AgentPropertiesValue *)(untyped_value);
  *value = *item;
}

void aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__assign_function__AgentProperties__properties(
  void * untyped_member, size_t index, const void * untyped_value)
{
  aimdk_msgs__msg__AgentPropertiesValue * item =
    ((aimdk_msgs__msg__AgentPropertiesValue *)
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_function__AgentProperties__properties(untyped_member, index));
  const aimdk_msgs__msg__AgentPropertiesValue * value =
    (const aimdk_msgs__msg__AgentPropertiesValue *)(untyped_value);
  *item = *value;
}

bool aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__resize_function__AgentProperties__properties(
  void * untyped_member, size_t size)
{
  aimdk_msgs__msg__AgentPropertiesValue__Sequence * member =
    (aimdk_msgs__msg__AgentPropertiesValue__Sequence *)(untyped_member);
  aimdk_msgs__msg__AgentPropertiesValue__Sequence__fini(member);
  return aimdk_msgs__msg__AgentPropertiesValue__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_member_array[1] = {
  {
    "properties",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs__msg__AgentProperties, properties),  // bytes offset in struct
    NULL,  // default value
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__size_function__AgentProperties__properties,  // size() function pointer
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_const_function__AgentProperties__properties,  // get_const(index) function pointer
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__get_function__AgentProperties__properties,  // get(index) function pointer
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__fetch_function__AgentProperties__properties,  // fetch(index, &value) function pointer
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__assign_function__AgentProperties__properties,  // assign(index, value) function pointer
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__resize_function__AgentProperties__properties  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_members = {
  "aimdk_msgs__msg",  // message namespace
  "AgentProperties",  // message name
  1,  // number of fields
  sizeof(aimdk_msgs__msg__AgentProperties),
  aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_member_array,  // message members
  aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_init_function,  // function to initialize message memory (memory has to be allocated)
  aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_type_support_handle = {
  0,
  &aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_aimdk_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, AgentProperties)() {
  aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, aimdk_msgs, msg, AgentPropertiesValue)();
  if (!aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_type_support_handle.typesupport_identifier) {
    aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &aimdk_msgs__msg__AgentProperties__rosidl_typesupport_introspection_c__AgentProperties_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
