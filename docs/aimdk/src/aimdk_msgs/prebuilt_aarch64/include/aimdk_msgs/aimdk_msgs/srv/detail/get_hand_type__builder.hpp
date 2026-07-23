// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from aimdk_msgs:srv/GetHandType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__BUILDER_HPP_
#define AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "aimdk_msgs/srv/detail/get_hand_type__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetHandType_Request_request
{
public:
  Init_GetHandType_Request_request()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::aimdk_msgs::srv::GetHandType_Request request(::aimdk_msgs::srv::GetHandType_Request::_request_type arg)
  {
    msg_.request = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetHandType_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetHandType_Request>()
{
  return aimdk_msgs::srv::builder::Init_GetHandType_Request_request();
}

}  // namespace aimdk_msgs


namespace aimdk_msgs
{

namespace srv
{

namespace builder
{

class Init_GetHandType_Response_right_hands_type
{
public:
  explicit Init_GetHandType_Response_right_hands_type(::aimdk_msgs::srv::GetHandType_Response & msg)
  : msg_(msg)
  {}
  ::aimdk_msgs::srv::GetHandType_Response right_hands_type(::aimdk_msgs::srv::GetHandType_Response::_right_hands_type_type arg)
  {
    msg_.right_hands_type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::aimdk_msgs::srv::GetHandType_Response msg_;
};

class Init_GetHandType_Response_left_hands_type
{
public:
  explicit Init_GetHandType_Response_left_hands_type(::aimdk_msgs::srv::GetHandType_Response & msg)
  : msg_(msg)
  {}
  Init_GetHandType_Response_right_hands_type left_hands_type(::aimdk_msgs::srv::GetHandType_Response::_left_hands_type_type arg)
  {
    msg_.left_hands_type = std::move(arg);
    return Init_GetHandType_Response_right_hands_type(msg_);
  }

private:
  ::aimdk_msgs::srv::GetHandType_Response msg_;
};

class Init_GetHandType_Response_reponse
{
public:
  Init_GetHandType_Response_reponse()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetHandType_Response_left_hands_type reponse(::aimdk_msgs::srv::GetHandType_Response::_reponse_type arg)
  {
    msg_.reponse = std::move(arg);
    return Init_GetHandType_Response_left_hands_type(msg_);
  }

private:
  ::aimdk_msgs::srv::GetHandType_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::aimdk_msgs::srv::GetHandType_Response>()
{
  return aimdk_msgs::srv::builder::Init_GetHandType_Response_reponse();
}

}  // namespace aimdk_msgs

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_HAND_TYPE__BUILDER_HPP_
