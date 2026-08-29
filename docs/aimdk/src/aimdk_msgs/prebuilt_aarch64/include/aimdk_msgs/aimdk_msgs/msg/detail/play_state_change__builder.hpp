// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/PlayStateChange.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/play_state_change__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_PlayStateChange_state
{
public:
  explicit Init_PlayStateChange_state(::aimdk_msgs::msg::PlayStateChange & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::PlayStateChange state(::aimdk_msgs::msg::PlayStateChange::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayStateChange msg_;
};

class Init_PlayStateChange_pkg_name
{
public:
  Init_PlayStateChange_pkg_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlayStateChange_state pkg_name(::aimdk_msgs::msg::PlayStateChange::_pkg_name_type arg)
  {
    msg_.pkg_name = std::move(arg);
    return Init_PlayStateChange_state(msg_);
  }

private:
  ::aimdk_msgs::msg::PlayStateChange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::PlayStateChange>()
{
  return aimdk_msgs::msg::builder::Init_PlayStateChange_pkg_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__BUILDER_HPP_
