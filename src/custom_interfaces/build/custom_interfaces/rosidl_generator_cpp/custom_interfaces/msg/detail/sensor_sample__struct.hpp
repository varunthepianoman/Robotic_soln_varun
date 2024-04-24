// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/SensorSample.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SENSOR_SAMPLE__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__SENSOR_SAMPLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__SensorSample __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__SensorSample __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SensorSample_
{
  using Type = SensorSample_<ContainerAllocator>;

  explicit SensorSample_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->data.begin(), this->data.end(), 0.0);
    }
  }

  explicit SensorSample_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : data(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 6>::iterator, double>(this->data.begin(), this->data.end(), 0.0);
    }
  }

  // field types and members
  using _data_type =
    std::array<double, 6>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::array<double, 6> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::SensorSample_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::SensorSample_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SensorSample_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SensorSample_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__SensorSample
    std::shared_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__SensorSample
    std::shared_ptr<custom_interfaces::msg::SensorSample_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorSample_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorSample_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorSample_

// alias to use template instance with default allocator
using SensorSample =
  custom_interfaces::msg::SensorSample_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SENSOR_SAMPLE__STRUCT_HPP_
