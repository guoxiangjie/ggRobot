// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetMicSourceRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_mic_source_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMicSourceRequest_Request_mic_source
{
public:
  explicit Init_SetMicSourceRequest_Request_mic_source(::aimdk_msgs::srv::SetMicSourceRequest_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMicSourceRequest_Request mic_source(::aimdk_msgs::srv::SetMicSourceRequest_Request::_mic_source_type arg)
  {
    msg_.mic_source = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMicSourceRequest_Request msg_;
};

class Init_SetMicSourceRequest_Request_header
{
public:
  Init_SetMicSourceRequest_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMicSourceRequest_Request_mic_source header(::aimdk_msgs::srv::SetMicSourceRequest_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SetMicSourceRequest_Request_mic_source(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMicSourceRequest_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMicSourceRequest_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetMicSourceRequest_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMicSourceRequest_Response_header
{
public:
  Init_SetMicSourceRequest_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::SetMicSourceRequest_Response header(::aimdk_msgs::srv::SetMicSourceRequest_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMicSourceRequest_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMicSourceRequest_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetMicSourceRequest_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MIC_SOURCE_REQUEST__BUILDER_HPP_
