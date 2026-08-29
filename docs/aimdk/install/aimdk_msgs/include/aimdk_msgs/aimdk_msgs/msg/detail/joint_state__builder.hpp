// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/JointState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__JOINT_STATE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__JOINT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/joint_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_JointState_error_code
{
public:
  explicit Init_JointState_error_code(::aimdk_msgs::msg::JointState & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::JointState error_code(::aimdk_msgs::msg::JointState::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::JointState msg_;
};

class Init_JointState_effort
{
public:
  explicit Init_JointState_effort(::aimdk_msgs::msg::JointState & msg)
  : msg_(msg)
  {}
  Init_JointState_error_code effort(::aimdk_msgs::msg::JointState::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return Init_JointState_error_code(msg_);
  }

private:
  ::aimdk_msgs::msg::JointState msg_;
};

class Init_JointState_velocity
{
public:
  explicit Init_JointState_velocity(::aimdk_msgs::msg::JointState & msg)
  : msg_(msg)
  {}
  Init_JointState_effort velocity(::aimdk_msgs::msg::JointState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_JointState_effort(msg_);
  }

private:
  ::aimdk_msgs::msg::JointState msg_;
};

class Init_JointState_position
{
public:
  explicit Init_JointState_position(::aimdk_msgs::msg::JointState & msg)
  : msg_(msg)
  {}
  Init_JointState_velocity position(::aimdk_msgs::msg::JointState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_JointState_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::JointState msg_;
};

class Init_JointState_name
{
public:
  Init_JointState_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointState_position name(::aimdk_msgs::msg::JointState::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_JointState_position(msg_);
  }

private:
  ::aimdk_msgs::msg::JointState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::JointState>()
{
  return aimdk_msgs::msg::builder::Init_JointState_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__JOINT_STATE__BUILDER_HPP_
