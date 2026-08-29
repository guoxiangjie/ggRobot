// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/HandStateArray.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/message_header__struct.hpp"
// Member 'left_hand_type'
// Member 'right_hand_type'
#include "aimdk_msgs/msg/detail/hand_type__struct.hpp"
// Member 'left_hands'
// Member 'right_hands'
#include "aimdk_msgs/msg/detail/hand_state__struct.hpp"
// Member 'left_touch_sensors'
// Member 'right_touch_sensors'
#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__HandStateArray __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__HandStateArray __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandStateArray_
{
  using Type = HandStateArray_<ContainerAllocator>;

  explicit HandStateArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    left_hand_type(_init),
    left_touch_sensors(_init),
    right_hand_type(_init),
    right_touch_sensors(_init)
  {
    (void)_init;
  }

  explicit HandStateArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    left_hand_type(_alloc, _init),
    left_touch_sensors(_alloc, _init),
    right_hand_type(_alloc, _init),
    right_touch_sensors(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _left_hand_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _left_hand_type_type left_hand_type;
  using _left_hands_type =
    std::vector<aimdk_msgs::msg::HandState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandState_<ContainerAllocator>>>;
  _left_hands_type left_hands;
  using _left_touch_sensors_type =
    aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>;
  _left_touch_sensors_type left_touch_sensors;
  using _right_hand_type_type =
    aimdk_msgs::msg::HandType_<ContainerAllocator>;
  _right_hand_type_type right_hand_type;
  using _right_hands_type =
    std::vector<aimdk_msgs::msg::HandState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandState_<ContainerAllocator>>>;
  _right_hands_type right_hands;
  using _right_touch_sensors_type =
    aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>;
  _right_touch_sensors_type right_touch_sensors;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__left_hand_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->left_hand_type = _arg;
    return *this;
  }
  Type & set__left_hands(
    const std::vector<aimdk_msgs::msg::HandState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandState_<ContainerAllocator>>> & _arg)
  {
    this->left_hands = _arg;
    return *this;
  }
  Type & set__left_touch_sensors(
    const aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> & _arg)
  {
    this->left_touch_sensors = _arg;
    return *this;
  }
  Type & set__right_hand_type(
    const aimdk_msgs::msg::HandType_<ContainerAllocator> & _arg)
  {
    this->right_hand_type = _arg;
    return *this;
  }
  Type & set__right_hands(
    const std::vector<aimdk_msgs::msg::HandState_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HandState_<ContainerAllocator>>> & _arg)
  {
    this->right_hands = _arg;
    return *this;
  }
  Type & set__right_touch_sensors(
    const aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> & _arg)
  {
    this->right_touch_sensors = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::HandStateArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::HandStateArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandStateArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandStateArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__HandStateArray
    std::shared_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__HandStateArray
    std::shared_ptr<aimdk_msgs::msg::HandStateArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandStateArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->left_hand_type != other.left_hand_type) {
      return false;
    }
    if (this->left_hands != other.left_hands) {
      return false;
    }
    if (this->left_touch_sensors != other.left_touch_sensors) {
      return false;
    }
    if (this->right_hand_type != other.right_hand_type) {
      return false;
    }
    if (this->right_hands != other.right_hands) {
      return false;
    }
    if (this->right_touch_sensors != other.right_touch_sensors) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandStateArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandStateArray_

// alias to use template instance with default allocator
using HandStateArray =
  aimdk_msgs::msg::HandStateArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_STATE_ARRAY__STRUCT_HPP_
