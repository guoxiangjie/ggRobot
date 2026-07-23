// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/McLocomotionVelocity.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/mc_locomotion_velocity__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const McLocomotionVelocity & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: source
  {
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << ", ";
  }

  // member: forward_velocity
  {
    out << "forward_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.forward_velocity, out);
    out << ", ";
  }

  // member: lateral_velocity
  {
    out << "lateral_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.lateral_velocity, out);
    out << ", ";
  }

  // member: angular_velocity
  {
    out << "angular_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const McLocomotionVelocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << "\n";
  }

  // member: forward_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "forward_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.forward_velocity, out);
    out << "\n";
  }

  // member: lateral_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lateral_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.lateral_velocity, out);
    out << "\n";
  }

  // member: angular_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const McLocomotionVelocity & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::McLocomotionVelocity & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::McLocomotionVelocity & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::McLocomotionVelocity>()
{
  return "aimdk_msgs::msg::McLocomotionVelocity";
}

template<>
inline const char * name<aimdk_msgs::msg::McLocomotionVelocity>()
{
  return "aimdk_msgs/msg/McLocomotionVelocity";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::McLocomotionVelocity>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::McLocomotionVelocity>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::McLocomotionVelocity>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_LOCOMOTION_VELOCITY__TRAITS_HPP_
