// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/MessageHeader.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/message_header__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_MessageHeader_meas_stamp
{
public:
  explicit Init_MessageHeader_meas_stamp(::aimdk_msgs::msg::MessageHeader & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::MessageHeader meas_stamp(::aimdk_msgs::msg::MessageHeader::_meas_stamp_type arg)
  {
    msg_.meas_stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::MessageHeader msg_;
};

class Init_MessageHeader_sequence
{
public:
  explicit Init_MessageHeader_sequence(::aimdk_msgs::msg::MessageHeader & msg)
  : msg_(msg)
  {}
  Init_MessageHeader_meas_stamp sequence(::aimdk_msgs::msg::MessageHeader::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_MessageHeader_meas_stamp(msg_);
  }

private:
  ::aimdk_msgs::msg::MessageHeader msg_;
};

class Init_MessageHeader_frame_id
{
public:
  explicit Init_MessageHeader_frame_id(::aimdk_msgs::msg::MessageHeader & msg)
  : msg_(msg)
  {}
  Init_MessageHeader_sequence frame_id(::aimdk_msgs::msg::MessageHeader::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_MessageHeader_sequence(msg_);
  }

private:
  ::aimdk_msgs::msg::MessageHeader msg_;
};

class Init_MessageHeader_stamp
{
public:
  Init_MessageHeader_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MessageHeader_frame_id stamp(::aimdk_msgs::msg::MessageHeader::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_MessageHeader_frame_id(msg_);
  }

private:
  ::aimdk_msgs::msg::MessageHeader msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::MessageHeader>()
{
  return aimdk_msgs::msg::builder::Init_MessageHeader_stamp();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__BUILDER_HPP_
