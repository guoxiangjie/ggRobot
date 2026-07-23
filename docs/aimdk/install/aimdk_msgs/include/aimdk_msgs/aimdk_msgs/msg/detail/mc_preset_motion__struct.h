// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McPresetMotion.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RAISE_HAND'.
/**
  * 抬手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__RAISE_HAND = 1001l
};

/// Constant 'WAVE_HAND'.
/**
  * 挥手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__WAVE_HAND = 1002l
};

/// Constant 'SHAKE_HAND'.
/**
  * 握手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__SHAKE_HAND = 1003l
};

/// Constant 'FLYING_KISS_HAND'.
/**
  * 飞吻
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__FLYING_KISS_HAND = 1004l
};

/// Constant 'CLAP_HAND'.
/**
  * 击掌
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__CLAP_HAND = 1008l
};

/// Constant 'TURN_WAVE_HAND'.
/**
  * 转身挥手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__TURN_WAVE_HAND = 2001l
};

/// Constant 'INTERACTION_BOW'.
/**
  * 交互动作--鞠躬
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_BOW = 3001l
};

/// Constant 'INTERACTION_LIKE'.
/**
  * 交互动作--点赞
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_LIKE = 3002l
};

/// Constant 'INTERACTION_YE'.
/**
  * 交互动作--比YE
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_YE = 3003l
};

/// Constant 'INTERACTION_SWEATHEART'.
/**
  * 交互动作--头顶比心
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_SWEATHEART = 3004l
};

/// Constant 'SALUTE'.
/**
  * 交互动作--敬礼
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__SALUTE = 1013l
};

/// Constant 'INTERACTION_SAD'.
/**
  * 交互动作--悲伤
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_SAD = 3006l
};

/// Constant 'INTERACTION_LIGHTWAVE'.
/**
  * 交互动作--轻轻挥手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_LIGHTWAVE = 3007l
};

/// Constant 'INTERACTION_HUG'.
/**
  * 交互动作--拥抱
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_HUG = 3008l
};

/// Constant 'INTERACTION_HANDX'.
/**
  * 交互动作--胸前打叉
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_HANDX = 3009l
};

/// Constant 'INTERACTION_CHESTWAVE'.
/**
  * 交互动作--胸前挥手
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_CHESTWAVE = 3010l
};

/// Constant 'INTERACTION_CHEER'.
/**
  * 交互动作--加油
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_CHEER = 3011l
};

/// Constant 'INTERACTION_BLOWKISS'.
/**
  * 交互动作--低空飞吻
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_BLOWKISS = 3012l
};

/// Constant 'INTERACTION_BASSDANCE1'.
/**
  * 交互动作--巴斯舞1
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_BASSDANCE1 = 3013l
};

/// Constant 'INTERACTION_BASSDANCE2'.
/**
  * 交互动作--巴斯舞2
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_BASSDANCE2 = 3014l
};

/// Constant 'HITCLAP'.
/**
  * 交互动作--击掌
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__HITCLAP = 3015l
};

/// Constant 'INTERACTION_SPEAK'.
/**
  * 交互动作--说话手势
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_SPEAK = 3016l
};

/// Constant 'CLIPFIST'.
/**
  * 交互动作--碰拳
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__CLIPFIST = 1009l
};

/// Constant 'INTERACTION_PHOTOPOSTURE'.
/**
  * 交互动作--拍照姿势
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_PHOTOPOSTURE = 3018l
};

/// Constant 'INTERACTION_PHOTOTRIPPLEPOSTURE'.
/**
  * 交互动作--三连拍姿势
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__INTERACTION_PHOTOTRIPPLEPOSTURE = 3019l
};

/// Constant 'POINT_HEAD'.
/**
  * 头部动作--点头
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__POINT_HEAD = 4001l
};

/// Constant 'SHAKE_HEAD'.
/**
  * 头部动作--摇头
 */
enum
{
  aimdk_msgs__msg__McPresetMotion__SHAKE_HEAD = 4002l
};

/// Struct defined in msg/McPresetMotion in the package aimdk_msgs.
/**
  * 预设动作
 */
typedef struct aimdk_msgs__msg__McPresetMotion
{
  int32_t value;
} aimdk_msgs__msg__McPresetMotion;

// Struct for a sequence of aimdk_msgs__msg__McPresetMotion.
typedef struct aimdk_msgs__msg__McPresetMotion__Sequence
{
  aimdk_msgs__msg__McPresetMotion * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McPresetMotion__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_PRESET_MOTION__STRUCT_H_
