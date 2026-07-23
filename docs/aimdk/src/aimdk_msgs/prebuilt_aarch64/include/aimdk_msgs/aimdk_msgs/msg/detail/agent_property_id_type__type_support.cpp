// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:msg/AgentPropertyIdType.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/msg/detail/agent_property_id_type__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace aimdk_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void AgentPropertyIdType_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::msg::AgentPropertyIdType(_init);
}

void AgentPropertyIdType_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::msg::AgentPropertyIdType *>(message_memory);
  typed_message->~AgentPropertyIdType();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember AgentPropertyIdType_message_member_array[1] = {
  {
    "value",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::AgentPropertyIdType, value),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers AgentPropertyIdType_message_members = {
  "aimdk_msgs::msg",  // message namespace
  "AgentPropertyIdType",  // message name
  1,  // number of fields
  sizeof(aimdk_msgs::msg::AgentPropertyIdType),
  AgentPropertyIdType_message_member_array,  // message members
  AgentPropertyIdType_init_function,  // function to initialize message memory (memory has to be allocated)
  AgentPropertyIdType_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t AgentPropertyIdType_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &AgentPropertyIdType_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace aimdk_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aimdk_msgs::msg::AgentPropertyIdType>()
{
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::AgentPropertyIdType_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, msg, AgentPropertyIdType)() {
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::AgentPropertyIdType_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
