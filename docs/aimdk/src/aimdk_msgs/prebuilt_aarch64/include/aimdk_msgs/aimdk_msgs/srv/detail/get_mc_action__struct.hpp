// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetMcAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetMcAction_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetMcAction_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetMcAction_Request_
{
  using Type = GetMcAction_Request_<ContainerAllocator>;

  explicit GetMcAction_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init)
  {
    (void)_init;
  }

  explicit GetMcAction_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _request_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _request_type request;

  // setters for named parameter idiom
  Type & set__request(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->request = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetMcAction_Request
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetMcAction_Request
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetMcAction_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetMcAction_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetMcAction_Request_

// alias to use template instance with default allocator
using GetMcAction_Request =
  aimdk_msgs::srv::GetMcAction_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__struct.hpp"
// Member 'info'
#include "aimdk_msgs/msg/detail/mc_action_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetMcAction_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetMcAction_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetMcAction_Response_
{
  using Type = GetMcAction_Response_<ContainerAllocator>;

  explicit GetMcAction_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    info(_init)
  {
    (void)_init;
  }

  explicit GetMcAction_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>;
  _header_type header;
  using _info_type =
    aimdk_msgs::msg::McActionInfo_<ContainerAllocator>;
  _info_type info;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__info(
    const aimdk_msgs::msg::McActionInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetMcAction_Response
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetMcAction_Response
    std::shared_ptr<aimdk_msgs::srv::GetMcAction_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetMcAction_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->info != other.info) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetMcAction_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetMcAction_Response_

// alias to use template instance with default allocator
using GetMcAction_Response =
  aimdk_msgs::srv::GetMcAction_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetMcAction
{
  using Request = aimdk_msgs::srv::GetMcAction_Request;
  using Response = aimdk_msgs::srv::GetMcAction_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_MC_ACTION__STRUCT_HPP_
