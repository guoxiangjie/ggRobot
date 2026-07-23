// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/SetPmuLed.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/set_pmu_led__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetPmuLed_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    to_flow_style_yaml(msg.request, out);
    out << ", ";
  }

  // member: trace_id
  {
    out << "trace_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trace_id, out);
    out << ", ";
  }

  // member: led_strip_mode
  {
    out << "led_strip_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.led_strip_mode, out);
    out << ", ";
  }

  // member: r
  {
    out << "r: ";
    rosidl_generator_traits::value_to_yaml(msg.r, out);
    out << ", ";
  }

  // member: g
  {
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: priority
  {
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
    out << ", ";
  }

  // member: reset_priority
  {
    out << "reset_priority: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_priority, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetPmuLed_Request & msg,
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

  // member: trace_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trace_id: ";
    rosidl_generator_traits::value_to_yaml(msg.trace_id, out);
    out << "\n";
  }

  // member: led_strip_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "led_strip_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.led_strip_mode, out);
    out << "\n";
  }

  // member: r
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r: ";
    rosidl_generator_traits::value_to_yaml(msg.r, out);
    out << "\n";
  }

  // member: g
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "g: ";
    rosidl_generator_traits::value_to_yaml(msg.g, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
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

  // member: reset_priority
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reset_priority: ";
    rosidl_generator_traits::value_to_yaml(msg.reset_priority, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetPmuLed_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetPmuLed_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetPmuLed_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetPmuLed_Request>()
{
  return "aimdk_msgs::srv::SetPmuLed_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::SetPmuLed_Request>()
{
  return "aimdk_msgs/srv/SetPmuLed_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetPmuLed_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetPmuLed_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::SetPmuLed_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetPmuLed_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: status_code
  {
    out << "status_code: ";
    rosidl_generator_traits::value_to_yaml(msg.status_code, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetPmuLed_Response & msg,
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

  // member: status_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status_code: ";
    rosidl_generator_traits::value_to_yaml(msg.status_code, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetPmuLed_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetPmuLed_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetPmuLed_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetPmuLed_Response>()
{
  return "aimdk_msgs::srv::SetPmuLed_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::SetPmuLed_Response>()
{
  return "aimdk_msgs/srv/SetPmuLed_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetPmuLed_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::ResponseHeader>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetPmuLed_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::ResponseHeader>::value> {};

template<>
struct is_message<aimdk_msgs::srv::SetPmuLed_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::SetPmuLed>()
{
  return "aimdk_msgs::srv::SetPmuLed";
}

template<>
inline const char * name<aimdk_msgs::srv::SetPmuLed>()
{
  return "aimdk_msgs/srv/SetPmuLed";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetPmuLed>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::SetPmuLed_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::SetPmuLed_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetPmuLed>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::SetPmuLed_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::SetPmuLed_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::SetPmuLed>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::SetPmuLed_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::SetPmuLed_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__TRAITS_HPP_
