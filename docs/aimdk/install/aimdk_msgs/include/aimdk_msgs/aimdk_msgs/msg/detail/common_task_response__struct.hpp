// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/CommonTaskResponse.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__struct.hpp"
// Member 'state'
#include "aimdk_msgs/msg/detail/common_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__CommonTaskResponse __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__CommonTaskResponse __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CommonTaskResponse_
{
  using Type = CommonTaskResponse_<ContainerAllocator>;

  explicit CommonTaskResponse_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    state(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = 0ull;
    }
  }

  explicit CommonTaskResponse_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    state(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = 0ull;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>;
  _header_type header;
  using _task_id_type =
    uint64_t;
  _task_id_type task_id;
  using _state_type =
    aimdk_msgs::msg::CommonState_<ContainerAllocator>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__task_id(
    const uint64_t & _arg)
  {
    this->task_id = _arg;
    return *this;
  }
  Type & set__state(
    const aimdk_msgs::msg::CommonState_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__CommonTaskResponse
    std::shared_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__CommonTaskResponse
    std::shared_ptr<aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CommonTaskResponse_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->task_id != other.task_id) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const CommonTaskResponse_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CommonTaskResponse_

// alias to use template instance with default allocator
using CommonTaskResponse =
  aimdk_msgs::msg::CommonTaskResponse_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__COMMON_TASK_RESPONSE__STRUCT_HPP_
