// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/RobotResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'current_version'
#include "aimdk_msgs/msg/detail/current_version__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__RobotResource __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__RobotResource __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotResource_
{
  using Type = RobotResource_<ContainerAllocator>;

  explicit RobotResource_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : current_version(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resource_key = "";
    }
  }

  explicit RobotResource_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : resource_key(_alloc),
    current_version(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resource_key = "";
    }
  }

  // field types and members
  using _resource_key_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _resource_key_type resource_key;
  using _current_version_type =
    aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>;
  _current_version_type current_version;

  // setters for named parameter idiom
  Type & set__resource_key(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->resource_key = _arg;
    return *this;
  }
  Type & set__current_version(
    const aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> & _arg)
  {
    this->current_version = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::RobotResource_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::RobotResource_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::RobotResource_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::RobotResource_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__RobotResource
    std::shared_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__RobotResource
    std::shared_ptr<aimdk_msgs::msg::RobotResource_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotResource_ & other) const
  {
    if (this->resource_key != other.resource_key) {
      return false;
    }
    if (this->current_version != other.current_version) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotResource_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotResource_

// alias to use template instance with default allocator
using RobotResource =
  aimdk_msgs::msg::RobotResource_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE__STRUCT_HPP_
