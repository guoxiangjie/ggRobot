// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/NaviPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/navi_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_NaviPoint_navi_point
{
public:
  explicit Init_NaviPoint_navi_point(::aimdk_msgs::msg::NaviPoint & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::NaviPoint navi_point(::aimdk_msgs::msg::NaviPoint::_navi_point_type arg)
  {
    msg_.navi_point = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::NaviPoint msg_;
};

class Init_NaviPoint_point_id
{
public:
  Init_NaviPoint_point_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_NaviPoint_navi_point point_id(::aimdk_msgs::msg::NaviPoint::_point_id_type arg)
  {
    msg_.point_id = std::move(arg);
    return Init_NaviPoint_navi_point(msg_);
  }

private:
  ::aimdk_msgs::msg::NaviPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::NaviPoint>()
{
  return aimdk_msgs::msg::builder::Init_NaviPoint_point_id();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__BUILDER_HPP_
