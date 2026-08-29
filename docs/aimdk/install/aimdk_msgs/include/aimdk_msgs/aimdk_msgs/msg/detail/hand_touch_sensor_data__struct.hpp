// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__HandTouchSensorData __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__HandTouchSensorData __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandTouchSensorData_
{
  using Type = HandTouchSensorData_<ContainerAllocator>;

  explicit HandTouchSensorData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 36>::iterator, uint8_t>(this->palm_touch_data.begin(), this->palm_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 36>::iterator, uint8_t>(this->back_of_hand_touch_data.begin(), this->back_of_hand_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->thumb_touch_data.begin(), this->thumb_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->index_finger_touch_data.begin(), this->index_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->middle_finger_touch_data.begin(), this->middle_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->ring_finger_touch_data.begin(), this->ring_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->little_finger_touch_data.begin(), this->little_finger_touch_data.end(), 0);
    }
  }

  explicit HandTouchSensorData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : palm_touch_data(_alloc),
    back_of_hand_touch_data(_alloc),
    thumb_touch_data(_alloc),
    index_finger_touch_data(_alloc),
    middle_finger_touch_data(_alloc),
    ring_finger_touch_data(_alloc),
    little_finger_touch_data(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<uint8_t, 36>::iterator, uint8_t>(this->palm_touch_data.begin(), this->palm_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 36>::iterator, uint8_t>(this->back_of_hand_touch_data.begin(), this->back_of_hand_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->thumb_touch_data.begin(), this->thumb_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->index_finger_touch_data.begin(), this->index_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->middle_finger_touch_data.begin(), this->middle_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->ring_finger_touch_data.begin(), this->ring_finger_touch_data.end(), 0);
      std::fill<typename std::array<uint8_t, 16>::iterator, uint8_t>(this->little_finger_touch_data.begin(), this->little_finger_touch_data.end(), 0);
    }
  }

  // field types and members
  using _palm_touch_data_type =
    std::array<uint8_t, 36>;
  _palm_touch_data_type palm_touch_data;
  using _back_of_hand_touch_data_type =
    std::array<uint8_t, 36>;
  _back_of_hand_touch_data_type back_of_hand_touch_data;
  using _thumb_touch_data_type =
    std::array<uint8_t, 16>;
  _thumb_touch_data_type thumb_touch_data;
  using _index_finger_touch_data_type =
    std::array<uint8_t, 16>;
  _index_finger_touch_data_type index_finger_touch_data;
  using _middle_finger_touch_data_type =
    std::array<uint8_t, 16>;
  _middle_finger_touch_data_type middle_finger_touch_data;
  using _ring_finger_touch_data_type =
    std::array<uint8_t, 16>;
  _ring_finger_touch_data_type ring_finger_touch_data;
  using _little_finger_touch_data_type =
    std::array<uint8_t, 16>;
  _little_finger_touch_data_type little_finger_touch_data;

  // setters for named parameter idiom
  Type & set__palm_touch_data(
    const std::array<uint8_t, 36> & _arg)
  {
    this->palm_touch_data = _arg;
    return *this;
  }
  Type & set__back_of_hand_touch_data(
    const std::array<uint8_t, 36> & _arg)
  {
    this->back_of_hand_touch_data = _arg;
    return *this;
  }
  Type & set__thumb_touch_data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->thumb_touch_data = _arg;
    return *this;
  }
  Type & set__index_finger_touch_data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->index_finger_touch_data = _arg;
    return *this;
  }
  Type & set__middle_finger_touch_data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->middle_finger_touch_data = _arg;
    return *this;
  }
  Type & set__ring_finger_touch_data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->ring_finger_touch_data = _arg;
    return *this;
  }
  Type & set__little_finger_touch_data(
    const std::array<uint8_t, 16> & _arg)
  {
    this->little_finger_touch_data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__HandTouchSensorData
    std::shared_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__HandTouchSensorData
    std::shared_ptr<aimdk_msgs::msg::HandTouchSensorData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandTouchSensorData_ & other) const
  {
    if (this->palm_touch_data != other.palm_touch_data) {
      return false;
    }
    if (this->back_of_hand_touch_data != other.back_of_hand_touch_data) {
      return false;
    }
    if (this->thumb_touch_data != other.thumb_touch_data) {
      return false;
    }
    if (this->index_finger_touch_data != other.index_finger_touch_data) {
      return false;
    }
    if (this->middle_finger_touch_data != other.middle_finger_touch_data) {
      return false;
    }
    if (this->ring_finger_touch_data != other.ring_finger_touch_data) {
      return false;
    }
    if (this->little_finger_touch_data != other.little_finger_touch_data) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandTouchSensorData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandTouchSensorData_

// alias to use template instance with default allocator
using HandTouchSensorData =
  aimdk_msgs::msg::HandTouchSensorData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__STRUCT_HPP_
