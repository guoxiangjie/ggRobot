// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/SetMute.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MUTE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MUTE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/set_mute__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMute_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    to_flow_style_yaml(msg.request, out);
    out << ", ";
  }

  // member: is_mute
  {
    out << "is_mute: ";
    rosidl_generator_traits::value_to_yaml(msg.is_mute, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMute_Request & msg,
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

  // member: is_mute
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_mute: ";
    rosidl_generator_traits::value_to_yaml(msg.is_mute, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMute_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetMute_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetMute_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetMute_Request>()
{
  return "aimdk_msgs::srv::SetMute_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMute_Request>()
{
  return "aimdk_msgs/srv/SetMute_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMute_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMute_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::SetMute_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMute_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: reponse
  {
    out << "reponse: ";
    to_flow_style_yaml(msg.reponse, out);
    out << ", ";
  }

  // member: is_mute
  {
    out << "is_mute: ";
    rosidl_generator_traits::value_to_yaml(msg.is_mute, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMute_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: reponse
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reponse:\n";
    to_block_style_yaml(msg.reponse, out, indentation + 2);
  }

  // member: is_mute
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_mute: ";
    rosidl_generator_traits::value_to_yaml(msg.is_mute, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMute_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::SetMute_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::SetMute_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::SetMute_Response>()
{
  return "aimdk_msgs::srv::SetMute_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMute_Response>()
{
  return "aimdk_msgs/srv/SetMute_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMute_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonResponse>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMute_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonResponse>::value> {};

template<>
struct is_message<aimdk_msgs::srv::SetMute_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::SetMute>()
{
  return "aimdk_msgs::srv::SetMute";
}

template<>
inline const char * name<aimdk_msgs::srv::SetMute>()
{
  return "aimdk_msgs/srv/SetMute";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::SetMute>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::SetMute_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::SetMute_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::SetMute>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::SetMute_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::SetMute_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::SetMute>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::SetMute_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::SetMute_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MUTE__TRAITS_HPP_
