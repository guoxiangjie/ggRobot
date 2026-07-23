// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__TRAITS_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/srv/detail/get_all_joint_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAllJointState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: request
  {
    out << "request: ";
    to_flow_style_yaml(msg.request, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAllJointState_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAllJointState_Request & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetAllJointState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetAllJointState_Request & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetAllJointState_Request>()
{
  return "aimdk_msgs::srv::GetAllJointState_Request";
}

template<>
inline const char * name<aimdk_msgs::srv::GetAllJointState_Request>()
{
  return "aimdk_msgs/srv/GetAllJointState_Request";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetAllJointState_Request>
  : std::integral_constant<bool, has_fixed_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetAllJointState_Request>
  : std::integral_constant<bool, has_bounded_size<aimdk_msgs::msg::CommonRequest>::value> {};

template<>
struct is_message<aimdk_msgs::srv::GetAllJointState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__traits.hpp"
// Member 'head_joints'
// Member 'arm_joints'
// Member 'waist_joints'
// Member 'leg_joints'
#include "aimdk_msgs/msg/detail/joint_state__traits.hpp"

namespace aimdk_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAllJointState_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: reponse
  {
    out << "reponse: ";
    to_flow_style_yaml(msg.reponse, out);
    out << ", ";
  }

  // member: head_joints
  {
    if (msg.head_joints.size() == 0) {
      out << "head_joints: []";
    } else {
      out << "head_joints: [";
      size_t pending_items = msg.head_joints.size();
      for (auto item : msg.head_joints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: arm_joints
  {
    if (msg.arm_joints.size() == 0) {
      out << "arm_joints: []";
    } else {
      out << "arm_joints: [";
      size_t pending_items = msg.arm_joints.size();
      for (auto item : msg.arm_joints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: waist_joints
  {
    if (msg.waist_joints.size() == 0) {
      out << "waist_joints: []";
    } else {
      out << "waist_joints: [";
      size_t pending_items = msg.waist_joints.size();
      for (auto item : msg.waist_joints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: leg_joints
  {
    if (msg.leg_joints.size() == 0) {
      out << "leg_joints: []";
    } else {
      out << "leg_joints: [";
      size_t pending_items = msg.leg_joints.size();
      for (auto item : msg.leg_joints) {
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
  const GetAllJointState_Response & msg,
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

  // member: head_joints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.head_joints.size() == 0) {
      out << "head_joints: []\n";
    } else {
      out << "head_joints:\n";
      for (auto item : msg.head_joints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: arm_joints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.arm_joints.size() == 0) {
      out << "arm_joints: []\n";
    } else {
      out << "arm_joints:\n";
      for (auto item : msg.arm_joints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: waist_joints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waist_joints.size() == 0) {
      out << "waist_joints: []\n";
    } else {
      out << "waist_joints:\n";
      for (auto item : msg.waist_joints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: leg_joints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.leg_joints.size() == 0) {
      out << "leg_joints: []\n";
    } else {
      out << "leg_joints:\n";
      for (auto item : msg.leg_joints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAllJointState_Response & msg, bool use_flow_style = false)
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
  const aimdk_msgs::srv::GetAllJointState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::srv::GetAllJointState_Response & msg)
{
  return aimdk_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::srv::GetAllJointState_Response>()
{
  return "aimdk_msgs::srv::GetAllJointState_Response";
}

template<>
inline const char * name<aimdk_msgs::srv::GetAllJointState_Response>()
{
  return "aimdk_msgs/srv/GetAllJointState_Response";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetAllJointState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetAllJointState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<aimdk_msgs::srv::GetAllJointState_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<aimdk_msgs::srv::GetAllJointState>()
{
  return "aimdk_msgs::srv::GetAllJointState";
}

template<>
inline const char * name<aimdk_msgs::srv::GetAllJointState>()
{
  return "aimdk_msgs/srv/GetAllJointState";
}

template<>
struct has_fixed_size<aimdk_msgs::srv::GetAllJointState>
  : std::integral_constant<
    bool,
    has_fixed_size<aimdk_msgs::srv::GetAllJointState_Request>::value &&
    has_fixed_size<aimdk_msgs::srv::GetAllJointState_Response>::value
  >
{
};

template<>
struct has_bounded_size<aimdk_msgs::srv::GetAllJointState>
  : std::integral_constant<
    bool,
    has_bounded_size<aimdk_msgs::srv::GetAllJointState_Request>::value &&
    has_bounded_size<aimdk_msgs::srv::GetAllJointState_Response>::value
  >
{
};

template<>
struct is_service<aimdk_msgs::srv::GetAllJointState>
  : std::true_type
{
};

template<>
struct is_service_request<aimdk_msgs::srv::GetAllJointState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<aimdk_msgs::srv::GetAllJointState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__TRAITS_HPP_
