// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/AudioCapture.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/audio_capture__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamps'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'info'
#include "aimdk_msgs/msg/detail/audio_info__traits.hpp"
// Member 'data'
#include "aimdk_msgs/msg/detail/audio_data__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AudioCapture & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamps
  {
    out << "stamps: ";
    to_flow_style_yaml(msg.stamps, out);
    out << ", ";
  }

  // member: mic_channels
  {
    out << "mic_channels: ";
    rosidl_generator_traits::value_to_yaml(msg.mic_channels, out);
    out << ", ";
  }

  // member: ref_channels
  {
    out << "ref_channels: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_channels, out);
    out << ", ";
  }

  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: data
  {
    out << "data: ";
    to_flow_style_yaml(msg.data, out);
    out << ", ";
  }

  // member: pkg_name
  {
    out << "pkg_name: ";
    rosidl_generator_traits::value_to_yaml(msg.pkg_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AudioCapture & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamps:\n";
    to_block_style_yaml(msg.stamps, out, indentation + 2);
  }

  // member: mic_channels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mic_channels: ";
    rosidl_generator_traits::value_to_yaml(msg.mic_channels, out);
    out << "\n";
  }

  // member: ref_channels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_channels: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_channels, out);
    out << "\n";
  }

  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data:\n";
    to_block_style_yaml(msg.data, out, indentation + 2);
  }

  // member: pkg_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pkg_name: ";
    rosidl_generator_traits::value_to_yaml(msg.pkg_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AudioCapture & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::AudioCapture & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::AudioCapture & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::AudioCapture>()
{
  return "aimdk_msgs::msg::AudioCapture";
}

template<>
inline const char * name<aimdk_msgs::msg::AudioCapture>()
{
  return "aimdk_msgs/msg/AudioCapture";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::AudioCapture>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::AudioCapture>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::AudioCapture>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__TRAITS_HPP_
