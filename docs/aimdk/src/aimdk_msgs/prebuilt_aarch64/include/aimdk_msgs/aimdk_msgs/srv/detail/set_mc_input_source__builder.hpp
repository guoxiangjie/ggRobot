// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetMcInputSource.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_mc_input_source__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcInputSource_Request_input_source
{
public:
  explicit Init_SetMcInputSource_Request_input_source(::aimdk_msgs::srv::SetMcInputSource_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMcInputSource_Request input_source(::aimdk_msgs::srv::SetMcInputSource_Request::_input_source_type arg)
  {
    msg_.input_source = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcInputSource_Request msg_;
};

class Init_SetMcInputSource_Request_action
{
public:
  explicit Init_SetMcInputSource_Request_action(::aimdk_msgs::srv::SetMcInputSource_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcInputSource_Request_input_source action(::aimdk_msgs::srv::SetMcInputSource_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_SetMcInputSource_Request_input_source(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcInputSource_Request msg_;
};

class Init_SetMcInputSource_Request_request
{
public:
  Init_SetMcInputSource_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMcInputSource_Request_action request(::aimdk_msgs::srv::SetMcInputSource_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetMcInputSource_Request_action(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcInputSource_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcInputSource_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetMcInputSource_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcInputSource_Response_response
{
public:
  Init_SetMcInputSource_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::SetMcInputSource_Response response(::aimdk_msgs::srv::SetMcInputSource_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcInputSource_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcInputSource_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetMcInputSource_Response_response();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_INPUT_SOURCE__BUILDER_HPP_
