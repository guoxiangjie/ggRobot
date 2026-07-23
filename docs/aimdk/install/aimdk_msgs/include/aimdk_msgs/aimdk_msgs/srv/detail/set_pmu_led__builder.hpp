// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetPmuLed.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_pmu_led__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetPmuLed_Request_reset_priority
{
public:
  explicit Init_SetPmuLed_Request_reset_priority(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetPmuLed_Request reset_priority(::aimdk_msgs::srv::SetPmuLed_Request::_reset_priority_type arg)
  {
    msg_.reset_priority = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_priority
{
public:
  explicit Init_SetPmuLed_Request_priority(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_reset_priority priority(::aimdk_msgs::srv::SetPmuLed_Request::_priority_type arg)
  {
    msg_.priority = std::move(arg);
    return Init_SetPmuLed_Request_reset_priority(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_b
{
public:
  explicit Init_SetPmuLed_Request_b(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_priority b(::aimdk_msgs::srv::SetPmuLed_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_SetPmuLed_Request_priority(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_g
{
public:
  explicit Init_SetPmuLed_Request_g(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_b g(::aimdk_msgs::srv::SetPmuLed_Request::_g_type arg)
  {
    msg_.g = std::move(arg);
    return Init_SetPmuLed_Request_b(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_r
{
public:
  explicit Init_SetPmuLed_Request_r(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_g r(::aimdk_msgs::srv::SetPmuLed_Request::_r_type arg)
  {
    msg_.r = std::move(arg);
    return Init_SetPmuLed_Request_g(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_led_strip_mode
{
public:
  explicit Init_SetPmuLed_Request_led_strip_mode(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_r led_strip_mode(::aimdk_msgs::srv::SetPmuLed_Request::_led_strip_mode_type arg)
  {
    msg_.led_strip_mode = std::move(arg);
    return Init_SetPmuLed_Request_r(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_trace_id
{
public:
  explicit Init_SetPmuLed_Request_trace_id(::aimdk_msgs::srv::SetPmuLed_Request & msg)
  : msg_(msg)
  {}
  Init_SetPmuLed_Request_led_strip_mode trace_id(::aimdk_msgs::srv::SetPmuLed_Request::_trace_id_type arg)
  {
    msg_.trace_id = std::move(arg);
    return Init_SetPmuLed_Request_led_strip_mode(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

class Init_SetPmuLed_Request_request
{
public:
  Init_SetPmuLed_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPmuLed_Request_trace_id request(::aimdk_msgs::srv::SetPmuLed_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetPmuLed_Request_trace_id(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetPmuLed_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetPmuLed_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetPmuLed_Response_status_code
{
public:
  explicit Init_SetPmuLed_Response_status_code(::aimdk_msgs::srv::SetPmuLed_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetPmuLed_Response status_code(::aimdk_msgs::srv::SetPmuLed_Response::_status_code_type arg)
  {
    msg_.status_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Response msg_;
};

class Init_SetPmuLed_Response_header
{
public:
  Init_SetPmuLed_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPmuLed_Response_status_code header(::aimdk_msgs::srv::SetPmuLed_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SetPmuLed_Response_status_code(msg_);
  }

private:
  ::aimdk_msgs::srv::SetPmuLed_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetPmuLed_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetPmuLed_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__BUILDER_HPP_
