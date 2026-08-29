// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/AgentPropertyIdType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__AgentPropertyIdType __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__AgentPropertyIdType __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentPropertyIdType_
{
  using Type = AgentPropertyIdType_<ContainerAllocator>;

  explicit AgentPropertyIdType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0;
    }
  }

  explicit AgentPropertyIdType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
  static constexpr uint8_t AGENT_PROPERTY_UNDEFINED =
    0u;
  static constexpr uint8_t AGENT_PROPERTY_LANGUAGE =
    1u;
  static constexpr uint8_t AGENT_PROPERTY_RUN_MODE =
    2u;
  static constexpr uint8_t AGENT_PROPERTY_GREET =
    3u;
  static constexpr uint8_t AGENT_PROPERTY_HEAD_FOLLOW =
    4u;
  static constexpr uint8_t AGENT_PROPERTY_DUPLEX_TIMEOUT =
    5u;
  static constexpr uint8_t AGENT_PROPERTY_ENVIRONMENT_SWITCH =
    6u;
  static constexpr uint8_t AGENT_PROPERTY_WELCOME_STATUS =
    7u;
  static constexpr uint8_t AGENT_PROPERTY_SITE_SWITCH =
    8u;
  static constexpr uint8_t AGENT_PROPERTY_LANGUAGE_LIST =
    9u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__AgentPropertyIdType
    std::shared_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__AgentPropertyIdType
    std::shared_ptr<aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentPropertyIdType_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentPropertyIdType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentPropertyIdType_

// alias to use template instance with default allocator
using AgentPropertyIdType =
  aimdk_msgs::msg::AgentPropertyIdType_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_UNDEFINED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_LANGUAGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_RUN_MODE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_GREET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_HEAD_FOLLOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_DUPLEX_TIMEOUT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_ENVIRONMENT_SWITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_WELCOME_STATUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_SITE_SWITCH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t AgentPropertyIdType_<ContainerAllocator>::AGENT_PROPERTY_LANGUAGE_LIST;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_HPP_
