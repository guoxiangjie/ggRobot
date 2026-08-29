// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/McActionInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/mc_action_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'current_action'
#include "aimdk_msgs/msg/detail/mc_action__traits.hpp"
// Member 'status'
#include "aimdk_msgs/msg/detail/mc_action_status__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const McActionInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_action
  {
    out << "current_action: ";
    to_flow_style_yaml(msg.current_action, out);
    out << ", ";
  }

  // member: action_desc
  {
    out << "action_desc: ";
    rosidl_generator_traits::value_to_yaml(msg.action_desc, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    to_flow_style_yaml(msg.status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const McActionInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_action
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_action:\n";
    to_block_style_yaml(msg.current_action, out, indentation + 2);
  }

  // member: action_desc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "action_desc: ";
    rosidl_generator_traits::value_to_yaml(msg.action_desc, out);
    out << "\n";
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status:\n";
    to_block_style_yaml(msg.status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const McActionInfo & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::McActionInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::McActionInfo & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::McActionInfo>()
{
  return "aimdk_msgs::msg::McActionInfo";
}

template<>
inline const char * name<aimdk_msgs::msg::McActionInfo>()
{
  return "aimdk_msgs/msg/McActionInfo";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::McActionInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::McActionInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::McActionInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_INFO__TRAITS_HPP_
