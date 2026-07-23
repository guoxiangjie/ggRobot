// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/PlayAudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/play_audio_file__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_PlayAudioFile_Request_play_stamps
{
public:
  explicit Init_PlayAudioFile_Request_play_stamps(::aimdk_msgs::srv::PlayAudioFile_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::PlayAudioFile_Request play_stamps(::aimdk_msgs::srv::PlayAudioFile_Request::_play_stamps_type arg)
  {
    msg_.play_stamps = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayAudioFile_Request msg_;
};

class Init_PlayAudioFile_Request_file
{
public:
  explicit Init_PlayAudioFile_Request_file(::aimdk_msgs::srv::PlayAudioFile_Request & msg)
  : msg_(msg)
  {}
  Init_PlayAudioFile_Request_play_stamps file(::aimdk_msgs::srv::PlayAudioFile_Request::_file_type arg)
  {
    msg_.file = std::move(arg);
    return Init_PlayAudioFile_Request_play_stamps(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayAudioFile_Request msg_;
};

class Init_PlayAudioFile_Request_request
{
public:
  Init_PlayAudioFile_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayAudioFile_Request_file request(::aimdk_msgs::srv::PlayAudioFile_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PlayAudioFile_Request_file(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayAudioFile_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::PlayAudioFile_Request>()
{
  return aimdk_msgs::srv::builder::Init_PlayAudioFile_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_PlayAudioFile_Response_reponse
{
public:
  Init_PlayAudioFile_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::PlayAudioFile_Response reponse(::aimdk_msgs::srv::PlayAudioFile_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::PlayAudioFile_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::PlayAudioFile_Response>()
{
  return aimdk_msgs::srv::builder::Init_PlayAudioFile_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__BUILDER_HPP_
