#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Pose
from nav_msgs.msg import Odometry
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSDurabilityPolicy


class RelocalizationNode(Node):
    def __init__(self):
        super().__init__('relocalization_node')

        # /integrated_command subscriber requires TRANSIENT_LOCAL durability
        command_qos = QoSProfile(
            depth=10,
            durability=QoSDurabilityPolicy.TRANSIENT_LOCAL,
        )

        # Create publishers
        self.integrated_command_pub = self.create_publisher(
            String, '/integrated_command', command_qos)
        self.relocalization_pose_pub = self.create_publisher(
            Pose, '/relocalization_pose', 10)

        # Create subscriber with BEST_EFFORT QoS
        lidar_loc_qos = QoSProfile(
            depth=10,
            reliability=QoSReliabilityPolicy.BEST_EFFORT
        )

        self.odometry_sub = self.create_subscription(
            Odometry,
            '/slam/lidar_odom',
            self.odometry_callback,
            qos_profile=lidar_loc_qos
        )

        # Setup timer to publish messages in sequence
        self.success_received = False
        self.timeout_timer = None

        # Wait for subscribers before publishing
        self.publish_timer = self.create_timer(0.2, self.wait_and_publish)

    def wait_and_publish(self):
        if (self.integrated_command_pub.get_subscription_count() == 0 or
                self.relocalization_pose_pub.get_subscription_count() == 0):
            self.get_logger().info(
                f'Waiting for subscribers... '
                f'(command: {self.integrated_command_pub.get_subscription_count()}, '
                f'pose: {self.relocalization_pose_pub.get_subscription_count()})',
                throttle_duration_sec=2.0)
            return
        self.publish_timer.cancel()
        self.publish_sequence()

    def publish_sequence(self):
        # Publish integrated_command
        integrated_command_msg = String()
        integrated_command_msg.data = 'start_relocalization:1778133306741'
        self.integrated_command_pub.publish(integrated_command_msg)
        self.get_logger().info('Published integrated_command')

        # Schedule relocalization_pose publication after delay
        self.relocalization_pose_timer = self.create_timer(
            1.0,
            self.publish_relocalization_pose
        )

    def publish_relocalization_pose(self):
        # Cancel this timer immediately so it only fires once
        self.relocalization_pose_timer.cancel()

        relocalization_pose_msg = Pose()
        relocalization_pose_msg.position.x = 1041.0
        relocalization_pose_msg.position.y = 630.0
        relocalization_pose_msg.position.z = 0.0
        relocalization_pose_msg.orientation.x = 0.0
        relocalization_pose_msg.orientation.y = 0.0
        relocalization_pose_msg.orientation.z = 0.0
        relocalization_pose_msg.orientation.w = 1.0

        self.relocalization_pose_pub.publish(relocalization_pose_msg)
        self.get_logger().info('Published relocalization_pose')

        # Start timeout timer (30 seconds)
        self.timeout_timer = self.create_timer(
            30.0,
            self.timeout_callback
        )

        self.get_logger().info('Waiting for robot pose data (timeout: 30s)...')

    def odometry_callback(self, msg):
        if not self.success_received:
            self.success_received = True
            if self.timeout_timer is not None:
                self.timeout_timer.cancel()
            self.get_logger().info('Received odometry data - Relocalization successful!')
            if rclpy.ok():
                rclpy.shutdown()

    def timeout_callback(self):
        if not self.success_received:
            self.get_logger().error('Timeout reached - Relocalization failed!')
            if rclpy.ok():
                rclpy.shutdown()


def main(args=None):
    rclpy.init(args=args)
    node = RelocalizationNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
