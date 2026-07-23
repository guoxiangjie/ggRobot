// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AgentPropertiesValue.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'key'
#include "aimdk_msgs/msg/detail/agent_property_id_type__struct.h"
// Member 'value'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/AgentPropertiesValue in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__AgentPropertiesValue
{
  aimdk_msgs__msg__AgentPropertyIdType key;
  rosidl_runtime_c__String value;
} aimdk_msgs__msg__AgentPropertiesValue;

// Struct for a sequence of aimdk_msgs__msg__AgentPropertiesValue.
typedef struct aimdk_msgs__msg__AgentPropertiesValue__Sequence
{
  aimdk_msgs__msg__AgentPropertiesValue * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AgentPropertiesValue__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_H_
