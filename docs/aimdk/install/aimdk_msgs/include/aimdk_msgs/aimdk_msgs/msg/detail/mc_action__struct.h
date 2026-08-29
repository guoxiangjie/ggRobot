// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from aimdk_msgs:msg/McAction.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_H_
#define AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PASSIVE_DEFAULT'.
/**
  * 被动模式
 */
enum
{
  aimdk_msgs__msg__McAction__PASSIVE_DEFAULT = 1l
};

/// Constant 'SOFT_EMERGENCY_STOP'.
/**
  * 软急停
 */
enum
{
  aimdk_msgs__msg__McAction__SOFT_EMERGENCY_STOP = 2l
};

/// Constant 'DAMPING_DEFAULT'.
/**
  * 阻尼模式
 */
enum
{
  aimdk_msgs__msg__McAction__DAMPING_DEFAULT = 3l
};

/// Constant 'ZERO_TORQUE_DEFAULT'.
/**
  * 零力矩模式
 */
enum
{
  aimdk_msgs__msg__McAction__ZERO_TORQUE_DEFAULT = 4l
};

/// Constant 'JOINT_DEFAULT'.
/**
  * 位控站立模式
 */
enum
{
  aimdk_msgs__msg__McAction__JOINT_DEFAULT = 100l
};

/// Constant 'JOINT_FREEZE'.
/**
  * 位控关节锁定模式
 */
enum
{
  aimdk_msgs__msg__McAction__JOINT_FREEZE = 101l
};

/// Constant 'STAND_DEFAULT'.
/**
  * 力控站立模式
 */
enum
{
  aimdk_msgs__msg__McAction__STAND_DEFAULT = 200l
};

/// Constant 'STAND_BODY_CONTROL'.
/**
  * 站立+身体运动模式
 */
enum
{
  aimdk_msgs__msg__McAction__STAND_BODY_CONTROL = 201l
};

/// Constant 'LOCOMOTION_DEFAULT'.
/**
  * 行走模式
 */
enum
{
  aimdk_msgs__msg__McAction__LOCOMOTION_DEFAULT = 300l
};

/// Constant 'RUN_DEFAULT'.
/**
  * 跑步模式
 */
enum
{
  aimdk_msgs__msg__McAction__RUN_DEFAULT = 301l
};

/// Constant 'LOCOMOTION_STEP'.
/**
  * 越野模式
 */
enum
{
  aimdk_msgs__msg__McAction__LOCOMOTION_STEP = 302l
};

/// Constant 'VR_REMOTE_CONTROLLER'.
/**
  * VR遥操模式
 */
enum
{
  aimdk_msgs__msg__McAction__VR_REMOTE_CONTROLLER = 400l
};

/// Constant 'SIT_DOWN_DEFAULT'.
/**
  * 技能类
  * 坐下
 */
enum
{
  aimdk_msgs__msg__McAction__SIT_DOWN_DEFAULT = 2000l
};

/// Constant 'CROUCH_DOWN_DEFAULT'.
/**
  * 蹲下
 */
enum
{
  aimdk_msgs__msg__McAction__CROUCH_DOWN_DEFAULT = 2002l
};

/// Constant 'LIE_DOWN_DEFAULT'.
/**
  * 躺倒
 */
enum
{
  aimdk_msgs__msg__McAction__LIE_DOWN_DEFAULT = 2004l
};

/// Constant 'STAND_UP_DEFAULT'.
/**
  * 平躺站起
 */
enum
{
  aimdk_msgs__msg__McAction__STAND_UP_DEFAULT = 2005l
};

/// Constant 'ASCEND_STAIRS'.
/**
  * 上楼梯
 */
enum
{
  aimdk_msgs__msg__McAction__ASCEND_STAIRS = 2006l
};

/// Constant 'DESCEND_STAIRS'.
/**
  * 下楼梯
 */
enum
{
  aimdk_msgs__msg__McAction__DESCEND_STAIRS = 2008l
};

/// Struct defined in msg/McAction in the package aimdk_msgs.
/**
  * 定义枚举字段
 */
typedef struct aimdk_msgs__msg__McAction
{
  int32_t value;
} aimdk_msgs__msg__McAction;

// Struct for a sequence of aimdk_msgs__msg__McAction.
typedef struct aimdk_msgs__msg__McAction__Sequence
{
  aimdk_msgs__msg__McAction * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} aimdk_msgs__msg__McAction__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__MC_ACTION__STRUCT_H_
