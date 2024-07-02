// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from interface:msg/ServoMotorState.idl
// generated code does not contain a copyright notice
#include "interface/msg/detail/servo_motor_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
interface__msg__ServoMotorState__init(interface__msg__ServoMotorState * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    interface__msg__ServoMotorState__fini(msg);
    return false;
  }
  // degree
  return true;
}

void
interface__msg__ServoMotorState__fini(interface__msg__ServoMotorState * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // degree
}

bool
interface__msg__ServoMotorState__are_equal(const interface__msg__ServoMotorState * lhs, const interface__msg__ServoMotorState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // degree
  if (lhs->degree != rhs->degree) {
    return false;
  }
  return true;
}

bool
interface__msg__ServoMotorState__copy(
  const interface__msg__ServoMotorState * input,
  interface__msg__ServoMotorState * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // degree
  output->degree = input->degree;
  return true;
}

interface__msg__ServoMotorState *
interface__msg__ServoMotorState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interface__msg__ServoMotorState * msg = (interface__msg__ServoMotorState *)allocator.allocate(sizeof(interface__msg__ServoMotorState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(interface__msg__ServoMotorState));
  bool success = interface__msg__ServoMotorState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
interface__msg__ServoMotorState__destroy(interface__msg__ServoMotorState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    interface__msg__ServoMotorState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
interface__msg__ServoMotorState__Sequence__init(interface__msg__ServoMotorState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interface__msg__ServoMotorState * data = NULL;

  if (size) {
    data = (interface__msg__ServoMotorState *)allocator.zero_allocate(size, sizeof(interface__msg__ServoMotorState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = interface__msg__ServoMotorState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        interface__msg__ServoMotorState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
interface__msg__ServoMotorState__Sequence__fini(interface__msg__ServoMotorState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      interface__msg__ServoMotorState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

interface__msg__ServoMotorState__Sequence *
interface__msg__ServoMotorState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interface__msg__ServoMotorState__Sequence * array = (interface__msg__ServoMotorState__Sequence *)allocator.allocate(sizeof(interface__msg__ServoMotorState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = interface__msg__ServoMotorState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
interface__msg__ServoMotorState__Sequence__destroy(interface__msg__ServoMotorState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    interface__msg__ServoMotorState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
interface__msg__ServoMotorState__Sequence__are_equal(const interface__msg__ServoMotorState__Sequence * lhs, const interface__msg__ServoMotorState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!interface__msg__ServoMotorState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
interface__msg__ServoMotorState__Sequence__copy(
  const interface__msg__ServoMotorState__Sequence * input,
  interface__msg__ServoMotorState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(interface__msg__ServoMotorState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    interface__msg__ServoMotorState * data =
      (interface__msg__ServoMotorState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!interface__msg__ServoMotorState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          interface__msg__ServoMotorState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!interface__msg__ServoMotorState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
