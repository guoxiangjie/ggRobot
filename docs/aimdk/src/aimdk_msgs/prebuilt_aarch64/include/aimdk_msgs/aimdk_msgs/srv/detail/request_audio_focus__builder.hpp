// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/RequestAudioFocus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/request_audio_focus__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_RequestAudioFocus_Request_focus_requester
{
public:
  explicit Init_RequestAudioFocus_Request_focus_requester(::aimdk_msgs::srv::RequestAudioFocus_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::RequestAudioFocus_Request focus_requester(::aimdk_msgs::srv::RequestAudioFocus_Request::_focus_requester_type arg)
  {
    msg_.focus_requester = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::RequestAudioFocus_Request msg_;
};

class Init_RequestAudioFocus_Request_request
{
public:
  Init_RequestAudioFocus_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RequestAudioFocus_Request_focus_requester request(::aimdk_msgs::srv::RequestAudioFocus_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_RequestAudioFocus_Request_focus_requester(msg_);
  }

private:
  ::aimdk_msgs::srv::RequestAudioFocus_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::RequestAudioFocus_Request>()
{
  return aimdk_msgs::srv::builder::Init_RequestAudioFocus_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_RequestAudioFocus_Response_focus_response
{
public:
  explicit Init_RequestAudioFocus_Response_focus_response(::aimdk_msgs::srv::RequestAudioFocus_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::RequestAudioFocus_Response focus_response(::aimdk_msgs::srv::RequestAudioFocus_Response::_focus_response_type arg)
  {
    msg_.focus_response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::RequestAudioFocus_Response msg_;
};

class Init_RequestAudioFocus_Response_reponse
{
public:
  Init_RequestAudioFocus_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RequestAudioFocus_Response_focus_response reponse(::aimdk_msgs::srv::RequestAudioFocus_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return Init_RequestAudioFocus_Response_focus_response(msg_);
  }

private:
  ::aimdk_msgs::srv::RequestAudioFocus_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::RequestAudioFocus_Response>()
{
  return aimdk_msgs::srv::builder::Init_RequestAudioFocus_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__BUILDER_HPP_
