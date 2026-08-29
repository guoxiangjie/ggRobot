// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/processed_audio_output__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__traits.hpp"
// Member 'audio_vad_state'
#include "aimdk_msgs/msg/detail/audio_vad_state_type__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ProcessedAudioOutput & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: stream_id
  {
    out << "stream_id: ";
    rosidl_generator_traits::value_to_yaml(msg.stream_id, out);
    out << ", ";
  }

  // member: audio_vad_state
  {
    out << "audio_vad_state: ";
    to_flow_style_yaml(msg.audio_vad_state, out);
    out << ", ";
  }

  // member: audio_data
  {
    if (msg.audio_data.size() == 0) {
      out << "audio_data: []";
    } else {
      out << "audio_data: [";
      size_t pending_items = msg.audio_data.size();
      for (auto item : msg.audio_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const ProcessedAudioOutput & msg,
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

  // member: stream_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stream_id: ";
    rosidl_generator_traits::value_to_yaml(msg.stream_id, out);
    out << "\n";
  }

  // member: audio_vad_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "audio_vad_state:\n";
    to_block_style_yaml(msg.audio_vad_state, out, indentation + 2);
  }

  // member: audio_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.audio_data.size() == 0) {
      out << "audio_data: []\n";
    } else {
      out << "audio_data:\n";
      for (auto item : msg.audio_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProcessedAudioOutput & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::ProcessedAudioOutput & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::ProcessedAudioOutput & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::ProcessedAudioOutput>()
{
  return "aimdk_msgs::msg::ProcessedAudioOutput";
}

template<>
inline const char * name<aimdk_msgs::msg::ProcessedAudioOutput>()
{
  return "aimdk_msgs/msg/ProcessedAudioOutput";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::ProcessedAudioOutput>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::ProcessedAudioOutput>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::ProcessedAudioOutput>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__TRAITS_HPP_
