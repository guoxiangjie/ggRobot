// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/McActionCommand.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'action'
#include "aimdk_msgs/msg/detail/mc_action__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__McActionCommand __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__McActionCommand __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct McActionCommand_
{
  using Type = McActionCommand_<ContainerAllocator>;

  explicit McActionCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action_desc = "";
    }
  }

  explicit McActionCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_alloc, _init),
    action_desc(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action_desc = "";
    }
  }

  // field types and members
  using _action_type =
    aimdk_msgs::msg::McAction_<ContainerAllocator>;
  _action_type action;
  using _action_desc_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _action_desc_type action_desc;

  // setters for named parameter idiom
  Type & set__action(
    const aimdk_msgs::msg::McAction_<ContainerAllocator> & _arg)
  {
    this->action = _arg;
    return *this;
  }
  Type & set__action_desc(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->action_desc = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::McActionCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::McActionCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McActionCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::McActionCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__McActionCommand
    std::shared_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__McActionCommand
    std::shared_ptr<aimdk_msgs::msg::McActionCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const McActionCommand_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    if (this->action_desc != other.action_desc) {
      return false;
    }
    return true;
  }
  bool operator!=(const McActionCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct McActionCommand_

// alias to use template instance with default allocator
using McActionCommand =
  aimdk_msgs::msg::McActionCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION_COMMAND__STRUCT_HPP_
