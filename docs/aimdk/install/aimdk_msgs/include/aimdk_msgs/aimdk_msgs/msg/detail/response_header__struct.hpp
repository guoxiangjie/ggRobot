// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/ResponseHeader.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__ResponseHeader __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__ResponseHeader __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ResponseHeader_
{
  using Type = ResponseHeader_<ContainerAllocator>;

  explicit ResponseHeader_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->code = 0ll;
    }
  }

  explicit ResponseHeader_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->code = 0ll;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _code_type =
    int64_t;
  _code_type code;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__code(
    const int64_t & _arg)
  {
    this->code = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__ResponseHeader
    std::shared_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__ResponseHeader
    std::shared_ptr<aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ResponseHeader_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->code != other.code) {
      return false;
    }
    return true;
  }
  bool operator!=(const ResponseHeader_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ResponseHeader_

// alias to use template instance with default allocator
using ResponseHeader =
  aimdk_msgs::msg::ResponseHeader_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__RESPONSE_HEADER__STRUCT_HPP_
