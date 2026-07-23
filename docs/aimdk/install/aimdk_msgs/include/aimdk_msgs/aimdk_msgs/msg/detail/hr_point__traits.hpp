// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/HRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HR_POINT__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HR_POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/hr_point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'qr_list'
#include "aimdk_msgs/msg/detail/qr_code__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HRPoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: point_id
  {
    out << "point_id: ";
    rosidl_generator_traits::value_to_yaml(msg.point_id, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: qr_list
  {
    if (msg.qr_list.size() == 0) {
      out << "qr_list: []";
    } else {
      out << "qr_list: [";
      size_t pending_items = msg.qr_list.size();
      for (auto item : msg.qr_list) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: use_head
  {
    out << "use_head: ";
    rosidl_generator_traits::value_to_yaml(msg.use_head, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HRPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: point_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "point_id: ";
    rosidl_generator_traits::value_to_yaml(msg.point_id, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: qr_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.qr_list.size() == 0) {
      out << "qr_list: []\n";
    } else {
      out << "qr_list:\n";
      for (auto item : msg.qr_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: use_head
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_head: ";
    rosidl_generator_traits::value_to_yaml(msg.use_head, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HRPoint & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::HRPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::HRPoint & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::HRPoint>()
{
  return "aimdk_msgs::msg::HRPoint";
}

template<>
inline const char * name<aimdk_msgs::msg::HRPoint>()
{
  return "aimdk_msgs/msg/HRPoint";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::HRPoint>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::HRPoint>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::HRPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__HR_POINT__TRAITS_HPP_
