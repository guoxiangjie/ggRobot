// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:msg/CurrentVersion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__BUILDER_HPP_
#define AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/msg/detail/current_version__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace msg
{

namespace builder
{

class Init_CurrentVersion_download_timestamp_seconds
{
public:
  explicit Init_CurrentVersion_download_timestamp_seconds(::aimdk_msgs::msg::CurrentVersion & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::msg::CurrentVersion download_timestamp_seconds(::aimdk_msgs::msg::CurrentVersion::_download_timestamp_seconds_type arg)
  {
    msg_.download_timestamp_seconds = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::msg::CurrentVersion msg_;
};

class Init_CurrentVersion_files
{
public:
  explicit Init_CurrentVersion_files(::aimdk_msgs::msg::CurrentVersion & msg)
  : msg_(msg)
  {}
  Init_CurrentVersion_download_timestamp_seconds files(::aimdk_msgs::msg::CurrentVersion::_files_type arg)
  {
    msg_.files = std::move(arg);
    return Init_CurrentVersion_download_timestamp_seconds(msg_);
  }

private:
  ::aimdk_msgs::msg::CurrentVersion msg_;
};

class Init_CurrentVersion_name
{
public:
  explicit Init_CurrentVersion_name(::aimdk_msgs::msg::CurrentVersion & msg)
  : msg_(msg)
  {}
  Init_CurrentVersion_files name(::aimdk_msgs::msg::CurrentVersion::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_CurrentVersion_files(msg_);
  }

private:
  ::aimdk_msgs::msg::CurrentVersion msg_;
};

class Init_CurrentVersion_version
{
public:
  Init_CurrentVersion_version()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CurrentVersion_name version(::aimdk_msgs::msg::CurrentVersion::_version_type arg)
  {
    msg_.version = std::move(arg);
    return Init_CurrentVersion_name(msg_);
  }

private:
  ::aimdk_msgs::msg::CurrentVersion msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::msg::CurrentVersion>()
{
  return aimdk_msgs::msg::builder::Init_CurrentVersion_version();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__BUILDER_HPP_
