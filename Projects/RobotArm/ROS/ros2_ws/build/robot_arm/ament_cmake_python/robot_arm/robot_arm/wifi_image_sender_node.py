#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import socket
import struct
import pickle
import numpy as np
import threading
import time

class WifiImageSenderNode(Node):
    def __init__(self):
        super().__init__('wifi_image_sender_node')
        self.subscription = self.create_subscription(
            Image,
            '/camera/image',
            self.listener_callback,
            10
        )
        self.bridge = CvBridge()
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind(('0.0.0.0', 8000))
        self.server_socket.listen(1)
        self.get_logger().info('Waiting for a connection...')
        self.conn = None
        self.addr = None
        self.stop = False
        self.connection_thread = threading.Thread(target=self.accept_connections)
        self.connection_thread.daemon = True  # Make the thread a daemon thread
        self.connection_thread.start()

    def accept_connections(self):
        while not self.stop:
            try:
                self.conn, self.addr = self.server_socket.accept()
                self.get_logger().info(f'Connected by: {str(self.addr)}')
                # self.conn.settimeout(1.0)  # Set a timeout for the connection
                # while True:
                #     try:
                #         data = self.conn.recv(1024)  # Test if the connection is still alive
                #         if not data:
                #             raise ConnectionResetError
                #     except (socket.timeout, ConnectionResetError):
                #         self.get_logger().info('Connection lost. Waiting for a new connection...')
                #         self.conn = None
                #         break
            except Exception as e:
                self.get_logger().error(f'Error accepting connection: {str(e)}')
                time.sleep(1)

    def listener_callback(self, msg):
        if self.conn is None:
            return

        try:
            # Convert ROS Image message to OpenCV image
            frame = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            if frame is not None:
                self.send_frame(frame)
            else:
                self.get_logger().error('Received an empty frame.')
        except Exception as e:
            self.get_logger().error(f'Error converting image: {e}')

    def send_frame(self, frame):
        if self.conn is None:
            return

        try:
            # Encode frame as PNG
            _, buffer = cv2.imencode('.png', frame)
            # Serialize frame
            data = buffer.tobytes()
            size = len(data)
            
            # self.get_logger().info(f'Image size sent {str(size)}.')

            # Send 0x01 byte, size, and data
            self.conn.sendall(b'\x01' + struct.pack(">L", size) + data)
            # self.get_logger().info('Frame sent successfully.')
        except Exception as e:
            self.get_logger().error(f'Exception in send_frame: {str(e)}')
            self.conn = None  # Reset connection on error
            
    def destroy_node(self):
        self.get_logger().info('Node destroyed')
        self.conn.close()
        self.stop = True
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    image_sender = WifiImageSenderNode()
    try:
        rclpy.spin(image_sender)
    except KeyboardInterrupt:
        pass
    image_sender.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
