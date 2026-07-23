// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_stored_map_by_name__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetStoredMapByName_Request_map_name
{
public:
  explicit Init_GetStoredMapByName_Request_map_name(::aimdk_msgs::srv::GetStoredMapByName_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetStoredMapByName_Request map_name(::aimdk_msgs::srv::GetStoredMapByName_Request::_map_name_type arg)
  {
    msg_.map_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Request msg_;
};

class Init_GetStoredMapByName_Request_header
{
public:
  Init_GetStoredMapByName_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetStoredMapByName_Request_map_name header(::aimdk_msgs::srv::GetStoredMapByName_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GetStoredMapByName_Request_map_name(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetStoredMapByName_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetStoredMapByName_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetStoredMapByName_Response_map_id
{
public:
  explicit Init_GetStoredMapByName_Response_map_id(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetStoredMapByName_Response map_id(::aimdk_msgs::srv::GetStoredMapByName_Response::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_regions
{
public:
  explicit Init_GetStoredMapByName_Response_regions(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_map_id regions(::aimdk_msgs::srv::GetStoredMapByName_Response::_regions_type arg)
  {
    msg_.regions = std::move(arg);
    return Init_GetStoredMapByName_Response_map_id(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_paths
{
public:
  explicit Init_GetStoredMapByName_Response_paths(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_regions paths(::aimdk_msgs::srv::GetStoredMapByName_Response::_paths_type arg)
  {
    msg_.paths = std::move(arg);
    return Init_GetStoredMapByName_Response_regions(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_hr_points
{
public:
  explicit Init_GetStoredMapByName_Response_hr_points(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_paths hr_points(::aimdk_msgs::srv::GetStoredMapByName_Response::_hr_points_type arg)
  {
    msg_.hr_points = std::move(arg);
    return Init_GetStoredMapByName_Response_paths(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_qr_points
{
public:
  explicit Init_GetStoredMapByName_Response_qr_points(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_hr_points qr_points(::aimdk_msgs::srv::GetStoredMapByName_Response::_qr_points_type arg)
  {
    msg_.qr_points = std::move(arg);
    return Init_GetStoredMapByName_Response_hr_points(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_navi_points
{
public:
  explicit Init_GetStoredMapByName_Response_navi_points(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_qr_points navi_points(::aimdk_msgs::srv::GetStoredMapByName_Response::_navi_points_type arg)
  {
    msg_.navi_points = std::move(arg);
    return Init_GetStoredMapByName_Response_qr_points(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_data
{
public:
  explicit Init_GetStoredMapByName_Response_data(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_navi_points data(::aimdk_msgs::srv::GetStoredMapByName_Response::_data_type arg)
  {
    msg_.data = std::move(arg);
    return Init_GetStoredMapByName_Response_navi_points(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_map_path
{
public:
  explicit Init_GetStoredMapByName_Response_map_path(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_data map_path(::aimdk_msgs::srv::GetStoredMapByName_Response::_map_path_type arg)
  {
    msg_.map_path = std::move(arg);
    return Init_GetStoredMapByName_Response_data(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_map_version
{
public:
  explicit Init_GetStoredMapByName_Response_map_version(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_map_path map_version(::aimdk_msgs::srv::GetStoredMapByName_Response::_map_version_type arg)
  {
    msg_.map_version = std::move(arg);
    return Init_GetStoredMapByName_Response_map_path(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_map_info
{
public:
  explicit Init_GetStoredMapByName_Response_map_info(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_map_version map_info(::aimdk_msgs::srv::GetStoredMapByName_Response::_map_info_type arg)
  {
    msg_.map_info = std::move(arg);
    return Init_GetStoredMapByName_Response_map_version(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_header
{
public:
  explicit Init_GetStoredMapByName_Response_header(::aimdk_msgs::srv::GetStoredMapByName_Response & msg)
  : msg_(msg)
  {}
  Init_GetStoredMapByName_Response_map_info header(::aimdk_msgs::srv::GetStoredMapByName_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GetStoredMapByName_Response_map_info(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

class Init_GetStoredMapByName_Response_code
{
public:
  Init_GetStoredMapByName_Response_code()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetStoredMapByName_Response_header code(::aimdk_msgs::srv::GetStoredMapByName_Response::_code_type arg)
  {
    msg_.code = std::move(arg);
    return Init_GetStoredMapByName_Response_header(msg_);
  }

private:
  ::aimdk_msgs::srv::GetStoredMapByName_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetStoredMapByName_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetStoredMapByName_Response_code();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__BUILDER_HPP_
