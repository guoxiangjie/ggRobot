// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/msg/detail/hand_command_array__struct.hpp"
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

void HandCommandArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::msg::HandCommandArray(_init);
}

void HandCommandArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::msg::HandCommandArray *>(message_memory);
  typed_message->~HandCommandArray();
}

size_t size_function__HandCommandArray__left_hands(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return member->size();
}

const void * get_const_function__HandCommandArray__left_hands(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return &member[index];
}

void * get_function__HandCommandArray__left_hands(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandCommandArray__left_hands(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::HandCommand *>(
    get_const_function__HandCommandArray__left_hands(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::HandCommand *>(untyped_value);
  value = item;
}

void assign_function__HandCommandArray__left_hands(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::HandCommand *>(
    get_function__HandCommandArray__left_hands(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::HandCommand *>(untyped_value);
  item = value;
}

void resize_function__HandCommandArray__left_hands(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  member->resize(size);
}

size_t size_function__HandCommandArray__right_hands(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return member->size();
}

const void * get_const_function__HandCommandArray__right_hands(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return &member[index];
}

void * get_function__HandCommandArray__right_hands(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandCommandArray__right_hands(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::HandCommand *>(
    get_const_function__HandCommandArray__right_hands(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::HandCommand *>(untyped_value);
  value = item;
}

void assign_function__HandCommandArray__right_hands(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::HandCommand *>(
    get_function__HandCommandArray__right_hands(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::HandCommand *>(untyped_value);
  item = value;
}

void resize_function__HandCommandArray__right_hands(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::HandCommand> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember HandCommandArray_message_member_array[5] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::MessageHeader>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandCommandArray, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "left_hand_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::HandType>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandCommandArray, left_hand_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "left_hands",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::HandCommand>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandCommandArray, left_hands),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandCommandArray__left_hands,  // size() function pointer
    get_const_function__HandCommandArray__left_hands,  // get_const(index) function pointer
    get_function__HandCommandArray__left_hands,  // get(index) function pointer
    fetch_function__HandCommandArray__left_hands,  // fetch(index, &value) function pointer
    assign_function__HandCommandArray__left_hands,  // assign(index, value) function pointer
    resize_function__HandCommandArray__left_hands  // resize(index) function pointer
  },
  {
    "right_hand_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::HandType>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandCommandArray, right_hand_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "right_hands",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::HandCommand>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandCommandArray, right_hands),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandCommandArray__right_hands,  // size() function pointer
    get_const_function__HandCommandArray__right_hands,  // get_const(index) function pointer
    get_function__HandCommandArray__right_hands,  // get(index) function pointer
    fetch_function__HandCommandArray__right_hands,  // fetch(index, &value) function pointer
    assign_function__HandCommandArray__right_hands,  // assign(index, value) function pointer
    resize_function__HandCommandArray__right_hands  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers HandCommandArray_message_members = {
  "aimdk_msgs::msg",  // message namespace
  "HandCommandArray",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs::msg::HandCommandArray),
  HandCommandArray_message_member_array,  // message members
  HandCommandArray_init_function,  // function to initialize message memory (memory has to be allocated)
  HandCommandArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t HandCommandArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &HandCommandArray_message_members,
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
get_message_type_support_handle<aimdk_msgs::msg::HandCommandArray>()
{
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::HandCommandArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, msg, HandCommandArray)() {
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::HandCommandArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
