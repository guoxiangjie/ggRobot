// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/NaviPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/navi_point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'navi_point'
#include "geometry_msgs/msg/detail/pose2_d__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const NaviPoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: point_id
  {
    out << "point_id: ";
    rosidl_generator_traits::value_to_yaml(msg.point_id, out);
    out << ", ";
  }

  // member: navi_point
  {
    out << "navi_point: ";
    to_flow_style_yaml(msg.navi_point, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NaviPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: point_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "point_id: ";
    rosidl_generator_traits::value_to_yaml(msg.point_id, out);
    out << "\n";
  }

  // member: navi_point
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "navi_point:\n";
    to_block_style_yaml(msg.navi_point, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NaviPoint & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace aimdk_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aimdk_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aimdk_msgs::msg::NaviPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::NaviPoint & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::NaviPoint>()
{
  return "aimdk_msgs::msg::NaviPoint";
}

template<>
inline const char * name<aimdk_msgs::msg::NaviPoint>()
{
  return "aimdk_msgs/msg/NaviPoint";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::NaviPoint>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Pose2D>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::NaviPoint>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Pose2D>::value> {};

template<>
struct is_message<aimdk_msgs::msg::NaviPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__TRAITS_HPP_
