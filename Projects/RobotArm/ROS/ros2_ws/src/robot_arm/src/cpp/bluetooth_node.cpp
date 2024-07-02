#include <rclcpp/rclcpp.hpp>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <std_msgs/msg/float32.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <dbus/dbus.h>
#include "robot_arm/servo_config.hpp"
#include <atomic>
#include <thread>
#include <unordered_map>
#include "interface/msg/servo_motor_state.hpp"

#define IMAGE_MSG 0x01
#define DISTANCE_MSG 0x02

// ROS Node responsible for setting up an RFCOMM server and routing servo  bluetooth messages to the servo node
class BluetoothNode : public rclcpp::Node {
public:
    // Initalization of the bluetooth node
    BluetoothNode() : Node("bluetooth_node"), stop_flag(false) {
        RCLCPP_INFO(this->get_logger(), "Bluetooth node started.");
        // Create publishers to publish servo changes to each servo
        servo_publisher_ = this->create_publisher<interface::msg::ServoMotorState>("ServoMotorState", 10);
        distance_subscriber_ = this->create_subscription<std_msgs::msg::Float32>("/sensor/ultrasonic", 10, [this](std_msgs::msg::Float32 msg) {
            this->distanceSubscriptionCallback(msg);
        });
        // Setup RFCOMM server
        initializeBluetooth();
        // Create a subsequent thread to listen for connections after bluetooth server has been setup
        listen_thread_ = std::thread(&BluetoothNode::listenForConnections, this); // Start the listening thread
        // TODO: Add a thread montor task that checks if stop_flag is true and force the listenForConnections thread to stop
    }

    ~BluetoothNode() {
        stop_flag = true; // Signal the thread to stop
        if (listen_thread_.joinable()) {
            listen_thread_.join();
        }
        if (sock_fd >= 0) {
            close(sock_fd);
        }
        RCLCPP_INFO(this->get_logger(), "Bluetooth node stopped.");
    }

private:
    int sock_fd = -1, client_fd = -1;
    struct sockaddr_rc rem_addr = { 0 };
    char buf[1024] = { 0 };
    socklen_t opt = sizeof(rem_addr);
    std::thread listen_thread_;
    std::atomic<bool> stop_flag;
    rclcpp::Publisher<interface::msg::ServoMotorState>::SharedPtr servo_publisher_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr distance_subscriber_;

    void initializeBluetooth() {
        // Get our bluetooth device id
        int dev_id = hci_get_route(NULL);
        if (dev_id < 0) {
            RCLCPP_ERROR(this->get_logger(), "Error getting Bluetooth device ID");
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Bluetooth device ID: %d", dev_id);

        // Set device to discoverable
        if (!makeDeviceDiscoverable(dev_id)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to set device to discoverable mode");
            close(sock_fd);
            return;
        }

        struct sockaddr_rc local_addr = { 0 };
        bdaddr_t bdaddr_any =  {{0, 0, 0, 0, 0, 0}};
        // Create socket for connection
        sock_fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (sock_fd == -1) {
            perror("socket");
            return;
        }

        // Allow for address reuse
        int reuse = 1;
        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
            perror("setsockopt");
            close(sock_fd);
            return;
        }

        local_addr.rc_family = AF_BLUETOOTH;
        local_addr.rc_bdaddr = bdaddr_any;
        local_addr.rc_channel = (uint8_t) 1; // RFCOMM channel 1

        // Bind the socket to the corresponding address
        if (bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
            perror("bind");
            RCLCPP_ERROR(this->get_logger(), "bind failed");
            close(sock_fd);
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Bluetooth socket bound");

        // set the server to listen for connections.
        if (listen(sock_fd, 1) < 0) { // Listen for 1 connection
            RCLCPP_ERROR(this->get_logger(), "Error listening on socket");
            close(sock_fd);
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Listening for Bluetooth connections...");
    }

    bool makeDeviceDiscoverable(int dev_id) {
        int ctl = hci_open_dev(dev_id);
        if (ctl < 0) {
            RCLCPP_ERROR(this->get_logger(), "Could not open HCI device.");
            return false;
        }

        uint8_t scan_enable = 0x03; // 0x03 to enable both inquiry and page scan
        int ret = hci_send_cmd(ctl, OGF_HOST_CTL, OCF_WRITE_SCAN_ENABLE, 1, (void *)&scan_enable);
        close(ctl);

        if (ret < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to set HCI device scan enable.");
            return false;
        }

        RCLCPP_INFO(this->get_logger(), "Device is now discoverable.");
        return true;
    }

    void listenForConnections() {
        // While our node is still active we should listen for connections.
        while (rclcpp::ok() && !stop_flag.load()) { // Check for node shutdown and stop flag
            // Server will sit on accept until a connection has been made.
            client_fd = accept(sock_fd, (struct sockaddr *)&rem_addr, &opt);
            if (client_fd < 0) {
                if (stop_flag.load()) break; // Exit if stopping
                RCLCPP_ERROR(this->get_logger(), "Error accepting connection");
                continue; // Continue listening for new connections
            }

            char address[18];
            ba2str(&rem_addr.rc_bdaddr, address);
            RCLCPP_INFO(this->get_logger(), "Accepted connection from %s", address);

            while (rclcpp::ok() && !stop_flag.load()) {
                // Read the next available message
                ssize_t bytes_read = read(client_fd, buf, sizeof(buf) - 1); 
                if (bytes_read > 0) {
                    buf[bytes_read] = '\0'; // Null-terminate the string
                    std::string message(buf);
                    std::string servo_name;
                    double angle;
                    std::istringstream iss(message); 

                    if (!(iss >> servo_name)) {
                        RCLCPP_ERROR(this->get_logger(), "Error parsing servo name");
                        continue;
                    }

                    if (!(iss >> angle)) {
                        RCLCPP_ERROR(this->get_logger(), "Error parsing angle");
                        continue;
                    }

                    // publish the servo change message for the specified servo.
                    if (servo_gpio_map.count(servo_name) > 0) {
                        auto msg = interface::msg::ServoMotorState();
                        msg.name = servo_name;
                        msg.degree = angle;
                        servo_publisher_->publish(msg);
                        RCLCPP_INFO(this->get_logger(), "Published command for %s: '%f' angle", servo_name.c_str(), angle);
                    }
                } else if (bytes_read == 0) {
                    RCLCPP_INFO(this->get_logger(), "Client disconnected");
                    close(client_fd);
                    break;
                } else {
                    perror("read");
                    RCLCPP_ERROR(this->get_logger(), "Error reading from client");
                    close(client_fd);
                    break;
                }
            }
        }
        close(sock_fd);
    }

    void distanceSubscriptionCallback(std_msgs::msg::Float32 msg) {
        if (client_fd < 0) {
             return;
        }
        float distance = msg.data;

        uint8_t messageType = DISTANCE_MSG;
        send(client_fd, &messageType, 1, 0);

        uint8_t distanceBytes[4];
        uint32_t distanceInt = *reinterpret_cast<uint32_t*>(&distance);
        distanceBytes[0] = (distanceInt >> 24) & 0xFF;
        distanceBytes[1] = (distanceInt >> 16) & 0xFF;
        distanceBytes[2] = (distanceInt >> 8) & 0xFF;
        distanceBytes[3] = distanceInt & 0xFF;
        send(client_fd, distanceBytes, 4, 0);
    }
};

int main(int argc, char* argv[]) {
    // Initialize this node
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BluetoothNode>();
    // Run the node. Code will sit here until the node has been stopped.
    rclcpp::spin(node);
    // Clean up the node.
    rclcpp::shutdown();
    return 0;
}
