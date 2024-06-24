// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_arm:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_
#define ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_arm/msg/detail/servo_motor_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_arm
{

namespace msg
{

namespace builder
{

class Init_ServoMotorState_degree
{
public:
  explicit Init_ServoMotorState_degree(::robot_arm::msg::ServoMotorState & msg)
  : msg_(msg)
  {}
  ::robot_arm::msg::ServoMotorState degree(::robot_arm::msg::ServoMotorState::_degree_type arg)
  {
    msg_.degree = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_arm::msg::ServoMotorState msg_;
};

class Init_ServoMotorState_name
{
public:
  Init_ServoMotorState_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoMotorState_degree name(::robot_arm::msg::ServoMotorState::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ServoMotorState_degree(msg_);
  }

private:
  ::robot_arm::msg::ServoMotorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_arm::msg::ServoMotorState>()
{
  return robot_arm::msg::builder::Init_ServoMotorState_name();
}

}  // namespace robot_arm

#endif  // ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_
