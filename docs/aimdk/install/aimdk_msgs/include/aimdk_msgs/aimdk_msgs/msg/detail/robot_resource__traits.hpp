// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/RobotResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/robot_resource__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'current_version'
#include "aimdk_msgs/msg/detail/current_version__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotResource & msg,
  std::ostream & out)
{
  out << "{";
  // member: resource_key
  {
    out << "resource_key: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_key, out);
    out << ", ";
  }

  // member: current_version
  {
    out << "current_version: ";
    to_flow_style_yaml(msg.current_version, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotResource & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: resource_key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resource_key: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_key, out);
    out << "\n";
  }

  // member: current_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_version:\n";
    to_block_style_yaml(msg.current_version, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotResource & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::RobotResource & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::RobotResource & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::RobotResource>()
{
  return "aimdk_msgs::msg::RobotResource";
}

template<>
inline const char * name<aimdk_msgs::msg::RobotResource>()
{
  return "aimdk_msgs/msg/RobotResource";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::RobotResource>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::RobotResource>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::RobotResource>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__TRAITS_HPP_
