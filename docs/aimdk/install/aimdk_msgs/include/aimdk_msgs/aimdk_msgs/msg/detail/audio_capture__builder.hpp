// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/AudioCapture.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/audio_capture__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_AudioCapture_pkg_name
{
public:
  explicit Init_AudioCapture_pkg_name(::aimdk_msgs::msg::AudioCapture & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::AudioCapture pkg_name(::aimdk_msgs::msg::AudioCapture::_pkg_name_type arg)
  {
    msg_.pkg_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

class Init_AudioCapture_data
{
public:
  explicit Init_AudioCapture_data(::aimdk_msgs::msg::AudioCapture & msg)
  : msg_(msg)
  {}
  Init_AudioCapture_pkg_name data(::aimdk_msgs::msg::AudioCapture::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_AudioCapture_pkg_name(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

class Init_AudioCapture_info
{
public:
  explicit Init_AudioCapture_info(::aimdk_msgs::msg::AudioCapture & msg)
  : msg_(msg)
  {}
  Init_AudioCapture_data info(::aimdk_msgs::msg::AudioCapture::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_AudioCapture_data(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

class Init_AudioCapture_ref_channels
{
public:
  explicit Init_AudioCapture_ref_channels(::aimdk_msgs::msg::AudioCapture & msg)
  : msg_(msg)
  {}
  Init_AudioCapture_info ref_channels(::aimdk_msgs::msg::AudioCapture::_ref_channels_type arg)
  {
    msg_.ref_channels = std::move(arg);
    return Init_AudioCapture_info(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

class Init_AudioCapture_mic_channels
{
public:
  explicit Init_AudioCapture_mic_channels(::aimdk_msgs::msg::AudioCapture & msg)
  : msg_(msg)
  {}
  Init_AudioCapture_ref_channels mic_channels(::aimdk_msgs::msg::AudioCapture::_mic_channels_type arg)
  {
    msg_.mic_channels = std::move(arg);
    return Init_AudioCapture_ref_channels(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

class Init_AudioCapture_stamps
{
public:
  Init_AudioCapture_stamps()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AudioCapture_mic_channels stamps(::aimdk_msgs::msg::AudioCapture::_stamps_type arg)
  {
    msg_.stamps = std::move(arg);
    return Init_AudioCapture_mic_channels(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioCapture msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::AudioCapture>()
{
  return aimdk_msgs::msg::builder::Init_AudioCapture_stamps();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__BUILDER_HPP_
