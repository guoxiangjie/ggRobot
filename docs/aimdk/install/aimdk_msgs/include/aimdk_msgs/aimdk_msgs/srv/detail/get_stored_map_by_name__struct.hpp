// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Request __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Request __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetStoredMapByName_Request_
{
  using Type = GetStoredMapByName_Request_<ContainerAllocator>;

  explicit GetStoredMapByName_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_name = "";
    }
  }

  explicit GetStoredMapByName_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    map_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_name = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _map_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_name_type map_name;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__map_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Request
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Request
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetStoredMapByName_Request_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->map_name != other.map_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetStoredMapByName_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetStoredMapByName_Request_

// alias to use template instance with default allocator
using GetStoredMapByName_Request =
  aimdk_msgs::srv::GetStoredMapByName_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs


// Include directives for member types
// Member 'header'
// already included above
// #include "std_msgs/msg/detail/header__struct.hpp"
// Member 'map_info'
#include "nav_msgs/msg/detail/map_meta_data__struct.hpp"
// Member 'navi_points'
#include "aimdk_msgs/msg/detail/navi_point__struct.hpp"
// Member 'qr_points'
#include "aimdk_msgs/msg/detail/qr_point__struct.hpp"
// Member 'hr_points'
#include "aimdk_msgs/msg/detail/hr_point__struct.hpp"
// Member 'paths'
#include "aimdk_msgs/msg/detail/path__struct.hpp"
// Member 'regions'
#include "aimdk_msgs/msg/detail/region__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Response __attribute__((deprecated))
#else
# define DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Response __declspec(deprecated)
#endif

namespace aimdk_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetStoredMapByName_Response_
{
  using Type = GetStoredMapByName_Response_<ContainerAllocator>;

  explicit GetStoredMapByName_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    map_info(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->code = 0ull;
      this->map_version = 0ull;
      this->map_path = "";
      this->map_id = 0ull;
    }
  }

  explicit GetStoredMapByName_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    map_info(_alloc, _init),
    map_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->code = 0ull;
      this->map_version = 0ull;
      this->map_path = "";
      this->map_id = 0ull;
    }
  }

  // field types and members
  using _code_type =
    uint64_t;
  _code_type code;
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _map_info_type =
    nav_msgs::msg::MapMetaData_<ContainerAllocator>;
  _map_info_type map_info;
  using _map_version_type =
    uint64_t;
  _map_version_type map_version;
  using _map_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_path_type map_path;
  using _data_type =
    std::vector<int8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int8_t>>;
  _data_type data;
  using _navi_points_type =
    std::vector<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>>;
  _navi_points_type navi_points;
  using _qr_points_type =
    std::vector<aimdk_msgs::msg::QRPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::QRPoint_<ContainerAllocator>>>;
  _qr_points_type qr_points;
  using _hr_points_type =
    std::vector<aimdk_msgs::msg::HRPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HRPoint_<ContainerAllocator>>>;
  _hr_points_type hr_points;
  using _paths_type =
    std::vector<aimdk_msgs::msg::Path_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::Path_<ContainerAllocator>>>;
  _paths_type paths;
  using _regions_type =
    std::vector<aimdk_msgs::msg::Region_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::Region_<ContainerAllocator>>>;
  _regions_type regions;
  using _map_id_type =
    uint64_t;
  _map_id_type map_id;

  // setters for named parameter idiom
  Type & set__code(
    const uint64_t & _arg)
  {
    this->code = _arg;
    return *this;
  }
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__map_info(
    const nav_msgs::msg::MapMetaData_<ContainerAllocator> & _arg)
  {
    this->map_info = _arg;
    return *this;
  }
  Type & set__map_version(
    const uint64_t & _arg)
  {
    this->map_version = _arg;
    return *this;
  }
  Type & set__map_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_path = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<int8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int8_t>> & _arg)
  {
    this->data = _arg;
    return *this;
  }
  Type & set__navi_points(
    const std::vector<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::NaviPoint_<ContainerAllocator>>> & _arg)
  {
    this->navi_points = _arg;
    return *this;
  }
  Type & set__qr_points(
    const std::vector<aimdk_msgs::msg::QRPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::QRPoint_<ContainerAllocator>>> & _arg)
  {
    this->qr_points = _arg;
    return *this;
  }
  Type & set__hr_points(
    const std::vector<aimdk_msgs::msg::HRPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::HRPoint_<ContainerAllocator>>> & _arg)
  {
    this->hr_points = _arg;
    return *this;
  }
  Type & set__paths(
    const std::vector<aimdk_msgs::msg::Path_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::Path_<ContainerAllocator>>> & _arg)
  {
    this->paths = _arg;
    return *this;
  }
  Type & set__regions(
    const std::vector<aimdk_msgs::msg::Region_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<aimdk_msgs::msg::Region_<ContainerAllocator>>> & _arg)
  {
    this->regions = _arg;
    return *this;
  }
  Type & set__map_id(
    const uint64_t & _arg)
  {
    this->map_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Response
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__aimdk_msgs__srv__GetStoredMapByName_Response
    std::shared_ptr<aimdk_msgs::srv::GetStoredMapByName_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetStoredMapByName_Response_ & other) const
  {
    if (this->code != other.code) {
      return false;
    }
    if (this->header != other.header) {
      return false;
    }
    if (this->map_info != other.map_info) {
      return false;
    }
    if (this->map_version != other.map_version) {
      return false;
    }
    if (this->map_path != other.map_path) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    if (this->navi_points != other.navi_points) {
      return false;
    }
    if (this->qr_points != other.qr_points) {
      return false;
    }
    if (this->hr_points != other.hr_points) {
      return false;
    }
    if (this->paths != other.paths) {
      return false;
    }
    if (this->regions != other.regions) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetStoredMapByName_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetStoredMapByName_Response_

// alias to use template instance with default allocator
using GetStoredMapByName_Response =
  aimdk_msgs::srv::GetStoredMapByName_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace aimdk_msgs

namespace aimdk_msgs
{

namespace srv
{

struct GetStoredMapByName
{
  using Request = aimdk_msgs::srv::GetStoredMapByName_Request;
  using Response = aimdk_msgs::srv::GetStoredMapByName_Response;
};

}  // namespace srv

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_HPP_
