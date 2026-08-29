// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetHandType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_HPP_

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
# define DEPRECATED__aimdk_msgs__srv__GetHandType_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetHandType_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetHandType_Request_
{
  using Type = GetHandType_Request_<ContainerAllocator>;

  explicit GetHandType_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init)
  {
    (void)_init;
  }

  explicit GetHandType_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetHandType_Request
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetHandType_Request
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetHandType_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetHandType_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetHandType_Request_

// alias to use template instance with default allocator
using GetHandType_Request =
  aimdk_msgs::srv::GetHandType_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
// Member 'left_hands_type'
// Member 'right_hands_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetHandType_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetHandType_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetHandType_Response_
{
  using Type = GetHandType_Response_<ContainerAllocator>;

  explicit GetHandType_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_init),
    left_hands_type(_init),
    right_hands_type(_init)
  {
    (void)_init;
  }

  explicit GetHandType_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_alloc, _init),
    left_hands_type(_alloc, _init),
    right_hands_type(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _reponse_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _reponse_type reponse;
  using _left_hands_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _left_hands_type_type left_hands_type;
  using _right_hands_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _right_hands_type_type right_hands_type;

  // setters for named parameter idiom
  Type & set__reponse(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->reponse = _arg;
    return *this;
  }
  Type & set__left_hands_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->left_hands_type = _arg;
    return *this;
  }
  Type & set__right_hands_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->right_hands_type = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetHandType_Response
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetHandType_Response
    std::shared_ptr<aimdk_msgs::srv::GetHandType_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetHandType_Response_ & other) const
  {
    if (this->reponse != other.reponse) {
      return false;
    }
    if (this->left_hands_type != other.left_hands_type) {
      return false;
    }
    if (this->right_hands_type != other.right_hands_type) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetHandType_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetHandType_Response_

// alias to use template instance with default allocator
using GetHandType_Response =
  aimdk_msgs::srv::GetHandType_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetHandType
{
  using Request = aimdk_msgs::srv::GetHandType_Request;
  using Response = aimdk_msgs::srv::GetHandType_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__STRUCT_HPP_
