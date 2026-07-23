// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/PlayStateChange.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/play_state_change__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'state'
#include "aimdk_msgs/msg/detail/play_state_type__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PlayStateChange & msg,
  std::ostream & out)
{
  out << "{";
  // member: pkg_name
  {
    out << "pkg_name: ";
    rosidl_generator_traits::value_to_yaml(msg.pkg_name, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    to_flow_style_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayStateChange & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pkg_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pkg_name: ";
    rosidl_generator_traits::value_to_yaml(msg.pkg_name, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state:\n";
    to_block_style_yaml(msg.state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayStateChange & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::PlayStateChange & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::PlayStateChange & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::PlayStateChange>()
{
  return "aimdk_msgs::msg::PlayStateChange";
}

template<>
inline const char * name<aimdk_msgs::msg::PlayStateChange>()
{
  return "aimdk_msgs/msg/PlayStateChange";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::PlayStateChange>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::PlayStateChange>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::PlayStateChange>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__TRAITS_HPP_
