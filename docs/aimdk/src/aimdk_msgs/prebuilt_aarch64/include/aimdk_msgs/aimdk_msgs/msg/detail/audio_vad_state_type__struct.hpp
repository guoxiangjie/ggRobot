// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/AudioVadStateType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__AudioVadStateType __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__AudioVadStateType __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AudioVadStateType_
{
  using Type = AudioVadStateType_<ContainerAllocator>;

  explicit AudioVadStateType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit AudioVadStateType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  // field types and members
  using _value_type =
    uint8_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const uint8_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t AUDIO_VAD_STATE_NONE =
    0u;
  static constexpr uint8_t AUDIO_VAD_STATE_BEGIN =
    1u;
  static constexpr uint8_t AUDIO_VAD_STATE_PROCESSING =
    2u;
  static constexpr uint8_t AUDIO_VAD_STATE_END =
    3u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__AudioVadStateType
    std::shared_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__AudioVadStateType
    std::shared_ptr<aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AudioVadStateType_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const AudioVadStateType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AudioVadStateType_

// alias to use template instance with default allocator
using AudioVadStateType =
  aimdk_msgs::msg::AudioVadStateType_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AudioVadStateType_<ContainerAllocator>::AUDIO_VAD_STATE_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AudioVadStateType_<ContainerAllocator>::AUDIO_VAD_STATE_BEGIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AudioVadStateType_<ContainerAllocator>::AUDIO_VAD_STATE_PROCESSING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AudioVadStateType_<ContainerAllocator>::AUDIO_VAD_STATE_END;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AUDIO_VAD_STATE_TYPE__STRUCT_HPP_
