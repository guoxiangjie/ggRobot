// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_HandTouchSensorData_little_finger_touch_data
{
public:
  explicit Init_HandTouchSensorData_little_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::HandTouchSensorData little_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_little_finger_touch_data_type arg)
  {
    msg_.little_finger_touch_data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_ring_finger_touch_data
{
public:
  explicit Init_HandTouchSensorData_ring_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  Init_HandTouchSensorData_little_finger_touch_data ring_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_ring_finger_touch_data_type arg)
  {
    msg_.ring_finger_touch_data = std::move(arg);
    return Init_HandTouchSensorData_little_finger_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_middle_finger_touch_data
{
public:
  explicit Init_HandTouchSensorData_middle_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  Init_HandTouchSensorData_ring_finger_touch_data middle_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_middle_finger_touch_data_type arg)
  {
    msg_.middle_finger_touch_data = std::move(arg);
    return Init_HandTouchSensorData_ring_finger_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_index_finger_touch_data
{
public:
  explicit Init_HandTouchSensorData_index_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  Init_HandTouchSensorData_middle_finger_touch_data index_finger_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_index_finger_touch_data_type arg)
  {
    msg_.index_finger_touch_data = std::move(arg);
    return Init_HandTouchSensorData_middle_finger_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_thumb_touch_data
{
public:
  explicit Init_HandTouchSensorData_thumb_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  Init_HandTouchSensorData_index_finger_touch_data thumb_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_thumb_touch_data_type arg)
  {
    msg_.thumb_touch_data = std::move(arg);
    return Init_HandTouchSensorData_index_finger_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_back_of_hand_touch_data
{
public:
  explicit Init_HandTouchSensorData_back_of_hand_touch_data(::aimdk_msgs::msg::HandTouchSensorData & msg)
  : msg_(msg)
  {}
  Init_HandTouchSensorData_thumb_touch_data back_of_hand_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_back_of_hand_touch_data_type arg)
  {
    msg_.back_of_hand_touch_data = std::move(arg);
    return Init_HandTouchSensorData_thumb_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

class Init_HandTouchSensorData_palm_touch_data
{
public:
  Init_HandTouchSensorData_palm_touch_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandTouchSensorData_back_of_hand_touch_data palm_touch_data(::aimdk_msgs::msg::HandTouchSensorData::_palm_touch_data_type arg)
  {
    msg_.palm_touch_data = std::move(arg);
    return Init_HandTouchSensorData_back_of_hand_touch_data(msg_);
  }

private:
  ::aimdk_msgs::msg::HandTouchSensorData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::HandTouchSensorData>()
{
  return aimdk_msgs::msg::builder::Init_HandTouchSensorData_palm_touch_data();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__BUILDER_HPP_
