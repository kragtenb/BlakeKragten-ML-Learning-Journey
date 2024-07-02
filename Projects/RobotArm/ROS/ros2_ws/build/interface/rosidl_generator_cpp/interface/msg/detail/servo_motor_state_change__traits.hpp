// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interface:msg/ServoMotorStateChange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__TRAITS_HPP_
#define INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interface/msg/detail/servo_motor_state_change__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoMotorStateChange & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: previous_degree
  {
    out << "previous_degree: ";
    rosidl_generator_traits::value_to_yaml(msg.previous_degree, out);
    out << ", ";
  }

  // member: new_degree
  {
    out << "new_degree: ";
    rosidl_generator_traits::value_to_yaml(msg.new_degree, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoMotorStateChange & msg,
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

  // member: previous_degree
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "previous_degree: ";
    rosidl_generator_traits::value_to_yaml(msg.previous_degree, out);
    out << "\n";
  }

  // member: new_degree
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_degree: ";
    rosidl_generator_traits::value_to_yaml(msg.new_degree, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoMotorStateChange & msg, bool use_flow_style = false)
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

}  // namespace interface

namespace rosidl_generator_traits
{

[[deprecated("use interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interface::msg::ServoMotorStateChange & msg,
  std::ostream & out, size_t indentation = 0)
{
  interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const interface::msg::ServoMotorStateChange & msg)
{
  return interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<interface::msg::ServoMotorStateChange>()
{
  return "interface::msg::ServoMotorStateChange";
}

template<>
inline const char * name<interface::msg::ServoMotorStateChange>()
{
  return "interface/msg/ServoMotorStateChange";
}

template<>
struct has_fixed_size<interface::msg::ServoMotorStateChange>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<interface::msg::ServoMotorStateChange>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<interface::msg::ServoMotorStateChange>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTERFACE__MSG__DETAIL__SERVO_MOTOR_STATE_CHANGE__TRAITS_HPP_
