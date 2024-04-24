// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:srv/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SensorRead in the package custom_interfaces.
typedef struct custom_interfaces__srv__SensorRead_Request
{
  /// Request params: Number of samples. An int between [1, 8].
  int8_t num_samples;
} custom_interfaces__srv__SensorRead_Request;

// Struct for a sequence of custom_interfaces__srv__SensorRead_Request.
typedef struct custom_interfaces__srv__SensorRead_Request__Sequence
{
  custom_interfaces__srv__SensorRead_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__SensorRead_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'readings'
#include "custom_interfaces/msg/detail/sensor_sample__struct.h"

// constants for array fields with an upper bound
// readings
enum
{
  custom_interfaces__srv__SensorRead_Response__readings__MAX_SIZE = 8
};

/// Struct defined in srv/SensorRead in the package custom_interfaces.
typedef struct custom_interfaces__srv__SensorRead_Response
{
  custom_interfaces__msg__SensorSample__Sequence readings;
} custom_interfaces__srv__SensorRead_Response;

// Struct for a sequence of custom_interfaces__srv__SensorRead_Response.
typedef struct custom_interfaces__srv__SensorRead_Response__Sequence
{
  custom_interfaces__srv__SensorRead_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__SensorRead_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_H_
