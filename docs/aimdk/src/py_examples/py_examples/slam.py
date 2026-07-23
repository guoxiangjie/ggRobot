import sys
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSDurabilityPolicy, QoSReliabilityPolicy
from std_msgs.msg import String


class SlamCommandPublisher(Node):
    def __init__(self):
        super().__init__('slam_command_publisher')
        qos = QoSProfile(
            depth=10,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
            reliability=QoSReliabilityPolicy.RELIABLE,
        )
        self.publisher_ = self.create_publisher(
            String, '/integrated_command', qos)

    def publish_start_mapping(self):
        msg = String()
        msg.data = 'start_mapping'
        self.get_logger().info(f'Publishing: "{msg.data}"')
        self.publisher_.publish(msg)

    def publish_stop_mapping(self, map_name):
        msg = String()
        msg.data = f'stop_mapping:{map_name}'
        self.get_logger().info(f'Publishing: "{msg.data}"')
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    slam_command_publisher = SlamCommandPublisher()

    try:
        while rclpy.ok():
            input_value = input(
                "Enter 1 to start mapping, 2 to stop mapping: ")

            if input_value == '1':
                slam_command_publisher.publish_start_mapping()
            elif input_value == '2':
                map_name = input("Enter map name: ")
                slam_command_publisher.publish_stop_mapping(map_name)
            else:
                print("Invalid input. Please enter 1 or 2.")
    except KeyboardInterrupt:
        pass
    finally:
        slam_command_publisher.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
