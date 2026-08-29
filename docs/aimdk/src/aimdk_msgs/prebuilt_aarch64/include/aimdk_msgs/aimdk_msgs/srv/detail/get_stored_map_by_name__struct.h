// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/GetStoredMapByName.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'map_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetStoredMapByName in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetStoredMapByName_Request
{
  /// 请求数据头
  std_msgs__msg__Header header;
  /// -------------------------------------------------------------
  /// 地图名称
  rosidl_runtime_c__String map_name;
} aimdk_msgs__srv__GetStoredMapByName_Request;

// Struct for a sequence of aimdk_msgs__srv__GetStoredMapByName_Request.
typedef struct aimdk_msgs__srv__GetStoredMapByName_Request__Sequence
{
  aimdk_msgs__srv__GetStoredMapByName_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetStoredMapByName_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
// already included above
// #include "std_msgs/msg/detail/header__struct.h"
// Member 'map_info'
#include "nav_msgs/msg/detail/map_meta_data__struct.h"
// Member 'map_path'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'navi_points'
#include "aimdk_msgs/msg/detail/navi_point__struct.h"
// Member 'qr_points'
#include "aimdk_msgs/msg/detail/qr_point__struct.h"
// Member 'hr_points'
#include "aimdk_msgs/msg/detail/hr_point__struct.h"
// Member 'paths'
#include "aimdk_msgs/msg/detail/path__struct.h"
// Member 'regions'
#include "aimdk_msgs/msg/detail/region__struct.h"

/// Struct defined in srv/GetStoredMapByName in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__GetStoredMapByName_Response
{
  /// 接口返回码, 0代表成功，其他错误码有各自含义
  uint64_t code;
  /// -------------------------------------------------------------
  /// 响应数据头
  std_msgs__msg__Header header;
  /// -------------------------------------------------------------
  /// 地图信息, 包含了长宽，分辨率等信息
  nav_msgs__msg__MapMetaData map_info;
  /// -------------------------------------------------------------
  /// 拓扑信息
  /// 相应地图的版本号
  uint64_t map_version;
  /// -------------------------------------------------------------
  /// 地图路径, 地图保存的png路径
  rosidl_runtime_c__String map_path;
  /// -------------------------------------------------------------
  /// 地图数据 单通道数据，三个值-1，100，0 (此字段暂时因T2跨板通信保留)
  rosidl_runtime_c__int8__Sequence data;
  /// -------------------------------------------------------------
  /// 导航点拓扑信息，二维位姿，已变换到世界坐标系下
  aimdk_msgs__msg__NaviPoint__Sequence navi_points;
  /// -------------------------------------------------------------
  /// 二维码点拓扑信息
  aimdk_msgs__msg__QRPoint__Sequence qr_points;
  /// -------------------------------------------------------------
  /// 高精度点拓扑信息
  aimdk_msgs__msg__HRPoint__Sequence hr_points;
  /// -------------------------------------------------------------
  /// 路径拓扑信息
  aimdk_msgs__msg__Path__Sequence paths;
  /// -------------------------------------------------------------
  /// 拓扑信息
  /// 区域拓扑信息，当前仅包含虚拟墙信息
  aimdk_msgs__msg__Region__Sequence regions;
  /// -------------------------------------------------------------
  /// 地图ID
  uint64_t map_id;
} aimdk_msgs__srv__GetStoredMapByName_Response;

// Struct for a sequence of aimdk_msgs__srv__GetStoredMapByName_Response.
typedef struct aimdk_msgs__srv__GetStoredMapByName_Response__Sequence
{
  aimdk_msgs__srv__GetStoredMapByName_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__GetStoredMapByName_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__GET_STORED_MAP_BY_NAME__STRUCT_H_
