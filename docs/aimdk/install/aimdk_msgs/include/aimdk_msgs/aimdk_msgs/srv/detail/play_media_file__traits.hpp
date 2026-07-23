// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/PlayMediaFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/play_media_file__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"
// Member 'media_file_req'
#include "aimdk_msgs/msg/detail/play_media_file_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlayMediaFile_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: media_file_req
  {
    out << "media_file_req: ";
    to_flow_style_yaml(msg.media_file_req, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayMediaFile_Request & msg,
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

  // member: media_file_req
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "media_file_req:\n";
    to_block_style_yaml(msg.media_file_req, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayMediaFile_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::PlayMediaFile_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::PlayMediaFile_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::PlayMediaFile_Request>()
{
  return "aimdk_msgs::srv::PlayMediaFile_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayMediaFile_Request>()
{
  return "aimdk_msgs/srv/PlayMediaFile_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayMediaFile_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value && has_fixed_size<aimdk_msgs::msg::PlayMediaFileRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayMediaFile_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value && has_bounded_size<aimdk_msgs::msg::PlayMediaFileRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::PlayMediaFile_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"
// Member 'tts_resp'
#include "aimdk_msgs/msg/detail/play_tts_response__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlayMediaFile_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: tts_resp
  {
    out << "tts_resp: ";
    to_flow_style_yaml(msg.tts_resp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlayMediaFile_Response & msg,
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

  // member: tts_resp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tts_resp:\n";
    to_block_style_yaml(msg.tts_resp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlayMediaFile_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::PlayMediaFile_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::PlayMediaFile_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::PlayMediaFile_Response>()
{
  return "aimdk_msgs::srv::PlayMediaFile_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayMediaFile_Response>()
{
  return "aimdk_msgs/srv/PlayMediaFile_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayMediaFile_Response>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonResponse>::value && has_fixed_size<aimdk_msgs::msg::PlayTtsResponse>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayMediaFile_Response>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonResponse>::value && has_bounded_size<aimdk_msgs::msg::PlayTtsResponse>::value> {};

template<>
struct is_message<aimdk_msgs::srv::PlayMediaFile_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::PlayMediaFile>()
{
  return "aimdk_msgs::srv::PlayMediaFile";
}

template<>
inline const char * name<aimdk_msgs::srv::PlayMediaFile>()
{
  return "aimdk_msgs/srv/PlayMediaFile";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::PlayMediaFile>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::PlayMediaFile_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::PlayMediaFile_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::PlayMediaFile>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::PlayMediaFile_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::PlayMediaFile_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::PlayMediaFile>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::PlayMediaFile_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::PlayMediaFile_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_MEDIA_FILE__TRAITS_HPP_
