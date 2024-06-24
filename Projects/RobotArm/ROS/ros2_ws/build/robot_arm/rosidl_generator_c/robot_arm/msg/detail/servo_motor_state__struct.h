// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_arm:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_H_
#define ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ServoMotorState in the package robot_arm.
/**
  * File: robot_arm/msg/ServoMotorState.msg
 */
typedef struct robot_arm__msg__ServoMotorState
{
  rosidl_runtime_c__String name;
  float degree;
} robot_arm__msg__ServoMotorState;

// Struct for a sequence of robot_arm__msg__ServoMotorState.
typedef struct robot_arm__msg__ServoMotorState__Sequence
{
  robot_arm__msg__ServoMotorState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_arm__msg__ServoMotorState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_H_
