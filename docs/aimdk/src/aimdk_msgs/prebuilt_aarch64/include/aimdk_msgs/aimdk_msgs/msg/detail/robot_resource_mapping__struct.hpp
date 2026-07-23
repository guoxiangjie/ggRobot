// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/RobotResourceMapping.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'robot_resource_list'
#include "aimdk_msgs/msg/detail/robot_resource__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__RobotResourceMapping __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__RobotResourceMapping __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotResourceMapping_
{
  using Type = RobotResourceMapping_<ContainerAllocator>;

  explicit RobotResourceMapping_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_master = false;
      this->robot_ip = "";
    }
  }

  explicit RobotResourceMapping_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_ip(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_master = false;
      this->robot_ip = "";
    }
  }

  // field types and members
  using _is_master_type =
    bool;
  _is_master_type is_master;
  using _robot_ip_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_ip_type robot_ip;
  using _robot_resource_list_type =
    std::vector<aimdk_msgs::msg::RobotResource_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::RobotResource_<ContainerAllocator>>>;
  _robot_resource_list_type robot_resource_list;

  // setters for named parameter idiom
  Type & set__is_master(
    const bool & _arg)
  {
    this->is_master = _arg;
    return *this;
  }
  Type & set__robot_ip(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_ip = _arg;
    return *this;
  }
  Type & set__robot_resource_list(
    const std::vector<aimdk_msgs::msg::RobotResource_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::RobotResource_<ContainerAllocator>>> & _arg)
  {
    this->robot_resource_list = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__RobotResourceMapping
    std::shared_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__RobotResourceMapping
    std::shared_ptr<aimdk_msgs::msg::RobotResourceMapping_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotResourceMapping_ & other) const
  {
    if (this->is_master != other.is_master) {
      return false;
    }
    if (this->robot_ip != other.robot_ip) {
      return false;
    }
    if (this->robot_resource_list != other.robot_resource_list) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotResourceMapping_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotResourceMapping_

// alias to use template instance with default allocator
using RobotResourceMapping =
  aimdk_msgs::msg::RobotResourceMapping_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__ROBOT_RESOURCE_MAPPING__STRUCT_HPP_
