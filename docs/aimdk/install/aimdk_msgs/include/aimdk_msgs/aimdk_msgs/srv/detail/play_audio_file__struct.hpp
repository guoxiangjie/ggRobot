// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/PlayAudioFile.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_HPP_

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
// Member 'file'
#include "aimdk_msgs/msg/detail/audio_file__struct.hpp"
// Member 'play_stamps'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayAudioFile_Request_
{
  using Type = PlayAudioFile_Request_<ContainerAllocator>;

  explicit PlayAudioFile_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_init),
    file(_init),
    play_stamps(_init)
  {
    (void)_init;
  }

  explicit PlayAudioFile_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : request(_alloc, _init),
    file(_alloc, _init),
    play_stamps(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _request_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _request_type request;
  using _file_type =
    aimdk_msgs::msg::AudioFile_<ContainerAllocator>;
  _file_type file;
  using _play_stamps_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _play_stamps_type play_stamps;

  // setters for named parameter idiom
  Type & set__request(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__file(
    const aimdk_msgs::msg::AudioFile_<ContainerAllocator> & _arg)
  {
    this->file = _arg;
    return *this;
  }
  Type & set__play_stamps(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->play_stamps = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Request
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Request
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayAudioFile_Request_ & other) const
  {
    if (this->request != other.request) {
      return false;
    }
    if (this->file != other.file) {
      return false;
    }
    if (this->play_stamps != other.play_stamps) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayAudioFile_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayAudioFile_Request_

// alias to use template instance with default allocator
using PlayAudioFile_Request =
  aimdk_msgs::srv::PlayAudioFile_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'reponse'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayAudioFile_Response_
{
  using Type = PlayAudioFile_Response_<ContainerAllocator>;

  explicit PlayAudioFile_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_init)
  {
    (void)_init;
  }

  explicit PlayAudioFile_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reponse(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _reponse_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _reponse_type reponse;

  // setters for named parameter idiom
  Type & set__reponse(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->reponse = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Response
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayAudioFile_Response
    std::shared_ptr<aimdk_msgs::srv::PlayAudioFile_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayAudioFile_Response_ & other) const
  {
    if (this->reponse != other.reponse) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayAudioFile_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayAudioFile_Response_

// alias to use template instance with default allocator
using PlayAudioFile_Response =
  aimdk_msgs::srv::PlayAudioFile_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct PlayAudioFile
{
  using Request = aimdk_msgs::srv::PlayAudioFile_Request;
  using Response = aimdk_msgs::srv::PlayAudioFile_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_AUDIO_FILE__STRUCT_HPP_
