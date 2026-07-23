// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_command_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandCommandArray_right_hands
{
public:
  explicit Init_HandCommandArray_right_hands(::aimdk_msgs::msg::HandCommandArray & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandCommandArray right_hands(::aimdk_msgs::msg::HandCommandArray::_right_hands_type arg)
  {
    msg_.right_hands = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommandArray msg_;
};

class Init_HandCommandArray_right_hand_type
{
public:
  explicit Init_HandCommandArray_right_hand_type(::aimdk_msgs::msg::HandCommandArray & msg)
  : msg_(msg)
  {}
  Init_HandCommandArray_right_hands right_hand_type(::aimdk_msgs::msg::HandCommandArray::_right_hand_type_type arg)
  {
    msg_.right_hand_type = std::move(arg);
    return Init_HandCommandArray_right_hands(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommandArray msg_;
};

class Init_HandCommandArray_left_hands
{
public:
  explicit Init_HandCommandArray_left_hands(::aimdk_msgs::msg::HandCommandArray & msg)
  : msg_(msg)
  {}
  Init_HandCommandArray_right_hand_type left_hands(::aimdk_msgs::msg::HandCommandArray::_left_hands_type arg)
  {
    msg_.left_hands = std::move(arg);
    return Init_HandCommandArray_right_hand_type(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommandArray msg_;
};

class Init_HandCommandArray_left_hand_type
{
public:
  explicit Init_HandCommandArray_left_hand_type(::aimdk_msgs::msg::HandCommandArray & msg)
  : msg_(msg)
  {}
  Init_HandCommandArray_left_hands left_hand_type(::aimdk_msgs::msg::HandCommandArray::_left_hand_type_type arg)
  {
    msg_.left_hand_type = std::move(arg);
    return Init_HandCommandArray_left_hands(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommandArray msg_;
};

class Init_HandCommandArray_header
{
public:
  Init_HandCommandArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandCommandArray_left_hand_type header(::aimdk_msgs::msg::HandCommandArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HandCommandArray_left_hand_type(msg_);
  }

private:
  ::aimdk_msgs::msg::HandCommandArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandCommandArray>()
{
  return aimdk_msgs::msg::builder::Init_HandCommandArray_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__BUILDER_HPP_
