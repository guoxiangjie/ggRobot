// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/GetCurrentInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/get_current_input_source__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCurrentInputSource_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    to_flow_style_yaml(msg.request, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCurrentInputSource_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "request:\n";
    to_block_style_yaml(msg.request, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCurrentInputSource_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace aimdk_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aimdk_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aimdk_msgs::srv::GetCurrentInputSource_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetCurrentInputSource_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetCurrentInputSource_Request>()
{
  return "aimdk_msgs::srv::GetCurrentInputSource_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::GetCurrentInputSource_Request>()
{
  return "aimdk_msgs/srv/GetCurrentInputSource_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetCurrentInputSource_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetCurrentInputSource_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::GetCurrentInputSource_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__traits.hpp"
// Member 'input_source'
#include "aimdk_msgs/msg/detail/mc_input_source__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCurrentInputSource_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: response
  {
    out << "response: ";
    to_flow_style_yaml(msg.response, out);
    out << ", ";
  }

  // member: input_source
  {
    out << "input_source: ";
    to_flow_style_yaml(msg.input_source, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCurrentInputSource_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "response:\n";
    to_block_style_yaml(msg.response, out, indentation + 2);
  }

  // member: input_source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "input_source:\n";
    to_block_style_yaml(msg.input_source, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCurrentInputSource_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace aimdk_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aimdk_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aimdk_msgs::srv::GetCurrentInputSource_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetCurrentInputSource_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetCurrentInputSource_Response>()
{
  return "aimdk_msgs::srv::GetCurrentInputSource_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::GetCurrentInputSource_Response>()
{
  return "aimdk_msgs/srv/GetCurrentInputSource_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetCurrentInputSource_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonTaskResponse>::value && has_fixed_size<aimdk_msgs::msg::McInputSource>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetCurrentInputSource_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonTaskResponse>::value && has_bounded_size<aimdk_msgs::msg::McInputSource>::value> {};

template<>
struct is_message<aimdk_msgs::srv::GetCurrentInputSource_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::GetCurrentInputSource>()
{
  return "aimdk_msgs::srv::GetCurrentInputSource";
}

template<>
inline const char * name<aimdk_msgs::srv::GetCurrentInputSource>()
{
  return "aimdk_msgs/srv/GetCurrentInputSource";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetCurrentInputSource>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::GetCurrentInputSource_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::GetCurrentInputSource_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetCurrentInputSource>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::GetCurrentInputSource_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::GetCurrentInputSource_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::GetCurrentInputSource>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::GetCurrentInputSource_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::GetCurrentInputSource_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__TRAITS_HPP_
