// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetMcAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_mc_action__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetMcAction_Request_request
{
public:
  Init_GetMcAction_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetMcAction_Request request(::aimdk_msgs::srv::GetMcAction_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetMcAction_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetMcAction_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetMcAction_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetMcAction_Response_info
{
public:
  explicit Init_GetMcAction_Response_info(::aimdk_msgs::srv::GetMcAction_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetMcAction_Response info(::aimdk_msgs::srv::GetMcAction_Response::_info_type arg)
  {
    msg_.info = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetMcAction_Response msg_;
};

class Init_GetMcAction_Response_header
{
public:
  Init_GetMcAction_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetMcAction_Response_info header(::aimdk_msgs::srv::GetMcAction_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GetMcAction_Response_info(msg_);
  }

private:
  ::aimdk_msgs::srv::GetMcAction_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetMcAction_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetMcAction_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__BUILDER_HPP_
