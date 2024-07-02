#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import RPi.GPIO as GPIO
import time

class DistanceNode(Node):

    def __init__(self):
        super().__init__("distance_node")
        self.publisher = self.create_publisher(Float32, '/sensor/ultrasonic', 10)

        # Initialize GPIO
        self.TRIG = 23
        self.ECHO = 24
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.TRIG, GPIO.OUT)
        GPIO.setup(self.ECHO, GPIO.IN)

        # Start with the trigger set to low
        GPIO.output(self.TRIG, False)
        self.get_logger().info("Waiting for sensor to settle")
        time.sleep(2)

        # Create a timer to call the timer_callback function at 30Hz
        self.timer = self.create_timer(1/30, self.timer_callback)

    def timer_callback(self):
        
        # Send a 10us pulse to trigger the sensor
        GPIO.output(self.TRIG, True)
        time.sleep(0.00001)  # 10 microseconds
        GPIO.output(self.TRIG, False)

        # Measure the time the echo is received with timeout
        pulse_start = None
        timeout_start = time.time()

        while GPIO.input(self.ECHO) == 0:
            pulse_start = time.time()
            if pulse_start - timeout_start > 0.01:  # 10 ms timeout
                self.get_logger().error("Timeout waiting for ECHO to go high")
                return

        pulse_end = None
        timeout_start = time.time()

        while GPIO.input(self.ECHO) == 1:
            pulse_end = time.time()
            if pulse_end - timeout_start > 0.01:  # 10 ms timeout
                self.get_logger().error("Timeout waiting for ECHO to go low")
                return

        if pulse_start is not None and pulse_end is not None:
            # Calculate the pulse duration
            pulse_duration = pulse_end - pulse_start
            # Calculate the distance (pulse_duration * speed of sound / 2)
            distance = pulse_duration * 17150
            distance = round(distance, 1)

            # Publish the distance
            distance_msg = Float32()
            distance_msg.data = distance
            self.publisher.publish(distance_msg)
            # self.get_logger().info(f"Published distance: {distance} cm")
        else:
            self.get_logger().error("Failed to get a valid pulse start and end")

    def destroy_node(self):
        GPIO.cleanup()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = DistanceNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
