// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetMcAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_ACTION__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_ACTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_mc_action__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcAction_Request_command
{
public:
  explicit Init_SetMcAction_Request_command(::aimdk_msgs::srv::SetMcAction_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMcAction_Request command(::aimdk_msgs::srv::SetMcAction_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcAction_Request msg_;
};

class Init_SetMcAction_Request_source
{
public:
  explicit Init_SetMcAction_Request_source(::aimdk_msgs::srv::SetMcAction_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcAction_Request_command source(::aimdk_msgs::srv::SetMcAction_Request::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_SetMcAction_Request_command(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcAction_Request msg_;
};

class Init_SetMcAction_Request_header
{
public:
  Init_SetMcAction_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMcAction_Request_source header(::aimdk_msgs::srv::SetMcAction_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SetMcAction_Request_source(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcAction_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcAction_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetMcAction_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcAction_Response_response
{
public:
  Init_SetMcAction_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::SetMcAction_Response response(::aimdk_msgs::srv::SetMcAction_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcAction_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcAction_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetMcAction_Response_response();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_ACTION__BUILDER_HPP_
