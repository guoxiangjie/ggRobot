// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/McActionInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/mc_action_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_McActionInfo_status
{
public:
  explicit Init_McActionInfo_status(::aimdk_msgs::msg::McActionInfo & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::McActionInfo status(::aimdk_msgs::msg::McActionInfo::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionInfo msg_;
};

class Init_McActionInfo_action_desc
{
public:
  explicit Init_McActionInfo_action_desc(::aimdk_msgs::msg::McActionInfo & msg)
  : msg_(msg)
  {}
  Init_McActionInfo_status action_desc(::aimdk_msgs::msg::McActionInfo::_action_desc_type arg)
  {
    msg_.action_desc = std::move(arg);
    return Init_McActionInfo_status(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionInfo msg_;
};

class Init_McActionInfo_current_action
{
public:
  Init_McActionInfo_current_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_McActionInfo_action_desc current_action(::aimdk_msgs::msg::McActionInfo::_current_action_type arg)
  {
    msg_.current_action = std::move(arg);
    return Init_McActionInfo_action_desc(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::McActionInfo>()
{
  return aimdk_msgs::msg::builder::Init_McActionInfo_current_action();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__BUILDER_HPP_
