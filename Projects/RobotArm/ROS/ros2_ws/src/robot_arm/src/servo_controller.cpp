#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <pigpio.h>
#include <chrono>
#include <unordered_map>
#include <functional>
#include "robot_arm/servo_config.hpp"
#include "robot_arm/msg/servo_motor_state.hpp"

// This class will listen for servo motor changes and apply them to the corresponding motor
class ServoNode : public rclcpp::Node {
public:
    ServoNode()
    : Node("multi_servo_controller") {
        if (gpioInitialise() < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to initialize GPIO");
            return;
        }

        servo_init_position_ = {
            {"wrist_up_down", 180.0},
            {"hand", 0.0},
            {"elbow", 180.0},
            {"base", 90.0},
            {"wrist_rotation", 80.0},
            {"shoulder", 130.0}
        };

        publisher_ = this->create_publisher<robot_arm::msg::ServoMotorState>("", 0.0);
        
        init_position();

        // Create a subscriber for each servo topic
        for (const auto& topic_pin : servo_topics) {
            auto callback = [this, topic_pin](const std_msgs::msg::Float64::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "Received position for %s: '%f'", topic_pin.first.c_str(), msg->data);
                adjustServo(topic_pin.second, msg->data);
            };
            subscribers_.emplace_back(this->create_subscription<std_msgs::msg::Float64>(
                topic_pin.first, 10, callback));
        }
    }

    ~ServoNode() {
        gpioTerminate();
    }

private:
    void init_position() {
        for (const auto& topic_pin : servo_topics) {
            // Set the PWM frequency to 50Hz for each servo pin. Set all to init position.
            if (gpioSetPWMfrequency(topic_pin.second, 50) != 50) {
                RCLCPP_ERROR(this->get_logger(), "Failed to set PWM frequency for GPIO %d", topic_pin.second);
            }
            int pwm_value = static_cast<int>((servo_init_position_[topic_pin.first] / 180.0) * 2000 + 500); 
            gpioServo(topic_pin.first, topic_pin.second, pwm_value); 
        }
    }

    void adjustServo(string servo_name, int gpio_pin, double position) {
        // Convert position (typically 0.0 to 180.0 degrees) to PWM value
        if (position < 0.0) {
            position = 0.0
        }

        if (position > 180.0) {
            position = 180.0
        }

        int pwm_value = static_cast<int>((position / 180.0) * 2000 + 500); // Convert to range [500, 2500]
        RCLCPP_INFO(this->get_logger(), "Adjusting servo %s to PWM value: %d", servo_name, position);
        RCLCPP_INFO(this->get_logger(), "Adjusting servo on GPIO %d to PWM value: %d", gpio_pin, pwm_value);
        gpioServo(gpio_pin, pwm_value); 
        publish_servo_motor_state_change(servo_name, position)

        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Ensure stable PWM signal 
    }

    void publish_servo_motor_state_change(string servo_name, float32 value) {
        auto message = my_robot_msgs::msg::ServoMotorState(servo_name, value);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s' to %f degrees", message.name.c_str(), message.degree);
        publisher_->publish(message);
    }

    std::unordered_map<std::string, double> servo_init_position_;
    std::vector<rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr> subscribers_;
    std::unordered_map<std::string, rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr> servo_publishers_;
    rclcpp::Publisher<robot_arm::msg::ServoMotorState>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    // Initialize this node
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServoNode>();
    // Run the node. Code will sit here until the node has been stopped.
    rclcpp::spin(node);
    // Clean up the node.
    rclcpp::shutdown();
    return 0;
}
