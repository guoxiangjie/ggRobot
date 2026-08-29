// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/SetMcPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/set_mc_preset_motion__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcPresetMotion_Request_play_timestamp
{
public:
  explicit Init_SetMcPresetMotion_Request_play_timestamp(::aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::SetMcPresetMotion_Request play_timestamp(::aimdk_msgs::srv::SetMcPresetMotion_Request::_play_timestamp_type arg)
  {
    msg_.play_timestamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

class Init_SetMcPresetMotion_Request_ani_path
{
public:
  explicit Init_SetMcPresetMotion_Request_ani_path(::aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcPresetMotion_Request_play_timestamp ani_path(::aimdk_msgs::srv::SetMcPresetMotion_Request::_ani_path_type arg)
  {
    msg_.ani_path = std::move(arg);
    return Init_SetMcPresetMotion_Request_play_timestamp(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

class Init_SetMcPresetMotion_Request_interrupt
{
public:
  explicit Init_SetMcPresetMotion_Request_interrupt(::aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcPresetMotion_Request_ani_path interrupt(::aimdk_msgs::srv::SetMcPresetMotion_Request::_interrupt_type arg)
  {
    msg_.interrupt = std::move(arg);
    return Init_SetMcPresetMotion_Request_ani_path(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

class Init_SetMcPresetMotion_Request_motion
{
public:
  explicit Init_SetMcPresetMotion_Request_motion(::aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcPresetMotion_Request_interrupt motion(::aimdk_msgs::srv::SetMcPresetMotion_Request::_motion_type arg)
  {
    msg_.motion = std::move(arg);
    return Init_SetMcPresetMotion_Request_interrupt(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

class Init_SetMcPresetMotion_Request_area
{
public:
  explicit Init_SetMcPresetMotion_Request_area(::aimdk_msgs::srv::SetMcPresetMotion_Request & msg)
  : msg_(msg)
  {}
  Init_SetMcPresetMotion_Request_motion area(::aimdk_msgs::srv::SetMcPresetMotion_Request::_area_type arg)
  {
    msg_.area = std::move(arg);
    return Init_SetMcPresetMotion_Request_motion(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

class Init_SetMcPresetMotion_Request_header
{
public:
  Init_SetMcPresetMotion_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetMcPresetMotion_Request_area header(::aimdk_msgs::srv::SetMcPresetMotion_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_SetMcPresetMotion_Request_area(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcPresetMotion_Request>()
{
  return aimdk_msgs::srv::builder::Init_SetMcPresetMotion_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_SetMcPresetMotion_Response_response
{
public:
  Init_SetMcPresetMotion_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::SetMcPresetMotion_Response response(::aimdk_msgs::srv::SetMcPresetMotion_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::SetMcPresetMotion_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::SetMcPresetMotion_Response>()
{
  return aimdk_msgs::srv::builder::Init_SetMcPresetMotion_Response_response();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_MC_PRESET_MOTION__BUILDER_HPP_
