// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/CommonResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_RESPONSE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_RESPONSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_CommonResponse_message
{
public:
  explicit Init_CommonResponse_message(::aimdk_msgs::msg::CommonResponse & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::CommonResponse message(::aimdk_msgs::msg::CommonResponse::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonResponse msg_;
};

class Init_CommonResponse_status
{
public:
  explicit Init_CommonResponse_status(::aimdk_msgs::msg::CommonResponse & msg)
  : msg_(msg)
  {}
  Init_CommonResponse_message status(::aimdk_msgs::msg::CommonResponse::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_CommonResponse_message(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonResponse msg_;
};

class Init_CommonResponse_header
{
public:
  Init_CommonResponse_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CommonResponse_status header(::aimdk_msgs::msg::CommonResponse::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CommonResponse_status(msg_);
  }

private:
  ::aimdk_msgs::msg::CommonResponse msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::CommonResponse>()
{
  return aimdk_msgs::msg::builder::Init_CommonResponse_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_RESPONSE__BUILDER_HPP_
