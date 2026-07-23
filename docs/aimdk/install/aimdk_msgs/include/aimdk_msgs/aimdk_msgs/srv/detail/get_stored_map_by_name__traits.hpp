// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStoredMapByName_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: map_name
  {
    out << "map_name: ";
    rosidl_generator_traits::value_to_yaml(msg.map_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStoredMapByName_Request & msg,
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

  // member: map_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_name: ";
    rosidl_generator_traits::value_to_yaml(msg.map_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStoredMapByName_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetStoredMapByName_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetStoredMapByName_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetStoredMapByName_Request>()
{
  return "aimdk_msgs::srv::GetStoredMapByName_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::GetStoredMapByName_Request>()
{
  return "aimdk_msgs/srv/GetStoredMapByName_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetStoredMapByName_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetStoredMapByName_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::GetStoredMapByName_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'header'
// already included above
// #include "std_msgs/msg/detail/header__traits.hpp"
// Member 'map_info'
#include "nav_msgs/msg/detail/map_meta_data__traits.hpp"
// Member 'navi_points'
#include "aimdk_msgs/msg/detail/navi_point__traits.hpp"
// Member 'qr_points'
#include "aimdk_msgs/msg/detail/qr_point__traits.hpp"
// Member 'hr_points'
#include "aimdk_msgs/msg/detail/hr_point__traits.hpp"
// Member 'paths'
#include "aimdk_msgs/msg/detail/path__traits.hpp"
// Member 'regions'
#include "aimdk_msgs/msg/detail/region__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetStoredMapByName_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: code
  {
    out << "code: ";
    rosidl_generator_traits::value_to_yaml(msg.code, out);
    out << ", ";
  }

  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: map_info
  {
    out << "map_info: ";
    to_flow_style_yaml(msg.map_info, out);
    out << ", ";
  }

  // member: map_version
  {
    out << "map_version: ";
    rosidl_generator_traits::value_to_yaml(msg.map_version, out);
    out << ", ";
  }

  // member: map_path
  {
    out << "map_path: ";
    rosidl_generator_traits::value_to_yaml(msg.map_path, out);
    out << ", ";
  }

  // member: data
  {
    if (msg.data.size() == 0) {
      out << "data: []";
    } else {
      out << "data: [";
      size_t pending_items = msg.data.size();
      for (auto item : msg.data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: navi_points
  {
    if (msg.navi_points.size() == 0) {
      out << "navi_points: []";
    } else {
      out << "navi_points: [";
      size_t pending_items = msg.navi_points.size();
      for (auto item : msg.navi_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: qr_points
  {
    if (msg.qr_points.size() == 0) {
      out << "qr_points: []";
    } else {
      out << "qr_points: [";
      size_t pending_items = msg.qr_points.size();
      for (auto item : msg.qr_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: hr_points
  {
    if (msg.hr_points.size() == 0) {
      out << "hr_points: []";
    } else {
      out << "hr_points: [";
      size_t pending_items = msg.hr_points.size();
      for (auto item : msg.hr_points) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: paths
  {
    if (msg.paths.size() == 0) {
      out << "paths: []";
    } else {
      out << "paths: [";
      size_t pending_items = msg.paths.size();
      for (auto item : msg.paths) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: regions
  {
    if (msg.regions.size() == 0) {
      out << "regions: []";
    } else {
      out << "regions: [";
      size_t pending_items = msg.regions.size();
      for (auto item : msg.regions) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetStoredMapByName_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "code: ";
    rosidl_generator_traits::value_to_yaml(msg.code, out);
    out << "\n";
  }

  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: map_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_info:\n";
    to_block_style_yaml(msg.map_info, out, indentation + 2);
  }

  // member: map_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_version: ";
    rosidl_generator_traits::value_to_yaml(msg.map_version, out);
    out << "\n";
  }

  // member: map_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_path: ";
    rosidl_generator_traits::value_to_yaml(msg.map_path, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: navi_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.navi_points.size() == 0) {
      out << "navi_points: []\n";
    } else {
      out << "navi_points:\n";
      for (auto item : msg.navi_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: qr_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.qr_points.size() == 0) {
      out << "qr_points: []\n";
    } else {
      out << "qr_points:\n";
      for (auto item : msg.qr_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: hr_points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.hr_points.size() == 0) {
      out << "hr_points: []\n";
    } else {
      out << "hr_points:\n";
      for (auto item : msg.hr_points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: paths
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.paths.size() == 0) {
      out << "paths: []\n";
    } else {
      out << "paths:\n";
      for (auto item : msg.paths) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: regions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.regions.size() == 0) {
      out << "regions: []\n";
    } else {
      out << "regions:\n";
      for (auto item : msg.regions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: map_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetStoredMapByName_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetStoredMapByName_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetStoredMapByName_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetStoredMapByName_Response>()
{
  return "aimdk_msgs::srv::GetStoredMapByName_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::GetStoredMapByName_Response>()
{
  return "aimdk_msgs/srv/GetStoredMapByName_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetStoredMapByName_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetStoredMapByName_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::GetStoredMapByName_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::GetStoredMapByName>()
{
  return "aimdk_msgs::srv::GetStoredMapByName";
}

template<>
inline const char * name<aimdk_msgs::srv::GetStoredMapByName>()
{
  return "aimdk_msgs/srv/GetStoredMapByName";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetStoredMapByName>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::GetStoredMapByName_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::GetStoredMapByName_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetStoredMapByName>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::GetStoredMapByName_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::GetStoredMapByName_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::GetStoredMapByName>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::GetStoredMapByName_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::GetStoredMapByName_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__TRAITS_HPP_
