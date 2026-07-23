// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/ResponseHeader.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/response_header__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_ResponseHeader_code
{
public:
  explicit Init_ResponseHeader_code(::aimdk_msgs::msg::ResponseHeader & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::ResponseHeader code(::aimdk_msgs::msg::ResponseHeader::_code_type arg)
  {
    msg_.code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::ResponseHeader msg_;
};

class Init_ResponseHeader_stamp
{
public:
  Init_ResponseHeader_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ResponseHeader_code stamp(::aimdk_msgs::msg::ResponseHeader::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_ResponseHeader_code(msg_);
  }

private:
  ::aimdk_msgs::msg::ResponseHeader msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::ResponseHeader>()
{
  return aimdk_msgs::msg::builder::Init_ResponseHeader_stamp();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__BUILDER_HPP_
