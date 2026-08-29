// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/SetAgentPropertiesRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__struct.hpp"
// Member 'contents'
#include "aimdk_msgs/msg/detail/agent_properties__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAgentPropertiesRequest_Request_
{
  using Type = SetAgentPropertiesRequest_Request_<ContainerAllocator>;

  explicit SetAgentPropertiesRequest_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    contents(_init)
  {
    (void)_init;
  }

  explicit SetAgentPropertiesRequest_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    contents(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _header_type header;
  using _contents_type =
    aimdk_msgs::msg::AgentProperties_<ContainerAllocator>;
  _contents_type contents;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__contents(
    const aimdk_msgs::msg::AgentProperties_<ContainerAllocator> & _arg)
  {
    this->contents = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Request
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Request
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAgentPropertiesRequest_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->contents != other.contents) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAgentPropertiesRequest_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAgentPropertiesRequest_Request_

// alias to use template instance with default allocator
using SetAgentPropertiesRequest_Request =
  aimdk_msgs::srv::SetAgentPropertiesRequest_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetAgentPropertiesRequest_Response_
{
  using Type = SetAgentPropertiesRequest_Response_<ContainerAllocator>;

  explicit SetAgentPropertiesRequest_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit SetAgentPropertiesRequest_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _header_type header;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Response
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetAgentPropertiesRequest_Response
    std::shared_ptr<aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetAgentPropertiesRequest_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetAgentPropertiesRequest_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetAgentPropertiesRequest_Response_

// alias to use template instance with default allocator
using SetAgentPropertiesRequest_Response =
  aimdk_msgs::srv::SetAgentPropertiesRequest_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct SetAgentPropertiesRequest
{
  using Request = aimdk_msgs::srv::SetAgentPropertiesRequest_Request;
  using Response = aimdk_msgs::srv::SetAgentPropertiesRequest_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__STRUCT_HPP_
