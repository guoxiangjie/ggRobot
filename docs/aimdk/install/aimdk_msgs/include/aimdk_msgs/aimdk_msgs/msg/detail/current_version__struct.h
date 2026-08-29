// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/CurrentVersion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'version'
// Member 'name'
// Member 'files'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/CurrentVersion in the package aimdk_msgs.
/**
  * ------------------------------------------------------------------------------------
  * 机上资源的当前版本的数据类型定义
  * ------------------------------------------------------------------------------------
  * 资源版本号
 */
typedef struct aimdk_msgs__msg__CurrentVersion
{
  rosidl_runtime_c__String version;
  /// 资源名称
  rosidl_runtime_c__String name;
  /// 资源路径
  rosidl_runtime_c__String__Sequence files;
  /// 资源下载时间
  uint64_t download_timestamp_seconds;
} aimdk_msgs__msg__CurrentVersion;

// Struct for a sequence of aimdk_msgs__msg__CurrentVersion.
typedef struct aimdk_msgs__msg__CurrentVersion__Sequence
{
  aimdk_msgs__msg__CurrentVersion * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__CurrentVersion__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__CURRENT_VERSION__STRUCT_H_
