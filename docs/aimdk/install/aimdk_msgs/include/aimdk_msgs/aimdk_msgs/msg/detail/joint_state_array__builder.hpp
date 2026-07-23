// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/JointStateArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/joint_state_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_JointStateArray_joints
{
public:
  explicit Init_JointStateArray_joints(::aimdk_msgs::msg::JointStateArray & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::JointStateArray joints(::aimdk_msgs::msg::JointStateArray::_joints_type arg)
  {
    msg_.joints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::JointStateArray msg_;
};

class Init_JointStateArray_state
{
public:
  explicit Init_JointStateArray_state(::aimdk_msgs::msg::JointStateArray & msg)
  : msg_(msg)
  {}
  Init_JointStateArray_joints state(::aimdk_msgs::msg::JointStateArray::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_JointStateArray_joints(msg_);
  }

private:
  ::aimdk_msgs::msg::JointStateArray msg_;
};

class Init_JointStateArray_header
{
public:
  Init_JointStateArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_JointStateArray_state header(::aimdk_msgs::msg::JointStateArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_JointStateArray_state(msg_);
  }

private:
  ::aimdk_msgs::msg::JointStateArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::JointStateArray>()
{
  return aimdk_msgs::msg::builder::Init_JointStateArray_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__BUILDER_HPP_
