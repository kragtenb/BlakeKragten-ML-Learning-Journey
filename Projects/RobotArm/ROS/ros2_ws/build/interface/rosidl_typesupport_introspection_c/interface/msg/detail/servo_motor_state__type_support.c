// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from interface:msg/ServoMotorState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "interface/msg/detail/servo_motor_state__rosidl_typesupport_introspection_c.h"
#include "interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "interface/msg/detail/servo_motor_state__functions.h"
#include "interface/msg/detail/servo_motor_state__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  interface__msg__ServoMotorState__init(message_memory);
}

void interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_fini_function(void * message_memory)
{
  interface__msg__ServoMotorState__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_member_array[2] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(interface__msg__ServoMotorState, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "degree",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(interface__msg__ServoMotorState, degree),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_members = {
  "interface__msg",  // message namespace
  "ServoMotorState",  // message name
  2,  // number of fields
  sizeof(interface__msg__ServoMotorState),
  interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_member_array,  // message members
  interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_init_function,  // function to initialize message memory (memory has to be allocated)
  interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_type_support_handle = {
  0,
  &interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, interface, msg, ServoMotorState)() {
  if (!interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_type_support_handle.typesupport_identifier) {
    interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &interface__msg__ServoMotorState__rosidl_typesupport_introspection_c__ServoMotorState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
