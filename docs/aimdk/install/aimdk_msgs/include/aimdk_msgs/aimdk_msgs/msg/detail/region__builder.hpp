// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/Region.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__REGION__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__REGION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/region__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_Region_polygon
{
public:
  explicit Init_Region_polygon(::aimdk_msgs::msg::Region & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::Region polygon(::aimdk_msgs::msg::Region::_polygon_type arg)
  {
    msg_.polygon = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::Region msg_;
};

class Init_Region_name
{
public:
  explicit Init_Region_name(::aimdk_msgs::msg::Region & msg)
  : msg_(msg)
  {}
  Init_Region_polygon name(::aimdk_msgs::msg::Region::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Region_polygon(msg_);
  }

private:
  ::aimdk_msgs::msg::Region msg_;
};

class Init_Region_drawing_type
{
public:
  explicit Init_Region_drawing_type(::aimdk_msgs::msg::Region & msg)
  : msg_(msg)
  {}
  Init_Region_name drawing_type(::aimdk_msgs::msg::Region::_drawing_type_type arg)
  {
    msg_.drawing_type = std::move(arg);
    return Init_Region_name(msg_);
  }

private:
  ::aimdk_msgs::msg::Region msg_;
};

class Init_Region_type
{
public:
  Init_Region_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Region_drawing_type type(::aimdk_msgs::msg::Region::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_Region_drawing_type(msg_);
  }

private:
  ::aimdk_msgs::msg::Region msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::Region>()
{
  return aimdk_msgs::msg::builder::Init_Region_type();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__REGION__BUILDER_HPP_
