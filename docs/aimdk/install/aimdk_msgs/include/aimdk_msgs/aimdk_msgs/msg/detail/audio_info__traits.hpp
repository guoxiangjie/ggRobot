// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/AudioInfo.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/audio_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AudioInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: channels
  {
    out << "channels: ";
    rosidl_generator_traits::value_to_yaml(msg.channels, out);
    out << ", ";
  }

  // member: sample_rate
  {
    out << "sample_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_rate, out);
    out << ", ";
  }

  // member: size
  {
    out << "size: ";
    rosidl_generator_traits::value_to_yaml(msg.size, out);
    out << ", ";
  }

  // member: sample_format
  {
    out << "sample_format: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_format, out);
    out << ", ";
  }

  // member: coding_format
  {
    out << "coding_format: ";
    rosidl_generator_traits::value_to_yaml(msg.coding_format, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AudioInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: channels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "channels: ";
    rosidl_generator_traits::value_to_yaml(msg.channels, out);
    out << "\n";
  }

  // member: sample_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sample_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_rate, out);
    out << "\n";
  }

  // member: size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size: ";
    rosidl_generator_traits::value_to_yaml(msg.size, out);
    out << "\n";
  }

  // member: sample_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sample_format: ";
    rosidl_generator_traits::value_to_yaml(msg.sample_format, out);
    out << "\n";
  }

  // member: coding_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coding_format: ";
    rosidl_generator_traits::value_to_yaml(msg.coding_format, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AudioInfo & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::AudioInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::AudioInfo & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::AudioInfo>()
{
  return "aimdk_msgs::msg::AudioInfo";
}

template<>
inline const char * name<aimdk_msgs::msg::AudioInfo>()
{
  return "aimdk_msgs/msg/AudioInfo";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::AudioInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::AudioInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::AudioInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_INFO__TRAITS_HPP_
