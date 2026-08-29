// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/AgentPropertiesValue.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/agent_properties_value__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_AgentPropertiesValue_value
{
public:
  explicit Init_AgentPropertiesValue_value(::aimdk_msgs::msg::AgentPropertiesValue & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::AgentPropertiesValue value(::aimdk_msgs::msg::AgentPropertiesValue::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::AgentPropertiesValue msg_;
};

class Init_AgentPropertiesValue_key
{
public:
  Init_AgentPropertiesValue_key()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgentPropertiesValue_value key(::aimdk_msgs::msg::AgentPropertiesValue::_key_type arg)
  {
    msg_.key = std::move(arg);
    return Init_AgentPropertiesValue_value(msg_);
  }

private:
  ::aimdk_msgs::msg::AgentPropertiesValue msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::AgentPropertiesValue>()
{
  return aimdk_msgs::msg::builder::Init_AgentPropertiesValue_key();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__BUILDER_HPP_
