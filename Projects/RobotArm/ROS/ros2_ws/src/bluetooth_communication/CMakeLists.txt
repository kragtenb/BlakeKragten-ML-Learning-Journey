find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)

install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
)

ament_python_install_package(${PROJECT_NAME})

install(
    PROGRAMS
    bluetooth_communication/bluetooth_node.py
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
