// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/MigrateSystemState.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__MIGRATE_SYSTEM_STATE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__MIGRATE_SYSTEM_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/migrate_system_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_MigrateSystemState_Request_state
{
public:
  explicit Init_MigrateSystemState_Request_state(::aimdk_msgs::srv::MigrateSystemState_Request & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::MigrateSystemState_Request state(::aimdk_msgs::srv::MigrateSystemState_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::MigrateSystemState_Request msg_;
};

class Init_MigrateSystemState_Request_header
{
public:
  Init_MigrateSystemState_Request_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MigrateSystemState_Request_state header(::aimdk_msgs::srv::MigrateSystemState_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MigrateSystemState_Request_state(msg_);
  }

private:
  ::aimdk_msgs::srv::MigrateSystemState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::MigrateSystemState_Request>()
{
  return aimdk_msgs::srv::builder::Init_MigrateSystemState_Request_header();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_MigrateSystemState_Response_header
{
public:
  Init_MigrateSystemState_Response_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::MigrateSystemState_Response header(::aimdk_msgs::srv::MigrateSystemState_Response::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::MigrateSystemState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::MigrateSystemState_Response>()
{
  return aimdk_msgs::srv::builder::Init_MigrateSystemState_Response_header();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__MIGRATE_SYSTEM_STATE__BUILDER_HPP_
