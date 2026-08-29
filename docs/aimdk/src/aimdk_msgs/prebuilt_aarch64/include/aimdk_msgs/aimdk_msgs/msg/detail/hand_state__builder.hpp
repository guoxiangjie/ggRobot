// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandState_faultcode
{
public:
  explicit Init_HandState_faultcode(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandState faultcode(::aimdk_msgs::msg::HandState::_faultcode_type arg)
  {
    msg_.faultcode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_state
{
public:
  explicit Init_HandState_state(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_faultcode state(::aimdk_msgs::msg::HandState::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_HandState_faultcode(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_effort
{
public:
  explicit Init_HandState_effort(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_state effort(::aimdk_msgs::msg::HandState::_effort_type arg)
  {
    msg_.effort = std::move(arg);
    return Init_HandState_state(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_velocity
{
public:
  explicit Init_HandState_velocity(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_effort velocity(::aimdk_msgs::msg::HandState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_HandState_effort(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_position
{
public:
  explicit Init_HandState_position(::aimdk_msgs::msg::HandState & msg)
  : msg_(msg)
  {}
  Init_HandState_velocity position(::aimdk_msgs::msg::HandState::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_HandState_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

class Init_HandState_name
{
public:
  Init_HandState_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandState_position name(::aimdk_msgs::msg::HandState::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_HandState_position(msg_);
  }

private:
  ::aimdk_msgs::msg::HandState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandState>()
{
  return aimdk_msgs::msg::builder::Init_HandState_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_STATE__BUILDER_HPP_
