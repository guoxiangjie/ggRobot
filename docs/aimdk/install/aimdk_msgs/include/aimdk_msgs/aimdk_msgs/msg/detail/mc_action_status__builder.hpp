// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/McActionStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/mc_action_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_McActionStatus_value
{
public:
  Init_McActionStatus_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::msg::McActionStatus value(::aimdk_msgs::msg::McActionStatus::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::McActionStatus>()
{
  return aimdk_msgs::msg::builder::Init_McActionStatus_value();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_STATUS__BUILDER_HPP_
