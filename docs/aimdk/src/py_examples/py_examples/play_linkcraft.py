#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from aimdk_msgs.srv import GetRobotResources, ExecuteActionResource


class RobotResourceClient(Node):
    def __init__(self):
        super().__init__('robot_resource_client')

        self.get_resource_client = self.create_client(
            GetRobotResources,
            '/aimdk_5Fmsgs/srv/GetRobotResources'
        )
        self.play_resource_client = self.create_client(
            ExecuteActionResource,
            '/aimdk_5Fmsgs/srv/ExecuteActionResource'
        )

        self.resources = []

    def get_robot_resources(self):
        while not self.get_resource_client.wait_for_service(timeout_sec=1.0):
            if not rclpy.ok():
                self.get_logger().error("Interrupted while waiting for the service. Exiting.")
                return False
            self.get_logger().info("Service not available, waiting again...")

        request = GetRobotResources.Request()
        future = self.get_resource_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)

        if future.result() is None:
            self.get_logger().error("Failed to call GetRobotResources")
            return False

        response = future.result()
        self.resources = list(response.robot_resources)
        self.get_logger().info(f"Found {len(self.resources)} resources")
        return True

    def print_resource_menu(self):
        if not self.resources:
            print("(no resources)")
            return

        print("\n=== Available Robot Resources ===")
        for idx, resource in enumerate(self.resources):
            ver = resource.current_version
            print(f"[{idx}] {ver.name or '<no name>'}")
            print(f"     key:     {resource.resource_key}")
            print(f"     version: {ver.version}")
        print("=================================\n")

    def pick_resource(self):
        if not self.resources:
            return None

        while True:
            try:
                raw = input(
                    f"Select resource index [0-{len(self.resources) - 1}] (q to quit): ").strip()
            except EOFError:
                return None
            if raw.lower() in ("q", "quit", "exit"):
                return None
            if not raw.isdigit():
                print("Please enter a number.")
                continue
            idx = int(raw)
            if 0 <= idx < len(self.resources):
                return self.resources[idx]
            print(f"Index out of range (0-{len(self.resources) - 1}).")

    def play_resource(self, resource):
        while not self.play_resource_client.wait_for_service(timeout_sec=1.0):
            if not rclpy.ok():
                self.get_logger().error("Interrupted while waiting for service.")
                return
            self.get_logger().info("Service not available, waiting...")

        request = ExecuteActionResource.Request()
        request.resource_key = resource.resource_key
        request.resource_version = resource.current_version.version

        if "onnx" in request.resource_key:
            request.meta = '{"resource_type": "BODY_MONTION"}'
        else:
            request.meta = '{"resource_type": "ARM_MONTION"}'

        self.get_logger().info("Sending request:")
        self.get_logger().info(f"  resource_key: {request.resource_key}")
        self.get_logger().info(
            f"  resource_version: {request.resource_version}")
        self.get_logger().info(f"  meta: {request.meta}")

        future = self.play_resource_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)

        if future.result() is not None:
            self.handle_response(future.result())
        else:
            self.get_logger().error("Failed to call ExecuteActionResource")

    def handle_response(self, response):
        self.get_logger().info("Service response received:")
        self.get_logger().info("Response Header:")
        self.get_logger().info(
            f"  stamp: {response.header.header.stamp.sec}.{response.header.header.stamp.nanosec:09}")
        self.get_logger().info(f"  code: {response.header.header.code}")
        self.get_logger().info("Status:")
        self.get_logger().info(f"  value: {response.header.status.value}")
        self.get_logger().info(f"  message: {response.header.message}")


def main(args=None):
    rclpy.init(args=args)
    client_node = None
    try:
        client_node = RobotResourceClient()
        if not client_node.get_robot_resources():
            return
        client_node.print_resource_menu()
        chosen = client_node.pick_resource()
        if chosen is None:
            client_node.get_logger().info("No resource selected, exiting.")
            return
        client_node.play_resource(chosen)
    except KeyboardInterrupt:
        pass
    finally:
        if client_node:
            client_node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
