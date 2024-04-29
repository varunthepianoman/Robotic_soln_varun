cmake_minimum_required(VERSION 3.8)
project(sensor_package_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# set(CMAKE_CXX_STANDARD 17) # Humble targets C++17.
# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
# find dependencies
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# Include Cpp "include" directory
include_directories(include)
# Create Cpp executable
add_executable(bringup_executable src/bringup_cpp.cpp)

ament_target_dependencies(bringup_executable rclcpp)
# Install Python modules
ament_python_install_package(${PROJECT_NAME})
# Install Python executables
install(PROGRAMS
  sensor_package_cpp/sensor_service.py
  sensor_package_cpp/sensor_client.py
  sensor_package_cpp/submodules/sensor.py
  DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install Cpp executables
install(TARGETS
  bringup_executable 
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
