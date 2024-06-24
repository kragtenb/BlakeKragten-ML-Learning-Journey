// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from robot_arm:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "robot_arm/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "robot_arm/msg/detail/servo_motor_state__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace robot_arm
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_arm
cdr_serialize(
  const robot_arm::msg::ServoMotorState & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_arm
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  robot_arm::msg::ServoMotorState & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_arm
get_serialized_size(
  const robot_arm::msg::ServoMotorState & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_arm
max_serialized_size_ServoMotorState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace robot_arm

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_robot_arm
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_arm, msg, ServoMotorState)();

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
