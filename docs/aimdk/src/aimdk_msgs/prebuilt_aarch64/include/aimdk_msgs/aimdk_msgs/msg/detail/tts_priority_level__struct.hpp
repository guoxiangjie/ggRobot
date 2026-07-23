// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/TtsPriorityLevel.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__TtsPriorityLevel __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__TtsPriorityLevel __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TtsPriorityLevel_
{
  using Type = TtsPriorityLevel_<ContainerAllocator>;

  explicit TtsPriorityLevel_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit TtsPriorityLevel_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t UNKNOWN =
    0u;
  static constexpr uint8_t BACKGROUND_L1 =
    1u;
  static constexpr uint8_t SERVICE_L2 =
    2u;
  static constexpr uint8_t MISSION_L4 =
    4u;
  static constexpr uint8_t INTERACTION_L6 =
    6u;
  static constexpr uint8_t SYSTEM_L7 =
    7u;
  static constexpr uint8_t WARNING_L8 =
    8u;
  static constexpr uint8_t SAFETY_L10 =
    10u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__TtsPriorityLevel
    std::shared_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__TtsPriorityLevel
    std::shared_ptr<aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TtsPriorityLevel_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const TtsPriorityLevel_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TtsPriorityLevel_

// alias to use template instance with default allocator
using TtsPriorityLevel =
  aimdk_msgs::msg::TtsPriorityLevel_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::BACKGROUND_L1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::SERVICE_L2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::MISSION_L4;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::INTERACTION_L6;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::SYSTEM_L7;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::WARNING_L8;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TtsPriorityLevel_<ContainerAllocator>::SAFETY_L10;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__TTS_PRIORITY_LEVEL__STRUCT_HPP_
