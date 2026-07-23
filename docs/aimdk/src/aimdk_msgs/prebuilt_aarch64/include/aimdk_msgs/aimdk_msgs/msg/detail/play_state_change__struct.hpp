// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/PlayStateChange.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'state'
#include "aimdk_msgs/msg/detail/play_state_type__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__PlayStateChange __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__PlayStateChange __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PlayStateChange_
{
  using Type = PlayStateChange_<ContainerAllocator>;

  explicit PlayStateChange_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pkg_name = "";
    }
  }

  explicit PlayStateChange_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pkg_name(_alloc),
    state(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pkg_name = "";
    }
  }

  // field types and members
  using _pkg_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pkg_name_type pkg_name;
  using _state_type =
    aimdk_msgs::msg::PlayStateType_<ContainerAllocator>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__pkg_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pkg_name = _arg;
    return *this;
  }
  Type & set__state(
    const aimdk_msgs::msg::PlayStateType_<ContainerAllocator> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__PlayStateChange
    std::shared_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__PlayStateChange
    std::shared_ptr<aimdk_msgs::msg::PlayStateChange_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayStateChange_ & other) const
  {
    if (this->pkg_name != other.pkg_name) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayStateChange_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayStateChange_

// alias to use template instance with default allocator
using PlayStateChange =
  aimdk_msgs::msg::PlayStateChange_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_STATE_CHANGE__STRUCT_HPP_
