// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/McLocomotionVelocity.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/mc_locomotion_velocity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_McLocomotionVelocity_angular_velocity
{
public:
  explicit Init_McLocomotionVelocity_angular_velocity(::aimdk_msgs::msg::McLocomotionVelocity & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::McLocomotionVelocity angular_velocity(::aimdk_msgs::msg::McLocomotionVelocity::_angular_velocity_type arg)
  {
    msg_.angular_velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::McLocomotionVelocity msg_;
};

class Init_McLocomotionVelocity_lateral_velocity
{
public:
  explicit Init_McLocomotionVelocity_lateral_velocity(::aimdk_msgs::msg::McLocomotionVelocity & msg)
  : msg_(msg)
  {}
  Init_McLocomotionVelocity_angular_velocity lateral_velocity(::aimdk_msgs::msg::McLocomotionVelocity::_lateral_velocity_type arg)
  {
    msg_.lateral_velocity = std::move(arg);
    return Init_McLocomotionVelocity_angular_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::McLocomotionVelocity msg_;
};

class Init_McLocomotionVelocity_forward_velocity
{
public:
  explicit Init_McLocomotionVelocity_forward_velocity(::aimdk_msgs::msg::McLocomotionVelocity & msg)
  : msg_(msg)
  {}
  Init_McLocomotionVelocity_lateral_velocity forward_velocity(::aimdk_msgs::msg::McLocomotionVelocity::_forward_velocity_type arg)
  {
    msg_.forward_velocity = std::move(arg);
    return Init_McLocomotionVelocity_lateral_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::McLocomotionVelocity msg_;
};

class Init_McLocomotionVelocity_source
{
public:
  explicit Init_McLocomotionVelocity_source(::aimdk_msgs::msg::McLocomotionVelocity & msg)
  : msg_(msg)
  {}
  Init_McLocomotionVelocity_forward_velocity source(::aimdk_msgs::msg::McLocomotionVelocity::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_McLocomotionVelocity_forward_velocity(msg_);
  }

private:
  ::aimdk_msgs::msg::McLocomotionVelocity msg_;
};

class Init_McLocomotionVelocity_header
{
public:
  Init_McLocomotionVelocity_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_McLocomotionVelocity_source header(::aimdk_msgs::msg::McLocomotionVelocity::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_McLocomotionVelocity_source(msg_);
  }

private:
  ::aimdk_msgs::msg::McLocomotionVelocity msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::McLocomotionVelocity>()
{
  return aimdk_msgs::msg::builder::Init_McLocomotionVelocity_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__BUILDER_HPP_
