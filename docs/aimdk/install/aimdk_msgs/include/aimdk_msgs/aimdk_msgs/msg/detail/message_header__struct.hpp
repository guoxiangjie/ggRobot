// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/MessageHeader.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
// Member 'meas_stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__MessageHeader __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__MessageHeader __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MessageHeader_
{
  using Type = MessageHeader_<ContainerAllocator>;

  explicit MessageHeader_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init),
    meas_stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->sequence = 0ul;
    }
  }

  explicit MessageHeader_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    frame_id(_alloc),
    meas_stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->sequence = 0ul;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _sequence_type =
    uint32_t;
  _sequence_type sequence;
  using _meas_stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _meas_stamp_type meas_stamp;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__sequence(
    const uint32_t & _arg)
  {
    this->sequence = _arg;
    return *this;
  }
  Type & set__meas_stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->meas_stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::MessageHeader_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::MessageHeader_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__MessageHeader
    std::shared_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__MessageHeader
    std::shared_ptr<aimdk_msgs::msg::MessageHeader_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MessageHeader_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->sequence != other.sequence) {
      return false;
    }
    if (this->meas_stamp != other.meas_stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MessageHeader_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MessageHeader_

// alias to use template instance with default allocator
using MessageHeader =
  aimdk_msgs::msg::MessageHeader_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MESSAGE_HEADER__STRUCT_HPP_
