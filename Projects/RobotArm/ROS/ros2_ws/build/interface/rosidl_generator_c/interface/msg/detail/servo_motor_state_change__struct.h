// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interface:msg/ServoMotorStateChange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__STRUCT_H_
#define INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__STRUCT_H_

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

/// Struct defined in msg/ServoMotorStateChange in the package interface.
/**
  * File: interface/msg/ServoMotorStateChange.msg
 */
typedef struct interface__msg__ServoMotorStateChange
{
  rosidl_runtime_c__String name;
  double previous_degree;
  double new_degree;
} interface__msg__ServoMotorStateChange;

// Struct for a sequence of interface__msg__ServoMotorStateChange.
typedef struct interface__msg__ServoMotorStateChange__Sequence
{
  interface__msg__ServoMotorStateChange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interface__msg__ServoMotorStateChange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__STRUCT_H_
