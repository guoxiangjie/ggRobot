// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/CurrentVersion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/current_version__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CurrentVersion & msg,
  std::ostream & out)
{
  out << "{";
  // member: version
  {
    out << "version: ";
    rosidl_generator_traits::value_to_yaml(msg.version, out);
    out << ", ";
  }

  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: files
  {
    if (msg.files.size() == 0) {
      out << "files: []";
    } else {
      out << "files: [";
      size_t pending_items = msg.files.size();
      for (auto item : msg.files) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: download_timestamp_seconds
  {
    out << "download_timestamp_seconds: ";
    rosidl_generator_traits::value_to_yaml(msg.download_timestamp_seconds, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CurrentVersion & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "version: ";
    rosidl_generator_traits::value_to_yaml(msg.version, out);
    out << "\n";
  }

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: files
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.files.size() == 0) {
      out << "files: []\n";
    } else {
      out << "files:\n";
      for (auto item : msg.files) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: download_timestamp_seconds
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "download_timestamp_seconds: ";
    rosidl_generator_traits::value_to_yaml(msg.download_timestamp_seconds, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CurrentVersion & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::CurrentVersion & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::CurrentVersion & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::CurrentVersion>()
{
  return "aimdk_msgs::msg::CurrentVersion";
}

template<>
inline const char * name<aimdk_msgs::msg::CurrentVersion>()
{
  return "aimdk_msgs/msg/CurrentVersion";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::CurrentVersion>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::CurrentVersion>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::CurrentVersion>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__TRAITS_HPP_
