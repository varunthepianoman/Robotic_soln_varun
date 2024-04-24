// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:srv/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__BUILDER_HPP_
#define CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_interfaces/srv/detail/sensor_read__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_SensorRead_Request_num_samples
{
public:
  Init_SensorRead_Request_num_samples()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interfaces::srv::SensorRead_Request num_samples(::custom_interfaces::srv::SensorRead_Request::_num_samples_type arg)
  {
    msg_.num_samples = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::SensorRead_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::SensorRead_Request>()
{
  return custom_interfaces::srv::builder::Init_SensorRead_Request_num_samples();
}

}  // namespace custom_interfaces


namespace custom_interfaces
{

namespace srv
{

namespace builder
{

class Init_SensorRead_Response_readings
{
public:
  Init_SensorRead_Response_readings()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interfaces::srv::SensorRead_Response readings(::custom_interfaces::srv::SensorRead_Response::_readings_type arg)
  {
    msg_.readings = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::srv::SensorRead_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::srv::SensorRead_Response>()
{
  return custom_interfaces::srv::builder::Init_SensorRead_Response_readings();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__BUILDER_HPP_
