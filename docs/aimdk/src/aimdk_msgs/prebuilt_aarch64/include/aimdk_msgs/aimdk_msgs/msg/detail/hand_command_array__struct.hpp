// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/HandCommandArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_HPP_

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
// Member 'left_hand_type'
// Member 'right_hand_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.hpp"
// Member 'left_hands'
// Member 'right_hands'
#include "aimdk_msgs/msg/detail/hand_command__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__HandCommandArray __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__HandCommandArray __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandCommandArray_
{
  using Type = HandCommandArray_<ContainerAllocator>;

  explicit HandCommandArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    left_hand_type(_init),
    right_hand_type(_init)
  {
    (void)_init;
  }

  explicit HandCommandArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    left_hand_type(_alloc, _init),
    right_hand_type(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _left_hand_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _left_hand_type_type left_hand_type;
  using _left_hands_type =
    std::vector<aimdk_msgs::msg::HandCommand_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandCommand_<ContainerAllocator>>>;
  _left_hands_type left_hands;
  using _right_hand_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _right_hand_type_type right_hand_type;
  using _right_hands_type =
    std::vector<aimdk_msgs::msg::HandCommand_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandCommand_<ContainerAllocator>>>;
  _right_hands_type right_hands;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__left_hand_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->left_hand_type = _arg;
    return *this;
  }
  Type & set__left_hands(
    const std::vector<aimdk_msgs::msg::HandCommand_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandCommand_<ContainerAllocator>>> & _arg)
  {
    this->left_hands = _arg;
    return *this;
  }
  Type & set__right_hand_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->right_hand_type = _arg;
    return *this;
  }
  Type & set__right_hands(
    const std::vector<aimdk_msgs::msg::HandCommand_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandCommand_<ContainerAllocator>>> & _arg)
  {
    this->right_hands = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__HandCommandArray
    std::shared_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__HandCommandArray
    std::shared_ptr<aimdk_msgs::msg::HandCommandArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandCommandArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->left_hand_type != other.left_hand_type) {
      return false;
    }
    if (this->left_hands != other.left_hands) {
      return false;
    }
    if (this->right_hand_type != other.right_hand_type) {
      return false;
    }
    if (this->right_hands != other.right_hands) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandCommandArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandCommandArray_

// alias to use template instance with default allocator
using HandCommandArray =
  aimdk_msgs::msg::HandCommandArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_COMMAND_ARRAY__STRUCT_HPP_
