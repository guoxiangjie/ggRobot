// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/ExecuteActionResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/execute_action_resource__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"
// Member 'slaves'
#include "aimdk_msgs/msg/detail/slave_device__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ExecuteActionResource_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: resource_key
  {
    out << "resource_key: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_key, out);
    out << ", ";
  }

  // member: resource_version
  {
    out << "resource_version: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_version, out);
    out << ", ";
  }

  // member: slaves
  {
    if (msg.slaves.size() == 0) {
      out << "slaves: []";
    } else {
      out << "slaves: [";
      size_t pending_items = msg.slaves.size();
      for (auto item : msg.slaves) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: meta
  {
    out << "meta: ";
    rosidl_generator_traits::value_to_yaml(msg.meta, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteActionResource_Request & msg,
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

  // member: resource_key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resource_key: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_key, out);
    out << "\n";
  }

  // member: resource_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resource_version: ";
    rosidl_generator_traits::value_to_yaml(msg.resource_version, out);
    out << "\n";
  }

  // member: slaves
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.slaves.size() == 0) {
      out << "slaves: []\n";
    } else {
      out << "slaves:\n";
      for (auto item : msg.slaves) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: meta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "meta: ";
    rosidl_generator_traits::value_to_yaml(msg.meta, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteActionResource_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::ExecuteActionResource_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::ExecuteActionResource_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::ExecuteActionResource_Request>()
{
  return "aimdk_msgs::srv::ExecuteActionResource_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::ExecuteActionResource_Request>()
{
  return "aimdk_msgs/srv/ExecuteActionResource_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::ExecuteActionResource_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::ExecuteActionResource_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::ExecuteActionResource_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ExecuteActionResource_Response & msg,
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
  const ExecuteActionResource_Response & msg,
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

inline std::string to_yaml(const ExecuteActionResource_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::ExecuteActionResource_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::ExecuteActionResource_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::ExecuteActionResource_Response>()
{
  return "aimdk_msgs::srv::ExecuteActionResource_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::ExecuteActionResource_Response>()
{
  return "aimdk_msgs/srv/ExecuteActionResource_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::ExecuteActionResource_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonResponse>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::ExecuteActionResource_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonResponse>::value> {};

template<>
struct is_message<aimdk_msgs::srv::ExecuteActionResource_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::ExecuteActionResource>()
{
  return "aimdk_msgs::srv::ExecuteActionResource";
}

template<>
inline const char * name<aimdk_msgs::srv::ExecuteActionResource>()
{
  return "aimdk_msgs/srv/ExecuteActionResource";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::ExecuteActionResource>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::ExecuteActionResource_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::ExecuteActionResource_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::ExecuteActionResource>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::ExecuteActionResource_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::ExecuteActionResource_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::ExecuteActionResource>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::ExecuteActionResource_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::ExecuteActionResource_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__TRAITS_HPP_
