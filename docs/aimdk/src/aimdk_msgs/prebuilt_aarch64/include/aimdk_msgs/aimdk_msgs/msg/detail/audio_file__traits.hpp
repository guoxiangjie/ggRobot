// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/AudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/audio_file__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'info'
#include "aimdk_msgs/msg/detail/audio_info__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AudioFile & msg,
  std::ostream & out)
{
  out << "{";
  // member: pkg_name
  {
    out << "pkg_name: ";
    rosidl_generator_traits::value_to_yaml(msg.pkg_name, out);
    out << ", ";
  }

  // member: file_name
  {
    out << "file_name: ";
    rosidl_generator_traits::value_to_yaml(msg.file_name, out);
    out << ", ";
  }

  // member: file_path
  {
    out << "file_path: ";
    rosidl_generator_traits::value_to_yaml(msg.file_path, out);
    out << ", ";
  }

  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: priority
  {
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << ", ";
  }

  // member: priority_weight
  {
    out << "priority_weight: ";
    rosidl_generator_traits::value_to_yaml(msg.priority_weight, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AudioFile & msg,
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

  // member: file_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "file_name: ";
    rosidl_generator_traits::value_to_yaml(msg.file_name, out);
    out << "\n";
  }

  // member: file_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "file_path: ";
    rosidl_generator_traits::value_to_yaml(msg.file_path, out);
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

  // member: priority
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << "\n";
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AudioFile & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::AudioFile & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::AudioFile & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::AudioFile>()
{
  return "aimdk_msgs::msg::AudioFile";
}

template<>
inline const char * name<aimdk_msgs::msg::AudioFile>()
{
  return "aimdk_msgs/msg/AudioFile";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::AudioFile>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::AudioFile>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::AudioFile>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_FILE__TRAITS_HPP_
