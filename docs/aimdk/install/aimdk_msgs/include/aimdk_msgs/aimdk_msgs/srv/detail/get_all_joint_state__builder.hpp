// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_all_joint_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAllJointState_Request_request
{
public:
  Init_GetAllJointState_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetAllJointState_Request request(::aimdk_msgs::srv::GetAllJointState_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetAllJointState_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetAllJointState_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetAllJointState_Response_leg_joints
{
public:
  explicit Init_GetAllJointState_Response_leg_joints(::aimdk_msgs::srv::GetAllJointState_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetAllJointState_Response leg_joints(::aimdk_msgs::srv::GetAllJointState_Response::_leg_joints_type arg)
  {
    msg_.leg_joints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Response msg_;
};

class Init_GetAllJointState_Response_waist_joints
{
public:
  explicit Init_GetAllJointState_Response_waist_joints(::aimdk_msgs::srv::GetAllJointState_Response & msg)
  : msg_(msg)
  {}
  Init_GetAllJointState_Response_leg_joints waist_joints(::aimdk_msgs::srv::GetAllJointState_Response::_waist_joints_type arg)
  {
    msg_.waist_joints = std::move(arg);
    return Init_GetAllJointState_Response_leg_joints(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Response msg_;
};

class Init_GetAllJointState_Response_arm_joints
{
public:
  explicit Init_GetAllJointState_Response_arm_joints(::aimdk_msgs::srv::GetAllJointState_Response & msg)
  : msg_(msg)
  {}
  Init_GetAllJointState_Response_waist_joints arm_joints(::aimdk_msgs::srv::GetAllJointState_Response::_arm_joints_type arg)
  {
    msg_.arm_joints = std::move(arg);
    return Init_GetAllJointState_Response_waist_joints(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Response msg_;
};

class Init_GetAllJointState_Response_head_joints
{
public:
  explicit Init_GetAllJointState_Response_head_joints(::aimdk_msgs::srv::GetAllJointState_Response & msg)
  : msg_(msg)
  {}
  Init_GetAllJointState_Response_arm_joints head_joints(::aimdk_msgs::srv::GetAllJointState_Response::_head_joints_type arg)
  {
    msg_.head_joints = std::move(arg);
    return Init_GetAllJointState_Response_arm_joints(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Response msg_;
};

class Init_GetAllJointState_Response_reponse
{
public:
  Init_GetAllJointState_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetAllJointState_Response_head_joints reponse(::aimdk_msgs::srv::GetAllJointState_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return Init_GetAllJointState_Response_head_joints(msg_);
  }

private:
  ::aimdk_msgs::srv::GetAllJointState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetAllJointState_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetAllJointState_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__BUILDER_HPP_
