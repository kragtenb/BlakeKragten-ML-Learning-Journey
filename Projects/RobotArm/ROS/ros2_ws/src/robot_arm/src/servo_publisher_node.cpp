#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

using namespace std::chrono_literals;

class ServoPublisher : public rclcpp::Node {
public:
    ServoPublisher()
    : Node("servo_publisher"), count_(0) {
        publisher_ = this->create_publisher<std_msgs::msg::Float64>("/elbow", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&ServoPublisher::publish_message, this));
    }

private:
    void publish_message() {
        auto message = std_msgs::msg::Float64();
        message.data = 45.0;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServoPublisher>());
    rclcpp::shutdown();
    return 0;
}
