// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/QRCode.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__QR_CODE__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__QR_CODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/qr_code__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_QRCode_pose
{
public:
  explicit Init_QRCode_pose(::aimdk_msgs::msg::QRCode & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::QRCode pose(::aimdk_msgs::msg::QRCode::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::QRCode msg_;
};

class Init_QRCode_code
{
public:
  Init_QRCode_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_QRCode_pose code(::aimdk_msgs::msg::QRCode::_code_type arg)
  {
    msg_.code = std::move(arg);
    return Init_QRCode_pose(msg_);
  }

private:
  ::aimdk_msgs::msg::QRCode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::QRCode>()
{
  return aimdk_msgs::msg::builder::Init_QRCode_code();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__QR_CODE__BUILDER_HPP_
