// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.hpp"
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

void HandTouchSensorData_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::msg::HandTouchSensorData(_init);
}

void HandTouchSensorData_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::msg::HandTouchSensorData *>(message_memory);
  typed_message->~HandTouchSensorData();
}

size_t size_function__HandTouchSensorData__palm_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * get_const_function__HandTouchSensorData__palm_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 36> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__palm_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 36> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__palm_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__palm_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__palm_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__palm_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__back_of_hand_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 36;
}

const void * get_const_function__HandTouchSensorData__back_of_hand_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 36> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__back_of_hand_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 36> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__back_of_hand_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__back_of_hand_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__back_of_hand_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__back_of_hand_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__thumb_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__HandTouchSensorData__thumb_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__thumb_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__thumb_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__thumb_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__thumb_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__thumb_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__index_finger_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__HandTouchSensorData__index_finger_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__index_finger_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__index_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__index_finger_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__index_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__index_finger_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__middle_finger_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__HandTouchSensorData__middle_finger_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__middle_finger_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__middle_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__middle_finger_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__middle_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__middle_finger_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__ring_finger_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__HandTouchSensorData__ring_finger_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__ring_finger_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__ring_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__ring_finger_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__ring_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__ring_finger_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

size_t size_function__HandTouchSensorData__little_finger_touch_data(const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * get_const_function__HandTouchSensorData__little_finger_touch_data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void * get_function__HandTouchSensorData__little_finger_touch_data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<uint8_t, 16> *>(untyped_member);
  return &member[index];
}

void fetch_function__HandTouchSensorData__little_finger_touch_data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint8_t *>(
    get_const_function__HandTouchSensorData__little_finger_touch_data(untyped_member, index));
  auto & value = *reinterpret_cast<uint8_t *>(untyped_value);
  value = item;
}

void assign_function__HandTouchSensorData__little_finger_touch_data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint8_t *>(
    get_function__HandTouchSensorData__little_finger_touch_data(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint8_t *>(untyped_value);
  item = value;
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember HandTouchSensorData_message_member_array[7] = {
  {
    "palm_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, palm_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__palm_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__palm_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__palm_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__palm_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__palm_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "back_of_hand_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    36,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, back_of_hand_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__back_of_hand_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__back_of_hand_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__back_of_hand_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__back_of_hand_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__back_of_hand_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "thumb_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, thumb_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__thumb_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__thumb_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__thumb_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__thumb_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__thumb_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "index_finger_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, index_finger_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__index_finger_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__index_finger_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__index_finger_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__index_finger_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__index_finger_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "middle_finger_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, middle_finger_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__middle_finger_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__middle_finger_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__middle_finger_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__middle_finger_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__middle_finger_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "ring_finger_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, ring_finger_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__ring_finger_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__ring_finger_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__ring_finger_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__ring_finger_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__ring_finger_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "little_finger_touch_data",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::msg::HandTouchSensorData, little_finger_touch_data),  // bytes offset in struct
    nullptr,  // default value
    size_function__HandTouchSensorData__little_finger_touch_data,  // size() function pointer
    get_const_function__HandTouchSensorData__little_finger_touch_data,  // get_const(index) function pointer
    get_function__HandTouchSensorData__little_finger_touch_data,  // get(index) function pointer
    fetch_function__HandTouchSensorData__little_finger_touch_data,  // fetch(index, &value) function pointer
    assign_function__HandTouchSensorData__little_finger_touch_data,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers HandTouchSensorData_message_members = {
  "aimdk_msgs::msg",  // message namespace
  "HandTouchSensorData",  // message name
  7,  // number of fields
  sizeof(aimdk_msgs::msg::HandTouchSensorData),
  HandTouchSensorData_message_member_array,  // message members
  HandTouchSensorData_init_function,  // function to initialize message memory (memory has to be allocated)
  HandTouchSensorData_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t HandTouchSensorData_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &HandTouchSensorData_message_members,
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
get_message_type_support_handle<aimdk_msgs::msg::HandTouchSensorData>()
{
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::HandTouchSensorData_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, msg, HandTouchSensorData)() {
  return &::aimdk_msgs::msg::rosidl_typesupport_introspection_cpp::HandTouchSensorData_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
