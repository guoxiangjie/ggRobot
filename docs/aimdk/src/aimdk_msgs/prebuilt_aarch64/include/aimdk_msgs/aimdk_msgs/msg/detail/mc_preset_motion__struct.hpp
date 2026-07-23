// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/McPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__McPresetMotion __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__McPresetMotion __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct McPresetMotion_
{
  using Type = McPresetMotion_<ContainerAllocator>;

  explicit McPresetMotion_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0l;
    }
  }

  explicit McPresetMotion_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0l;
    }
  }

  // field types and members
  using _value_type =
    int32_t;
  _value_type value;

  // setters for named parameter idiom
  Type & set__value(
    const int32_t & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int32_t RAISE_HAND =
    1001;
  static constexpr int32_t WAVE_HAND =
    1002;
  static constexpr int32_t SHAKE_HAND =
    1003;
  static constexpr int32_t FLYING_KISS_HAND =
    1004;
  static constexpr int32_t CLAP_HAND =
    1008;
  static constexpr int32_t TURN_WAVE_HAND =
    2001;
  static constexpr int32_t INTERACTION_BOW =
    3001;
  static constexpr int32_t INTERACTION_LIKE =
    3002;
  static constexpr int32_t INTERACTION_YE =
    3003;
  static constexpr int32_t INTERACTION_SWEATHEART =
    3004;
  static constexpr int32_t SALUTE =
    1013;
  static constexpr int32_t INTERACTION_SAD =
    3006;
  static constexpr int32_t INTERACTION_LIGHTWAVE =
    3007;
  static constexpr int32_t INTERACTION_HUG =
    3008;
  static constexpr int32_t INTERACTION_HANDX =
    3009;
  static constexpr int32_t INTERACTION_CHESTWAVE =
    3010;
  static constexpr int32_t INTERACTION_CHEER =
    3011;
  static constexpr int32_t INTERACTION_BLOWKISS =
    3012;
  static constexpr int32_t INTERACTION_BASSDANCE1 =
    3013;
  static constexpr int32_t INTERACTION_BASSDANCE2 =
    3014;
  static constexpr int32_t HITCLAP =
    3015;
  static constexpr int32_t INTERACTION_SPEAK =
    3016;
  static constexpr int32_t CLIPFIST =
    1009;
  static constexpr int32_t INTERACTION_PHOTOPOSTURE =
    3018;
  static constexpr int32_t INTERACTION_PHOTOTRIPPLEPOSTURE =
    3019;
  static constexpr int32_t POINT_HEAD =
    4001;
  static constexpr int32_t SHAKE_HEAD =
    4002;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__McPresetMotion
    std::shared_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__McPresetMotion
    std::shared_ptr<aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const McPresetMotion_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const McPresetMotion_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct McPresetMotion_

// alias to use template instance with default allocator
using McPresetMotion =
  aimdk_msgs::msg::McPresetMotion_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::RAISE_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::WAVE_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::SHAKE_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::FLYING_KISS_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::CLAP_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::TURN_WAVE_HAND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_BOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_LIKE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_YE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_SWEATHEART;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::SALUTE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_SAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_LIGHTWAVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_HUG;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_HANDX;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_CHESTWAVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_CHEER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_BLOWKISS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_BASSDANCE1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_BASSDANCE2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::HITCLAP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_SPEAK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::CLIPFIST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_PHOTOPOSTURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::INTERACTION_PHOTOTRIPPLEPOSTURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::POINT_HEAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McPresetMotion_<ContainerAllocator>::SHAKE_HEAD;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_HPP_
