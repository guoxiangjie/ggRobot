// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace aimdk_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetStoredMapByName_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::srv::GetStoredMapByName_Request(_init);
}

void GetStoredMapByName_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::srv::GetStoredMapByName_Request *>(message_memory);
  typed_message->~GetStoredMapByName_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetStoredMapByName_Request_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Request, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Request, map_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetStoredMapByName_Request_message_members = {
  "aimdk_msgs::srv",  // message namespace
  "GetStoredMapByName_Request",  // message name
  2,  // number of fields
  sizeof(aimdk_msgs::srv::GetStoredMapByName_Request),
  GetStoredMapByName_Request_message_member_array,  // message members
  GetStoredMapByName_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetStoredMapByName_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetStoredMapByName_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetStoredMapByName_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace aimdk_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aimdk_msgs::srv::GetStoredMapByName_Request>()
{
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetStoredMapByName_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetStoredMapByName_Request)() {
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetStoredMapByName_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace aimdk_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetStoredMapByName_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::srv::GetStoredMapByName_Response(_init);
}

void GetStoredMapByName_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::srv::GetStoredMapByName_Response *>(message_memory);
  typed_message->~GetStoredMapByName_Response();
}

size_t size_function__GetStoredMapByName_Response__data(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int8_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__data(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int8_t> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__data(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int8_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__data(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int8_t *>(
    get_const_function__GetStoredMapByName_Response__data(untyped_member, index));
  auto & value = *reinterpret_cast<int8_t *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__data(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int8_t *>(
    get_function__GetStoredMapByName_Response__data(untyped_member, index));
  const auto & value = *reinterpret_cast<const int8_t *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__data(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int8_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetStoredMapByName_Response__navi_points(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::NaviPoint> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__navi_points(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::NaviPoint> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__navi_points(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::NaviPoint> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__navi_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::NaviPoint *>(
    get_const_function__GetStoredMapByName_Response__navi_points(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::NaviPoint *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__navi_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::NaviPoint *>(
    get_function__GetStoredMapByName_Response__navi_points(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::NaviPoint *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__navi_points(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::NaviPoint> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetStoredMapByName_Response__qr_points(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::QRPoint> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__qr_points(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::QRPoint> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__qr_points(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::QRPoint> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__qr_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::QRPoint *>(
    get_const_function__GetStoredMapByName_Response__qr_points(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::QRPoint *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__qr_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::QRPoint *>(
    get_function__GetStoredMapByName_Response__qr_points(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::QRPoint *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__qr_points(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::QRPoint> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetStoredMapByName_Response__hr_points(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::HRPoint> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__hr_points(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::HRPoint> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__hr_points(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::HRPoint> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__hr_points(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::HRPoint *>(
    get_const_function__GetStoredMapByName_Response__hr_points(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::HRPoint *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__hr_points(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::HRPoint *>(
    get_function__GetStoredMapByName_Response__hr_points(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::HRPoint *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__hr_points(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::HRPoint> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetStoredMapByName_Response__paths(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::Path> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__paths(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::Path> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__paths(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::Path> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__paths(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::Path *>(
    get_const_function__GetStoredMapByName_Response__paths(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::Path *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__paths(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::Path *>(
    get_function__GetStoredMapByName_Response__paths(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::Path *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__paths(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::Path> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetStoredMapByName_Response__regions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::Region> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetStoredMapByName_Response__regions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::Region> *>(untyped_member);
  return &member[index];
}

void * get_function__GetStoredMapByName_Response__regions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::Region> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetStoredMapByName_Response__regions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::Region *>(
    get_const_function__GetStoredMapByName_Response__regions(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::Region *>(untyped_value);
  value = item;
}

void assign_function__GetStoredMapByName_Response__regions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::Region *>(
    get_function__GetStoredMapByName_Response__regions(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::Region *>(untyped_value);
  item = value;
}

void resize_function__GetStoredMapByName_Response__regions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::Region> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetStoredMapByName_Response_message_member_array[12] = {
  {
    "code",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, code),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<nav_msgs::msg::MapMetaData>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, map_info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_version",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, map_version),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_path",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, map_path),  // bytes offset in struct
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
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, data),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__data,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__data,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__data,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__data,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__data,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__data  // resize(index) function pointer
  },
  {
    "navi_points",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::NaviPoint>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, navi_points),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__navi_points,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__navi_points,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__navi_points,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__navi_points,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__navi_points,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__navi_points  // resize(index) function pointer
  },
  {
    "qr_points",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::QRPoint>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, qr_points),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__qr_points,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__qr_points,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__qr_points,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__qr_points,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__qr_points,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__qr_points  // resize(index) function pointer
  },
  {
    "hr_points",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::HRPoint>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, hr_points),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__hr_points,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__hr_points,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__hr_points,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__hr_points,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__hr_points,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__hr_points  // resize(index) function pointer
  },
  {
    "paths",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::Path>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, paths),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__paths,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__paths,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__paths,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__paths,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__paths,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__paths  // resize(index) function pointer
  },
  {
    "regions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::Region>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, regions),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetStoredMapByName_Response__regions,  // size() function pointer
    get_const_function__GetStoredMapByName_Response__regions,  // get_const(index) function pointer
    get_function__GetStoredMapByName_Response__regions,  // get(index) function pointer
    fetch_function__GetStoredMapByName_Response__regions,  // fetch(index, &value) function pointer
    assign_function__GetStoredMapByName_Response__regions,  // assign(index, value) function pointer
    resize_function__GetStoredMapByName_Response__regions  // resize(index) function pointer
  },
  {
    "map_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetStoredMapByName_Response, map_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetStoredMapByName_Response_message_members = {
  "aimdk_msgs::srv",  // message namespace
  "GetStoredMapByName_Response",  // message name
  12,  // number of fields
  sizeof(aimdk_msgs::srv::GetStoredMapByName_Response),
  GetStoredMapByName_Response_message_member_array,  // message members
  GetStoredMapByName_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetStoredMapByName_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetStoredMapByName_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetStoredMapByName_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace aimdk_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<aimdk_msgs::srv::GetStoredMapByName_Response>()
{
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetStoredMapByName_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetStoredMapByName_Response)() {
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetStoredMapByName_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace aimdk_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetStoredMapByName_service_members = {
  "aimdk_msgs::srv",  // service namespace
  "GetStoredMapByName",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<aimdk_msgs::srv::GetStoredMapByName>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t GetStoredMapByName_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetStoredMapByName_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace aimdk_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<aimdk_msgs::srv::GetStoredMapByName>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetStoredMapByName_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::aimdk_msgs::srv::GetStoredMapByName_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::aimdk_msgs::srv::GetStoredMapByName_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetStoredMapByName)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<aimdk_msgs::srv::GetStoredMapByName>();
}

#ifdef __cplusplus
}
#endif
