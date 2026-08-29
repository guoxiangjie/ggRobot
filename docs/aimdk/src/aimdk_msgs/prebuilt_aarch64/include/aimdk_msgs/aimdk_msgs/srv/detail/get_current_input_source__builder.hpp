// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetCurrentInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_current_input_source__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetCurrentInputSource_Request_request
{
public:
  Init_GetCurrentInputSource_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetCurrentInputSource_Request request(::aimdk_msgs::srv::GetCurrentInputSource_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetCurrentInputSource_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetCurrentInputSource_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetCurrentInputSource_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetCurrentInputSource_Response_input_source
{
public:
  explicit Init_GetCurrentInputSource_Response_input_source(::aimdk_msgs::srv::GetCurrentInputSource_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetCurrentInputSource_Response input_source(::aimdk_msgs::srv::GetCurrentInputSource_Response::_input_source_type arg)
  {
    msg_.input_source = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetCurrentInputSource_Response msg_;
};

class Init_GetCurrentInputSource_Response_response
{
public:
  Init_GetCurrentInputSource_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetCurrentInputSource_Response_input_source response(::aimdk_msgs::srv::GetCurrentInputSource_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return Init_GetCurrentInputSource_Response_input_source(msg_);
  }

private:
  ::aimdk_msgs::srv::GetCurrentInputSource_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetCurrentInputSource_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetCurrentInputSource_Response_response();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_CURRENT_INPUT_SOURCE__BUILDER_HPP_
