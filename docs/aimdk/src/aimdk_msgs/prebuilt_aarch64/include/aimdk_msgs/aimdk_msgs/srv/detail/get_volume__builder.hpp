// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetVolume.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_VOLUME__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_VOLUME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_volume__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetVolume_Request_request
{
public:
  Init_GetVolume_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetVolume_Request request(::aimdk_msgs::srv::GetVolume_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetVolume_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetVolume_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetVolume_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetVolume_Response_audio_volume
{
public:
  explicit Init_GetVolume_Response_audio_volume(::aimdk_msgs::srv::GetVolume_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetVolume_Response audio_volume(::aimdk_msgs::srv::GetVolume_Response::_audio_volume_type arg)
  {
    msg_.audio_volume = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetVolume_Response msg_;
};

class Init_GetVolume_Response_reponse
{
public:
  Init_GetVolume_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetVolume_Response_audio_volume reponse(::aimdk_msgs::srv::GetVolume_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return Init_GetVolume_Response_audio_volume(msg_);
  }

private:
  ::aimdk_msgs::srv::GetVolume_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetVolume_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetVolume_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_VOLUME__BUILDER_HPP_
