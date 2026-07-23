// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/CommonTaskResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/common_task_response__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__traits.hpp"
// Member 'state'
#include "aimdk_msgs/msg/detail/common_state__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CommonTaskResponse & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: task_id
  {
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    to_flow_style_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CommonTaskResponse & msg,
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

  // member: task_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state:\n";
    to_block_style_yaml(msg.state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CommonTaskResponse & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::CommonTaskResponse & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::CommonTaskResponse & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::CommonTaskResponse>()
{
  return "aimdk_msgs::msg::CommonTaskResponse";
}

template<>
inline const char * name<aimdk_msgs::msg::CommonTaskResponse>()
{
  return "aimdk_msgs/msg/CommonTaskResponse";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::CommonTaskResponse>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonState>::value && has_fixed_size<aimdk_msgs::msg::ResponseHeader>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::CommonTaskResponse>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonState>::value && has_bounded_size<aimdk_msgs::msg::ResponseHeader>::value> {};

template<>
struct is_message<aimdk_msgs::msg::CommonTaskResponse>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__TRAITS_HPP_
