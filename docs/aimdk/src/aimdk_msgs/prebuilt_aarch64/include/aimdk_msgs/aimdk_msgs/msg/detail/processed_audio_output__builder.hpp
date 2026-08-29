// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/processed_audio_output__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_ProcessedAudioOutput_audio_data
{
public:
  explicit Init_ProcessedAudioOutput_audio_data(::aimdk_msgs::msg::ProcessedAudioOutput & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::ProcessedAudioOutput audio_data(::aimdk_msgs::msg::ProcessedAudioOutput::_audio_data_type arg)
  {
    msg_.audio_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::ProcessedAudioOutput msg_;
};

class Init_ProcessedAudioOutput_audio_vad_state
{
public:
  explicit Init_ProcessedAudioOutput_audio_vad_state(::aimdk_msgs::msg::ProcessedAudioOutput & msg)
  : msg_(msg)
  {}
  Init_ProcessedAudioOutput_audio_data audio_vad_state(::aimdk_msgs::msg::ProcessedAudioOutput::_audio_vad_state_type arg)
  {
    msg_.audio_vad_state = std::move(arg);
    return Init_ProcessedAudioOutput_audio_data(msg_);
  }

private:
  ::aimdk_msgs::msg::ProcessedAudioOutput msg_;
};

class Init_ProcessedAudioOutput_stream_id
{
public:
  explicit Init_ProcessedAudioOutput_stream_id(::aimdk_msgs::msg::ProcessedAudioOutput & msg)
  : msg_(msg)
  {}
  Init_ProcessedAudioOutput_audio_vad_state stream_id(::aimdk_msgs::msg::ProcessedAudioOutput::_stream_id_type arg)
  {
    msg_.stream_id = std::move(arg);
    return Init_ProcessedAudioOutput_audio_vad_state(msg_);
  }

private:
  ::aimdk_msgs::msg::ProcessedAudioOutput msg_;
};

class Init_ProcessedAudioOutput_header
{
public:
  Init_ProcessedAudioOutput_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ProcessedAudioOutput_stream_id header(::aimdk_msgs::msg::ProcessedAudioOutput::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ProcessedAudioOutput_stream_id(msg_);
  }

private:
  ::aimdk_msgs::msg::ProcessedAudioOutput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::ProcessedAudioOutput>()
{
  return aimdk_msgs::msg::builder::Init_ProcessedAudioOutput_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__BUILDER_HPP_
