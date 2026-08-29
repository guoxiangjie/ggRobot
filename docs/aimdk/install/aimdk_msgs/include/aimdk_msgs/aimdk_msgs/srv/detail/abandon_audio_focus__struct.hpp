// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/AbandonAudioFocus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__ABANDON_AUDIO_FOCUS__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__ABANDON_AUDIO_FOCUS__STRUCT_HPP_

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
// Member 'focus_requester'
#include "aimdk_msgs/msg/detail/focus_requester__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct AbandonAudioFocus_Request_
{
  using Type = AbandonAudioFocus_Request_<ContainerAllocator>;

  explicit AbandonAudioFocus_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init),
    focus_requester(_init)
  {
    (void)_init;
  }

  explicit AbandonAudioFocus_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_alloc, _init),
    focus_requester(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _request_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _request_type request;
  using _focus_requester_type =
    aimdk_msgs::msg::FocusRequester_<ContainerAllocator>;
  _focus_requester_type focus_requester;

  // setters for named parameter idiom
  Type & set__request(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__focus_requester(
    const aimdk_msgs::msg::FocusRequester_<ContainerAllocator> & _arg)
  {
    this->focus_requester = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Request
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Request
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AbandonAudioFocus_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    if (this->focus_requester != other.focus_requester) {
      return false;
    }
    return true;
  }
  bool operator!=(const AbandonAudioFocus_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AbandonAudioFocus_Request_

// alias to use template instance with default allocator
using AbandonAudioFocus_Request =
  aimdk_msgs::srv::AbandonAudioFocus_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
// Member 'focus_response'
#include "aimdk_msgs/msg/detail/focus_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct AbandonAudioFocus_Response_
{
  using Type = AbandonAudioFocus_Response_<ContainerAllocator>;

  explicit AbandonAudioFocus_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_init),
    focus_response(_init)
  {
    (void)_init;
  }

  explicit AbandonAudioFocus_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_alloc, _init),
    focus_response(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _reponse_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _reponse_type reponse;
  using _focus_response_type =
    aimdk_msgs::msg::FocusResponse_<ContainerAllocator>;
  _focus_response_type focus_response;

  // setters for named parameter idiom
  Type & set__reponse(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->reponse = _arg;
    return *this;
  }
  Type & set__focus_response(
    const aimdk_msgs::msg::FocusResponse_<ContainerAllocator> & _arg)
  {
    this->focus_response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Response
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__AbandonAudioFocus_Response
    std::shared_ptr<aimdk_msgs::srv::AbandonAudioFocus_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AbandonAudioFocus_Response_ & other) const
  {
    if (this->reponse != other.reponse) {
      return false;
    }
    if (this->focus_response != other.focus_response) {
      return false;
    }
    return true;
  }
  bool operator!=(const AbandonAudioFocus_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AbandonAudioFocus_Response_

// alias to use template instance with default allocator
using AbandonAudioFocus_Response =
  aimdk_msgs::srv::AbandonAudioFocus_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct AbandonAudioFocus
{
  using Request = aimdk_msgs::srv::AbandonAudioFocus_Request;
  using Response = aimdk_msgs::srv::AbandonAudioFocus_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__ABANDON_AUDIO_FOCUS__STRUCT_HPP_
