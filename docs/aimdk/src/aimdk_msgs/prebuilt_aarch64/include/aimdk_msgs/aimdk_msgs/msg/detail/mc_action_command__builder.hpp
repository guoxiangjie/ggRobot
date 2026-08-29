// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/McActionCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/mc_action_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_McActionCommand_action_desc
{
public:
  explicit Init_McActionCommand_action_desc(::aimdk_msgs::msg::McActionCommand & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::McActionCommand action_desc(::aimdk_msgs::msg::McActionCommand::_action_desc_type arg)
  {
    msg_.action_desc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionCommand msg_;
};

class Init_McActionCommand_action
{
public:
  Init_McActionCommand_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_McActionCommand_action_desc action(::aimdk_msgs::msg::McActionCommand::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_McActionCommand_action_desc(msg_);
  }

private:
  ::aimdk_msgs::msg::McActionCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::McActionCommand>()
{
  return aimdk_msgs::msg::builder::Init_McActionCommand_action();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__BUILDER_HPP_
