#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.executors import SingleThreadedExecutor
from aimdk_msgs.srv import GetStoredMapByName
from std_msgs.msg import Header


class MapClient(Node):
    def __init__(self):
        super().__init__('get_map_client')
        self.client = self.create_client(
            GetStoredMapByName,
            '/aimdk_5Fmsgs/srv/GetStoredMapByName'
        )

    def send_request(self, map_name):
        while not self.client.wait_for_service(timeout_sec=1.0):
            if not rclpy.ok():
                self.get_logger().error("Interrupted while waiting for service.")
                return
            self.get_logger().info("Service not available, waiting again...")

        request = GetStoredMapByName.Request()

        request.header = Header()
        request.header.stamp = self.get_clock().now().to_msg()
        request.header.frame_id = ""

        request.map_name = map_name

        future = self.client.call_async(request)

        executor = SingleThreadedExecutor()
        executor.add_node(self)
        executor.spin_until_future_complete(future, timeout_sec=60.0)
        executor.remove_node(self)

        if future.result() is None:
            self.get_logger().error("Service call failed or timed out.")
            return

        result = future.result()

        if result.code == 0:
            self.get_logger().info("Service call succeeded")
            self.get_logger().info(f"Map path: {result.map_path}")
            self.get_logger().info(
                f"Map resolution: {result.map_info.resolution}")
            self.get_logger().info(f"Map width: {result.map_info.width}")
            self.get_logger().info(f"Map height: {result.map_info.height}")
            self.get_logger().info(f"Map id: {result.map_id}")
        else:
            self.get_logger().error(
                f"Service call failed with code: {result.code}")


def main(args=None):
    rclpy.init(args=args)

    client = MapClient()
    try:
        client.send_request("map_name")
    except KeyboardInterrupt:
        pass
    finally:
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
