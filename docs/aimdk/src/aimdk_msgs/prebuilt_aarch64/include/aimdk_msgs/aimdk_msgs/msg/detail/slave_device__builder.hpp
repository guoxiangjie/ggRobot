// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/SlaveDevice.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/slave_device__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_SlaveDevice_ip
{
public:
  Init_SlaveDevice_ip()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::msg::SlaveDevice ip(::aimdk_msgs::msg::SlaveDevice::_ip_type arg)
  {
    msg_.ip = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::SlaveDevice msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::SlaveDevice>()
{
  return aimdk_msgs::msg::builder::Init_SlaveDevice_ip();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__SLAVE_DEVICE__BUILDER_HPP_
