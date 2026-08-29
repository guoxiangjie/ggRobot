// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/FaceEmojiStatus.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__FaceEmojiStatus __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__FaceEmojiStatus __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FaceEmojiStatus_
{
  using Type = FaceEmojiStatus_<ContainerAllocator>;

  explicit FaceEmojiStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->e_path = "";
      this->e_id = 0;
      this->mode = 0;
      this->priority = 0l;
      this->status = 0;
      this->time_to_end_ms = 0.0;
    }
  }

  explicit FaceEmojiStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    e_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->e_path = "";
      this->e_id = 0;
      this->mode = 0;
      this->priority = 0l;
      this->status = 0;
      this->time_to_end_ms = 0.0;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _e_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _e_path_type e_path;
  using _e_path_list_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _e_path_list_type e_path_list;
  using _e_id_type =
    uint8_t;
  _e_id_type e_id;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _priority_type =
    int32_t;
  _priority_type priority;
  using _status_type =
    uint8_t;
  _status_type status;
  using _time_to_end_ms_type =
    double;
  _time_to_end_ms_type time_to_end_ms;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__e_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->e_path = _arg;
    return *this;
  }
  Type & set__e_path_list(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->e_path_list = _arg;
    return *this;
  }
  Type & set__e_id(
    const uint8_t & _arg)
  {
    this->e_id = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__priority(
    const int32_t & _arg)
  {
    this->priority = _arg;
    return *this;
  }
  Type & set__status(
    const uint8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__time_to_end_ms(
    const double & _arg)
  {
    this->time_to_end_ms = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATUS_IDLE =
    0u;
  static constexpr uint8_t STATUS_START =
    1u;
  static constexpr uint8_t STATUS_RUNNING =
    2u;
  static constexpr uint8_t STATUS_FINISHED =
    3u;
  static constexpr uint8_t STATUS_STOPPED =
    4u;

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__FaceEmojiStatus
    std::shared_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__FaceEmojiStatus
    std::shared_ptr<aimdk_msgs::msg::FaceEmojiStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FaceEmojiStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->e_path != other.e_path) {
      return false;
    }
    if (this->e_path_list != other.e_path_list) {
      return false;
    }
    if (this->e_id != other.e_id) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->priority != other.priority) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    if (this->time_to_end_ms != other.time_to_end_ms) {
      return false;
    }
    return true;
  }
  bool operator!=(const FaceEmojiStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FaceEmojiStatus_

// alias to use template instance with default allocator
using FaceEmojiStatus =
  aimdk_msgs::msg::FaceEmojiStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FaceEmojiStatus_<ContainerAllocator>::STATUS_IDLE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FaceEmojiStatus_<ContainerAllocator>::STATUS_START;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FaceEmojiStatus_<ContainerAllocator>::STATUS_RUNNING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FaceEmojiStatus_<ContainerAllocator>::STATUS_FINISHED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FaceEmojiStatus_<ContainerAllocator>::STATUS_STOPPED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__FACE_EMOJI_STATUS__STRUCT_HPP_
