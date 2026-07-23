// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/PlayTts.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/play_tts__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_PlayTts_Request_tts_req
{
public:
  explicit Init_PlayTts_Request_tts_req(::aimdk_msgs::srv::PlayTts_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::PlayTts_Request tts_req(::aimdk_msgs::srv::PlayTts_Request::_tts_req_type arg)
  {
    msg_.tts_req = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayTts_Request msg_;
};

class Init_PlayTts_Request_header
{
public:
  Init_PlayTts_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayTts_Request_tts_req header(::aimdk_msgs::srv::PlayTts_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PlayTts_Request_tts_req(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayTts_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::PlayTts_Request>()
{
  return aimdk_msgs::srv::builder::Init_PlayTts_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_PlayTts_Response_tts_resp
{
public:
  explicit Init_PlayTts_Response_tts_resp(::aimdk_msgs::srv::PlayTts_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::PlayTts_Response tts_resp(::aimdk_msgs::srv::PlayTts_Response::_tts_resp_type arg)
  {
    msg_.tts_resp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayTts_Response msg_;
};

class Init_PlayTts_Response_header
{
public:
  Init_PlayTts_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayTts_Response_tts_resp header(::aimdk_msgs::srv::PlayTts_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PlayTts_Response_tts_resp(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayTts_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::PlayTts_Response>()
{
  return aimdk_msgs::srv::builder::Init_PlayTts_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__BUILDER_HPP_
