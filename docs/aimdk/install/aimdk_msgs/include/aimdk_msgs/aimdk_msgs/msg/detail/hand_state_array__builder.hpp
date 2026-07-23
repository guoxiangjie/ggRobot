// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandStateArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_state_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandStateArray_right_touch_sensors
{
public:
  explicit Init_HandStateArray_right_touch_sensors(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandStateArray right_touch_sensors(::aimdk_msgs::msg::HandStateArray::_right_touch_sensors_type arg)
  {
    msg_.right_touch_sensors = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_right_hands
{
public:
  explicit Init_HandStateArray_right_hands(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  Init_HandStateArray_right_touch_sensors right_hands(::aimdk_msgs::msg::HandStateArray::_right_hands_type arg)
  {
    msg_.right_hands = std::move(arg);
    return Init_HandStateArray_right_touch_sensors(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_right_hand_type
{
public:
  explicit Init_HandStateArray_right_hand_type(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  Init_HandStateArray_right_hands right_hand_type(::aimdk_msgs::msg::HandStateArray::_right_hand_type_type arg)
  {
    msg_.right_hand_type = std::move(arg);
    return Init_HandStateArray_right_hands(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_left_touch_sensors
{
public:
  explicit Init_HandStateArray_left_touch_sensors(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  Init_HandStateArray_right_hand_type left_touch_sensors(::aimdk_msgs::msg::HandStateArray::_left_touch_sensors_type arg)
  {
    msg_.left_touch_sensors = std::move(arg);
    return Init_HandStateArray_right_hand_type(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_left_hands
{
public:
  explicit Init_HandStateArray_left_hands(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  Init_HandStateArray_left_touch_sensors left_hands(::aimdk_msgs::msg::HandStateArray::_left_hands_type arg)
  {
    msg_.left_hands = std::move(arg);
    return Init_HandStateArray_left_touch_sensors(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_left_hand_type
{
public:
  explicit Init_HandStateArray_left_hand_type(::aimdk_msgs::msg::HandStateArray & msg)
  : msg_(msg)
  {}
  Init_HandStateArray_left_hands left_hand_type(::aimdk_msgs::msg::HandStateArray::_left_hand_type_type arg)
  {
    msg_.left_hand_type = std::move(arg);
    return Init_HandStateArray_left_hands(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

class Init_HandStateArray_header
{
public:
  Init_HandStateArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandStateArray_left_hand_type header(::aimdk_msgs::msg::HandStateArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HandStateArray_left_hand_type(msg_);
  }

private:
  ::aimdk_msgs::msg::HandStateArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandStateArray>()
{
  return aimdk_msgs::msg::builder::Init_HandStateArray_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__BUILDER_HPP_
