// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/PlayTtsRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/play_tts_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_PlayTtsRequest_is_interrupted
{
public:
  explicit Init_PlayTtsRequest_is_interrupted(::aimdk_msgs::msg::PlayTtsRequest & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::PlayTtsRequest is_interrupted(::aimdk_msgs::msg::PlayTtsRequest::_is_interrupted_type arg)
  {
    msg_.is_interrupted = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

class Init_PlayTtsRequest_trace_id
{
public:
  explicit Init_PlayTtsRequest_trace_id(::aimdk_msgs::msg::PlayTtsRequest & msg)
  : msg_(msg)
  {}
  Init_PlayTtsRequest_is_interrupted trace_id(::aimdk_msgs::msg::PlayTtsRequest::_trace_id_type arg)
  {
    msg_.trace_id = std::move(arg);
    return Init_PlayTtsRequest_is_interrupted(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

class Init_PlayTtsRequest_domain
{
public:
  explicit Init_PlayTtsRequest_domain(::aimdk_msgs::msg::PlayTtsRequest & msg)
  : msg_(msg)
  {}
  Init_PlayTtsRequest_trace_id domain(::aimdk_msgs::msg::PlayTtsRequest::_domain_type arg)
  {
    msg_.domain = std::move(arg);
    return Init_PlayTtsRequest_trace_id(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

class Init_PlayTtsRequest_priority_weight
{
public:
  explicit Init_PlayTtsRequest_priority_weight(::aimdk_msgs::msg::PlayTtsRequest & msg)
  : msg_(msg)
  {}
  Init_PlayTtsRequest_domain priority_weight(::aimdk_msgs::msg::PlayTtsRequest::_priority_weight_type arg)
  {
    msg_.priority_weight = std::move(arg);
    return Init_PlayTtsRequest_domain(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

class Init_PlayTtsRequest_priority_level
{
public:
  explicit Init_PlayTtsRequest_priority_level(::aimdk_msgs::msg::PlayTtsRequest & msg)
  : msg_(msg)
  {}
  Init_PlayTtsRequest_priority_weight priority_level(::aimdk_msgs::msg::PlayTtsRequest::_priority_level_type arg)
  {
    msg_.priority_level = std::move(arg);
    return Init_PlayTtsRequest_priority_weight(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

class Init_PlayTtsRequest_text
{
public:
  Init_PlayTtsRequest_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayTtsRequest_priority_level text(::aimdk_msgs::msg::PlayTtsRequest::_text_type arg)
  {
    msg_.text = std::move(arg);
    return Init_PlayTtsRequest_priority_level(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::PlayTtsRequest>()
{
  return aimdk_msgs::msg::builder::Init_PlayTtsRequest_text();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__BUILDER_HPP_
