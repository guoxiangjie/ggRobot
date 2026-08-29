// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/PlayTtsResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/play_tts_response__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'priority_level'
#include "aimdk_msgs/msg/detail/tts_priority_level__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PlayTtsResponse & msg,
  std::ostream & out)
{
  out << "{";
  // member: text
  {
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
    out << ", ";
  }

  // member: priority_level
  {
    out << "priority_level: ";
    to_flow_style_yaml(msg.priority_level, out);
    out << ", ";
  }

  // member: priority_weight
  {
    out << "priority_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.priority_weight, out);
    out << ", ";
  }

  // member: domain
  {
    out << "domain: ";
    rosidl_generator_traits::value_to_yaml(msg.domain, out);
    out << ", ";
  }

  // member: trace_id
  {
    out << "trace_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trace_id, out);
    out << ", ";
  }

  // member: is_success
  {
    out << "is_success: ";
    rosidl_generator_traits::value_to_yaml(msg.is_success, out);
    out << ", ";
  }

  // member: error_message
  {
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << ", ";
  }

  // member: estimated_duration
  {
    out << "estimated_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_duration, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayTtsResponse & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: text
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "text: ";
    rosidl_generator_traits::value_to_yaml(msg.text, out);
    out << "\n";
  }

  // member: priority_level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "priority_level:\n";
    to_block_style_yaml(msg.priority_level, out, indentation + 2);
  }

  // member: priority_weight
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "priority_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.priority_weight, out);
    out << "\n";
  }

  // member: domain
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "domain: ";
    rosidl_generator_traits::value_to_yaml(msg.domain, out);
    out << "\n";
  }

  // member: trace_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trace_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trace_id, out);
    out << "\n";
  }

  // member: is_success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_success: ";
    rosidl_generator_traits::value_to_yaml(msg.is_success, out);
    out << "\n";
  }

  // member: error_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_message: ";
    rosidl_generator_traits::value_to_yaml(msg.error_message, out);
    out << "\n";
  }

  // member: estimated_duration
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_duration: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_duration, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayTtsResponse & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::PlayTtsResponse & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::PlayTtsResponse & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::PlayTtsResponse>()
{
  return "aimdk_msgs::msg::PlayTtsResponse";
}

template<>
inline const char * name<aimdk_msgs::msg::PlayTtsResponse>()
{
  return "aimdk_msgs/msg/PlayTtsResponse";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::PlayTtsResponse>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::PlayTtsResponse>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::PlayTtsResponse>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_RESPONSE__TRAITS_HPP_
