// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from aimdk_msgs:msg/HandTouchSensorData.idl
// generated code does not contain a copyright notice

#ifndef AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__FUNCTIONS_H_
#define AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "aimdk_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "aimdk_msgs/msg/detail/hand_touch_sensor_data__struct.h"

/// Initialize msg/HandTouchSensorData message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * aimdk_msgs__msg__HandTouchSensorData
 * )) before or use
 * aimdk_msgs__msg__HandTouchSensorData__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__init(aimdk_msgs__msg__HandTouchSensorData * msg);

/// Finalize msg/HandTouchSensorData message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
void
aimdk_msgs__msg__HandTouchSensorData__fini(aimdk_msgs__msg__HandTouchSensorData * msg);

/// Create msg/HandTouchSensorData message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * aimdk_msgs__msg__HandTouchSensorData__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
aimdk_msgs__msg__HandTouchSensorData *
aimdk_msgs__msg__HandTouchSensorData__create();

/// Destroy msg/HandTouchSensorData message.
/**
 * It calls
 * aimdk_msgs__msg__HandTouchSensorData__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
void
aimdk_msgs__msg__HandTouchSensorData__destroy(aimdk_msgs__msg__HandTouchSensorData * msg);

/// Check for msg/HandTouchSensorData message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__are_equal(const aimdk_msgs__msg__HandTouchSensorData * lhs, const aimdk_msgs__msg__HandTouchSensorData * rhs);

/// Copy a msg/HandTouchSensorData message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__copy(
  const aimdk_msgs__msg__HandTouchSensorData * input,
  aimdk_msgs__msg__HandTouchSensorData * output);

/// Initialize array of msg/HandTouchSensorData messages.
/**
 * It allocates the memory for the number of elements and calls
 * aimdk_msgs__msg__HandTouchSensorData__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__init(aimdk_msgs__msg__HandTouchSensorData__Sequence * array, size_t size);

/// Finalize array of msg/HandTouchSensorData messages.
/**
 * It calls
 * aimdk_msgs__msg__HandTouchSensorData__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
void
aimdk_msgs__msg__HandTouchSensorData__Sequence__fini(aimdk_msgs__msg__HandTouchSensorData__Sequence * array);

/// Create array of msg/HandTouchSensorData messages.
/**
 * It allocates the memory for the array and calls
 * aimdk_msgs__msg__HandTouchSensorData__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
aimdk_msgs__msg__HandTouchSensorData__Sequence *
aimdk_msgs__msg__HandTouchSensorData__Sequence__create(size_t size);

/// Destroy array of msg/HandTouchSensorData messages.
/**
 * It calls
 * aimdk_msgs__msg__HandTouchSensorData__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
void
aimdk_msgs__msg__HandTouchSensorData__Sequence__destroy(aimdk_msgs__msg__HandTouchSensorData__Sequence * array);

/// Check for msg/HandTouchSensorData message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__are_equal(const aimdk_msgs__msg__HandTouchSensorData__Sequence * lhs, const aimdk_msgs__msg__HandTouchSensorData__Sequence * rhs);

/// Copy an array of msg/HandTouchSensorData messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_aimdk_msgs
bool
aimdk_msgs__msg__HandTouchSensorData__Sequence__copy(
  const aimdk_msgs__msg__HandTouchSensorData__Sequence * input,
  aimdk_msgs__msg__HandTouchSensorData__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AIMDK_MSGS__MSG__DETAIL__HAND_TOUCH_SENSOR_DATA__FUNCTIONS_H_
