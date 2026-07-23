// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetSystemState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetSystemState_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetSystemState_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSystemState_Request_
{
  using Type = GetSystemState_Request_<ContainerAllocator>;

  explicit GetSystemState_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit GetSystemState_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _header_type header;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetSystemState_Request
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetSystemState_Request
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSystemState_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSystemState_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSystemState_Request_

// alias to use template instance with default allocator
using GetSystemState_Request =
  aimdk_msgs::srv::GetSystemState_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
// Member 'curr_status'
#include "aimdk_msgs/msg/detail/system_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetSystemState_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetSystemState_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSystemState_Response_
{
  using Type = GetSystemState_Response_<ContainerAllocator>;

  explicit GetSystemState_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    curr_status(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cur_state = "";
    }
  }

  explicit GetSystemState_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    cur_state(_alloc),
    curr_status(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cur_state = "";
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _header_type header;
  using _cur_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _cur_state_type cur_state;
  using _curr_status_type =
    aimdk_msgs::msg::SystemStatus_<ContainerAllocator>;
  _curr_status_type curr_status;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__cur_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->cur_state = _arg;
    return *this;
  }
  Type & set__curr_status(
    const aimdk_msgs::msg::SystemStatus_<ContainerAllocator> & _arg)
  {
    this->curr_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetSystemState_Response
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetSystemState_Response
    std::shared_ptr<aimdk_msgs::srv::GetSystemState_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSystemState_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->cur_state != other.cur_state) {
      return false;
    }
    if (this->curr_status != other.curr_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSystemState_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSystemState_Response_

// alias to use template instance with default allocator
using GetSystemState_Response =
  aimdk_msgs::srv::GetSystemState_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetSystemState
{
  using Request = aimdk_msgs::srv::GetSystemState_Request;
  using Response = aimdk_msgs::srv::GetSystemState_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_SYSTEM_STATE__STRUCT_HPP_
