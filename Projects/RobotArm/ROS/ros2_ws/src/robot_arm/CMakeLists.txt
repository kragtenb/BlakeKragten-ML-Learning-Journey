cmake_minimum_required(VERSION 3.8)
project(robot_arm)

# Add the directory containing Findpigpio.cmake to CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH "~/pigpio-master/util" ${CMAKE_MODULE_PATH})


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(interface REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclpy REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED IMPORTED_TARGET dbus-1)

# Manually find and link libbluetooth
find_path(LIBBLUETOOTH_INCLUDE_DIR bluetooth/bluetooth.h)
find_library(LIBBLUETOOTH_LIBRARY bluetooth)

# Add the pigpio library
find_library(PIGPIO_LIBRARY pigpio REQUIRED)
find_path(PIGPIO_INCLUDE_DIR pigpio.h REQUIRED)

# Add the include directory to the include paths
include_directories(
  include
  ${PIGPIO_INCLUDE_DIR}
  ${LIBBLUETOOTH_INCLUDE_DIR}
)

add_executable(servo_node src/cpp/servo_node.cpp)
ament_target_dependencies(servo_node
  rclcpp
  std_msgs
  interface
)
target_link_libraries(servo_node ${PIGPIO_LIBRARY})

# Add the bluetooth_node executable
add_executable(bluetooth_node src/cpp/bluetooth_node.cpp)  
ament_target_dependencies(bluetooth_node
  rclcpp
  std_msgs
  interface
  sensor_msgs
  cv_bridge
  OpenCV
) # Add any other necessary dependencies

# Make sure to link libbluetooth library
if (LIBBLUETOOTH_INCLUDE_DIR AND LIBBLUETOOTH_LIBRARY)
    include_directories(${LIBBLUETOOTH_INCLUDE_DIR} ${DBUS_INCLUDE_DIRS})
    target_link_libraries(bluetooth_node ${LIBBLUETOOTH_LIBRARY} ${DBUS_LIBRARIES})
else()
    message(FATAL_ERROR "libbluetooth not found")
endif()

install(TARGETS
  servo_node
  bluetooth_node   # Add bluetooth_node to the installation
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
ament_python_install_package(${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  robot_arm/camera_node.py
  robot_arm/distance_node.py
  robot_arm/wifi_image_sender_node.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
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

ament_package()
