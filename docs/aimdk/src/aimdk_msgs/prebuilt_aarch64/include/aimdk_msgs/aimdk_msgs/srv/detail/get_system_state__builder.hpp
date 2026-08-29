// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetSystemState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_system_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetSystemState_Request_header
{
public:
  Init_GetSystemState_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetSystemState_Request header(::aimdk_msgs::srv::GetSystemState_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetSystemState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetSystemState_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetSystemState_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetSystemState_Response_curr_status
{
public:
  explicit Init_GetSystemState_Response_curr_status(::aimdk_msgs::srv::GetSystemState_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetSystemState_Response curr_status(::aimdk_msgs::srv::GetSystemState_Response::_curr_status_type arg)
  {
    msg_.curr_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetSystemState_Response msg_;
};

class Init_GetSystemState_Response_cur_state
{
public:
  explicit Init_GetSystemState_Response_cur_state(::aimdk_msgs::srv::GetSystemState_Response & msg)
  : msg_(msg)
  {}
  Init_GetSystemState_Response_curr_status cur_state(::aimdk_msgs::srv::GetSystemState_Response::_cur_state_type arg)
  {
    msg_.cur_state = std::move(arg);
    return Init_GetSystemState_Response_curr_status(msg_);
  }

private:
  ::aimdk_msgs::srv::GetSystemState_Response msg_;
};

class Init_GetSystemState_Response_header
{
public:
  Init_GetSystemState_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetSystemState_Response_cur_state header(::aimdk_msgs::srv::GetSystemState_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GetSystemState_Response_cur_state(msg_);
  }

private:
  ::aimdk_msgs::srv::GetSystemState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetSystemState_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetSystemState_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__BUILDER_HPP_
