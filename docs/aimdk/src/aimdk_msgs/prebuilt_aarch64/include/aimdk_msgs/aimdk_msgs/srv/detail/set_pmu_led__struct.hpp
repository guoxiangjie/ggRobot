// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/SetPmuLed.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_HPP_

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
# define DEPRECATED__aimdk_msgs__srv__SetPmuLed_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetPmuLed_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetPmuLed_Request_
{
  using Type = SetPmuLed_Request_<ContainerAllocator>;

  explicit SetPmuLed_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trace_id = "";
      this->led_strip_mode = 0;
      this->r = 0;
      this->g = 0;
      this->b = 0;
      this->priority = 0l;
      this->reset_priority = false;
    }
  }

  explicit SetPmuLed_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_alloc, _init),
    trace_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->trace_id = "";
      this->led_strip_mode = 0;
      this->r = 0;
      this->g = 0;
      this->b = 0;
      this->priority = 0l;
      this->reset_priority = false;
    }
  }

  // field types and members
  using _request_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _request_type request;
  using _trace_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _trace_id_type trace_id;
  using _led_strip_mode_type =
    uint8_t;
  _led_strip_mode_type led_strip_mode;
  using _r_type =
    uint8_t;
  _r_type r;
  using _g_type =
    uint8_t;
  _g_type g;
  using _b_type =
    uint8_t;
  _b_type b;
  using _priority_type =
    int32_t;
  _priority_type priority;
  using _reset_priority_type =
    bool;
  _reset_priority_type reset_priority;

  // setters for named parameter idiom
  Type & set__request(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__trace_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->trace_id = _arg;
    return *this;
  }
  Type & set__led_strip_mode(
    const uint8_t & _arg)
  {
    this->led_strip_mode = _arg;
    return *this;
  }
  Type & set__r(
    const uint8_t & _arg)
  {
    this->r = _arg;
    return *this;
  }
  Type & set__g(
    const uint8_t & _arg)
  {
    this->g = _arg;
    return *this;
  }
  Type & set__b(
    const uint8_t & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__priority(
    const int32_t & _arg)
  {
    this->priority = _arg;
    return *this;
  }
  Type & set__reset_priority(
    const bool & _arg)
  {
    this->reset_priority = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t LED_STRIP_MODE_CONSTANT =
    0u;
  static constexpr uint8_t LED_STRIP_MODE_BREATH =
    1u;
  static constexpr uint8_t LED_STRIP_MODE_FLASH =
    2u;
  static constexpr uint8_t LED_STRIP_MODE_FLOW =
    3u;
  static constexpr uint8_t LED_STRIP_MODE_MAX =
    4u;

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetPmuLed_Request
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetPmuLed_Request
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPmuLed_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    if (this->trace_id != other.trace_id) {
      return false;
    }
    if (this->led_strip_mode != other.led_strip_mode) {
      return false;
    }
    if (this->r != other.r) {
      return false;
    }
    if (this->g != other.g) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->priority != other.priority) {
      return false;
    }
    if (this->reset_priority != other.reset_priority) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPmuLed_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPmuLed_Request_

// alias to use template instance with default allocator
using SetPmuLed_Request =
  aimdk_msgs::srv::SetPmuLed_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetPmuLed_Request_<ContainerAllocator>::LED_STRIP_MODE_CONSTANT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetPmuLed_Request_<ContainerAllocator>::LED_STRIP_MODE_BREATH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetPmuLed_Request_<ContainerAllocator>::LED_STRIP_MODE_FLASH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetPmuLed_Request_<ContainerAllocator>::LED_STRIP_MODE_FLOW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetPmuLed_Request_<ContainerAllocator>::LED_STRIP_MODE_MAX;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__SetPmuLed_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetPmuLed_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetPmuLed_Response_
{
  using Type = SetPmuLed_Response_<ContainerAllocator>;

  explicit SetPmuLed_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status_code = 0;
    }
  }

  explicit SetPmuLed_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status_code = 0;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::ResponseHeader_<ContainerAllocator>;
  _header_type header;
  using _status_code_type =
    uint16_t;
  _status_code_type status_code;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::ResponseHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__status_code(
    const uint16_t & _arg)
  {
    this->status_code = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetPmuLed_Response
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetPmuLed_Response
    std::shared_ptr<aimdk_msgs::srv::SetPmuLed_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPmuLed_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->status_code != other.status_code) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPmuLed_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPmuLed_Response_

// alias to use template instance with default allocator
using SetPmuLed_Response =
  aimdk_msgs::srv::SetPmuLed_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct SetPmuLed
{
  using Request = aimdk_msgs::srv::SetPmuLed_Request;
  using Response = aimdk_msgs::srv::SetPmuLed_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_HPP_
