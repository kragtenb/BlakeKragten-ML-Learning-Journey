// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interface:msg/ServoMotorStateChange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__BUILDER_HPP_
#define INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interface/msg/detail/servo_motor_state_change__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interface
{

namespace msg
{

namespace builder
{

class Init_ServoMotorStateChange_new_degree
{
public:
  explicit Init_ServoMotorStateChange_new_degree(::interface::msg::ServoMotorStateChange & msg)
  : msg_(msg)
  {}
  ::interface::msg::ServoMotorStateChange new_degree(::interface::msg::ServoMotorStateChange::_new_degree_type arg)
  {
    msg_.new_degree = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interface::msg::ServoMotorStateChange msg_;
};

class Init_ServoMotorStateChange_previous_degree
{
public:
  explicit Init_ServoMotorStateChange_previous_degree(::interface::msg::ServoMotorStateChange & msg)
  : msg_(msg)
  {}
  Init_ServoMotorStateChange_new_degree previous_degree(::interface::msg::ServoMotorStateChange::_previous_degree_type arg)
  {
    msg_.previous_degree = std::move(arg);
    return Init_ServoMotorStateChange_new_degree(msg_);
  }

private:
  ::interface::msg::ServoMotorStateChange msg_;
};

class Init_ServoMotorStateChange_name
{
public:
  Init_ServoMotorStateChange_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoMotorStateChange_previous_degree name(::interface::msg::ServoMotorStateChange::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_ServoMotorStateChange_previous_degree(msg_);
  }

private:
  ::interface::msg::ServoMotorStateChange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interface::msg::ServoMotorStateChange>()
{
  return interface::msg::builder::Init_ServoMotorStateChange_name();
}

}  // namespace interface

#endif  // INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__BUILDER_HPP_
