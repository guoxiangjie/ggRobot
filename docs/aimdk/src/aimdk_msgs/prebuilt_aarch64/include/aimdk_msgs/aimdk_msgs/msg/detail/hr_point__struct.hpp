// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/HRPoint.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'qr_list'
#include "aimdk_msgs/msg/detail/qr_code__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__HRPoint __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__HRPoint __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HRPoint_
{
  using Type = HRPoint_<ContainerAllocator>;

  explicit HRPoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point_id = 0l;
      this->use_head = false;
    }
  }

  explicit HRPoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->point_id = 0l;
      this->use_head = false;
    }
  }

  // field types and members
  using _point_id_type =
    int32_t;
  _point_id_type point_id;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _qr_list_type =
    std::vector<aimdk_msgs::msg::QRCode_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::QRCode_<ContainerAllocator>>>;
  _qr_list_type qr_list;
  using _use_head_type =
    bool;
  _use_head_type use_head;

  // setters for named parameter idiom
  Type & set__point_id(
    const int32_t & _arg)
  {
    this->point_id = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__qr_list(
    const std::vector<aimdk_msgs::msg::QRCode_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::QRCode_<ContainerAllocator>>> & _arg)
  {
    this->qr_list = _arg;
    return *this;
  }
  Type & set__use_head(
    const bool & _arg)
  {
    this->use_head = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::HRPoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::HRPoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HRPoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HRPoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__HRPoint
    std::shared_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__HRPoint
    std::shared_ptr<aimdk_msgs::msg::HRPoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HRPoint_ & other) const
  {
    if (this->point_id != other.point_id) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->qr_list != other.qr_list) {
      return false;
    }
    if (this->use_head != other.use_head) {
      return false;
    }
    return true;
  }
  bool operator!=(const HRPoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HRPoint_

// alias to use template instance with default allocator
using HRPoint =
  aimdk_msgs::msg::HRPoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HR_POINT__STRUCT_HPP_
