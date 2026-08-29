// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/ExecuteActionResource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/execute_action_resource__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_ExecuteActionResource_Request_meta
{
public:
  explicit Init_ExecuteActionResource_Request_meta(::aimdk_msgs::srv::ExecuteActionResource_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::ExecuteActionResource_Request meta(::aimdk_msgs::srv::ExecuteActionResource_Request::_meta_type arg)
  {
    msg_.meta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Request msg_;
};

class Init_ExecuteActionResource_Request_slaves
{
public:
  explicit Init_ExecuteActionResource_Request_slaves(::aimdk_msgs::srv::ExecuteActionResource_Request & msg)
  : msg_(msg)
  {}
  Init_ExecuteActionResource_Request_meta slaves(::aimdk_msgs::srv::ExecuteActionResource_Request::_slaves_type arg)
  {
    msg_.slaves = std::move(arg);
    return Init_ExecuteActionResource_Request_meta(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Request msg_;
};

class Init_ExecuteActionResource_Request_resource_version
{
public:
  explicit Init_ExecuteActionResource_Request_resource_version(::aimdk_msgs::srv::ExecuteActionResource_Request & msg)
  : msg_(msg)
  {}
  Init_ExecuteActionResource_Request_slaves resource_version(::aimdk_msgs::srv::ExecuteActionResource_Request::_resource_version_type arg)
  {
    msg_.resource_version = std::move(arg);
    return Init_ExecuteActionResource_Request_slaves(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Request msg_;
};

class Init_ExecuteActionResource_Request_resource_key
{
public:
  explicit Init_ExecuteActionResource_Request_resource_key(::aimdk_msgs::srv::ExecuteActionResource_Request & msg)
  : msg_(msg)
  {}
  Init_ExecuteActionResource_Request_resource_version resource_key(::aimdk_msgs::srv::ExecuteActionResource_Request::_resource_key_type arg)
  {
    msg_.resource_key = std::move(arg);
    return Init_ExecuteActionResource_Request_resource_version(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Request msg_;
};

class Init_ExecuteActionResource_Request_header
{
public:
  Init_ExecuteActionResource_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteActionResource_Request_resource_key header(::aimdk_msgs::srv::ExecuteActionResource_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ExecuteActionResource_Request_resource_key(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::ExecuteActionResource_Request>()
{
  return aimdk_msgs::srv::builder::Init_ExecuteActionResource_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_ExecuteActionResource_Response_header
{
public:
  Init_ExecuteActionResource_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::ExecuteActionResource_Response header(::aimdk_msgs::srv::ExecuteActionResource_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::ExecuteActionResource_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::ExecuteActionResource_Response>()
{
  return aimdk_msgs::srv::builder::Init_ExecuteActionResource_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__EXECUTE_ACTION_RESOURCE__BUILDER_HPP_
