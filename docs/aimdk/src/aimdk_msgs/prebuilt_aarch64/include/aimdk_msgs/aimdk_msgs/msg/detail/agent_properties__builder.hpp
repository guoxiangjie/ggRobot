// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/AgentProperties.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/agent_properties__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentProperties_properties
{
public:
  Init_AgentProperties_properties()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::msg::AgentProperties properties(::aimdk_msgs::msg::AgentProperties::_properties_type arg)
  {
    msg_.properties = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::AgentProperties msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::AgentProperties>()
{
  return aimdk_msgs::msg::builder::Init_AgentProperties_properties();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__BUILDER_HPP_
