// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PATH__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_Path_points
{
public:
  explicit Init_Path_points(::aimdk_msgs::msg::Path & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::Path points(::aimdk_msgs::msg::Path::_points_type arg)
  {
    msg_.points = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::Path msg_;
};

class Init_Path_path_id
{
public:
  Init_Path_path_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Path_points path_id(::aimdk_msgs::msg::Path::_path_id_type arg)
  {
    msg_.path_id = std::move(arg);
    return Init_Path_points(msg_);
  }

private:
  ::aimdk_msgs::msg::Path msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::Path>()
{
  return aimdk_msgs::msg::builder::Init_Path_path_id();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PATH__BUILDER_HPP_
