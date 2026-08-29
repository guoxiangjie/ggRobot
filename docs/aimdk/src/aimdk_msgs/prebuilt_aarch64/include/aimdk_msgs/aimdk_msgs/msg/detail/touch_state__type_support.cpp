// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:msg/TouchState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/msg/detail/touch_state__struct.hpp"
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

void TouchState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::msg::TouchState(_init);
}

void TouchState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::msg::TouchState *>(message_memory);
  typed_message->~TouchState();
}

size_t size_function__TouchState__data(const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * get_const_function__TouchState__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint32_t, 8> *>(untyped_member);
  return &member[index];
}

void * get_function__TouchState__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint32_t, 8> *>(untyped_member);
  return &member[index];
}

void fetch_function__TouchState__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__TouchState__data(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__TouchState__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__TouchState__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

size_t size_function__TouchState__threshold(const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * get_const_function__TouchState__threshold(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint32_t, 8> *>(untyped_member);
  return &member[index];
}

void * get_function__TouchState__threshold(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint32_t, 8> *>(untyped_member);
  return &member[index];
}

void fetch_function__TouchState__threshold(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__TouchState__threshold(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__TouchState__threshold(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__TouchState__threshold(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

size_t size_function__TouchState__is_touched(const void * untyped_member)
{
  (void)untyped_member;
  return 8;
}

const void * get_const_function__TouchState__is_touched(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<bool, 8> *>(untyped_member);
  return &member[index];
}

void * get_function__TouchState__is_touched(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<bool, 8> *>(untyped_member);
  return &member[index];
}

void fetch_function__TouchState__is_touched(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const bool *>(
    get_const_function__TouchState__is_touched(untyped_member, index));
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = item;
}

void assign_function__TouchState__is_touched(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<bool *>(
    get_function__TouchState__is_touched(untyped_member, index));
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TouchState_message_member_array[5] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::MessageHeader>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::TouchState, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "event_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::TouchState, event_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::TouchState, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__TouchState__data,  // size() function pointer
    get_const_function__TouchState__data,  // get_const(index) function pointer
    get_function__TouchState__data,  // get(index) function pointer
    fetch_function__TouchState__data,  // fetch(index, &value) function pointer
    assign_function__TouchState__data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "threshold",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::TouchState, threshold),  // bytes offset in struct
    nullptr,  // default value
    size_function__TouchState__threshold,  // size() function pointer
    get_const_function__TouchState__threshold,  // get_const(index) function pointer
    get_function__TouchState__threshold,  // get(index) function pointer
    fetch_function__TouchState__threshold,  // fetch(index, &value) function pointer
    assign_function__TouchState__threshold,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "is_touched",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    8,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::TouchState, is_touched),  // bytes offset in struct
    nullptr,  // default value
    size_function__TouchState__is_touched,  // size() function pointer
    get_const_function__TouchState__is_touched,  // get_const(index) function pointer
    get_function__TouchState__is_touched,  // get(index) function pointer
    fetch_function__TouchState__is_touched,  // fetch(index, &value) function pointer
    assign_function__TouchState__is_touched,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TouchState_message_members = {
  "aimdk_msgs::msg",  // message namespace
  "TouchState",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs::msg::TouchState),
  TouchState_message_member_array,  // message members
  TouchState_init_function,  // function to initialize message memory (memory has to be allocated)
  TouchState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TouchState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TouchState_message_members,
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
get_message_type_support_handle<aimdk_msgs::msg::TouchState>()
{
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::TouchState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, msg, TouchState)() {
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::TouchState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
