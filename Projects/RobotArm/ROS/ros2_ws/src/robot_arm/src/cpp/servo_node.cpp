#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <pigpio.h>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <string>
#include "robot_arm/servo_config.hpp"
#include "interface/msg/servo_motor_state.hpp"
#include "interface/msg/servo_motor_state_change.hpp"

// This class will listen for servo motor changes and apply them to the corresponding motor
class ServoNode : public rclcpp::Node {
public:
    ServoNode()
    : Node("servo_node") {
        if (gpioInitialise() < 0) {
            RCLCPP_ERROR(this->get_logger(), "Failed to initialize GPIO");
            return;
        }

        servo_current_position_ = {
            {"wrist_up_down", 180.0},
            {"hand", 0.0},
            {"elbow", 180.0},
            {"base", 90.0},
            {"wrist_rotation", 80.0},
            {"shoulder", 130.0}
        };

        

        publisher_ = this->create_publisher<interface::msg::ServoMotorStateChange>("ServoMotorStateChange", 10);
        subscriber_ = this->create_subscription<interface::msg::ServoMotorState>("ServoMotorState", 10,
            [this](const interface::msg::ServoMotorState::SharedPtr msg) {
                this->servoMotoStateCallback(msg);
            }
        );
        
        init_position();
    }

    ~ServoNode() {
        gpioTerminate();
    }

private:
    void servoMotoStateCallback(const interface::msg::ServoMotorState::SharedPtr msg) {
        if (servo_current_position_.count(msg->name) == 0) {
            RCLCPP_INFO(this->get_logger(), "Invalid servo state change request seen. Servo %s is not found.", msg->name.c_str());
            return;
        }
        RCLCPP_INFO(this->get_logger(), "Received servo state update for %s: '%f'", msg->name.c_str(), msg->degree);
        adjustServo(msg->name, servo_gpio_map.at(msg->name), msg->degree);
    }

    void init_position() {
        for (const auto& topic_pin : servo_gpio_map) {
            // Set the PWM frequency to 50Hz for each servo pin. Set all to init position.
            if (gpioSetPWMfrequency(topic_pin.second, 50) != 50) {
                RCLCPP_ERROR(this->get_logger(), "Failed to set PWM frequency for GPIO %d", topic_pin.second);
            }
            adjustServo(topic_pin.first, topic_pin.second, servo_current_position_[topic_pin.first]); 
        }
    }

    void adjustServo(std::string servo_name, int gpio_pin, double position) {
        // Convert position (typically 0.0 to 180.0 degrees) to PWM value
        double previousPosition = servo_current_position_[servo_name];
        if (position < 0.0) {
            position = 0.0;
        }

        if (position > 180.0) {
            position = 180.0;
        }

        int pwm_value = static_cast<int>((position / 180.0) * 2000 + 500); // Convert to range [500, 2500]
        RCLCPP_INFO(this->get_logger(), "Adjusting servo %s to angle: %f", servo_name.c_str(), position);
        RCLCPP_INFO(this->get_logger(), "Adjusting servo on GPIO %d to PWM value: %d", gpio_pin, pwm_value);
        gpioServo(gpio_pin, pwm_value); 
        publish_servo_motor_state_change(servo_name, previousPosition, position);

        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Ensure stable PWM signal 
    }

    void publish_servo_motor_state_change(std::string servo_name, double previousValue, double newValue) {
        auto message = interface::msg::ServoMotorStateChange();
        message.name = servo_name;
        message.previous_degree = previousValue;
        message.new_degree = newValue;
        servo_current_position_[servo_name] = newValue;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s' from %f to %f degrees", message.name.c_str(), message.previous_degree, message.new_degree);
        publisher_->publish(message);
    }

    std::unordered_map<std::string, double> servo_current_position_;
    rclcpp::Publisher<interface::msg::ServoMotorStateChange>::SharedPtr publisher_;
    rclcpp::Subscription<interface::msg::ServoMotorState>::SharedPtr subscriber_;
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
