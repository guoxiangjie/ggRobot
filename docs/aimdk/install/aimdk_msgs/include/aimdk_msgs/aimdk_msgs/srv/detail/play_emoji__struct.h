// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:srv/PlayEmoji.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_H_
#define AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'EMOTION_UNKNOWN'.
/**
  * 表情枚举
  * 未知
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_UNKNOWN = 0
};

/// Constant 'EMOTION_IDLE_BLINK'.
/**
  * 眨眼
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_BLINK = 1
};

/// Constant 'EMOTION_IDLE_CALM_1'.
/**
  * 平静-眼睛变化
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CALM_1 = 10
};

/// Constant 'EMOTION_IDLE_CALM_2'.
/**
  * 平静-眼睛变化
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CALM_2 = 11
};

/// Constant 'EMOTION_IDLE_GAME'.
/**
  * 平静-游戏
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_GAME = 20
};

/// Constant 'EMOTION_IDLE_CUTE_1'.
/**
  * 平静-卖萌
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CUTE_1 = 30
};

/// Constant 'EMOTION_IDLE_CUTE_2'.
/**
  * 平静-卖萌
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CUTE_2 = 31
};

/// Constant 'EMOTION_IDLE_CUTE_3'.
/**
  * 平静-卖萌
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CUTE_3 = 32
};

/// Constant 'EMOTION_IDLE_CUTE_4'.
/**
  * 平静-卖萌
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_IDLE_CUTE_4 = 33
};

/// Constant 'EMOTION_EYE_CLOSE'.
/**
  * 闭上眼
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_CLOSE = 40
};

/// Constant 'EMOTION_EYE_OPEN'.
/**
  * 睁开眼
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_OPEN = 50
};

/// Constant 'EMOTION_EYE_BORING_1'.
/**
  * 无聊
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_BORING_1 = 60
};

/// Constant 'EMOTION_EYE_ABNORMAL'.
/**
  * 异常
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_ABNORMAL = 70
};

/// Constant 'EMOTION_EYE_SLEEPY'.
/**
  * 睡着
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_SLEEPY = 80
};

/// Constant 'EMOTION_EYE_HAPPY'.
/**
  * 快乐
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_HAPPY = 90
};

/// Constant 'EMOTION_EYE_EXTREMEHAPPY_1'.
/**
  * 加倍开心
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_EXTREMEHAPPY_1 = 100
};

/// Constant 'EMOTION_EYE_EXTREMEHAPPY_2'.
/**
  * 狂喜
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_EXTREMEHAPPY_2 = 101
};

/// Constant 'EMOTION_EYE_SAD'.
/**
  * 悲伤
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_SAD = 110
};

/// Constant 'EMOTION_EYE_SYMPATHY'.
/**
  * 同情
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_SYMPATHY = 120
};

/// Constant 'EMOTION_EYE_CONFUSE'.
/**
  * 疑惑
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_CONFUSE = 130
};

/// Constant 'EMOTION_EYE_SHOCK'.
/**
  * 震惊
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_SHOCK = 140
};

/// Constant 'EMOTION_EYE_ACTCUTE'.
/**
  * 撒娇
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_ACTCUTE = 150
};

/// Constant 'EMOTION_EYE_SERIOUS'.
/**
  * 严肃
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_SERIOUS = 160
};

/// Constant 'EMOTION_EYE_THINKING'.
/**
  * 思考
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_THINKING = 170
};

/// Constant 'EMOTION_EYE_ANGRY'.
/**
  * 愤怒
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_ANGRY = 180
};

/// Constant 'EMOTION_EYE_EXTREMEANGRY'.
/**
  * 加倍愤怒
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_EXTREMEANGRY = 190
};

/// Constant 'EMOTION_EYE_ADORE'.
/**
  * 崇拜
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_ADORE = 200
};

/// Constant 'EMOTION_EYE_EXTREMEADORE'.
/**
  * 加倍崇拜
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_EXTREMEADORE = 210
};

/// Constant 'EMOTION_EYE_CHARGE'.
/**
  * 充电
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_EYE_CHARGE = 220
};

/// Constant 'EMOTION_MODE_ONCE'.
/**
  * 仅播放一次
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_MODE_ONCE = 1
};

/// Constant 'EMOTION_MODE_LOOP'.
/**
  * 循环播放
 */
enum
{
  aimdk_msgs__srv__PlayEmoji_Request__EMOTION_MODE_LOOP = 2
};

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_request__struct.h"

/// Struct defined in srv/PlayEmoji in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayEmoji_Request
{
  /// --------------------------------------------------------------------------------------------------------------
  /// 输入表情参数单独控制灯光播放
  /// --------------------------------------------------------------------------------------------------------------
  /// ----------------------------------------------------
  /// 请求头
  aimdk_msgs__msg__CommonRequest header;
  /// ----------------------------------------------------
  ///  表情 id
  uint8_t emotion_id;
  /// ----------------------------------------------------
  /// 播放模式枚举
  uint8_t mode;
  /// ----------------------------------------------------
  /// 播放优先级
  int32_t priority;
} aimdk_msgs__srv__PlayEmoji_Request;

// Struct for a sequence of aimdk_msgs__srv__PlayEmoji_Request.
typedef struct aimdk_msgs__srv__PlayEmoji_Request__Sequence
{
  aimdk_msgs__srv__PlayEmoji_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayEmoji_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "aimdk_msgs/msg/detail/common_response__struct.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/PlayEmoji in the package aimdk_msgs.
typedef struct aimdk_msgs__srv__PlayEmoji_Response
{
  /// ---------------------------------------------------- resp
  /// 响应头
  aimdk_msgs__msg__CommonResponse header;
  /// -----------------------------------------------------
  ///  是否控制成功
  bool success;
  rosidl_runtime_c__String message;
} aimdk_msgs__srv__PlayEmoji_Response;

// Struct for a sequence of aimdk_msgs__srv__PlayEmoji_Response.
typedef struct aimdk_msgs__srv__PlayEmoji_Response__Sequence
{
  aimdk_msgs__srv__PlayEmoji_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__srv__PlayEmoji_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__SRV__DETAIL__PLAY_EMOJI__STRUCT_H_
