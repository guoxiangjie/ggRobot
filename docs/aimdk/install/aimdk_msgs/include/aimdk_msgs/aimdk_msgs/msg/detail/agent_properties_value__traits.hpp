// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/AgentPropertiesValue.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/agent_properties_value__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'key'
#include "aimdk_msgs/msg/detail/agent_property_id_type__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgentPropertiesValue & msg,
  std::ostream & out)
{
  out << "{";
  // member: key
  {
    out << "key: ";
    to_flow_style_yaml(msg.key, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgentPropertiesValue & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "key:\n";
    to_block_style_yaml(msg.key, out, indentation + 2);
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgentPropertiesValue & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::AgentPropertiesValue & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::AgentPropertiesValue & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::AgentPropertiesValue>()
{
  return "aimdk_msgs::msg::AgentPropertiesValue";
}

template<>
inline const char * name<aimdk_msgs::msg::AgentPropertiesValue>()
{
  return "aimdk_msgs/msg/AgentPropertiesValue";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::AgentPropertiesValue>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::AgentPropertiesValue>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::AgentPropertiesValue>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__TRAITS_HPP_
