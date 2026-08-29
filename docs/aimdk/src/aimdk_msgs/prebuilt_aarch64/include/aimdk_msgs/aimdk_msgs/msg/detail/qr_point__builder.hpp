// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/QRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__QR_POINT__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__QR_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/qr_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_QRPoint_qr_code
{
public:
  explicit Init_QRPoint_qr_code(::aimdk_msgs::msg::QRPoint & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::QRPoint qr_code(::aimdk_msgs::msg::QRPoint::_qr_code_type arg)
  {
    msg_.qr_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::QRPoint msg_;
};

class Init_QRPoint_point_id
{
public:
  Init_QRPoint_point_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_QRPoint_qr_code point_id(::aimdk_msgs::msg::QRPoint::_point_id_type arg)
  {
    msg_.point_id = std::move(arg);
    return Init_QRPoint_qr_code(msg_);
  }

private:
  ::aimdk_msgs::msg::QRPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::QRPoint>()
{
  return aimdk_msgs::msg::builder::Init_QRPoint_point_id();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__QR_POINT__BUILDER_HPP_
