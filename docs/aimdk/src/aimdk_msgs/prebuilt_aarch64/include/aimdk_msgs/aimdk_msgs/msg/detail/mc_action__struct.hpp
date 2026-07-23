// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/McAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__McAction __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__McAction __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct McAction_
{
  using Type = McAction_<ContainerAllocator>;

  explicit McAction_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0l;
    }
  }

  explicit McAction_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr int32_t PASSIVE_DEFAULT =
    1;
  static constexpr int32_t SOFT_EMERGENCY_STOP =
    2;
  static constexpr int32_t DAMPING_DEFAULT =
    3;
  static constexpr int32_t ZERO_TORQUE_DEFAULT =
    4;
  static constexpr int32_t JOINT_DEFAULT =
    100;
  static constexpr int32_t JOINT_FREEZE =
    101;
  static constexpr int32_t STAND_DEFAULT =
    200;
  static constexpr int32_t STAND_BODY_CONTROL =
    201;
  static constexpr int32_t LOCOMOTION_DEFAULT =
    300;
  static constexpr int32_t RUN_DEFAULT =
    301;
  static constexpr int32_t LOCOMOTION_STEP =
    302;
  static constexpr int32_t VR_REMOTE_CONTROLLER =
    400;
  static constexpr int32_t SIT_DOWN_DEFAULT =
    2000;
  static constexpr int32_t CROUCH_DOWN_DEFAULT =
    2002;
  static constexpr int32_t LIE_DOWN_DEFAULT =
    2004;
  static constexpr int32_t STAND_UP_DEFAULT =
    2005;
  static constexpr int32_t ASCEND_STAIRS =
    2006;
  static constexpr int32_t DESCEND_STAIRS =
    2008;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::McAction_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::McAction_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McAction_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McAction_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__McAction
    std::shared_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__McAction
    std::shared_ptr<aimdk_msgs::msg::McAction_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const McAction_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const McAction_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct McAction_

// alias to use template instance with default allocator
using McAction =
  aimdk_msgs::msg::McAction_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::PASSIVE_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::SOFT_EMERGENCY_STOP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::DAMPING_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::ZERO_TORQUE_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::JOINT_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::JOINT_FREEZE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::STAND_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::STAND_BODY_CONTROL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::LOCOMOTION_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::RUN_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::LOCOMOTION_STEP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::VR_REMOTE_CONTROLLER;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::SIT_DOWN_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::CROUCH_DOWN_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::LIE_DOWN_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::STAND_UP_DEFAULT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::ASCEND_STAIRS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t McAction_<ContainerAllocator>::DESCEND_STAIRS;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_HPP_
