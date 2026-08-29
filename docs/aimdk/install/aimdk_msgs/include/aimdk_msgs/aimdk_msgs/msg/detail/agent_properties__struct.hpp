// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/AgentProperties.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'properties'
#include "aimdk_msgs/msg/detail/agent_properties_value__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__AgentProperties __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__AgentProperties __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgentProperties_
{
  using Type = AgentProperties_<ContainerAllocator>;

  explicit AgentProperties_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit AgentProperties_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _properties_type =
    std::vector<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>>;
  _properties_type properties;

  // setters for named parameter idiom
  Type & set__properties(
    const std::vector<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::AgentPropertiesValue_<ContainerAllocator>>> & _arg)
  {
    this->properties = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::AgentProperties_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::AgentProperties_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentProperties_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::AgentProperties_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__AgentProperties
    std::shared_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__AgentProperties
    std::shared_ptr<aimdk_msgs::msg::AgentProperties_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgentProperties_ & other) const
  {
    if (this->properties != other.properties) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgentProperties_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgentProperties_

// alias to use template instance with default allocator
using AgentProperties =
  aimdk_msgs::msg::AgentProperties_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTIES__STRUCT_HPP_
