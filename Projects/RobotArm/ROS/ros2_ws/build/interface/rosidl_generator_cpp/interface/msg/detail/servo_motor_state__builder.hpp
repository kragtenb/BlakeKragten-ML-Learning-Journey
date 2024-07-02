// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interface:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_
#define INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interface/msg/detail/servo_motor_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interface
{

namespace msg
{

namespace builder
{

class Init_ServoMotorState_degree
{
public:
  explicit Init_ServoMotorState_degree(::interface::msg::ServoMotorState & msg)
  : msg_(msg)
  {}
  ::interface::msg::ServoMotorState degree(::interface::msg::ServoMotorState::_degree_type arg)
  {
    msg_.degree = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interface::msg::ServoMotorState msg_;
};

class Init_ServoMotorState_name
{
public:
  Init_ServoMotorState_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoMotorState_degree name(::interface::msg::ServoMotorState::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ServoMotorState_degree(msg_);
  }

private:
  ::interface::msg::ServoMotorState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interface::msg::ServoMotorState>()
{
  return interface::msg::builder::Init_ServoMotorState_name();
}

}  // namespace interface

#endif  // INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE__BUILDER_HPP_
