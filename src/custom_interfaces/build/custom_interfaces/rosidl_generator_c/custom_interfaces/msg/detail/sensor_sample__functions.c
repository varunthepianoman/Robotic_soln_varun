// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces:msg/SensorSample.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/msg/detail/sensor_sample__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
custom_interfaces__msg__SensorSample__init(custom_interfaces__msg__SensorSample * msg)
{
  if (!msg) {
    return false;
  }
  // data
  return true;
}

void
custom_interfaces__msg__SensorSample__fini(custom_interfaces__msg__SensorSample * msg)
{
  if (!msg) {
    return;
  }
  // data
}

bool
custom_interfaces__msg__SensorSample__are_equal(const custom_interfaces__msg__SensorSample * lhs, const custom_interfaces__msg__SensorSample * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  for (size_t i = 0; i < 6; ++i) {
    if (lhs->data[i] != rhs->data[i]) {
      return false;
    }
  }
  return true;
}

bool
custom_interfaces__msg__SensorSample__copy(
  const custom_interfaces__msg__SensorSample * input,
  custom_interfaces__msg__SensorSample * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  for (size_t i = 0; i < 6; ++i) {
    output->data[i] = input->data[i];
  }
  return true;
}

custom_interfaces__msg__SensorSample *
custom_interfaces__msg__SensorSample__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__SensorSample * msg = (custom_interfaces__msg__SensorSample *)allocator.allocate(sizeof(custom_interfaces__msg__SensorSample), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__msg__SensorSample));
  bool success = custom_interfaces__msg__SensorSample__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__msg__SensorSample__destroy(custom_interfaces__msg__SensorSample * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_interfaces__msg__SensorSample__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_interfaces__msg__SensorSample__Sequence__init(custom_interfaces__msg__SensorSample__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__SensorSample * data = NULL;

  if (size) {
    data = (custom_interfaces__msg__SensorSample *)allocator.zero_allocate(size, sizeof(custom_interfaces__msg__SensorSample), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__msg__SensorSample__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__msg__SensorSample__fini(&data[i - 1]);
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
custom_interfaces__msg__SensorSample__Sequence__fini(custom_interfaces__msg__SensorSample__Sequence * array)
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
      custom_interfaces__msg__SensorSample__fini(&array->data[i]);
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

custom_interfaces__msg__SensorSample__Sequence *
custom_interfaces__msg__SensorSample__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_interfaces__msg__SensorSample__Sequence * array = (custom_interfaces__msg__SensorSample__Sequence *)allocator.allocate(sizeof(custom_interfaces__msg__SensorSample__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__msg__SensorSample__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_interfaces__msg__SensorSample__Sequence__destroy(custom_interfaces__msg__SensorSample__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_interfaces__msg__SensorSample__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_interfaces__msg__SensorSample__Sequence__are_equal(const custom_interfaces__msg__SensorSample__Sequence * lhs, const custom_interfaces__msg__SensorSample__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_interfaces__msg__SensorSample__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_interfaces__msg__SensorSample__Sequence__copy(
  const custom_interfaces__msg__SensorSample__Sequence * input,
  custom_interfaces__msg__SensorSample__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_interfaces__msg__SensorSample);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_interfaces__msg__SensorSample * data =
      (custom_interfaces__msg__SensorSample *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_interfaces__msg__SensorSample__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_interfaces__msg__SensorSample__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_interfaces__msg__SensorSample__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
