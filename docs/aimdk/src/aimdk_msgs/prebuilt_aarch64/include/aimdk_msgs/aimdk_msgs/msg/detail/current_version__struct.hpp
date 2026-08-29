// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:msg/CurrentVersion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_HPP_
#define AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__msg__CurrentVersion __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__msg__CurrentVersion __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CurrentVersion_
{
  using Type = CurrentVersion_<ContainerAllocator>;

  explicit CurrentVersion_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->version = "";
      this->name = "";
      this->download_timestamp_seconds = 0ull;
    }
  }

  explicit CurrentVersion_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : version(_alloc),
    name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->version = "";
      this->name = "";
      this->download_timestamp_seconds = 0ull;
    }
  }

  // field types and members
  using _version_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _version_type version;
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _files_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _files_type files;
  using _download_timestamp_seconds_type =
    uint64_t;
  _download_timestamp_seconds_type download_timestamp_seconds;

  // setters for named parameter idiom
  Type & set__version(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->version = _arg;
    return *this;
  }
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__files(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->files = _arg;
    return *this;
  }
  Type & set__download_timestamp_seconds(
    const uint64_t & _arg)
  {
    this->download_timestamp_seconds = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__msg__CurrentVersion
    std::shared_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__msg__CurrentVersion
    std::shared_ptr<aimdk_msgs::msg::CurrentVersion_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CurrentVersion_ & other) const
  {
    if (this->version != other.version) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->files != other.files) {
      return false;
    }
    if (this->download_timestamp_seconds != other.download_timestamp_seconds) {
      return false;
    }
    return true;
  }
  bool operator!=(const CurrentVersion_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CurrentVersion_

// alias to use template instance with default allocator
using CurrentVersion =
  aimdk_msgs::msg::CurrentVersion_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_HPP_
