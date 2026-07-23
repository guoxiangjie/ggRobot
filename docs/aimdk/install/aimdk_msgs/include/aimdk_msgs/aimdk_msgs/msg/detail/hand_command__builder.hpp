// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandCommand_effort
{
public:
  explicit Init_HandCommand_effort(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandCommand effort(::aimdk_msgs::msg::HandCommand::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_deceleration
{
public:
  explicit Init_HandCommand_deceleration(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_effort deceleration(::aimdk_msgs::msg::HandCommand::_deceleration_type arg)
  {
    msg_.deceleration = std::move(arg);
    return Init_HandCommand_effort(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_acceleration
{
public:
  explicit Init_HandCommand_acceleration(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_deceleration acceleration(::aimdk_msgs::msg::HandCommand::_acceleration_type arg)
  {
    msg_.acceleration = std::move(arg);
    return Init_HandCommand_deceleration(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_velocity
{
public:
  explicit Init_HandCommand_velocity(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_acceleration velocity(::aimdk_msgs::msg::HandCommand::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HandCommand_acceleration(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_position
{
public:
  explicit Init_HandCommand_position(::aimdk_msgs::msg::HandCommand & msg)
  : msg_(msg)
  {}
  Init_HandCommand_velocity position(::aimdk_msgs::msg::HandCommand::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HandCommand_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

class Init_HandCommand_name
{
public:
  Init_HandCommand_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandCommand_position name(::aimdk_msgs::msg::HandCommand::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HandCommand_position(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandCommand>()
{
  return aimdk_msgs::msg::builder::Init_HandCommand_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND__BUILDER_HPP_
