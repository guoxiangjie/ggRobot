// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/CommonTaskResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/common_task_response__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_CommonTaskResponse_state
{
public:
  explicit Init_CommonTaskResponse_state(::aimdk_msgs::msg::CommonTaskResponse & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::CommonTaskResponse state(::aimdk_msgs::msg::CommonTaskResponse::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonTaskResponse msg_;
};

class Init_CommonTaskResponse_task_id
{
public:
  explicit Init_CommonTaskResponse_task_id(::aimdk_msgs::msg::CommonTaskResponse & msg)
  : msg_(msg)
  {}
  Init_CommonTaskResponse_state task_id(::aimdk_msgs::msg::CommonTaskResponse::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_CommonTaskResponse_state(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonTaskResponse msg_;
};

class Init_CommonTaskResponse_header
{
public:
  Init_CommonTaskResponse_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CommonTaskResponse_task_id header(::aimdk_msgs::msg::CommonTaskResponse::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CommonTaskResponse_task_id(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonTaskResponse msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::CommonTaskResponse>()
{
  return aimdk_msgs::msg::builder::Init_CommonTaskResponse_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__BUILDER_HPP_
