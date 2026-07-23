// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetMute.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MUTE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MUTE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_mute__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMute_Request_is_mute
{
public:
  explicit Init_SetMute_Request_is_mute(::aimdk_msgs::srv::SetMute_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMute_Request is_mute(::aimdk_msgs::srv::SetMute_Request::_is_mute_type arg)
  {
    msg_.is_mute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMute_Request msg_;
};

class Init_SetMute_Request_request
{
public:
  Init_SetMute_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMute_Request_is_mute request(::aimdk_msgs::srv::SetMute_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetMute_Request_is_mute(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMute_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMute_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetMute_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMute_Response_is_mute
{
public:
  explicit Init_SetMute_Response_is_mute(::aimdk_msgs::srv::SetMute_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMute_Response is_mute(::aimdk_msgs::srv::SetMute_Response::_is_mute_type arg)
  {
    msg_.is_mute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMute_Response msg_;
};

class Init_SetMute_Response_reponse
{
public:
  Init_SetMute_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMute_Response_is_mute reponse(::aimdk_msgs::srv::SetMute_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return Init_SetMute_Response_is_mute(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMute_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMute_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetMute_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MUTE__BUILDER_HPP_
