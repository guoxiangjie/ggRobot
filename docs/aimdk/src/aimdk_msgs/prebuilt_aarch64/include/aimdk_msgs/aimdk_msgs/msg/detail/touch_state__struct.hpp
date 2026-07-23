// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/TouchState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__TouchState __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__TouchState __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TouchState_
{
  using Type = TouchState_<ContainerAllocator>;

  explicit TouchState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = 0;
      std::fill<typename std::array<uint32_t, 8>::iterator, uint32_t>(this->data.begin(), this->data.end(), 0ul);
      std::fill<typename std::array<uint32_t, 8>::iterator, uint32_t>(this->threshold.begin(), this->threshold.end(), 0ul);
      std::fill<typename std::array<bool, 8>::iterator, bool>(this->is_touched.begin(), this->is_touched.end(), false);
    }
  }

  explicit TouchState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    data(_alloc),
    threshold(_alloc),
    is_touched(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->event_type = 0;
      std::fill<typename std::array<uint32_t, 8>::iterator, uint32_t>(this->data.begin(), this->data.end(), 0ul);
      std::fill<typename std::array<uint32_t, 8>::iterator, uint32_t>(this->threshold.begin(), this->threshold.end(), 0ul);
      std::fill<typename std::array<bool, 8>::iterator, bool>(this->is_touched.begin(), this->is_touched.end(), false);
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _event_type_type =
    uint8_t;
  _event_type_type event_type;
  using _data_type =
    std::array<uint32_t, 8>;
  _data_type data;
  using _threshold_type =
    std::array<uint32_t, 8>;
  _threshold_type threshold;
  using _is_touched_type =
    std::array<bool, 8>;
  _is_touched_type is_touched;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__event_type(
    const uint8_t & _arg)
  {
    this->event_type = _arg;
    return *this;
  }
  Type & set__data(
    const std::array<uint32_t, 8> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__threshold(
    const std::array<uint32_t, 8> & _arg)
  {
    this->threshold = _arg;
    return *this;
  }
  Type & set__is_touched(
    const std::array<bool, 8> & _arg)
  {
    this->is_touched = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t UNKNOWN =
    0u;
  static constexpr uint8_t IDLE =
    1u;
  static constexpr uint8_t TOUCH =
    2u;
  static constexpr uint8_t SLIDE =
    3u;
  static constexpr uint8_t PAT_ONCE =
    4u;
  static constexpr uint8_t PAT_TWICE =
    5u;
  static constexpr uint8_t PAT_TRIPLE =
    6u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::TouchState_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::TouchState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::TouchState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::TouchState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__TouchState
    std::shared_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__TouchState
    std::shared_ptr<aimdk_msgs::msg::TouchState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TouchState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->event_type != other.event_type) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    if (this->threshold != other.threshold) {
      return false;
    }
    if (this->is_touched != other.is_touched) {
      return false;
    }
    return true;
  }
  bool operator!=(const TouchState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TouchState_

// alias to use template instance with default allocator
using TouchState =
  aimdk_msgs::msg::TouchState_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::TOUCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::SLIDE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::PAT_ONCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::PAT_TWICE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t TouchState_<ContainerAllocator>::PAT_TRIPLE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__TOUCH_STATE__STRUCT_HPP_
