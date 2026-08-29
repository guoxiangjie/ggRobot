// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/AgentPropertiesValue.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'key'
#include "aimdk_msgs/msg/detail/agent_property_id_type__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__AgentPropertiesValue __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__AgentPropertiesValue __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentPropertiesValue_
{
  using Type = AgentPropertiesValue_<ContainerAllocator>;

  explicit AgentPropertiesValue_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : key(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = "";
    }
  }

  explicit AgentPropertiesValue_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : key(_alloc, _init),
    value(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = "";
    }
  }

  // field types and members
  using _key_type =
    aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator>;
  _key_type key;
  using _value_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _value_type value;

  // setters for named parameter idiom
  Type & set__key(
    const aimdk_msgs::msg::AgentPropertyIdType_<ContainerAllocator> & _arg)
  {
    this->key = _arg;
    return *this;
  }
  Type & set__value(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__AgentPropertiesValue
    std::shared_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__AgentPropertiesValue
    std::shared_ptr<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentPropertiesValue_ & other) const
  {
    if (this->key != other.key) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentPropertiesValue_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentPropertiesValue_

// alias to use template instance with default allocator
using AgentPropertiesValue =
  aimdk_msgs::msg::AgentPropertiesValue_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES_VALUE__STRUCT_HPP_
