// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/RobotResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/robot_resource__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotResource_current_version
{
public:
  explicit Init_RobotResource_current_version(::aimdk_msgs::msg::RobotResource & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::RobotResource current_version(::aimdk_msgs::msg::RobotResource::_current_version_type arg)
  {
    msg_.current_version = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::RobotResource msg_;
};

class Init_RobotResource_resource_key
{
public:
  Init_RobotResource_resource_key()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotResource_current_version resource_key(::aimdk_msgs::msg::RobotResource::_resource_key_type arg)
  {
    msg_.resource_key = std::move(arg);
    return Init_RobotResource_current_version(msg_);
  }

private:
  ::aimdk_msgs::msg::RobotResource msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::RobotResource>()
{
  return aimdk_msgs::msg::builder::Init_RobotResource_resource_key();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__BUILDER_HPP_
