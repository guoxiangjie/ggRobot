// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__TRAITS_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace aimdk_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandTouchSensorData & msg,
  std::ostream & out)
{
  out << "{";
  // member: palm_touch_data
  {
    if (msg.palm_touch_data.size() == 0) {
      out << "palm_touch_data: []";
    } else {
      out << "palm_touch_data: [";
      size_t pending_items = msg.palm_touch_data.size();
      for (auto item : msg.palm_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: back_of_hand_touch_data
  {
    if (msg.back_of_hand_touch_data.size() == 0) {
      out << "back_of_hand_touch_data: []";
    } else {
      out << "back_of_hand_touch_data: [";
      size_t pending_items = msg.back_of_hand_touch_data.size();
      for (auto item : msg.back_of_hand_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: thumb_touch_data
  {
    if (msg.thumb_touch_data.size() == 0) {
      out << "thumb_touch_data: []";
    } else {
      out << "thumb_touch_data: [";
      size_t pending_items = msg.thumb_touch_data.size();
      for (auto item : msg.thumb_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: index_finger_touch_data
  {
    if (msg.index_finger_touch_data.size() == 0) {
      out << "index_finger_touch_data: []";
    } else {
      out << "index_finger_touch_data: [";
      size_t pending_items = msg.index_finger_touch_data.size();
      for (auto item : msg.index_finger_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: middle_finger_touch_data
  {
    if (msg.middle_finger_touch_data.size() == 0) {
      out << "middle_finger_touch_data: []";
    } else {
      out << "middle_finger_touch_data: [";
      size_t pending_items = msg.middle_finger_touch_data.size();
      for (auto item : msg.middle_finger_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ring_finger_touch_data
  {
    if (msg.ring_finger_touch_data.size() == 0) {
      out << "ring_finger_touch_data: []";
    } else {
      out << "ring_finger_touch_data: [";
      size_t pending_items = msg.ring_finger_touch_data.size();
      for (auto item : msg.ring_finger_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: little_finger_touch_data
  {
    if (msg.little_finger_touch_data.size() == 0) {
      out << "little_finger_touch_data: []";
    } else {
      out << "little_finger_touch_data: [";
      size_t pending_items = msg.little_finger_touch_data.size();
      for (auto item : msg.little_finger_touch_data) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const HandTouchSensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: palm_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.palm_touch_data.size() == 0) {
      out << "palm_touch_data: []\n";
    } else {
      out << "palm_touch_data:\n";
      for (auto item : msg.palm_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: back_of_hand_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.back_of_hand_touch_data.size() == 0) {
      out << "back_of_hand_touch_data: []\n";
    } else {
      out << "back_of_hand_touch_data:\n";
      for (auto item : msg.back_of_hand_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: thumb_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.thumb_touch_data.size() == 0) {
      out << "thumb_touch_data: []\n";
    } else {
      out << "thumb_touch_data:\n";
      for (auto item : msg.thumb_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: index_finger_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.index_finger_touch_data.size() == 0) {
      out << "index_finger_touch_data: []\n";
    } else {
      out << "index_finger_touch_data:\n";
      for (auto item : msg.index_finger_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: middle_finger_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.middle_finger_touch_data.size() == 0) {
      out << "middle_finger_touch_data: []\n";
    } else {
      out << "middle_finger_touch_data:\n";
      for (auto item : msg.middle_finger_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: ring_finger_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ring_finger_touch_data.size() == 0) {
      out << "ring_finger_touch_data: []\n";
    } else {
      out << "ring_finger_touch_data:\n";
      for (auto item : msg.ring_finger_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: little_finger_touch_data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.little_finger_touch_data.size() == 0) {
      out << "little_finger_touch_data: []\n";
    } else {
      out << "little_finger_touch_data:\n";
      for (auto item : msg.little_finger_touch_data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HandTouchSensorData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace aimdk_msgs

namespace rosidl_generator_traits
{

[[deprecated("use aimdk_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const aimdk_msgs::msg::HandTouchSensorData & msg,
  std::ostream & out, size_t indentation = 0)
{
  aimdk_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use aimdk_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const aimdk_msgs::msg::HandTouchSensorData & msg)
{
  return aimdk_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<aimdk_msgs::msg::HandTouchSensorData>()
{
  return "aimdk_msgs::msg::HandTouchSensorData";
}

template<>
inline const char * name<aimdk_msgs::msg::HandTouchSensorData>()
{
  return "aimdk_msgs/msg/HandTouchSensorData";
}

template<>
struct has_fixed_size<aimdk_msgs::msg::HandTouchSensorData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<aimdk_msgs::msg::HandTouchSensorData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<aimdk_msgs::msg::HandTouchSensorData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__TRAITS_HPP_
