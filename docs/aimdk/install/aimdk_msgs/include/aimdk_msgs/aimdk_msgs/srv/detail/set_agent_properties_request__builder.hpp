// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetAgentPropertiesRequest.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_agent_properties_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetAgentPropertiesRequest_Request_contents
{
public:
  explicit Init_SetAgentPropertiesRequest_Request_contents(::aimdk_msgs::srv::SetAgentPropertiesRequest_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetAgentPropertiesRequest_Request contents(::aimdk_msgs::srv::SetAgentPropertiesRequest_Request::_contents_type arg)
  {
    msg_.contents = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetAgentPropertiesRequest_Request msg_;
};

class Init_SetAgentPropertiesRequest_Request_header
{
public:
  Init_SetAgentPropertiesRequest_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetAgentPropertiesRequest_Request_contents header(::aimdk_msgs::srv::SetAgentPropertiesRequest_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SetAgentPropertiesRequest_Request_contents(msg_);
  }

private:
  ::aimdk_msgs::srv::SetAgentPropertiesRequest_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetAgentPropertiesRequest_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetAgentPropertiesRequest_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetAgentPropertiesRequest_Response_header
{
public:
  Init_SetAgentPropertiesRequest_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::SetAgentPropertiesRequest_Response header(::aimdk_msgs::srv::SetAgentPropertiesRequest_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetAgentPropertiesRequest_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetAgentPropertiesRequest_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetAgentPropertiesRequest_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_AGENT_PROPERTIES_REQUEST__BUILDER_HPP_
