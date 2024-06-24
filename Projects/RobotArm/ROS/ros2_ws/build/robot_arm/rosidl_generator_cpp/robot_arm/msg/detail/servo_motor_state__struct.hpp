// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_arm:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_HPP_
#define ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_arm__msg__ServoMotorState __attribute__((deprecated))
#else
# define DEPRECATED__robot_arm__msg__ServoMotorState __declspec(deprecated)
#endif

namespace robot_arm
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoMotorState_
{
  using Type = ServoMotorState_<ContainerAllocator>;

  explicit ServoMotorState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->degree = 0.0f;
    }
  }

  explicit ServoMotorState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->degree = 0.0f;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _degree_type =
    float;
  _degree_type degree;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__degree(
    const float & _arg)
  {
    this->degree = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_arm::msg::ServoMotorState_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_arm::msg::ServoMotorState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_arm::msg::ServoMotorState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_arm::msg::ServoMotorState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_arm__msg__ServoMotorState
    std::shared_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_arm__msg__ServoMotorState
    std::shared_ptr<robot_arm::msg::ServoMotorState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoMotorState_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->degree != other.degree) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoMotorState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoMotorState_

// alias to use template instance with default allocator
using ServoMotorState =
  robot_arm::msg::ServoMotorState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_arm

#endif  // ROBOT_ARM__MSG__DETAIL__SERVO_MOTOR_STATE__STRUCT_HPP_
