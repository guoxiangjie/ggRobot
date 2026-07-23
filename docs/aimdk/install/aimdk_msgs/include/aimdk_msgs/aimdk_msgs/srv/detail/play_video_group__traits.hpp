// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/PlayVideoGroup.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO_GROUP__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO_GROUP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/play_video_group__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlayVideoGroup_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: video_path_list
  {
    if (msg.video_path_list.size() == 0) {
      out << "video_path_list: []";
    } else {
      out << "video_path_list: [";
      size_t pending_items = msg.video_path_list.size();
      for (auto item : msg.video_path_list) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: priority
  {
    out << "priority: ";
    rosidl_generator_traits::value_to_yaml(msg.priority, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayVideoGroup_Request & msg,
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

  // member: video_path_list
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.video_path_list.size() == 0) {
      out << "video_path_list: []\n";
    } else {
      out << "video_path_list:\n";
      for (auto item : msg.video_path_list) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayVideoGroup_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::PlayVideoGroup_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::PlayVideoGroup_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::PlayVideoGroup_Request>()
{
  return "aimdk_msgs::srv::PlayVideoGroup_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayVideoGroup_Request>()
{
  return "aimdk_msgs/srv/PlayVideoGroup_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayVideoGroup_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayVideoGroup_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::PlayVideoGroup_Request>
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
  const PlayVideoGroup_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayVideoGroup_Response & msg,
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

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayVideoGroup_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::PlayVideoGroup_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::PlayVideoGroup_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::PlayVideoGroup_Response>()
{
  return "aimdk_msgs::srv::PlayVideoGroup_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayVideoGroup_Response>()
{
  return "aimdk_msgs/srv/PlayVideoGroup_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayVideoGroup_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayVideoGroup_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::PlayVideoGroup_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::PlayVideoGroup>()
{
  return "aimdk_msgs::srv::PlayVideoGroup";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayVideoGroup>()
{
  return "aimdk_msgs/srv/PlayVideoGroup";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayVideoGroup>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::PlayVideoGroup_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::PlayVideoGroup_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayVideoGroup>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::PlayVideoGroup_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::PlayVideoGroup_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::PlayVideoGroup>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::PlayVideoGroup_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::PlayVideoGroup_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_VIDEO_GROUP__TRAITS_HPP_
