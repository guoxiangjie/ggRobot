// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/PlayTtsResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/play_tts_response__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_PlayTtsResponse_estimated_duration
{
public:
  explicit Init_PlayTtsResponse_estimated_duration(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::PlayTtsResponse estimated_duration(::aimdk_msgs::msg::PlayTtsResponse::_estimated_duration_type arg)
  {
    msg_.estimated_duration = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_error_message
{
public:
  explicit Init_PlayTtsResponse_error_message(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_estimated_duration error_message(::aimdk_msgs::msg::PlayTtsResponse::_error_message_type arg)
  {
    msg_.error_message = std::move(arg);
    return Init_PlayTtsResponse_estimated_duration(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_is_success
{
public:
  explicit Init_PlayTtsResponse_is_success(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_error_message is_success(::aimdk_msgs::msg::PlayTtsResponse::_is_success_type arg)
  {
    msg_.is_success = std::move(arg);
    return Init_PlayTtsResponse_error_message(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_trace_id
{
public:
  explicit Init_PlayTtsResponse_trace_id(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_is_success trace_id(::aimdk_msgs::msg::PlayTtsResponse::_trace_id_type arg)
  {
    msg_.trace_id = std::move(arg);
    return Init_PlayTtsResponse_is_success(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_domain
{
public:
  explicit Init_PlayTtsResponse_domain(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_trace_id domain(::aimdk_msgs::msg::PlayTtsResponse::_domain_type arg)
  {
    msg_.domain = std::move(arg);
    return Init_PlayTtsResponse_trace_id(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_priority_weight
{
public:
  explicit Init_PlayTtsResponse_priority_weight(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_domain priority_weight(::aimdk_msgs::msg::PlayTtsResponse::_priority_weight_type arg)
  {
    msg_.priority_weight = std::move(arg);
    return Init_PlayTtsResponse_domain(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_priority_level
{
public:
  explicit Init_PlayTtsResponse_priority_level(::aimdk_msgs::msg::PlayTtsResponse & msg)
  : msg_(msg)
  {}
  Init_PlayTtsResponse_priority_weight priority_level(::aimdk_msgs::msg::PlayTtsResponse::_priority_level_type arg)
  {
    msg_.priority_level = std::move(arg);
    return Init_PlayTtsResponse_priority_weight(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

class Init_PlayTtsResponse_text
{
public:
  Init_PlayTtsResponse_text()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayTtsResponse_priority_level text(::aimdk_msgs::msg::PlayTtsResponse::_text_type arg)
  {
    msg_.text = std::move(arg);
    return Init_PlayTtsResponse_priority_level(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayTtsResponse msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::PlayTtsResponse>()
{
  return aimdk_msgs::msg::builder::Init_PlayTtsResponse_text();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__BUILDER_HPP_
