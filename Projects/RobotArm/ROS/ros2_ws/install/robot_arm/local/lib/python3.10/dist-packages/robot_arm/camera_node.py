#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

class CameraNode(Node):

    def __init__(self):
        super().__init__("camera_node")
        self.publisher = self.create_publisher(Image, '/camera/image', 10)
        
        self.bridge = CvBridge()
        
        # Initialize OpenCV VideoCapture
        self.cap = cv2.VideoCapture(0)  # 0 is the index of the camera
        
        if not self.cap.isOpened():
            self.get_logger().error("Failed to open camera")
            return
        
        self.timer = self.create_timer(1/30, self.capture_and_publish_camera_feed)  # Timer for looping to do 30fps
        
    def capture_and_publish_camera_feed(self):
        ret, frame = self.cap.read()
        if not ret:
            self.get_logger().error("Failed to capture image")
            return
        
        cv2.imwrite('/tmp/captured_frame.jpg', frame)  # Save the frame to a file
        image_message = self.bridge.cv2_to_imgmsg(frame, "bgr8")
        self.publisher.publish(image_message)
        # self.get_logger().info(f"Published image frame.")
        
    def destroy_node(self):
        self.get_logger().info(f"Node destroyed.")
        self.cap.release()
        super().destroy_node()
        
        
def main(args=None):
    rclpy.init(args=args)
    node = CameraNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()
    
if __name__ == '__main__':
    main()
