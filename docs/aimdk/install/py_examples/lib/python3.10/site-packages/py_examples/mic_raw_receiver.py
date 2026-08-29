#!/usr/bin/env python3
"""
Microphone raw data receiving example

This example subscribes to the `/aima/hal/audio/capture` topic to receive the robot's
raw audio data. It supports both the built-in microphone and the external
microphone audio streams, and automatically saves complete speech segments as PCM files.

Features:
- Automatically saves raw audio as PCM files
- Stores files categorized by timestamp and mic source

"""

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
from aimdk_msgs.msg import AudioCapture
import os
import time
from datetime import datetime
from collections import defaultdict
from typing import Dict, List


class RawAudioSubscriber(Node):
    def __init__(self):
        super().__init__('raw_audio_subscriber')

        # Audio buffers, stored separately by channels
        self.audio_buffers: Dict[int, List[bytes]] = defaultdict(list)
        self.mic_channels = 0
        self.ref_channels = 0
        self.inited = 0
        self.dump_timestamp = 0

        # Create audio output directory
        now = datetime.now()
        timestamp = now.strftime("%Y%m%d_%H%M%S_%f")[:-3]  # to milliseconds

        self.audio_output_dir = os.path.join("audio_recordings", timestamp)
        os.makedirs(self.audio_output_dir, exist_ok=True)

        # QoS settings
        # Note: deep queue to avoid missing data
        qos = QoSProfile(
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=500,
            reliability=QoSReliabilityPolicy.BEST_EFFORT
        )

        # Create subscriber
        self.subscription = self.create_subscription(
            AudioCapture,
            '/aima/hal/audio/capture',
            self.audio_callback,
            qos
        )

        self.get_logger().info("Start subscribing to raw audio data...")

    def audio_callback(self, msg: AudioCapture):
        """Audio data callback"""
        if not self.inited:
            self.mic_channels = msg.mic_channels
            self.ref_channels = msg.ref_channels
            self.dump_timestamp = time.time()
            self.inited = 1
        elif self.mic_channels != msg.mic_channels or self.ref_channels != msg.ref_channels:
            # quit as MIC switched
            self.get_logger().error(
                "MIC channels info changed (mic:{self.mic_channels} ref:{self.ref_channels}) -> (mic:{msg.mic_channels} ref:{msg.ref_channels})")
            if rclpy.ok():
                rclpy.shutdown()
            return
        audio_data = bytes(msg.data.data)

        self.handle_audio_data(audio_data)

    def handle_audio_data(self, audio_data: bytes):
        """Handle raw audio data"""

        # Split S16LE data into channels
        channels = self.ref_channels + self.mic_channels
        bytes_per_channel = 2
        unit_size = channels * bytes_per_channel
        base = 0
        for k in range(len(audio_data) // unit_size):
            for i in range(channels):
                tail = base + bytes_per_channel
                self.audio_buffers[i].append(audio_data[base:tail])
                base = tail

    def save_audio_segments(self):
        self.get_logger().info("🔄 Flashing cached audio data...")
        for i in range(self.mic_channels + self.ref_channels):
            self.save_audio_segment(i, i >= self.mic_channels)

    def save_audio_segment(self, channel: int, is_ref: bool):
        """Save audio segment"""
        if not self.audio_buffers[channel]:
            return

        # Merge all audio data
        audio_data = b''.join(self.audio_buffers[channel])
        self.audio_buffers[channel].clear()

        channel_type = 'mic'
        if is_ref:
            channel_type = 'ref'

        # Generate filename
        filepath = os.path.join(self.audio_output_dir,
                                f"channel_{channel}_{channel_type}.pcm")

        try:
            # Save PCM file
            with open(filepath, 'ab') as f:
                f.write(audio_data)

            self.get_logger().info(
                f"Audio segment saved: {filepath} append: {len(audio_data)} bytes)")

        except Exception as e:
            self.get_logger().error(f"Failed to save audio file: {str(e)}")

    def run(self):
        self.timer = self.create_timer(1.0, self.save_audio_segments)
        rclpy.spin(self)


def main(args=None):
    rclpy.init(args=args)
    node = None

    try:
        node = RawAudioSubscriber()
        node.get_logger().info("Listening to raw audio data, press Ctrl+C to exit...")
        node.run()
    except KeyboardInterrupt:
        rclpy.logging.get_logger('main').info(
            "Interrupt signal received, exiting...")

    if node:
        node.destroy_node()
    if rclpy.ok():
        rclpy.shutdown()


if __name__ == '__main__':
    main()
