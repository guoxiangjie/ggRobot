// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/AgentPropertyIdType.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'AGENT_PROPERTY_UNDEFINED'.
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_UNDEFINED = 0
};

/// Constant 'AGENT_PROPERTY_LANGUAGE'.
/**
  * value: "zh/en"
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_LANGUAGE = 1
};

/// Constant 'AGENT_PROPERTY_RUN_MODE'.
/**
  * 运行模式 value: "normal/only_voice/no_voice" normal: 正常模式，启用语音助手和语音识别  only_voice: 只启用提供降噪后音频  no_voice: 完全禁用agent，音频都不进行获取提供
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_RUN_MODE = 2
};

/// Constant 'AGENT_PROPERTY_GREET'.
/**
  * value: true/false
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_GREET = 3
};

/// Constant 'AGENT_PROPERTY_HEAD_FOLLOW'.
/**
  * value: true/false
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_HEAD_FOLLOW = 4
};

/// Constant 'AGENT_PROPERTY_DUPLEX_TIMEOUT'.
/**
  * value: "60" 超时时间，单位秒
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_DUPLEX_TIMEOUT = 5
};

/// Constant 'AGENT_PROPERTY_ENVIRONMENT_SWITCH'.
/**
  * value: "环境切换指令"
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_ENVIRONMENT_SWITCH = 6
};

/// Constant 'AGENT_PROPERTY_WELCOME_STATUS'.
/**
  * value: "人脸迎宾"
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_WELCOME_STATUS = 7
};

/// Constant 'AGENT_PROPERTY_SITE_SWITCH'.
/**
  * value: "服务站点切换"
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_SITE_SWITCH = 8
};

/// Constant 'AGENT_PROPERTY_LANGUAGE_LIST'.
/**
  * value: "语言支持列表（只读）"
 */
enum
{
  aimdk_msgs__msg__AgentPropertyIdType__AGENT_PROPERTY_LANGUAGE_LIST = 9
};

/// Struct defined in msg/AgentPropertyIdType in the package aimdk_msgs.
typedef struct aimdk_msgs__msg__AgentPropertyIdType
{
  uint8_t value;
} aimdk_msgs__msg__AgentPropertyIdType;

// Struct for a sequence of aimdk_msgs__msg__AgentPropertyIdType.
typedef struct aimdk_msgs__msg__AgentPropertyIdType__Sequence
{
  aimdk_msgs__msg__AgentPropertyIdType * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__AgentPropertyIdType__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__AGENT_PROPERTY_ID_TYPE__STRUCT_H_
