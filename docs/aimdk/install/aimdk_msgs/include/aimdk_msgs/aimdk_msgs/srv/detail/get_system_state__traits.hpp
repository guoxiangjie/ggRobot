// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/GetSystemState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/get_system_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetSystemState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetSystemState_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetSystemState_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetSystemState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetSystemState_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetSystemState_Request>()
{
  return "aimdk_msgs::srv::GetSystemState_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::GetSystemState_Request>()
{
  return "aimdk_msgs/srv/GetSystemState_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetSystemState_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetSystemState_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::GetSystemState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"
// Member 'curr_status'
#include "aimdk_msgs/msg/detail/system_status__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetSystemState_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: cur_state
  {
    out << "cur_state: ";
    rosidl_generator_traits::value_to_yaml(msg.cur_state, out);
    out << ", ";
  }

  // member: curr_status
  {
    out << "curr_status: ";
    to_flow_style_yaml(msg.curr_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetSystemState_Response & msg,
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

  // member: cur_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cur_state: ";
    rosidl_generator_traits::value_to_yaml(msg.cur_state, out);
    out << "\n";
  }

  // member: curr_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "curr_status:\n";
    to_block_style_yaml(msg.curr_status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetSystemState_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetSystemState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetSystemState_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetSystemState_Response>()
{
  return "aimdk_msgs::srv::GetSystemState_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::GetSystemState_Response>()
{
  return "aimdk_msgs/srv/GetSystemState_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetSystemState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetSystemState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::GetSystemState_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::GetSystemState>()
{
  return "aimdk_msgs::srv::GetSystemState";
}

template<>
inline const char * name<aimdk_msgs::srv::GetSystemState>()
{
  return "aimdk_msgs/srv/GetSystemState";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetSystemState>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::GetSystemState_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::GetSystemState_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetSystemState>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::GetSystemState_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::GetSystemState_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::GetSystemState>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::GetSystemState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::GetSystemState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__TRAITS_HPP_
