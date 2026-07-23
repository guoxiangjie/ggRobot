// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/AudioCapture.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamps'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'info'
#include "aimdk_msgs/msg/detail/audio_info__struct.hpp"
// Member 'data'
#include "aimdk_msgs/msg/detail/audio_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__AudioCapture __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__AudioCapture __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AudioCapture_
{
  using Type = AudioCapture_<ContainerAllocator>;

  explicit AudioCapture_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamps(_init),
    info(_init),
    data(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mic_channels = 0;
      this->ref_channels = 0;
      this->pkg_name = "";
    }
  }

  explicit AudioCapture_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamps(_alloc, _init),
    info(_alloc, _init),
    data(_alloc, _init),
    pkg_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mic_channels = 0;
      this->ref_channels = 0;
      this->pkg_name = "";
    }
  }

  // field types and members
  using _stamps_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamps_type stamps;
  using _mic_channels_type =
    uint8_t;
  _mic_channels_type mic_channels;
  using _ref_channels_type =
    uint8_t;
  _ref_channels_type ref_channels;
  using _info_type =
    aimdk_msgs::msg::AudioInfo_<ContainerAllocator>;
  _info_type info;
  using _data_type =
    aimdk_msgs::msg::AudioData_<ContainerAllocator>;
  _data_type data;
  using _pkg_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pkg_name_type pkg_name;

  // setters for named parameter idiom
  Type & set__stamps(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamps = _arg;
    return *this;
  }
  Type & set__mic_channels(
    const uint8_t & _arg)
  {
    this->mic_channels = _arg;
    return *this;
  }
  Type & set__ref_channels(
    const uint8_t & _arg)
  {
    this->ref_channels = _arg;
    return *this;
  }
  Type & set__info(
    const aimdk_msgs::msg::AudioInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__data(
    const aimdk_msgs::msg::AudioData_<ContainerAllocator> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__pkg_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pkg_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::AudioCapture_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::AudioCapture_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AudioCapture_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AudioCapture_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__AudioCapture
    std::shared_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__AudioCapture
    std::shared_ptr<aimdk_msgs::msg::AudioCapture_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AudioCapture_ & other) const
  {
    if (this->stamps != other.stamps) {
      return false;
    }
    if (this->mic_channels != other.mic_channels) {
      return false;
    }
    if (this->ref_channels != other.ref_channels) {
      return false;
    }
    if (this->info != other.info) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    if (this->pkg_name != other.pkg_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const AudioCapture_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AudioCapture_

// alias to use template instance with default allocator
using AudioCapture =
  aimdk_msgs::msg::AudioCapture_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_CAPTURE__STRUCT_HPP_
