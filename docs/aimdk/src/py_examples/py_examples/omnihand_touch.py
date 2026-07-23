#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
from aimdk_msgs.msg import HandStateArray, HandCommandArray
import time


class HandStateSubscriber(Node):
    def __init__(self):
        super().__init__('hand_state_subscriber')

        # Create publisher
        self.publisher_ = self.create_publisher(
            HandCommandArray,
            '/aima/hal/joint/hand/command',
            10
        )

        # Create QoS profile with BEST_EFFORT reliability
        qos_profile = QoSProfile(depth=10)
        qos_profile.reliability = ReliabilityPolicy.BEST_EFFORT

        # Create subscriber
        self.subscription = self.create_subscription(
            HandStateArray,
            '/aima/hal/joint/hand/state',
            self.topic_callback,
            qos_profile
        )

        # Create a timer to publish once per second
        self.timer = self.create_timer(1.0, self.publish_command)

        self.get_logger().info(
            "Subscriber started, listening to /aima/hal/joint/hand/state topic..."
        )

    def topic_callback(self, msg):
        """Callback function for handling incoming messages"""
        # Print message header information
        self.get_logger().info(
            f"Message received - Sequence: {msg.header.sequence}, "
            f"Timestamp: {msg.header.stamp.sec}.{msg.header.stamp.nanosec:09d}"
        )

        # Print left hand touch sensor data
        self.print_touch_sensor_data("Left Hand", msg.left_touch_sensors)

        # Print right hand touch sensor data
        self.print_touch_sensor_data("Right Hand", msg.right_touch_sensors)

        print()

    def print_touch_sensor_data(self, hand_name, sensor_data):
        """
        Print touch sensor data for a specific hand

        Args:
            hand_name: Name of the hand (Left Hand/Right Hand)
            sensor_data: Touch sensor data structure
        """
        print(f"=== {hand_name} Touch Sensor Data ===")

        # Print palm touch data
        print("Palm Touch Data (36 elements): ", end="")
        self.print_array(sensor_data.palm_touch_data)

        # Print back of hand touch data
        print("Back of Hand Touch Data (36 elements): ", end="")
        self.print_array(sensor_data.back_of_hand_touch_data)

        # Print finger touch data
        print("Thumb Touch Data (16 elements): ", end="")
        self.print_array(sensor_data.thumb_touch_data)

        print("Index Finger Touch Data (16 elements): ", end="")
        self.print_array(sensor_data.index_finger_touch_data)

        print("Middle Finger Touch Data (16 elements): ", end="")
        self.print_array(sensor_data.middle_finger_touch_data)

        print("Ring Finger Touch Data (16 elements): ", end="")
        self.print_array(sensor_data.ring_finger_touch_data)

        print("Little Finger Touch Data (16 elements): ", end="")
        self.print_array(sensor_data.little_finger_touch_data)

    def print_array(self, arr):
        """
        Print array of uint8_t elements

        Args:
            arr: Array to print (list or tuple)
        """
        print("[", end="")
        for i, val in enumerate(arr):
            print(f"{val:3d}", end="")
            if i < len(arr) - 1:
                print(" ", end="")
        print("]")

    def publish_command(self):
        """Publish hand command message"""
        message = HandCommandArray()

        # Set header
        message.header.stamp = self.get_clock().now().to_msg()
        message.header.frame_id = "hand_command"

        # Set the hand type
        message.left_hand_type.value = 1  # NIMBLE_HANDS
        message.right_hand_type.value = 1  # NIMBLE_HANDS

        # Create left hand command array
        from aimdk_msgs.msg import HandCommand
        message.left_hands = []

        # Set left thumb
        left_thumb = HandCommand()
        left_thumb.name = "left_thumb"
        left_thumb.position = 0.0
        left_thumb.velocity = 0.1
        left_thumb.acceleration = 0.0
        left_thumb.deceleration = 0.0
        left_thumb.effort = 0.0
        message.left_hands.append(left_thumb)

        # Set other left fingers
        for i in range(1, 10):
            finger = HandCommand()
            finger.name = "left_index"
            finger.position = 0.0
            finger.velocity = 0.1
            finger.acceleration = 0.0
            finger.deceleration = 0.0
            finger.effort = 0.0
            message.left_hands.append(finger)

        # Create right hand command array
        message.right_hands = []

        # Set right thumb
        right_thumb = HandCommand()
        right_thumb.name = "right_thumb"
        right_thumb.position = 0.0
        right_thumb.velocity = 0.1
        right_thumb.acceleration = 0.0
        right_thumb.deceleration = 0.0
        right_thumb.effort = 0.0
        message.right_hands.append(right_thumb)

        # Set other right fingers (pinky)
        for i in range(1, 10):
            finger = HandCommand()
            finger.name = "right_pinky"
            finger.position = 0.0
            finger.velocity = 0.1
            finger.acceleration = 0.0
            finger.deceleration = 0.0
            finger.effort = 0.0
            message.right_hands.append(finger)

        # Publish the message
        self.publisher_.publish(message)

        self.get_logger().info("Published hand command")


def main(args=None):
    rclpy.init(args=args)
    node = HandStateSubscriber()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
