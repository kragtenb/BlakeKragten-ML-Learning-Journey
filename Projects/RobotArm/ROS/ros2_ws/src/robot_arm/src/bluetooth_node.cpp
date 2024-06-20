#include <rclcpp/rclcpp.hpp>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <std_msgs/msg/float64.hpp>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <dbus/dbus.h>
#include "robot_arm/servo_config.hpp"
#include <atomic>
#include <thread>
#include <unordered_map>

class BluetoothNode : public rclcpp::Node {
public:
    BluetoothNode() : Node("bluetooth_node"), stop_flag(false) {
        RCLCPP_INFO(this->get_logger(), "Bluetooth node started.");
        for (const auto& topic : servo_topics) {
            servo_publishers_[topic.first] = 
                this->create_publisher<std_msgs::msg::Float64>("/" + topic.first, 10);
        }
        initializeBluetooth();
        listen_thread_ = std::thread(&BluetoothNode::listenForConnections, this); // Start the listening thread
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
    int sock_fd = -1, client_sock = -1;
    struct sockaddr_rc rem_addr = { 0 };
    char buf[1024] = { 0 };
    socklen_t opt = sizeof(rem_addr);
    std::thread listen_thread_;
    std::atomic<bool> stop_flag;
    std::unordered_map<std::string, rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr> servo_publishers_;

    void initializeBluetooth() {
        int dev_id = hci_get_route(NULL);
        if (dev_id < 0) {
            RCLCPP_ERROR(this->get_logger(), "Error getting Bluetooth device ID");
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Bluetooth device ID: %d", dev_id);

        if (!makeDeviceDiscoverable(dev_id)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to set device to discoverable mode");
            close(sock_fd);
            return;
        }

        struct sockaddr_rc local_addr = { 0 };
        bdaddr_t bdaddr_any =  {{0, 0, 0, 0, 0, 0}};
        sock_fd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        if (sock_fd == -1) {
            perror("socket");
            return;
        }

        int reuse = 1;
        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
            perror("setsockopt");
            close(sock_fd);
            return;
        }

        local_addr.rc_family = AF_BLUETOOTH;
        local_addr.rc_bdaddr = bdaddr_any;
        local_addr.rc_channel = (uint8_t) 1; // RFCOMM channel 1

        if (bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) == -1) {
            perror("bind");
            RCLCPP_ERROR(this->get_logger(), "bind failed");
            close(sock_fd);
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Bluetooth socket bound");

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
        while (rclcpp::ok() && !stop_flag.load()) { // Check for node shutdown and stop flag
            int client_fd = accept(sock_fd, (struct sockaddr *)&rem_addr, &opt);
            if (client_fd < 0) {
                if (stop_flag.load()) break; // Exit if stopping
                RCLCPP_ERROR(this->get_logger(), "Error accepting connection");
                continue; // Continue listening for new connections
            }

            char address[18];
            ba2str(&rem_addr.rc_bdaddr, address);
            RCLCPP_INFO(this->get_logger(), "Accepted connection from %s", address);

            while (rclcpp::ok() && !stop_flag.load()) {
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

                    if (servo_publishers_.count(servo_name) > 0) {
                        auto msg = std_msgs::msg::Float64();
                        msg.data = angle;
                        servo_publishers_[servo_name]->publish(msg);
                        RCLCPP_INFO(this->get_logger(), "Published command for %s: '%f'", servo_name.c_str(), angle);
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
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BluetoothNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
