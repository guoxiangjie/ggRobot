#!/usr/bin/env python3

import sys
import rclpy
import rclpy.logging
from rclpy.node import Node

from aimdk_msgs.srv import GetMicSourceRequest
from aimdk_msgs.msg import CommonRequest, CommonState


class GetMicSourceRequestClient(Node):
    def __init__(self):
        super().__init__('get_mic_source_request_client')
        self.client = self.create_client(
            GetMicSourceRequest, '/aimdk_5Fmsgs/srv/GetMicSourceRequest'
        )
        self.get_logger().info('✅ GetMicSourceRequest client node created.')

        # Wait for the service to become available
        while not self.client.wait_for_service(timeout_sec=2.0):
            self.get_logger().info('⏳ Service unavailable, waiting...')

        self.get_logger().info('🟢 Service available, ready to send request.')

    def send_request(self):
        req = GetMicSourceRequest.Request()
        req.header = CommonRequest()

        self.get_logger().info(
            f'📨 Sending request to get MIC source')
        for i in range(8):
            req.header.header.stamp = self.get_clock().now().to_msg()
            future = self.client.call_async(req)
            rclpy.spin_until_future_complete(self, future, timeout_sec=0.25)

            if future.done():
                break

            # retry as remote peer is NOT handled well by ROS
            self.get_logger().info(f'trying ... [{i}]')

        response = future.result()
        if response is None:
            self.get_logger().error('❌ Service call failed or timed out.')
            return

        if response.header.status.value == CommonState.SUCCESS:
            self.get_logger().info('✅ MIC source get successfully.')
            self.get_logger().info(f'MIC id: {response.mic_source}')
        else:
            self.get_logger().error(
                f'❌ Failed to get MIC source: {response.header.message}'
            )


def main(args=None):
    rclpy.init(args=args)
    node = None
    try:
        node = GetMicSourceRequestClient()
        node.send_request()
    except KeyboardInterrupt:
        pass
    except Exception as e:
        rclpy.logging.get_logger('main').error(
            f'Program exited with exception: {e}')

    if node:
        node.destroy_node()
    if rclpy.ok():
        rclpy.shutdown()


if __name__ == '__main__':
    main()
