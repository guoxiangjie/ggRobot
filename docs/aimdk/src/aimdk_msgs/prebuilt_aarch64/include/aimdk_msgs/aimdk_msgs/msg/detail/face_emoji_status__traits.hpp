// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/face_emoji_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const FaceEmojiStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: e_path
  {
    out << "e_path: ";
    rosidl_generator_traits::value_to_yaml(msg.e_path, out);
    out << ", ";
  }

  // member: e_path_list
  {
    if (msg.e_path_list.size() == 0) {
      out << "e_path_list: []";
    } else {
      out << "e_path_list: [";
      size_t pending_items = msg.e_path_list.size();
      for (auto item : msg.e_path_list) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: e_id
  {
    out << "e_id: ";
    rosidl_generator_traits::value_to_yaml(msg.e_id, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: priority
  {
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: time_to_end_ms
  {
    out << "time_to_end_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.time_to_end_ms, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FaceEmojiStatus & msg,
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

  // member: e_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "e_path: ";
    rosidl_generator_traits::value_to_yaml(msg.e_path, out);
    out << "\n";
  }

  // member: e_path_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.e_path_list.size() == 0) {
      out << "e_path_list: []\n";
    } else {
      out << "e_path_list:\n";
      for (auto item : msg.e_path_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: e_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "e_id: ";
    rosidl_generator_traits::value_to_yaml(msg.e_id, out);
    out << "\n";
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: priority
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << "\n";
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: time_to_end_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_to_end_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.time_to_end_ms, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FaceEmojiStatus & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::FaceEmojiStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::FaceEmojiStatus & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::FaceEmojiStatus>()
{
  return "aimdk_msgs::msg::FaceEmojiStatus";
}

template<>
inline const char * name<aimdk_msgs::msg::FaceEmojiStatus>()
{
  return "aimdk_msgs/msg/FaceEmojiStatus";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::FaceEmojiStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::FaceEmojiStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::FaceEmojiStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__TRAITS_HPP_
