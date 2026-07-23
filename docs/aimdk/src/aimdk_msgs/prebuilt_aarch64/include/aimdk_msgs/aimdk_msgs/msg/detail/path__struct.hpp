// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/Path.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'points'
#include "geometry_msgs/msg/detail/pose2_d__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__Path __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__Path __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Path_
{
  using Type = Path_<ContainerAllocator>;

  explicit Path_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->path_id = 0l;
    }
  }

  explicit Path_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->path_id = 0l;
    }
  }

  // field types and members
  using _path_id_type =
    int32_t;
  _path_id_type path_id;
  using _points_type =
    std::vector<geometry_msgs::msg::Pose2D_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose2D_<ContainerAllocator>>>;
  _points_type points;

  // setters for named parameter idiom
  Type & set__path_id(
    const int32_t & _arg)
  {
    this->path_id = _arg;
    return *this;
  }
  Type & set__points(
    const std::vector<geometry_msgs::msg::Pose2D_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose2D_<ContainerAllocator>>> & _arg)
  {
    this->points = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::Path_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::Path_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::Path_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::Path_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::Path_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::Path_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::Path_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::Path_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::Path_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::Path_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__Path
    std::shared_ptr<aimdk_msgs::msg::Path_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__Path
    std::shared_ptr<aimdk_msgs::msg::Path_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Path_ & other) const
  {
    if (this->path_id != other.path_id) {
      return false;
    }
    if (this->points != other.points) {
      return false;
    }
    return true;
  }
  bool operator!=(const Path_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Path_

// alias to use template instance with default allocator
using Path =
  aimdk_msgs::msg::Path_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PATH__STRUCT_HPP_
