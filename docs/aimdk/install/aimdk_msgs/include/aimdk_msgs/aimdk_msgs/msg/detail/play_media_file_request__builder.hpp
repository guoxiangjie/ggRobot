// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/PlayMediaFileRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/play_media_file_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_PlayMediaFileRequest_is_interrupted
{
public:
  explicit Init_PlayMediaFileRequest_is_interrupted(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::PlayMediaFileRequest is_interrupted(::aimdk_msgs::msg::PlayMediaFileRequest::_is_interrupted_type arg)
  {
    msg_.is_interrupted = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_trace_id
{
public:
  explicit Init_PlayMediaFileRequest_trace_id(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  Init_PlayMediaFileRequest_is_interrupted trace_id(::aimdk_msgs::msg::PlayMediaFileRequest::_trace_id_type arg)
  {
    msg_.trace_id = std::move(arg);
    return Init_PlayMediaFileRequest_is_interrupted(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_domain
{
public:
  explicit Init_PlayMediaFileRequest_domain(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  Init_PlayMediaFileRequest_trace_id domain(::aimdk_msgs::msg::PlayMediaFileRequest::_domain_type arg)
  {
    msg_.domain = std::move(arg);
    return Init_PlayMediaFileRequest_trace_id(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_priority_weight
{
public:
  explicit Init_PlayMediaFileRequest_priority_weight(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  Init_PlayMediaFileRequest_domain priority_weight(::aimdk_msgs::msg::PlayMediaFileRequest::_priority_weight_type arg)
  {
    msg_.priority_weight = std::move(arg);
    return Init_PlayMediaFileRequest_domain(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_priority_level
{
public:
  explicit Init_PlayMediaFileRequest_priority_level(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  Init_PlayMediaFileRequest_priority_weight priority_level(::aimdk_msgs::msg::PlayMediaFileRequest::_priority_level_type arg)
  {
    msg_.priority_level = std::move(arg);
    return Init_PlayMediaFileRequest_priority_weight(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_sample_rate
{
public:
  explicit Init_PlayMediaFileRequest_sample_rate(::aimdk_msgs::msg::PlayMediaFileRequest & msg)
  : msg_(msg)
  {}
  Init_PlayMediaFileRequest_priority_level sample_rate(::aimdk_msgs::msg::PlayMediaFileRequest::_sample_rate_type arg)
  {
    msg_.sample_rate = std::move(arg);
    return Init_PlayMediaFileRequest_priority_level(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

class Init_PlayMediaFileRequest_file_name
{
public:
  Init_PlayMediaFileRequest_file_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayMediaFileRequest_sample_rate file_name(::aimdk_msgs::msg::PlayMediaFileRequest::_file_name_type arg)
  {
    msg_.file_name = std::move(arg);
    return Init_PlayMediaFileRequest_sample_rate(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayMediaFileRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::PlayMediaFileRequest>()
{
  return aimdk_msgs::msg::builder::Init_PlayMediaFileRequest_file_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_MEDIA_FILE_REQUEST__BUILDER_HPP_
