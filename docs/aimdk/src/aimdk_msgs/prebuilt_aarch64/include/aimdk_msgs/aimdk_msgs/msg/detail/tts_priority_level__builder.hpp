// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/TtsPriorityLevel.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/tts_priority_level__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_TtsPriorityLevel_value
{
public:
  Init_TtsPriorityLevel_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::msg::TtsPriorityLevel value(::aimdk_msgs::msg::TtsPriorityLevel::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::TtsPriorityLevel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::TtsPriorityLevel>()
{
  return aimdk_msgs::msg::builder::Init_TtsPriorityLevel_value();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__BUILDER_HPP_
