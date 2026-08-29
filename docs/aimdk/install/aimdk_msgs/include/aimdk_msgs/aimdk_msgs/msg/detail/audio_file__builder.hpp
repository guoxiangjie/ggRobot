// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/AudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/audio_file__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_AudioFile_priority_weight
{
public:
  explicit Init_AudioFile_priority_weight(::aimdk_msgs::msg::AudioFile & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::AudioFile priority_weight(::aimdk_msgs::msg::AudioFile::_priority_weight_type arg)
  {
    msg_.priority_weight = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

class Init_AudioFile_priority
{
public:
  explicit Init_AudioFile_priority(::aimdk_msgs::msg::AudioFile & msg)
  : msg_(msg)
  {}
  Init_AudioFile_priority_weight priority(::aimdk_msgs::msg::AudioFile::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_AudioFile_priority_weight(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

class Init_AudioFile_info
{
public:
  explicit Init_AudioFile_info(::aimdk_msgs::msg::AudioFile & msg)
  : msg_(msg)
  {}
  Init_AudioFile_priority info(::aimdk_msgs::msg::AudioFile::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_AudioFile_priority(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

class Init_AudioFile_file_path
{
public:
  explicit Init_AudioFile_file_path(::aimdk_msgs::msg::AudioFile & msg)
  : msg_(msg)
  {}
  Init_AudioFile_info file_path(::aimdk_msgs::msg::AudioFile::_file_path_type arg)
  {
    msg_.file_path = std::move(arg);
    return Init_AudioFile_info(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

class Init_AudioFile_file_name
{
public:
  explicit Init_AudioFile_file_name(::aimdk_msgs::msg::AudioFile & msg)
  : msg_(msg)
  {}
  Init_AudioFile_file_path file_name(::aimdk_msgs::msg::AudioFile::_file_name_type arg)
  {
    msg_.file_name = std::move(arg);
    return Init_AudioFile_file_path(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

class Init_AudioFile_pkg_name
{
public:
  Init_AudioFile_pkg_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AudioFile_file_name pkg_name(::aimdk_msgs::msg::AudioFile::_pkg_name_type arg)
  {
    msg_.pkg_name = std::move(arg);
    return Init_AudioFile_file_name(msg_);
  }

private:
  ::aimdk_msgs::msg::AudioFile msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::AudioFile>()
{
  return aimdk_msgs::msg::builder::Init_AudioFile_pkg_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__BUILDER_HPP_
