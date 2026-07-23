// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/NaviPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'navi_point'
#include "geometry_msgs/msg/detail/pose2_d__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__NaviPoint __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__NaviPoint __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NaviPoint_
{
  using Type = NaviPoint_<ContainerAllocator>;

  explicit NaviPoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : navi_point(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point_id = 0l;
    }
  }

  explicit NaviPoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : navi_point(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point_id = 0l;
    }
  }

  // field types and members
  using _point_id_type =
    int32_t;
  _point_id_type point_id;
  using _navi_point_type =
    geometry_msgs::msg::Pose2D_<ContainerAllocator>;
  _navi_point_type navi_point;

  // setters for named parameter idiom
  Type & set__point_id(
    const int32_t & _arg)
  {
    this->point_id = _arg;
    return *this;
  }
  Type & set__navi_point(
    const geometry_msgs::msg::Pose2D_<ContainerAllocator> & _arg)
  {
    this->navi_point = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::NaviPoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::NaviPoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__NaviPoint
    std::shared_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__NaviPoint
    std::shared_ptr<aimdk_msgs::msg::NaviPoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NaviPoint_ & other) const
  {
    if (this->point_id != other.point_id) {
      return false;
    }
    if (this->navi_point != other.navi_point) {
      return false;
    }
    return true;
  }
  bool operator!=(const NaviPoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NaviPoint_

// alias to use template instance with default allocator
using NaviPoint =
  aimdk_msgs::msg::NaviPoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__NAVI_POINT__STRUCT_HPP_
