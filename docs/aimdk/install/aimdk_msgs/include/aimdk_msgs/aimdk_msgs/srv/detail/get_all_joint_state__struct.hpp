// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetAllJointState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_HPP_

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
# define DEPRECATED__aimdk_msgs__srv__GetAllJointState_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetAllJointState_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAllJointState_Request_
{
  using Type = GetAllJointState_Request_<ContainerAllocator>;

  explicit GetAllJointState_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init)
  {
    (void)_init;
  }

  explicit GetAllJointState_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetAllJointState_Request
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetAllJointState_Request
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAllJointState_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAllJointState_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAllJointState_Request_

// alias to use template instance with default allocator
using GetAllJointState_Request =
  aimdk_msgs::srv::GetAllJointState_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
// Member 'head_joints'
// Member 'arm_joints'
// Member 'waist_joints'
// Member 'leg_joints'
#include "aimdk_msgs/msg/detail/joint_state__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetAllJointState_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetAllJointState_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetAllJointState_Response_
{
  using Type = GetAllJointState_Response_<ContainerAllocator>;

  explicit GetAllJointState_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_init)
  {
    (void)_init;
  }

  explicit GetAllJointState_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _reponse_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _reponse_type reponse;
  using _head_joints_type =
    std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>>;
  _head_joints_type head_joints;
  using _arm_joints_type =
    std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>>;
  _arm_joints_type arm_joints;
  using _waist_joints_type =
    std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>>;
  _waist_joints_type waist_joints;
  using _leg_joints_type =
    std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>>;
  _leg_joints_type leg_joints;

  // setters for named parameter idiom
  Type & set__reponse(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->reponse = _arg;
    return *this;
  }
  Type & set__head_joints(
    const std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>> & _arg)
  {
    this->head_joints = _arg;
    return *this;
  }
  Type & set__arm_joints(
    const std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>> & _arg)
  {
    this->arm_joints = _arg;
    return *this;
  }
  Type & set__waist_joints(
    const std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>> & _arg)
  {
    this->waist_joints = _arg;
    return *this;
  }
  Type & set__leg_joints(
    const std::vector<aimdk_msgs::msg::JointState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::JointState_<ContainerAllocator>>> & _arg)
  {
    this->leg_joints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetAllJointState_Response
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetAllJointState_Response
    std::shared_ptr<aimdk_msgs::srv::GetAllJointState_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetAllJointState_Response_ & other) const
  {
    if (this->reponse != other.reponse) {
      return false;
    }
    if (this->head_joints != other.head_joints) {
      return false;
    }
    if (this->arm_joints != other.arm_joints) {
      return false;
    }
    if (this->waist_joints != other.waist_joints) {
      return false;
    }
    if (this->leg_joints != other.leg_joints) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetAllJointState_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetAllJointState_Response_

// alias to use template instance with default allocator
using GetAllJointState_Response =
  aimdk_msgs::srv::GetAllJointState_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetAllJointState
{
  using Request = aimdk_msgs::srv::GetAllJointState_Request;
  using Response = aimdk_msgs::srv::GetAllJointState_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_ALL_JOINT_STATE__STRUCT_HPP_
