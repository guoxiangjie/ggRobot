// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/McInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/mc_input_source__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_McInputSource_timeout
{
public:
  explicit Init_McInputSource_timeout(::aimdk_msgs::msg::McInputSource & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::McInputSource timeout(::aimdk_msgs::msg::McInputSource::_timeout_type arg)
  {
    msg_.timeout = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::McInputSource msg_;
};

class Init_McInputSource_priority
{
public:
  explicit Init_McInputSource_priority(::aimdk_msgs::msg::McInputSource & msg)
  : msg_(msg)
  {}
  Init_McInputSource_timeout priority(::aimdk_msgs::msg::McInputSource::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_McInputSource_timeout(msg_);
  }

private:
  ::aimdk_msgs::msg::McInputSource msg_;
};

class Init_McInputSource_name
{
public:
  Init_McInputSource_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_McInputSource_priority name(::aimdk_msgs::msg::McInputSource::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_McInputSource_priority(msg_);
  }

private:
  ::aimdk_msgs::msg::McInputSource msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::McInputSource>()
{
  return aimdk_msgs::msg::builder::Init_McInputSource_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_INPUT_SOURCE__BUILDER_HPP_
