// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/AgentProperties.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/agent_properties__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'properties'
#include "aimdk_msgs/msg/detail/agent_properties_value__traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgentProperties & msg,
  std::ostream & out)
{
  out << "{";
  // member: properties
  {
    if (msg.properties.size() == 0) {
      out << "properties: []";
    } else {
      out << "properties: [";
      size_t pending_items = msg.properties.size();
      for (auto item : msg.properties) {
        to_flow_style_yaml(item, out);
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
  const AgentProperties & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: properties
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.properties.size() == 0) {
      out << "properties: []\n";
    } else {
      out << "properties:\n";
      for (auto item : msg.properties) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgentProperties & msg, bool use_flow_style = false)
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
  const aimdk_msgs::msg::AgentProperties & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::AgentProperties & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::AgentProperties>()
{
  return "aimdk_msgs::msg::AgentProperties";
}

template<>
inline const char * name<aimdk_msgs::msg::AgentProperties>()
{
  return "aimdk_msgs/msg/AgentProperties";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::AgentProperties>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::AgentProperties>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::msg::AgentProperties>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__TRAITS_HPP_
