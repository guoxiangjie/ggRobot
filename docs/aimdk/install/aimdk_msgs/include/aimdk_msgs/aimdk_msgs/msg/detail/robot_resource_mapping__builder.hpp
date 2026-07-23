// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/RobotResourceMapping.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/robot_resource_mapping__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotResourceMapping_robot_resource_list
{
public:
  explicit Init_RobotResourceMapping_robot_resource_list(::aimdk_msgs::msg::RobotResourceMapping & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::RobotResourceMapping robot_resource_list(::aimdk_msgs::msg::RobotResourceMapping::_robot_resource_list_type arg)
  {
    msg_.robot_resource_list = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::RobotResourceMapping msg_;
};

class Init_RobotResourceMapping_robot_ip
{
public:
  explicit Init_RobotResourceMapping_robot_ip(::aimdk_msgs::msg::RobotResourceMapping & msg)
  : msg_(msg)
  {}
  Init_RobotResourceMapping_robot_resource_list robot_ip(::aimdk_msgs::msg::RobotResourceMapping::_robot_ip_type arg)
  {
    msg_.robot_ip = std::move(arg);
    return Init_RobotResourceMapping_robot_resource_list(msg_);
  }

private:
  ::aimdk_msgs::msg::RobotResourceMapping msg_;
};

class Init_RobotResourceMapping_is_master
{
public:
  Init_RobotResourceMapping_is_master()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotResourceMapping_robot_ip is_master(::aimdk_msgs::msg::RobotResourceMapping::_is_master_type arg)
  {
    msg_.is_master = std::move(arg);
    return Init_RobotResourceMapping_robot_ip(msg_);
  }

private:
  ::aimdk_msgs::msg::RobotResourceMapping msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::RobotResourceMapping>()
{
  return aimdk_msgs::msg::builder::Init_RobotResourceMapping_is_master();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__BUILDER_HPP_
