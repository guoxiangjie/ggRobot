// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/Region.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'polygon'
#include "geometry_msgs/msg/detail/polygon__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__Region __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__Region __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Region_
{
  using Type = Region_<ContainerAllocator>;

  explicit Region_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : polygon(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0;
      this->drawing_type = 0;
      this->name = "";
    }
  }

  explicit Region_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    polygon(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0;
      this->drawing_type = 0;
      this->name = "";
    }
  }

  // field types and members
  using _type_type =
    uint8_t;
  _type_type type;
  using _drawing_type_type =
    uint8_t;
  _drawing_type_type drawing_type;
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _polygon_type =
    geometry_msgs::msg::Polygon_<ContainerAllocator>;
  _polygon_type polygon;

  // setters for named parameter idiom
  Type & set__type(
    const uint8_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__drawing_type(
    const uint8_t & _arg)
  {
    this->drawing_type = _arg;
    return *this;
  }
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__polygon(
    const geometry_msgs::msg::Polygon_<ContainerAllocator> & _arg)
  {
    this->polygon = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t REGION_UNDEFINED =
    0u;
  static constexpr uint8_t REGION_WORKING_SPACE =
    1u;
  static constexpr uint8_t REGION_VIRTUAL_WALL =
    2u;
  static constexpr uint8_t REGION_DRAWING_UNDEFINED =
    0u;
  static constexpr uint8_t REGION_DRAWING_CLOSURE =
    1u;
  static constexpr uint8_t REGION_DRAWING_LINES =
    2u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::Region_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::Region_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::Region_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::Region_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::Region_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::Region_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::Region_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::Region_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::Region_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::Region_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__Region
    std::shared_ptr<aimdk_msgs::msg::Region_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__Region
    std::shared_ptr<aimdk_msgs::msg::Region_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Region_ & other) const
  {
    if (this->type != other.type) {
      return false;
    }
    if (this->drawing_type != other.drawing_type) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->polygon != other.polygon) {
      return false;
    }
    return true;
  }
  bool operator!=(const Region_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Region_

// alias to use template instance with default allocator
using Region =
  aimdk_msgs::msg::Region_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_UNDEFINED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_WORKING_SPACE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_VIRTUAL_WALL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_DRAWING_UNDEFINED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_DRAWING_CLOSURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Region_<ContainerAllocator>::REGION_DRAWING_LINES;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__REGION__STRUCT_HPP_
