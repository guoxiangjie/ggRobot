// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/ExecuteActionResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_HPP_

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
// Member 'slaves'
#include "aimdk_msgs/msg/detail/slave_device__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ExecuteActionResource_Request_
{
  using Type = ExecuteActionResource_Request_<ContainerAllocator>;

  explicit ExecuteActionResource_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resource_key = "";
      this->resource_version = "";
      this->meta = "";
    }
  }

  explicit ExecuteActionResource_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    resource_key(_alloc),
    resource_version(_alloc),
    meta(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->resource_key = "";
      this->resource_version = "";
      this->meta = "";
    }
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonRequest_<ContainerAllocator>;
  _header_type header;
  using _resource_key_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _resource_key_type resource_key;
  using _resource_version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _resource_version_type resource_version;
  using _slaves_type =
    std::vector<aimdk_msgs::msg::SlaveDevice_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::SlaveDevice_<ContainerAllocator>>>;
  _slaves_type slaves;
  using _meta_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _meta_type meta;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonRequest_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__resource_key(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->resource_key = _arg;
    return *this;
  }
  Type & set__resource_version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->resource_version = _arg;
    return *this;
  }
  Type & set__slaves(
    const std::vector<aimdk_msgs::msg::SlaveDevice_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::SlaveDevice_<ContainerAllocator>>> & _arg)
  {
    this->slaves = _arg;
    return *this;
  }
  Type & set__meta(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->meta = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Request
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Request
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteActionResource_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->resource_key != other.resource_key) {
      return false;
    }
    if (this->resource_version != other.resource_version) {
      return false;
    }
    if (this->slaves != other.slaves) {
      return false;
    }
    if (this->meta != other.meta) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteActionResource_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteActionResource_Request_

// alias to use template instance with default allocator
using ExecuteActionResource_Request =
  aimdk_msgs::srv::ExecuteActionResource_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ExecuteActionResource_Response_
{
  using Type = ExecuteActionResource_Response_<ContainerAllocator>;

  explicit ExecuteActionResource_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit ExecuteActionResource_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    aimdk_msgs::msg::CommonResponse_<ContainerAllocator>;
  _header_type header;

  // setters for named parameter idiom
  Type & set__header(
    const aimdk_msgs::msg::CommonResponse_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Response
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__ExecuteActionResource_Response
    std::shared_ptr<aimdk_msgs::srv::ExecuteActionResource_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteActionResource_Response_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteActionResource_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteActionResource_Response_

// alias to use template instance with default allocator
using ExecuteActionResource_Response =
  aimdk_msgs::srv::ExecuteActionResource_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct ExecuteActionResource
{
  using Request = aimdk_msgs::srv::ExecuteActionResource_Request;
  using Response = aimdk_msgs::srv::ExecuteActionResource_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__STRUCT_HPP_
