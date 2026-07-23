// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/RobotResourceMapping.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/robot_resource_mapping__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'robot_resource_list'
#include "aimdk_msgs/msg/detail/robot_resource__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotResourceMapping & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_master
  {
    out << "is_master: ";
    rosidl_generator_traits::value_to_yaml(msg.is_master, out);
    out << ", ";
  }

  // member: robot_ip
  {
    out << "robot_ip: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_ip, out);
    out << ", ";
  }

  // member: robot_resource_list
  {
    if (msg.robot_resource_list.size() == 0) {
      out << "robot_resource_list: []";
    } else {
      out << "robot_resource_list: [";
      size_t pending_items = msg.robot_resource_list.size();
      for (auto item : msg.robot_resource_list) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotResourceMapping & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_master
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_master: ";
    rosidl_generator_traits::value_to_yaml(msg.is_master, out);
    out << "\n";
  }

  // member: robot_ip
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_ip: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_ip, out);
    out << "\n";
  }

  // member: robot_resource_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.robot_resource_list.size() == 0) {
      out << "robot_resource_list: []\n";
    } else {
      out << "robot_resource_list:\n";
      for (auto item : msg.robot_resource_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotResourceMapping & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::RobotResourceMapping & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::RobotResourceMapping & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::RobotResourceMapping>()
{
  return "aimdk_msgs::msg::RobotResourceMapping";
}

template<>
inline const char * name<aimdk_msgs::msg::RobotResourceMapping>()
{
  return "aimdk_msgs/msg/RobotResourceMapping";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::RobotResourceMapping>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::RobotResourceMapping>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::RobotResourceMapping>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__TRAITS_HPP_
