// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/ProcessedAudioOutput.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_HPP_

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
// Member 'audio_vad_state'
#include "aimdk_msgs/msg/detail/audio_vad_state_type__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__ProcessedAudioOutput __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__ProcessedAudioOutput __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ProcessedAudioOutput_
{
  using Type = ProcessedAudioOutput_<ContainerAllocator>;

  explicit ProcessedAudioOutput_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    audio_vad_state(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stream_id = 0ul;
    }
  }

  explicit ProcessedAudioOutput_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    audio_vad_state(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->stream_id = 0ul;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::MessageHeader_<ContainerAllocator>;
  _header_type header;
  using _stream_id_type =
    uint32_t;
  _stream_id_type stream_id;
  using _audio_vad_state_type =
    aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator>;
  _audio_vad_state_type audio_vad_state;
  using _audio_data_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _audio_data_type audio_data;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::MessageHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__stream_id(
    const uint32_t & _arg)
  {
    this->stream_id = _arg;
    return *this;
  }
  Type & set__audio_vad_state(
    const aimdk_msgs::msg::AudioVadStateType_<ContainerAllocator> & _arg)
  {
    this->audio_vad_state = _arg;
    return *this;
  }
  Type & set__audio_data(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->audio_data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__ProcessedAudioOutput
    std::shared_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__ProcessedAudioOutput
    std::shared_ptr<aimdk_msgs::msg::ProcessedAudioOutput_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProcessedAudioOutput_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->stream_id != other.stream_id) {
      return false;
    }
    if (this->audio_vad_state != other.audio_vad_state) {
      return false;
    }
    if (this->audio_data != other.audio_data) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProcessedAudioOutput_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProcessedAudioOutput_

// alias to use template instance with default allocator
using ProcessedAudioOutput =
  aimdk_msgs::msg::ProcessedAudioOutput_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__PROCESSED_AUDIO_OUTPUT__STRUCT_HPP_
