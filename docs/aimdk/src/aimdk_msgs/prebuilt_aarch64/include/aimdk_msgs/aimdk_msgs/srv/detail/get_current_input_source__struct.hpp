// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetCurrentInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_HPP_

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
# define DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCurrentInputSource_Request_
{
  using Type = GetCurrentInputSource_Request_<ContainerAllocator>;

  explicit GetCurrentInputSource_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init)
  {
    (void)_init;
  }

  explicit GetCurrentInputSource_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Request
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Request
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCurrentInputSource_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCurrentInputSource_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCurrentInputSource_Request_

// alias to use template instance with default allocator
using GetCurrentInputSource_Request =
  aimdk_msgs::srv::GetCurrentInputSource_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__struct.hpp"
// Member 'input_source'
#include "aimdk_msgs/msg/detail/mc_input_source__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCurrentInputSource_Response_
{
  using Type = GetCurrentInputSource_Response_<ContainerAllocator>;

  explicit GetCurrentInputSource_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_init),
    input_source(_init)
  {
    (void)_init;
  }

  explicit GetCurrentInputSource_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_alloc, _init),
    input_source(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _response_type =
    aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>;
  _response_type response;
  using _input_source_type =
    aimdk_msgs::msg::McInputSource_<ContainerAllocator>;
  _input_source_type input_source;

  // setters for named parameter idiom
  Type & set__response(
    const aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> & _arg)
  {
    this->response = _arg;
    return *this;
  }
  Type & set__input_source(
    const aimdk_msgs::msg::McInputSource_<ContainerAllocator> & _arg)
  {
    this->input_source = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Response
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetCurrentInputSource_Response
    std::shared_ptr<aimdk_msgs::srv::GetCurrentInputSource_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCurrentInputSource_Response_ & other) const
  {
    if (this->response != other.response) {
      return false;
    }
    if (this->input_source != other.input_source) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCurrentInputSource_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCurrentInputSource_Response_

// alias to use template instance with default allocator
using GetCurrentInputSource_Response =
  aimdk_msgs::srv::GetCurrentInputSource_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetCurrentInputSource
{
  using Request = aimdk_msgs::srv::GetCurrentInputSource_Request;
  using Response = aimdk_msgs::srv::GetCurrentInputSource_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__STRUCT_HPP_
