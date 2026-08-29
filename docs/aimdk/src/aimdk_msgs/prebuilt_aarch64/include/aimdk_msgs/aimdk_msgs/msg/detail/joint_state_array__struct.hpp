// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/JointStateArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__STRUCT_HPP_

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
// Member 'state'
#include "aimdk_msgs/msg/detail/domain_error_state__struct.hpp"
// Member 'joints'
#include "aimdk_msgs/msg/detail/joint_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__JointStateArray __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__JointStateArray __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct JointStateArray_
{
  using Type = JointStateArray_<ContainerAllocator>;

  explicit JointStateArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    state(_init)
  {
    (void)_init;
  }

  explicit JointStateArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    state(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    aimdk_msgs::msg::DomainErrorState_<ContainerAllocator>;
  _state_type state;
  using _joints_type =
    std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>>;
  _joints_type joints;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__state(
    const aimdk_msgs::msg::DomainErrorState_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__joints(
    const std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>> & _arg)
  {
    this->joints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::JointStateArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::JointStateArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::JointStateArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::JointStateArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__JointStateArray
    std::shared_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__JointStateArray
    std::shared_ptr<aimdk_msgs::msg::JointStateArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const JointStateArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->joints != other.joints) {
      return false;
    }
    return true;
  }
  bool operator!=(const JointStateArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct JointStateArray_

// alias to use template instance with default allocator
using JointStateArray =
  aimdk_msgs::msg::JointStateArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__JOINT_STATE_ARRAY__STRUCT_HPP_
