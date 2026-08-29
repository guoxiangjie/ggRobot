// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/FocusResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/focus_response__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_FocusResponse_focus_gain
{
public:
  explicit Init_FocusResponse_focus_gain(::aimdk_msgs::msg::FocusResponse & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::FocusResponse focus_gain(::aimdk_msgs::msg::FocusResponse::_focus_gain_type arg)
  {
    msg_.focus_gain = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::FocusResponse msg_;
};

class Init_FocusResponse_pkg_name
{
public:
  Init_FocusResponse_pkg_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FocusResponse_focus_gain pkg_name(::aimdk_msgs::msg::FocusResponse::_pkg_name_type arg)
  {
    msg_.pkg_name = std::move(arg);
    return Init_FocusResponse_focus_gain(msg_);
  }

private:
  ::aimdk_msgs::msg::FocusResponse msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::FocusResponse>()
{
  return aimdk_msgs::msg::builder::Init_FocusResponse_pkg_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__FOCUS_RESPONSE__BUILDER_HPP_
