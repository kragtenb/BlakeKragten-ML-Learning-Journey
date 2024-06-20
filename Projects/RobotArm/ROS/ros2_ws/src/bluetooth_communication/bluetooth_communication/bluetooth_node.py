import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import bluetooth
from threading import Thread, Semaphore

class BluetoothNode(Node):
    def __init__(self):
        super().__init__('bluetooth_node')
        self.led_pin = 21
        self.connection = False
        self.script_end = False
        self.sem_send = Semaphore(0)
        self.sem_recv = Semaphore(0)
        
        self.server_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.port = bluetooth.PORT_ANY
        self.server_socket.bind(("", self.port))
        self.server_socket.listen(1)

        self.uuid = "00001101-0000-1000-8000-00805F9B34FB"  # Standard UUID for SPP
        bluetooth.advertise_service(self.server_socket, "BluetoothNodeServer",
                                    service_id=self.uuid,
                                    service_classes=[self.uuid, bluetooth.SERIAL_PORT_CLASS],
                                    profiles=[bluetooth.SERIAL_PORT_PROFILE])
        
        self.get_logger().info("Waiting for connection on RFCOMM channel %d" % self.port)
        self.client_socket, self.address = self.server_socket.accept()
        self.connection = True
        self.sem_recv.release()
        self.sem_send.release()
        self.get_logger().info("Accepted connection from %s" % str(self.address))
        
        self.recv_thread = Thread(target=self.recv)
        self.send_thread = Thread(target=self.send)
        
        self.recv_thread.daemon = True
        self.send_thread.daemon = True
        
        self.recv_thread.start()
        self.send_thread.start()
        
        self.send_pub = self.create_publisher(String, 'bluetooth_send', 10)
        self.recv_pub = self.create_publisher(String, 'bluetooth_recv', 10)
        self.recv_sub = self.create_subscription(String, 'bluetooth_send', self.send_callback, 10)
        
    def recv(self):
        self.sem_recv.acquire()
        while not self.script_end and rclpy.ok():
            data = self.client_socket.recv(1024)
            self.get_logger().info("Received: %s" % data)
            msg = String()
            msg.data = data.decode('utf-8')
            self.recv_pub.publish(msg)
            if data.decode('utf-8') == "q":
                self.get_logger().info("Quit")
                self.script_end = True
                break
        self.client_socket.close()
        self.server_socket.close()
        
    def send(self):
        self.sem_send.acquire()
        while not self.script_end and rclpy.ok():
            val = input()
            self.client_socket.send(str(val).encode('utf-8'))
        
    def send_callback(self, msg):
        self.client_socket.send(msg.data.encode('utf-8'))
        
def main(args=None):
    rclpy.init(args=args)
    node = BluetoothNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
