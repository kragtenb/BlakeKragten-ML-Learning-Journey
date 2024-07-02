// servo_config.hpp
#ifndef SERVO_CONFIG_HPP
#define SERVO_CONFIG_HPP

#include <unordered_map>
#include <string>

const std::unordered_map<std::string, int> servo_gpio_map = {
    {"wrist_up_down", 26},
    {"hand", 25},
    {"elbow", 13},
    {"base", 12},
    {"wrist_rotation", 6},
    {"shoulder", 5}
};

#endif // SERVO_CONFIG_HPP
