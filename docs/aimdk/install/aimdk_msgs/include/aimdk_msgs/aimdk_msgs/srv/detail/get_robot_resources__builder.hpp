// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetRobotResources.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_robot_resources__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetRobotResources_Request_header
{
public:
  Init_GetRobotResources_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetRobotResources_Request header(::aimdk_msgs::srv::GetRobotResources_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetRobotResources_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetRobotResources_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetRobotResources_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetRobotResources_Response_robot_resources
{
public:
  explicit Init_GetRobotResources_Response_robot_resources(::aimdk_msgs::srv::GetRobotResources_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetRobotResources_Response robot_resources(::aimdk_msgs::srv::GetRobotResources_Response::_robot_resources_type arg)
  {
    msg_.robot_resources = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetRobotResources_Response msg_;
};

class Init_GetRobotResources_Response_header
{
public:
  Init_GetRobotResources_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetRobotResources_Response_robot_resources header(::aimdk_msgs::srv::GetRobotResources_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GetRobotResources_Response_robot_resources(msg_);
  }

private:
  ::aimdk_msgs::srv::GetRobotResources_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetRobotResources_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetRobotResources_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__BUILDER_HPP_
