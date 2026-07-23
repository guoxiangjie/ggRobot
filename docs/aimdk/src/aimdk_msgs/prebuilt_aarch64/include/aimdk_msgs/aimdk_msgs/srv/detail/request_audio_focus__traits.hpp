// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/RequestAudioFocus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/request_audio_focus__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"
// Member 'focus_requester'
#include "aimdk_msgs/msg/detail/focus_requester__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RequestAudioFocus_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    to_flow_style_yaml(msg.request, out);
    out << ", ";
  }

  // member: focus_requester
  {
    out << "focus_requester: ";
    to_flow_style_yaml(msg.focus_requester, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RequestAudioFocus_Request & msg,
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

  // member: focus_requester
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "focus_requester:\n";
    to_block_style_yaml(msg.focus_requester, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RequestAudioFocus_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::RequestAudioFocus_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::RequestAudioFocus_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::RequestAudioFocus_Request>()
{
  return "aimdk_msgs::srv::RequestAudioFocus_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::RequestAudioFocus_Request>()
{
  return "aimdk_msgs/srv/RequestAudioFocus_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::RequestAudioFocus_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value && has_fixed_size<aimdk_msgs::msg::FocusRequester>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::RequestAudioFocus_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value && has_bounded_size<aimdk_msgs::msg::FocusRequester>::value> {};

template<>
struct is_message<aimdk_msgs::srv::RequestAudioFocus_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"
// Member 'focus_response'
#include "aimdk_msgs/msg/detail/focus_response__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const RequestAudioFocus_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: reponse
  {
    out << "reponse: ";
    to_flow_style_yaml(msg.reponse, out);
    out << ", ";
  }

  // member: focus_response
  {
    out << "focus_response: ";
    to_flow_style_yaml(msg.focus_response, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RequestAudioFocus_Response & msg,
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

  // member: focus_response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "focus_response:\n";
    to_block_style_yaml(msg.focus_response, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RequestAudioFocus_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::RequestAudioFocus_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::RequestAudioFocus_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::RequestAudioFocus_Response>()
{
  return "aimdk_msgs::srv::RequestAudioFocus_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::RequestAudioFocus_Response>()
{
  return "aimdk_msgs/srv/RequestAudioFocus_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::RequestAudioFocus_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonResponse>::value && has_fixed_size<aimdk_msgs::msg::FocusResponse>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::RequestAudioFocus_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonResponse>::value && has_bounded_size<aimdk_msgs::msg::FocusResponse>::value> {};

template<>
struct is_message<aimdk_msgs::srv::RequestAudioFocus_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::RequestAudioFocus>()
{
  return "aimdk_msgs::srv::RequestAudioFocus";
}

template<>
inline const char * name<aimdk_msgs::srv::RequestAudioFocus>()
{
  return "aimdk_msgs/srv/RequestAudioFocus";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::RequestAudioFocus>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::RequestAudioFocus_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::RequestAudioFocus_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::RequestAudioFocus>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::RequestAudioFocus_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::RequestAudioFocus_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::RequestAudioFocus>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::RequestAudioFocus_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::RequestAudioFocus_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__REQUEST_AUDIO_FOCUS__TRAITS_HPP_
