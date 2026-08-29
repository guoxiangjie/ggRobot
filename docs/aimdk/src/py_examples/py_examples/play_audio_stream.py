#!/usr/bin/env python3
"""
Raw audio stream playback example

This example would get audio focus first and then publish raw audio data
at fixed rate to `/aima/hal/audio/playback` topic. And it would stop playing
when audio focus is lost.

"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSDurabilityPolicy, QoSHistoryPolicy
from aimdk_msgs.msg import AudioPlayback, AudioInfo, AudioData, FocusResponse, FocusRequester, CommonState
from aimdk_msgs.srv import RequestAudioFocus, AbandonAudioFocus
import os
import signal
import time
import sys

global_node = None


def signal_handler(sig, frame):
    global global_node
    if global_node is not None:
        if global_node.is_holding_focus():
            global_node.send_request(False)
        global_node.get_logger().info(
            f"Received signal {sig}, abandon audio focus and shutting down")
    if rclpy.ok():
        rclpy.shutdown()
    sys.exit(0)


class FakeMicDevice():
    def __init__(self, raw_audio_file):
        self.audio_data = []
        self.channels = 1
        self.sample_rate = 16000
        self.bytes_per_sample = 2  # S16LE
        self.audio_length = 0
        with open(raw_audio_file, 'rb') as f:
            self.audio_data = list(f.read())
            self.audio_length = len(self.audio_data)

        self.index = 0
        self.start_time = 0

    def get_channel_count(self):
        return self.channels

    def get_sample_rate(self):
        return self.sample_rate

    def get_cached_data(self):
        now = time.monotonic()
        if not self.start_time:
            # fake init: assume audio data started 1s ago
            self.start_time = now - 1

        # cached data range since last call
        tail = int((now - self.start_time) * self.sample_rate) * \
            self.channels * self.bytes_per_sample
        data = self.audio_data[self.index:tail]
        if tail < self.audio_length:
            self.index = tail
        else:
            # loopback
            self.index = 0
            self.start_time = now
        return data


class AudioStreamPlayer(Node):
    def __init__(self):
        super().__init__('audio_stream_player')

        self.declare_parameter('raw_audio_path', '')
        self.raw_audio_path = self.get_parameter('raw_audio_path').value

        self.mic_device = FakeMicDevice(self.raw_audio_path)

        self.pkg_name = 'audio_stream_player{}'.format(os.getpid())
        self.focus = False
        self.focus_force = True

        self.get_logger().info(f'local pkg name: {self.pkg_name}')
        # Create focus request/release clients
        self.request_client = self.create_client(
            RequestAudioFocus,
            '/aimdk_5Fmsgs/srv/RequestAudioFocus')
        self.release_client = self.create_client(
            AbandonAudioFocus,
            '/aimdk_5Fmsgs/srv/AbandonAudioFocus')

        # Wait for the service to become available
        while not self.request_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().info('⏳ Service unavailable, waiting...')
        self.get_logger().info('🟢 Service available, ready to send request.')

        # Create focus event subscriber and raw audio publisher
        focus_qos = QoSProfile(
            reliability=QoSReliabilityPolicy.RELIABLE,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=10,
            durability=QoSDurabilityPolicy.VOLATILE
        )
        self.sub = self.create_subscription(
            FocusResponse,
            '/aima/hal/audio/focus_response',
            self.focus_event_callback, focus_qos
        )
        self.pub = self.create_publisher(
            AudioPlayback,
            '/aima/hal/audio/playback', 10
        )

    def send_request(self, focus: bool):
        if focus:
            self.send_focus_request()
        else:
            self.send_focus_release()

    def send_focus_request(self):
        req = RequestAudioFocus.Request()

        requester = FocusRequester()
        requester.pkg_name = self.pkg_name
        requester.priority = 6

        req.focus_requester = requester

        self.get_logger().info('📨 Sending RequestAudioFocus request')
        for i in range(8):
            future = self.request_client.call_async(req)
            rclpy.spin_until_future_complete(self, future, timeout_sec=0.25)

            if future.done():
                break

            # retry as remote peer is NOT handled well by ROS
            self.get_logger().info(f'trying ... [{i}]')

        response = future.result()
        if response is None:
            self.get_logger().error('❌ Service call failed or timed out.')
            return False

        if response.reponse.status.value == CommonState.SUCCESS:
            focus = response.focus_response.focus_gain
            self.focus = focus
            self.get_logger().info(f'✅ RequestAudioFocus done: focus {focus}')
            return True
        else:
            self.get_logger().error(
                f'❌ Failed in response of RequestAudioFocus: {response.reponse.message}'
            )
            return False

    def send_focus_release(self):
        req = AbandonAudioFocus.Request()

        requester = FocusRequester()
        requester.pkg_name = self.pkg_name

        req.focus_requester = requester

        self.get_logger().info('📨 Sending AbandonAudioFocus request')
        for i in range(8):
            future = self.release_client.call_async(req)
            rclpy.spin_until_future_complete(self, future, timeout_sec=0.25)

            if future.done():
                break

            # retry as remote peer is NOT handled well by ROS
            self.get_logger().info(f'trying ... [{i}]')

        response = future.result()
        if response is None:
            self.get_logger().error('❌ Service call failed or timed out.')
            return False

        if response.reponse.status.value == CommonState.SUCCESS:
            focus = response.focus_response.focus_gain
            # always focus False
            self.focus = focus
            self.get_logger().info(f'✅ AbandonAudioFocus done: focus {focus}')
            return True
        else:
            self.get_logger().error(
                f'❌ Failed in response of AbandonAudioFocus: {response.reponse.message}'
            )
            return False

    def focus_event_callback(self, msg: FocusResponse):
        pkg_name = msg.pkg_name
        focus = msg.focus_gain
        if msg.pkg_name == self.pkg_name:
            self.get_logger().info(
                f'receive foucs out event: focus state: {focus}')
            self.focus_force = msg.focus_gain

    def is_holding_focus(self):
        return self.focus and self.focus_force

    def spin_untill_focus(self):
        while rclpy.ok():
            self.focus_force = True
            self.send_request(True)
            if self.is_holding_focus():
                return
            self.get_logger().info("need retry to get focus")
            t1 = t0 = time.monotonic()
            while rclpy.ok() and t1 - t0 < 1.0:
                rclpy.spin_once(self, timeout_sec=0.1)
                t1 = time.monotonic()
        return

    def run_once(self):
        """ flush raw audio data cached since last call """

        raw_audio_msg = AudioPlayback()

        raw_audio_msg.pkg_name = self.pkg_name
        raw_audio_msg.token_id = self.pkg_name
        # fill AudioInfo
        audio_info = AudioInfo()
        audio_info.channels = self.mic_device.get_channel_count()
        audio_info.sample_rate = self.mic_device.get_sample_rate()
        # fill raw audio data
        audio_data = AudioData()
        cached_data = self.mic_device.get_cached_data()
        audio_data.data = cached_data
        raw_audio_msg.info = audio_info
        raw_audio_msg.data = audio_data
        # publish
        self.pub.publish(raw_audio_msg)

    def run(self):
        self.get_logger().info('🟢 publishing audio data ...')
        while rclpy.ok() and self.is_holding_focus():
            self.run_once()
            rclpy.spin_once(self, timeout_sec=0.05)
            time.sleep(0.05)

        if not self.is_holding_focus():
            self.get_logger().info("focus out, exiting...")


def main(args=None):
    global global_node
    rclpy.init(args=args)
    node = None

    try:
        node = AudioStreamPlayer()

        global_node = node
        signal.signal(signal.SIGINT, signal_handler)
        signal.signal(signal.SIGTERM, signal_handler)

        node.spin_untill_focus()
        node.run()

    except KeyboardInterrupt:
        rclpy.logging.get_logger('main').info(
            "Interrupt signal received, exiting...")
    except Exception as e:
        rclpy.logging.get_logger('main').error(
            f'Program exited with exception: {e}')

    if node:
        node.destroy_node()
    if rclpy.ok():
        rclpy.shutdown()


if __name__ == '__main__':
    main()
