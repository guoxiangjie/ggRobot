// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AgentProperties.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'properties'
#include "aimdk_msgs/msg/detail/agent_properties_value__struct.h"

/// Struct defined in msg/AgentProperties in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__AgentProperties
{
  aimdk_msgs__msg__AgentPropertiesValue__Sequence properties;
} aimdk_msgs__msg__AgentProperties;

// Struct for a sequence of aimdk_msgs__msg__AgentProperties.
typedef struct aimdk_msgs__msg__AgentProperties__Sequence
{
  aimdk_msgs__msg__AgentProperties * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AgentProperties__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_H_
