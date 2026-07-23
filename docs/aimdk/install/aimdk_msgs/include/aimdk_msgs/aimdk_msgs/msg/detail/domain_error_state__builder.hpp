// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/DomainErrorState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/domain_error_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_DomainErrorState_value
{
public:
  Init_DomainErrorState_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::msg::DomainErrorState value(::aimdk_msgs::msg::DomainErrorState::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::DomainErrorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::DomainErrorState>()
{
  return aimdk_msgs::msg::builder::Init_DomainErrorState_value();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__DOMAIN_ERROR_STATE__BUILDER_HPP_
