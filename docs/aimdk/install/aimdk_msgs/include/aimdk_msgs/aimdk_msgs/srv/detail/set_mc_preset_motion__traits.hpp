// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/SetMcPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/set_mc_preset_motion__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/request_header__traits.hpp"
// Member 'area'
#include "aimdk_msgs/msg/detail/mc_control_area__traits.hpp"
// Member 'motion'
#include "aimdk_msgs/msg/detail/mc_preset_motion__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMcPresetMotion_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: area
  {
    out << "area: ";
    to_flow_style_yaml(msg.area, out);
    out << ", ";
  }

  // member: motion
  {
    out << "motion: ";
    to_flow_style_yaml(msg.motion, out);
    out << ", ";
  }

  // member: interrupt
  {
    out << "interrupt: ";
    rosidl_generator_traits::value_to_yaml(msg.interrupt, out);
    out << ", ";
  }

  // member: ani_path
  {
    out << "ani_path: ";
    rosidl_generator_traits::value_to_yaml(msg.ani_path, out);
    out << ", ";
  }

  // member: play_timestamp
  {
    out << "play_timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.play_timestamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMcPresetMotion_Request & msg,
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

  // member: area
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "area:\n";
    to_block_style_yaml(msg.area, out, indentation + 2);
  }

  // member: motion
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motion:\n";
    to_block_style_yaml(msg.motion, out, indentation + 2);
  }

  // member: interrupt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "interrupt: ";
    rosidl_generator_traits::value_to_yaml(msg.interrupt, out);
    out << "\n";
  }

  // member: ani_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ani_path: ";
    rosidl_generator_traits::value_to_yaml(msg.ani_path, out);
    out << "\n";
  }

  // member: play_timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "play_timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.play_timestamp, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMcPresetMotion_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetMcPresetMotion_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetMcPresetMotion_Request>()
{
  return "aimdk_msgs::srv::SetMcPresetMotion_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMcPresetMotion_Request>()
{
  return "aimdk_msgs/srv/SetMcPresetMotion_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMcPresetMotion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMcPresetMotion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::SetMcPresetMotion_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMcPresetMotion_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: response
  {
    out << "response: ";
    to_flow_style_yaml(msg.response, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMcPresetMotion_Response & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMcPresetMotion_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetMcPresetMotion_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetMcPresetMotion_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetMcPresetMotion_Response>()
{
  return "aimdk_msgs::srv::SetMcPresetMotion_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMcPresetMotion_Response>()
{
  return "aimdk_msgs/srv/SetMcPresetMotion_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMcPresetMotion_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonTaskResponse>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMcPresetMotion_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonTaskResponse>::value> {};

template<>
struct is_message<aimdk_msgs::srv::SetMcPresetMotion_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::SetMcPresetMotion>()
{
  return "aimdk_msgs::srv::SetMcPresetMotion";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMcPresetMotion>()
{
  return "aimdk_msgs/srv/SetMcPresetMotion";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMcPresetMotion>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::SetMcPresetMotion_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::SetMcPresetMotion_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMcPresetMotion>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::SetMcPresetMotion_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::SetMcPresetMotion_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::SetMcPresetMotion>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::SetMcPresetMotion_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::SetMcPresetMotion_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__TRAITS_HPP_
