#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <pigpio.h>
#include <chrono>
#include <unordered_map>
#include <functional>
#include "robot_arm/servo_config.hpp"

class MultiServoController : public rclcpp::Node {
public:
    MultiServoController()
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

        timer_ = this->create_wall_timer(
                std::chrono::milliseconds(1000),
                std::bind(&MultiServoController::timerCallback, this)
            );
    }

    ~MultiServoController() {
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
            gpioServo(topic_pin.second, pwm_value); 
        }
    }

    void adjustServo(int gpio_pin, double position) {
        // Convert position (typically 0.0 to 180.0 degrees) to PWM value
        int pwm_value = static_cast<int>((position / 180.0) * 2000 + 500); // Convert to range [500, 2500]

        if (pwm_value < 500.0) {
            pwm_value = 500.0;
        }

        if (pwm_value > 2500.0) {
            pwm_value = 2500.0;
        }

        RCLCPP_INFO(this->get_logger(), "Adjusting servo on GPIO %d to PWM value: %d", gpio_pin, pwm_value);
        gpioServo(gpio_pin, pwm_value); 

        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Ensure stable PWM signal 
    }

    void timerCallback() {
        RCLCPP_INFO(this->get_logger(), "Node Alive");
    }

    rclcpp::TimerBase::SharedPtr timer_;

    std::unordered_map<std::string, double> servo_init_position_;
    std::vector<rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr> subscribers_;

};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MultiServoController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
