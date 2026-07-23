// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/face_emoji_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_FaceEmojiStatus_time_to_end_ms
{
public:
  explicit Init_FaceEmojiStatus_time_to_end_ms(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::FaceEmojiStatus time_to_end_ms(::aimdk_msgs::msg::FaceEmojiStatus::_time_to_end_ms_type arg)
  {
    msg_.time_to_end_ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_status
{
public:
  explicit Init_FaceEmojiStatus_status(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_time_to_end_ms status(::aimdk_msgs::msg::FaceEmojiStatus::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_FaceEmojiStatus_time_to_end_ms(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_priority
{
public:
  explicit Init_FaceEmojiStatus_priority(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_status priority(::aimdk_msgs::msg::FaceEmojiStatus::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_FaceEmojiStatus_status(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_mode
{
public:
  explicit Init_FaceEmojiStatus_mode(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_priority mode(::aimdk_msgs::msg::FaceEmojiStatus::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_FaceEmojiStatus_priority(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_e_id
{
public:
  explicit Init_FaceEmojiStatus_e_id(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_mode e_id(::aimdk_msgs::msg::FaceEmojiStatus::_e_id_type arg)
  {
    msg_.e_id = std::move(arg);
    return Init_FaceEmojiStatus_mode(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_e_path_list
{
public:
  explicit Init_FaceEmojiStatus_e_path_list(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_e_id e_path_list(::aimdk_msgs::msg::FaceEmojiStatus::_e_path_list_type arg)
  {
    msg_.e_path_list = std::move(arg);
    return Init_FaceEmojiStatus_e_id(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_e_path
{
public:
  explicit Init_FaceEmojiStatus_e_path(::aimdk_msgs::msg::FaceEmojiStatus & msg)
  : msg_(msg)
  {}
  Init_FaceEmojiStatus_e_path_list e_path(::aimdk_msgs::msg::FaceEmojiStatus::_e_path_type arg)
  {
    msg_.e_path = std::move(arg);
    return Init_FaceEmojiStatus_e_path_list(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

class Init_FaceEmojiStatus_header
{
public:
  Init_FaceEmojiStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FaceEmojiStatus_e_path header(::aimdk_msgs::msg::FaceEmojiStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_FaceEmojiStatus_e_path(msg_);
  }

private:
  ::aimdk_msgs::msg::FaceEmojiStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::FaceEmojiStatus>()
{
  return aimdk_msgs::msg::builder::Init_FaceEmojiStatus_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__BUILDER_HPP_
