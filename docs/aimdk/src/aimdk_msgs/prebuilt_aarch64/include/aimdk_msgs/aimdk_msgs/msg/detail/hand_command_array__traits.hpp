// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/hand_command_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__traits.hpp"
// Member 'left_hand_type'
// Member 'right_hand_type'
#include "aimdk_msgs/msg/detail/hand_type__traits.hpp"
// Member 'left_hands'
// Member 'right_hands'
#include "aimdk_msgs/msg/detail/hand_command__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandCommandArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: left_hand_type
  {
    out << "left_hand_type: ";
    to_flow_style_yaml(msg.left_hand_type, out);
    out << ", ";
  }

  // member: left_hands
  {
    if (msg.left_hands.size() == 0) {
      out << "left_hands: []";
    } else {
      out << "left_hands: [";
      size_t pending_items = msg.left_hands.size();
      for (auto item : msg.left_hands) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: right_hand_type
  {
    out << "right_hand_type: ";
    to_flow_style_yaml(msg.right_hand_type, out);
    out << ", ";
  }

  // member: right_hands
  {
    if (msg.right_hands.size() == 0) {
      out << "right_hands: []";
    } else {
      out << "right_hands: [";
      size_t pending_items = msg.right_hands.size();
      for (auto item : msg.right_hands) {
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
  const HandCommandArray & msg,
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

  // member: left_hand_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_hand_type:\n";
    to_block_style_yaml(msg.left_hand_type, out, indentation + 2);
  }

  // member: left_hands
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.left_hands.size() == 0) {
      out << "left_hands: []\n";
    } else {
      out << "left_hands:\n";
      for (auto item : msg.left_hands) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: right_hand_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_hand_type:\n";
    to_block_style_yaml(msg.right_hand_type, out, indentation + 2);
  }

  // member: right_hands
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.right_hands.size() == 0) {
      out << "right_hands: []\n";
    } else {
      out << "right_hands:\n";
      for (auto item : msg.right_hands) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HandCommandArray & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::HandCommandArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::HandCommandArray & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::HandCommandArray>()
{
  return "aimdk_msgs::msg::HandCommandArray";
}

template<>
inline const char * name<aimdk_msgs::msg::HandCommandArray>()
{
  return "aimdk_msgs/msg/HandCommandArray";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::HandCommandArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::HandCommandArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::HandCommandArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__TRAITS_HPP_
