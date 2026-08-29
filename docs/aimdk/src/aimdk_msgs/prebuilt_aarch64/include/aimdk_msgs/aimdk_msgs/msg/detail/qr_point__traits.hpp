// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/QRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__QR_POINT__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__QR_POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/qr_point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'qr_code'
#include "aimdk_msgs/msg/detail/qr_code__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const QRPoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: point_id
  {
    out << "point_id: ";
    rosidl_generator_traits::value_to_yaml(msg.point_id, out);
    out << ", ";
  }

  // member: qr_code
  {
    out << "qr_code: ";
    to_flow_style_yaml(msg.qr_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const QRPoint & msg,
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

  // member: qr_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "qr_code:\n";
    to_block_style_yaml(msg.qr_code, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const QRPoint & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::QRPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::QRPoint & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::QRPoint>()
{
  return "aimdk_msgs::msg::QRPoint";
}

template<>
inline const char * name<aimdk_msgs::msg::QRPoint>()
{
  return "aimdk_msgs/msg/QRPoint";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::QRPoint>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::QRCode>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::QRPoint>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::QRCode>::value> {};

template<>
struct is_message<aimdk_msgs::msg::QRPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__QR_POINT__TRAITS_HPP_
