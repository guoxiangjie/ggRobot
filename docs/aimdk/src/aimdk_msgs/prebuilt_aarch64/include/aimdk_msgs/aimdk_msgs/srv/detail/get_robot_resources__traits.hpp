// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/GetRobotResources.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/get_robot_resources__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotResources_Request & msg,
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
  const GetRobotResources_Request & msg,
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

inline std::string to_yaml(const GetRobotResources_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetRobotResources_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetRobotResources_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetRobotResources_Request>()
{
  return "aimdk_msgs::srv::GetRobotResources_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::GetRobotResources_Request>()
{
  return "aimdk_msgs/srv/GetRobotResources_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetRobotResources_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetRobotResources_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::GetRobotResources_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"
// Member 'robot_resources'
#include "aimdk_msgs/msg/detail/robot_resource__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotResources_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: robot_resources
  {
    if (msg.robot_resources.size() == 0) {
      out << "robot_resources: []";
    } else {
      out << "robot_resources: [";
      size_t pending_items = msg.robot_resources.size();
      for (auto item : msg.robot_resources) {
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
  const GetRobotResources_Response & msg,
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

  // member: robot_resources
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.robot_resources.size() == 0) {
      out << "robot_resources: []\n";
    } else {
      out << "robot_resources:\n";
      for (auto item : msg.robot_resources) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetRobotResources_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetRobotResources_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetRobotResources_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetRobotResources_Response>()
{
  return "aimdk_msgs::srv::GetRobotResources_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::GetRobotResources_Response>()
{
  return "aimdk_msgs/srv/GetRobotResources_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetRobotResources_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetRobotResources_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::GetRobotResources_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::GetRobotResources>()
{
  return "aimdk_msgs::srv::GetRobotResources";
}

template<>
inline const char * name<aimdk_msgs::srv::GetRobotResources>()
{
  return "aimdk_msgs/srv/GetRobotResources";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetRobotResources>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::GetRobotResources_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::GetRobotResources_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetRobotResources>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::GetRobotResources_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::GetRobotResources_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::GetRobotResources>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::GetRobotResources_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::GetRobotResources_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ROBOT_RESOURCES__TRAITS_HPP_
