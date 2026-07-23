#!/usr/bin/env python3

import sys
import rclpy
import rclpy.logging
from rclpy.node import Node

from aimdk_msgs.srv import SetMicSourceRequest
from aimdk_msgs.msg import CommonRequest, CommonState


class SetMicSourceRequestClient(Node):
    def __init__(self):
        super().__init__('set_mic_source_request_client')
        self.client = self.create_client(
            SetMicSourceRequest, '/aimdk_5Fmsgs/srv/SetMicSourceRequest'
        )
        self.get_logger().info('✅ SetMicSourceRequest client node created.')

        # Wait for the service to become available
        while not self.client.wait_for_service(timeout_sec=2.0):
            self.get_logger().info('⏳ Service unavailable, waiting...')

        self.get_logger().info('🟢 Service available, ready to send request.')

    def send_request(self, mic_source: int):
        req = SetMicSourceRequest.Request()
        req.header = CommonRequest()

        req.mic_source = mic_source

        self.get_logger().info(
            f'📨 Sending request to set mic source: {mic_source}')
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
            self.get_logger().info('✅ MIC source set successfully.')
        else:
            self.get_logger().error(
                f'❌ Failed to set MIC source: {response.header.message}'
            )


def main(args=None):
    mic_info = {
        0: ('int', 'internal MIC'),
        1: ('ext', 'external MIC'),
    }

    choices = {}
    for k, v in mic_info.items():
        choices[v[0]] = k

    rclpy.init(args=args)
    node = None
    try:
        # Prefer command-line argument, otherwise prompt for input
        if len(sys.argv) > 1:
            mic = sys.argv[1]
        else:
            print('{:<4} - {:<5} : {}'.format('abbr',
                  'mic_id', 'description'))
            for k, v in mic_info.items():
                print(f'{v[0]:<4} - {k:<5} : {v[1]}')
            mic = input('Enter abbr of MIC source:')

        mic_id = choices.get(mic)
        if mic_id is None:
            raise ValueError(f'Invalid abbr of MIC source: {mic}')

        node = SetMicSourceRequestClient()
        node.send_request(mic_id)
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
