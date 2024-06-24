// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_arm:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__TRAITS_HPP_
#define ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_arm/msg/detail/servo_motor_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_arm
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoMotorState & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: degree
  {
    out << "degree: ";
    rosidl_generator_traits::value_to_yaml(msg.degree, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoMotorState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: degree
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "degree: ";
    rosidl_generator_traits::value_to_yaml(msg.degree, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoMotorState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_arm

namespace rosidl_generator_traits
{

[[deprecated("use robot_arm::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_arm::msg::ServoMotorState & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_arm::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_arm::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_arm::msg::ServoMotorState & msg)
{
  return robot_arm::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_arm::msg::ServoMotorState>()
{
  return "robot_arm::msg::ServoMotorState";
}

template<>
inline const char * name<robot_arm::msg::ServoMotorState>()
{
  return "robot_arm/msg/ServoMotorState";
}

template<>
struct has_fixed_size<robot_arm::msg::ServoMotorState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_arm::msg::ServoMotorState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_arm::msg::ServoMotorState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__TRAITS_HPP_
