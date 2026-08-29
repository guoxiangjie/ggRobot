// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/SetMcPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/request_header__struct.hpp"
// Member 'area'
#include "aimdk_msgs/msg/detail/mc_control_area__struct.hpp"
// Member 'motion'
#include "aimdk_msgs/msg/detail/mc_preset_motion__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetMcPresetMotion_Request_
{
  using Type = SetMcPresetMotion_Request_<ContainerAllocator>;

  explicit SetMcPresetMotion_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    area(_init),
    motion(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->interrupt = false;
      this->ani_path = "";
      this->play_timestamp = 0ull;
    }
  }

  explicit SetMcPresetMotion_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    area(_alloc, _init),
    motion(_alloc, _init),
    ani_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->interrupt = false;
      this->ani_path = "";
      this->play_timestamp = 0ull;
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::RequestHeader_<ContainerAllocator>;
  _header_type header;
  using _area_type =
    aimdk_msgs::msg::McControlArea_<ContainerAllocator>;
  _area_type area;
  using _motion_type =
    aimdk_msgs::msg::McPresetMotion_<ContainerAllocator>;
  _motion_type motion;
  using _interrupt_type =
    bool;
  _interrupt_type interrupt;
  using _ani_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _ani_path_type ani_path;
  using _play_timestamp_type =
    uint64_t;
  _play_timestamp_type play_timestamp;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::RequestHeader_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__area(
    const aimdk_msgs::msg::McControlArea_<ContainerAllocator> & _arg)
  {
    this->area = _arg;
    return *this;
  }
  Type & set__motion(
    const aimdk_msgs::msg::McPresetMotion_<ContainerAllocator> & _arg)
  {
    this->motion = _arg;
    return *this;
  }
  Type & set__interrupt(
    const bool & _arg)
  {
    this->interrupt = _arg;
    return *this;
  }
  Type & set__ani_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->ani_path = _arg;
    return *this;
  }
  Type & set__play_timestamp(
    const uint64_t & _arg)
  {
    this->play_timestamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Request
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Request
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetMcPresetMotion_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->area != other.area) {
      return false;
    }
    if (this->motion != other.motion) {
      return false;
    }
    if (this->interrupt != other.interrupt) {
      return false;
    }
    if (this->ani_path != other.ani_path) {
      return false;
    }
    if (this->play_timestamp != other.play_timestamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetMcPresetMotion_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetMcPresetMotion_Request_

// alias to use template instance with default allocator
using SetMcPresetMotion_Request =
  aimdk_msgs::srv::SetMcPresetMotion_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'response'
#include "aimdk_msgs/msg/detail/common_task_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetMcPresetMotion_Response_
{
  using Type = SetMcPresetMotion_Response_<ContainerAllocator>;

  explicit SetMcPresetMotion_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_init)
  {
    (void)_init;
  }

  explicit SetMcPresetMotion_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : response(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _response_type =
    aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__response(
    const aimdk_msgs::msg::CommonTaskResponse_<ContainerAllocator> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Response
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__SetMcPresetMotion_Response
    std::shared_ptr<aimdk_msgs::srv::SetMcPresetMotion_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetMcPresetMotion_Response_ & other) const
  {
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetMcPresetMotion_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetMcPresetMotion_Response_

// alias to use template instance with default allocator
using SetMcPresetMotion_Response =
  aimdk_msgs::srv::SetMcPresetMotion_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct SetMcPresetMotion
{
  using Request = aimdk_msgs::srv::SetMcPresetMotion_Request;
  using Response = aimdk_msgs::srv::SetMcPresetMotion_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__STRUCT_HPP_
