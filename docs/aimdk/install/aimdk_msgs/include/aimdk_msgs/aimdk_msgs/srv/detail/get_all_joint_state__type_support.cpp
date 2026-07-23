// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "aimdk_msgs/srv/detail/get_all_joint_state__struct.hpp"
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

void GetAllJointState_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::srv::GetAllJointState_Request(_init);
}

void GetAllJointState_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::srv::GetAllJointState_Request *>(message_memory);
  typed_message->~GetAllJointState_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetAllJointState_Request_message_member_array[1] = {
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::CommonRequest>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Request, request),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetAllJointState_Request_message_members = {
  "aimdk_msgs::srv",  // message namespace
  "GetAllJointState_Request",  // message name
  1,  // number of fields
  sizeof(aimdk_msgs::srv::GetAllJointState_Request),
  GetAllJointState_Request_message_member_array,  // message members
  GetAllJointState_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetAllJointState_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetAllJointState_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetAllJointState_Request_message_members,
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
get_message_type_support_handle<aimdk_msgs::srv::GetAllJointState_Request>()
{
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetAllJointState_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetAllJointState_Request)() {
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetAllJointState_Request_message_type_support_handle;
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
// #include "aimdk_msgs/srv/detail/get_all_joint_state__struct.hpp"
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

void GetAllJointState_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) aimdk_msgs::srv::GetAllJointState_Response(_init);
}

void GetAllJointState_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<aimdk_msgs::srv::GetAllJointState_Response *>(message_memory);
  typed_message->~GetAllJointState_Response();
}

