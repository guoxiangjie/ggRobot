// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/SetPmuLed.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'LED_STRIP_MODE_CONSTANT'.
/**
  * led_strip_mode: 灯带模式枚举
  * 常亮
 */
enum
{
  aimdk_msgs__srv__SetPmuLed_Request__LED_STRIP_MODE_CONSTANT = 0
};

/// Constant 'LED_STRIP_MODE_BREATH'.
/**
  * 呼吸，4s周期，亮度正弦变化
 */
enum
{
  aimdk_msgs__srv__SetPmuLed_Request__LED_STRIP_MODE_BREATH = 1
};

/// Constant 'LED_STRIP_MODE_FLASH'.
/**
  * 闪烁，1s周期，0.5s亮，0.5s灭
 */
enum
{
  aimdk_msgs__srv__SetPmuLed_Request__LED_STRIP_MODE_FLASH = 2
};

/// Constant 'LED_STRIP_MODE_FLOW'.
/**
  * 流水，2s周期，从左到右依次点亮，然后灭
 */
enum
{
  aimdk_msgs__srv__SetPmuLed_Request__LED_STRIP_MODE_FLOW = 3
};

/// Constant 'LED_STRIP_MODE_MAX'.
/**
  * 无效
 */
enum
{
  aimdk_msgs__srv__SetPmuLed_Request__LED_STRIP_MODE_MAX = 4
};

// Include directives for member types
// Member 'request'
#include "aimdk_msgs/msg/detail/common_request__struct.h"
// Member 'trace_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetPmuLed in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetPmuLed_Request
{
  aimdk_msgs__msg__CommonRequest request;
  /// 来源追踪
  rosidl_runtime_c__String trace_id;
  /// 灯带模式
  uint8_t led_strip_mode;
  /// 红色分量
  uint8_t r;
  /// 绿色分量
  uint8_t g;
  /// 蓝色分量
  uint8_t b;
  /// 优先级
  int32_t priority;
  /// 优先级重置标志
  bool reset_priority;
} aimdk_msgs__srv__SetPmuLed_Request;

// Struct for a sequence of aimdk_msgs__srv__SetPmuLed_Request.
typedef struct aimdk_msgs__srv__SetPmuLed_Request__Sequence
{
  aimdk_msgs__srv__SetPmuLed_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetPmuLed_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/response_header__struct.h"

/// Struct defined in srv/SetPmuLed in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__SetPmuLed_Response
{
  /// 响应头
  aimdk_msgs__msg__ResponseHeader header;
  /// 设置是否成功
  uint16_t status_code;
} aimdk_msgs__srv__SetPmuLed_Response;

// Struct for a sequence of aimdk_msgs__srv__SetPmuLed_Response.
typedef struct aimdk_msgs__srv__SetPmuLed_Response__Sequence
{
  aimdk_msgs__srv__SetPmuLed_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__SetPmuLed_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__SET_PMU_LED__STRUCT_H_
