// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/PlayTtsRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'priority_level'
#include "aimdk_msgs/msg/detail/tts_priority_level__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__PlayTtsRequest __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__PlayTtsRequest __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PlayTtsRequest_
{
  using Type = PlayTtsRequest_<ContainerAllocator>;

  explicit PlayTtsRequest_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : priority_level(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->text = "";
      this->priority_weight = 0ul;
      this->domain = "";
      this->trace_id = "";
      this->is_interrupted = false;
    }
  }

  explicit PlayTtsRequest_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : text(_alloc),
    priority_level(_alloc, _init),
    domain(_alloc),
    trace_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->text = "";
      this->priority_weight = 0ul;
      this->domain = "";
      this->trace_id = "";
      this->is_interrupted = false;
    }
  }

  // field types and members
  using _text_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _text_type text;
  using _priority_level_type =
    aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator>;
  _priority_level_type priority_level;
  using _priority_weight_type =
    uint32_t;
  _priority_weight_type priority_weight;
  using _domain_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _domain_type domain;
  using _trace_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _trace_id_type trace_id;
  using _is_interrupted_type =
    bool;
  _is_interrupted_type is_interrupted;

  // setters for named parameter idiom
  Type & set__text(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->text = _arg;
    return *this;
  }
  Type & set__priority_level(
    const aimdk_msgs::msg::TtsPriorityLevel_<ContainerAllocator> & _arg)
  {
    this->priority_level = _arg;
    return *this;
  }
  Type & set__priority_weight(
    const uint32_t & _arg)
  {
    this->priority_weight = _arg;
    return *this;
  }
  Type & set__domain(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->domain = _arg;
    return *this;
  }
  Type & set__trace_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->trace_id = _arg;
    return *this;
  }
  Type & set__is_interrupted(
    const bool & _arg)
  {
    this->is_interrupted = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__PlayTtsRequest
    std::shared_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__PlayTtsRequest
    std::shared_ptr<aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayTtsRequest_ & other) const
  {
    if (this->text != other.text) {
      return false;
    }
    if (this->priority_level != other.priority_level) {
      return false;
    }
    if (this->priority_weight != other.priority_weight) {
      return false;
    }
    if (this->domain != other.domain) {
      return false;
    }
    if (this->trace_id != other.trace_id) {
      return false;
    }
    if (this->is_interrupted != other.is_interrupted) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayTtsRequest_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayTtsRequest_

// alias to use template instance with default allocator
using PlayTtsRequest =
  aimdk_msgs::msg::PlayTtsRequest_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PLAY_TTS_REQUEST__STRUCT_HPP_
