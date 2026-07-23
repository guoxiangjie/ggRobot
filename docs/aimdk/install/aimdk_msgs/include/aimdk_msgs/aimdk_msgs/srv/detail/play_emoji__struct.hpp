// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/PlayEmoji.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_HPP_

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
# define DEPRECATED__aimdk_msgs__srv__PlayEmoji_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayEmoji_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayEmoji_Request_
{
  using Type = PlayEmoji_Request_<ContainerAllocator>;

  explicit PlayEmoji_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->emotion_id = 0;
      this->mode = 0;
      this->priority = 0l;
    }
  }

  explicit PlayEmoji_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->emotion_id = 0;
      this->mode = 0;
      this->priority = 0l;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _header_type header;
  using _emotion_id_type =
    uint8_t;
  _emotion_id_type emotion_id;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _priority_type =
    int32_t;
  _priority_type priority;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__emotion_id(
    const uint8_t & _arg)
  {
    this->emotion_id = _arg;
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

  // constant declarations
  static constexpr uint8_t EMOTION_UNKNOWN =
    0u;
  static constexpr uint8_t EMOTION_IDLE_BLINK =
    1u;
  static constexpr uint8_t EMOTION_IDLE_CALM_1 =
    10u;
  static constexpr uint8_t EMOTION_IDLE_CALM_2 =
    11u;
  static constexpr uint8_t EMOTION_IDLE_GAME =
    20u;
  static constexpr uint8_t EMOTION_IDLE_CUTE_1 =
    30u;
  static constexpr uint8_t EMOTION_IDLE_CUTE_2 =
    31u;
  static constexpr uint8_t EMOTION_IDLE_CUTE_3 =
    32u;
  static constexpr uint8_t EMOTION_IDLE_CUTE_4 =
    33u;
  static constexpr uint8_t EMOTION_EYE_CLOSE =
    40u;
  static constexpr uint8_t EMOTION_EYE_OPEN =
    50u;
  static constexpr uint8_t EMOTION_EYE_BORING_1 =
    60u;
  static constexpr uint8_t EMOTION_EYE_ABNORMAL =
    70u;
  static constexpr uint8_t EMOTION_EYE_SLEEPY =
    80u;
  static constexpr uint8_t EMOTION_EYE_HAPPY =
    90u;
  static constexpr uint8_t EMOTION_EYE_EXTREMEHAPPY_1 =
    100u;
  static constexpr uint8_t EMOTION_EYE_EXTREMEHAPPY_2 =
    101u;
  static constexpr uint8_t EMOTION_EYE_SAD =
    110u;
  static constexpr uint8_t EMOTION_EYE_SYMPATHY =
    120u;
  static constexpr uint8_t EMOTION_EYE_CONFUSE =
    130u;
  static constexpr uint8_t EMOTION_EYE_SHOCK =
    140u;
  static constexpr uint8_t EMOTION_EYE_ACTCUTE =
    150u;
  static constexpr uint8_t EMOTION_EYE_SERIOUS =
    160u;
  static constexpr uint8_t EMOTION_EYE_THINKING =
    170u;
  static constexpr uint8_t EMOTION_EYE_ANGRY =
    180u;
  static constexpr uint8_t EMOTION_EYE_EXTREMEANGRY =
    190u;
  static constexpr uint8_t EMOTION_EYE_ADORE =
    200u;
  static constexpr uint8_t EMOTION_EYE_EXTREMEADORE =
    210u;
  static constexpr uint8_t EMOTION_EYE_CHARGE =
    220u;
  static constexpr uint8_t EMOTION_MODE_ONCE =
    1u;
  static constexpr uint8_t EMOTION_MODE_LOOP =
    2u;

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayEmoji_Request
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayEmoji_Request
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayEmoji_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->emotion_id != other.emotion_id) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->priority != other.priority) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayEmoji_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayEmoji_Request_

// alias to use template instance with default allocator
using PlayEmoji_Request =
  aimdk_msgs::srv::PlayEmoji_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_BLINK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CALM_1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CALM_2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_GAME;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CUTE_1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CUTE_2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CUTE_3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_IDLE_CUTE_4;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_CLOSE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_OPEN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_BORING_1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_ABNORMAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_SLEEPY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_HAPPY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_EXTREMEHAPPY_1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_EXTREMEHAPPY_2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_SAD;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_SYMPATHY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_CONFUSE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_SHOCK;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_ACTCUTE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_SERIOUS;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_THINKING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_ANGRY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_EXTREMEANGRY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_ADORE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_EXTREMEADORE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_EYE_CHARGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_MODE_ONCE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t PlayEmoji_Request_<ContainerAllocator>::EMOTION_MODE_LOOP;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__PlayEmoji_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayEmoji_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayEmoji_Response_
{
  using Type = PlayEmoji_Response_<ContainerAllocator>;

  explicit PlayEmoji_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit PlayEmoji_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _header_type header;
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayEmoji_Response
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayEmoji_Response
    std::shared_ptr<aimdk_msgs::srv::PlayEmoji_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayEmoji_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayEmoji_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayEmoji_Response_

// alias to use template instance with default allocator
using PlayEmoji_Response =
  aimdk_msgs::srv::PlayEmoji_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct PlayEmoji
{
  using Request = aimdk_msgs::srv::PlayEmoji_Request;
  using Response = aimdk_msgs::srv::PlayEmoji_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_HPP_