size_t size_function__GetAllJointState_Response__head_joints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetAllJointState_Response__head_joints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void * get_function__GetAllJointState_Response__head_joints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetAllJointState_Response__head_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(
    get_const_function__GetAllJointState_Response__head_joints(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::JointState *>(untyped_value);
  value = item;
}

void assign_function__GetAllJointState_Response__head_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::JointState *>(
    get_function__GetAllJointState_Response__head_joints(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(untyped_value);
  item = value;
}

void resize_function__GetAllJointState_Response__head_joints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetAllJointState_Response__arm_joints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetAllJointState_Response__arm_joints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void * get_function__GetAllJointState_Response__arm_joints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetAllJointState_Response__arm_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(
    get_const_function__GetAllJointState_Response__arm_joints(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::JointState *>(untyped_value);
  value = item;
}

void assign_function__GetAllJointState_Response__arm_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::JointState *>(
    get_function__GetAllJointState_Response__arm_joints(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(untyped_value);
  item = value;
}

void resize_function__GetAllJointState_Response__arm_joints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetAllJointState_Response__waist_joints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetAllJointState_Response__waist_joints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void * get_function__GetAllJointState_Response__waist_joints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetAllJointState_Response__waist_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(
    get_const_function__GetAllJointState_Response__waist_joints(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::JointState *>(untyped_value);
  value = item;
}

void assign_function__GetAllJointState_Response__waist_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::JointState *>(
    get_function__GetAllJointState_Response__waist_joints(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(untyped_value);
  item = value;
}

void resize_function__GetAllJointState_Response__waist_joints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetAllJointState_Response__leg_joints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetAllJointState_Response__leg_joints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void * get_function__GetAllJointState_Response__leg_joints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetAllJointState_Response__leg_joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(
    get_const_function__GetAllJointState_Response__leg_joints(untyped_member, index));
  auto & value = *reinterpret_cast<aimdk_msgs::msg::JointState *>(untyped_value);
  value = item;
}

void assign_function__GetAllJointState_Response__leg_joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<aimdk_msgs::msg::JointState *>(
    get_function__GetAllJointState_Response__leg_joints(untyped_member, index));
  const auto & value = *reinterpret_cast<const aimdk_msgs::msg::JointState *>(untyped_value);
  item = value;
}

void resize_function__GetAllJointState_Response__leg_joints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<aimdk_msgs::msg::JointState> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetAllJointState_Response_message_member_array[5] = {
  {
    "reponse",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::CommonResponse>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Response, reponse),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "head_joints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::JointState>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Response, head_joints),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetAllJointState_Response__head_joints,  // size() function pointer
    get_const_function__GetAllJointState_Response__head_joints,  // get_const(index) function pointer
    get_function__GetAllJointState_Response__head_joints,  // get(index) function pointer
    fetch_function__GetAllJointState_Response__head_joints,  // fetch(index, &value) function pointer
    assign_function__GetAllJointState_Response__head_joints,  // assign(index, value) function pointer
    resize_function__GetAllJointState_Response__head_joints  // resize(index) function pointer
  },
  {
    "arm_joints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::JointState>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Response, arm_joints),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetAllJointState_Response__arm_joints,  // size() function pointer
    get_const_function__GetAllJointState_Response__arm_joints,  // get_const(index) function pointer
    get_function__GetAllJointState_Response__arm_joints,  // get(index) function pointer
    fetch_function__GetAllJointState_Response__arm_joints,  // fetch(index, &value) function pointer
    assign_function__GetAllJointState_Response__arm_joints,  // assign(index, value) function pointer
    resize_function__GetAllJointState_Response__arm_joints  // resize(index) function pointer
  },
  {
    "waist_joints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::JointState>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Response, waist_joints),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetAllJointState_Response__waist_joints,  // size() function pointer
    get_const_function__GetAllJointState_Response__waist_joints,  // get_const(index) function pointer
    get_function__GetAllJointState_Response__waist_joints,  // get(index) function pointer
    fetch_function__GetAllJointState_Response__waist_joints,  // fetch(index, &value) function pointer
    assign_function__GetAllJointState_Response__waist_joints,  // assign(index, value) function pointer
    resize_function__GetAllJointState_Response__waist_joints  // resize(index) function pointer
  },
  {
    "leg_joints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<aimdk_msgs::msg::JointState>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(aimdk_msgs::srv::GetAllJointState_Response, leg_joints),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetAllJointState_Response__leg_joints,  // size() function pointer
    get_const_function__GetAllJointState_Response__leg_joints,  // get_const(index) function pointer
    get_function__GetAllJointState_Response__leg_joints,  // get(index) function pointer
    fetch_function__GetAllJointState_Response__leg_joints,  // fetch(index, &value) function pointer
    assign_function__GetAllJointState_Response__leg_joints,  // assign(index, value) function pointer
    resize_function__GetAllJointState_Response__leg_joints  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetAllJointState_Response_message_members = {
  "aimdk_msgs::srv",  // message namespace
  "GetAllJointState_Response",  // message name
  5,  // number of fields
  sizeof(aimdk_msgs::srv::GetAllJointState_Response),
  GetAllJointState_Response_message_member_array,  // message members
  GetAllJointState_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetAllJointState_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetAllJointState_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetAllJointState_Response_message_members,
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
get_message_type_support_handle<aimdk_msgs::srv::GetAllJointState_Response>()
{
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetAllJointState_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetAllJointState_Response)() {
  return &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetAllJointState_Response_message_type_support_handle;
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
// #include "aimdk_msgs/srv/detail/get_all_joint_state__struct.hpp"
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
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetAllJointState_service_members = {
  "aimdk_msgs::srv",  // service namespace
  "GetAllJointState",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<aimdk_msgs::srv::GetAllJointState>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t GetAllJointState_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetAllJointState_service_members,
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
get_service_type_support_handle<aimdk_msgs::srv::GetAllJointState>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::aimdk_msgs::srv::rosidl_typesupport_introspection_cpp::GetAllJointState_service_type_support_handle;
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
        ::aimdk_msgs::srv::GetAllJointState_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::aimdk_msgs::srv::GetAllJointState_Response
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
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, aimdk_msgs, srv, GetAllJointState)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<aimdk_msgs::srv::GetAllJointState>();
}

#ifdef __cplusplus
}
#endif
