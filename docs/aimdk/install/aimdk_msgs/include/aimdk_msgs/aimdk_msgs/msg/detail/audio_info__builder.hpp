// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/AudioInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/audio_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_AudioInfo_coding_format
{
public:
  explicit Init_AudioInfo_coding_format(::aimdk_msgs::msg::AudioInfo & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::AudioInfo coding_format(::aimdk_msgs::msg::AudioInfo::_coding_format_type arg)
  {
    msg_.coding_format = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioInfo msg_;
};

class Init_AudioInfo_sample_format
{
public:
  explicit Init_AudioInfo_sample_format(::aimdk_msgs::msg::AudioInfo & msg)
  : msg_(msg)
  {}
  Init_AudioInfo_coding_format sample_format(::aimdk_msgs::msg::AudioInfo::_sample_format_type arg)
  {
    msg_.sample_format = std::move(arg);
    return Init_AudioInfo_coding_format(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioInfo msg_;
};

class Init_AudioInfo_size
{
public:
  explicit Init_AudioInfo_size(::aimdk_msgs::msg::AudioInfo & msg)
  : msg_(msg)
  {}
  Init_AudioInfo_sample_format size(::aimdk_msgs::msg::AudioInfo::_size_type arg)
  {
    msg_.size = std::move(arg);
    return Init_AudioInfo_sample_format(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioInfo msg_;
};

class Init_AudioInfo_sample_rate
{
public:
  explicit Init_AudioInfo_sample_rate(::aimdk_msgs::msg::AudioInfo & msg)
  : msg_(msg)
  {}
  Init_AudioInfo_size sample_rate(::aimdk_msgs::msg::AudioInfo::_sample_rate_type arg)
  {
    msg_.sample_rate = std::move(arg);
    return Init_AudioInfo_size(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioInfo msg_;
};

class Init_AudioInfo_channels
{
public:
  Init_AudioInfo_channels()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AudioInfo_sample_rate channels(::aimdk_msgs::msg::AudioInfo::_channels_type arg)
  {
    msg_.channels = std::move(arg);
    return Init_AudioInfo_sample_rate(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::AudioInfo>()
{
  return aimdk_msgs::msg::builder::Init_AudioInfo_channels();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__BUILDER_HPP_
