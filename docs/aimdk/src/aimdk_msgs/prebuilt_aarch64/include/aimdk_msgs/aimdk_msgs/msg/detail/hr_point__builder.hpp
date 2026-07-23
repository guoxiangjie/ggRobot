// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HR_POINT__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HR_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hr_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HRPoint_use_head
{
public:
  explicit Init_HRPoint_use_head(::aimdk_msgs::msg::HRPoint & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HRPoint use_head(::aimdk_msgs::msg::HRPoint::_use_head_type arg)
  {
    msg_.use_head = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HRPoint msg_;
};

class Init_HRPoint_qr_list
{
public:
  explicit Init_HRPoint_qr_list(::aimdk_msgs::msg::HRPoint & msg)
  : msg_(msg)
  {}
  Init_HRPoint_use_head qr_list(::aimdk_msgs::msg::HRPoint::_qr_list_type arg)
  {
    msg_.qr_list = std::move(arg);
    return Init_HRPoint_use_head(msg_);
  }

private:
  ::aimdk_msgs::msg::HRPoint msg_;
};

class Init_HRPoint_pose
{
public:
  explicit Init_HRPoint_pose(::aimdk_msgs::msg::HRPoint & msg)
  : msg_(msg)
  {}
  Init_HRPoint_qr_list pose(::aimdk_msgs::msg::HRPoint::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_HRPoint_qr_list(msg_);
  }

private:
  ::aimdk_msgs::msg::HRPoint msg_;
};

class Init_HRPoint_point_id
{
public:
  Init_HRPoint_point_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HRPoint_pose point_id(::aimdk_msgs::msg::HRPoint::_point_id_type arg)
  {
    msg_.point_id = std::move(arg);
    return Init_HRPoint_pose(msg_);
  }

private:
  ::aimdk_msgs::msg::HRPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HRPoint>()
{
  return aimdk_msgs::msg::builder::Init_HRPoint_point_id();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HR_POINT__BUILDER_HPP_
