// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/PlayTts.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__STRUCT_HPP_

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
// Member 'tts_req'
#include "aimdk_msgs/msg/detail/play_tts_request__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__PlayTts_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayTts_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayTts_Request_
{
  using Type = PlayTts_Request_<ContainerAllocator>;

  explicit PlayTts_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    tts_req(_init)
  {
    (void)_init;
  }

  explicit PlayTts_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    tts_req(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _header_type header;
  using _tts_req_type =
    aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator>;
  _tts_req_type tts_req;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__tts_req(
    const aimdk_msgs::msg::PlayTtsRequest_<ContainerAllocator> & _arg)
  {
    this->tts_req = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayTts_Request
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayTts_Request
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayTts_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->tts_req != other.tts_req) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayTts_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayTts_Request_

// alias to use template instance with default allocator
using PlayTts_Request =
  aimdk_msgs::srv::PlayTts_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"
// Member 'tts_resp'
#include "aimdk_msgs/msg/detail/play_tts_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__PlayTts_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__PlayTts_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlayTts_Response_
{
  using Type = PlayTts_Response_<ContainerAllocator>;

  explicit PlayTts_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    tts_resp(_init)
  {
    (void)_init;
  }

  explicit PlayTts_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    tts_resp(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _header_type header;
  using _tts_resp_type =
    aimdk_msgs::msg::PlayTtsResponse_<ContainerAllocator>;
  _tts_resp_type tts_resp;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__tts_resp(
    const aimdk_msgs::msg::PlayTtsResponse_<ContainerAllocator> & _arg)
  {
    this->tts_resp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__PlayTts_Response
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__PlayTts_Response
    std::shared_ptr<aimdk_msgs::srv::PlayTts_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlayTts_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->tts_resp != other.tts_resp) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlayTts_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlayTts_Response_

// alias to use template instance with default allocator
using PlayTts_Response =
  aimdk_msgs::srv::PlayTts_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct PlayTts
{
  using Request = aimdk_msgs::srv::PlayTts_Request;
  using Response = aimdk_msgs::srv::PlayTts_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_TTS__STRUCT_HPP_
