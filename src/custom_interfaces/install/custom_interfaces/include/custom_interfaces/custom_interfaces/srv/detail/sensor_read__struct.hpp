// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:srv/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_HPP_
#define CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__srv__SensorRead_Request __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__srv__SensorRead_Request __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SensorRead_Request_
{
  using Type = SensorRead_Request_<ContainerAllocator>;

  explicit SensorRead_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_samples = 0;
    }
  }

  explicit SensorRead_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_samples = 0;
    }
  }

  // field types and members
  using _num_samples_type =
    int8_t;
  _num_samples_type num_samples;

  // setters for named parameter idiom
  Type & set__num_samples(
    const int8_t & _arg)
  {
    this->num_samples = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__srv__SensorRead_Request
    std::shared_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__srv__SensorRead_Request
    std::shared_ptr<custom_interfaces::srv::SensorRead_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorRead_Request_ & other) const
  {
    if (this->num_samples != other.num_samples) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorRead_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorRead_Request_

// alias to use template instance with default allocator
using SensorRead_Request =
  custom_interfaces::srv::SensorRead_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace custom_interfaces


// Include directives for member types
// Member 'readings'
#include "custom_interfaces/msg/detail/sensor_sample__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__custom_interfaces__srv__SensorRead_Response __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__srv__SensorRead_Response __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SensorRead_Response_
{
  using Type = SensorRead_Response_<ContainerAllocator>;

  explicit SensorRead_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SensorRead_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _readings_type =
    rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample_<ContainerAllocator>, 8, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<custom_interfaces::msg::SensorSample_<ContainerAllocator>>>;
  _readings_type readings;

  // setters for named parameter idiom
  Type & set__readings(
    const rosidl_runtime_cpp::BoundedVector<custom_interfaces::msg::SensorSample_<ContainerAllocator>, 8, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<custom_interfaces::msg::SensorSample_<ContainerAllocator>>> & _arg)
  {
    this->readings = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__srv__SensorRead_Response
    std::shared_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__srv__SensorRead_Response
    std::shared_ptr<custom_interfaces::srv::SensorRead_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SensorRead_Response_ & other) const
  {
    if (this->readings != other.readings) {
      return false;
    }
    return true;
  }
  bool operator!=(const SensorRead_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SensorRead_Response_

// alias to use template instance with default allocator
using SensorRead_Response =
  custom_interfaces::srv::SensorRead_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace custom_interfaces

namespace custom_interfaces
{

namespace srv
{

struct SensorRead
{
  using Request = custom_interfaces::srv::SensorRead_Request;
  using Response = custom_interfaces::srv::SensorRead_Response;
};

}  // namespace srv

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__SENSOR_READ__STRUCT_HPP_
