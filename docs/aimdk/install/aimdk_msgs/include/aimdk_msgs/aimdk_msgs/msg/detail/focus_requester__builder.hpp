// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/FocusRequester.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FOCUS_REQUESTER__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__FOCUS_REQUESTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/focus_requester__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_FocusRequester_priority_weight
{
public:
  explicit Init_FocusRequester_priority_weight(::aimdk_msgs::msg::FocusRequester & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::FocusRequester priority_weight(::aimdk_msgs::msg::FocusRequester::_priority_weight_type arg)
  {
    msg_.priority_weight = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::FocusRequester msg_;
};

class Init_FocusRequester_priority
{
public:
  explicit Init_FocusRequester_priority(::aimdk_msgs::msg::FocusRequester & msg)
  : msg_(msg)
  {}
  Init_FocusRequester_priority_weight priority(::aimdk_msgs::msg::FocusRequester::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_FocusRequester_priority_weight(msg_);
  }

private:
  ::aimdk_msgs::msg::FocusRequester msg_;
};

class Init_FocusRequester_pkg_name
{
public:
  Init_FocusRequester_pkg_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FocusRequester_priority pkg_name(::aimdk_msgs::msg::FocusRequester::_pkg_name_type arg)
  {
    msg_.pkg_name = std::move(arg);
    return Init_FocusRequester_priority(msg_);
  }

private:
  ::aimdk_msgs::msg::FocusRequester msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::FocusRequester>()
{
  return aimdk_msgs::msg::builder::Init_FocusRequester_pkg_name();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__FOCUS_REQUESTER__BUILDER_HPP_
