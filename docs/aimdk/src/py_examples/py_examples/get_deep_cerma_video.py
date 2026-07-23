#!/usr/bin/env python3
"""
Head depth camera multi-topic subscription example
RGB/Depth图像自动解码，实时弹窗显示画面
"""
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
from sensor_msgs.msg import Image, CompressedImage, CameraInfo
from collections import deque
import numpy as np
import cv2
from pathlib import Path

class CameraTopicEcho(Node):
    def __init__(self):
        super().__init__('camera_topic_echo')

        # Select the topic type to subscribe
        self.declare_parameter('topic_type', 'rgb_image')
        self.declare_parameter('dump_video_path', '')

        self.topic_type = self.get_parameter('topic_type').value
        self.dump_video_path = self.get_parameter('dump_video_path').value

        # SensorDataQoS: BEST_EFFORT + VOLATILE
        qos = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=5
        )

        # Create different subscribers based on topic_type
        if self.topic_type == "depth_image":
            self.topic_name = "/aima/hal/sensor/rgbd_head_front/depth_image"
            self.sub_image = self.create_subscription(
                Image, self.topic_name, self.cb_image, qos)
            self.get_logger().info(
                f"✅ Subscribing Depth Image: {self.topic_name}")

        elif self.topic_type == "rgb_image":
            self.topic_name = "/aima/hal/sensor/rgbd_head_front/rgb_image"
            self.sub_image = self.create_subscription(
                Image, self.topic_name, self.cb_image, qos)
            self.get_logger().info(
                f"✅ Subscribing RGB Image: {self.topic_name}")
            if self.dump_video_path:
                self.get_logger().info(
                    f"📝 Will dump received images to video: {self.dump_video_path}")

        elif self.topic_type == "rgb_image_compressed":
            self.topic_name = "/aima/hal/sensor/rgbd_head_front/rgb_image/compressed"
            self.sub_compressed = self.create_subscription(
                CompressedImage, self.topic_name, self.cb_compressed, qos)
            self.get_logger().info(
                f"✅ Subscribing CompressedImage: {self.topic_name}")

        elif self.topic_type == "rgb_camera_info":
            self.topic_name = "/aima/hal/sensor/rgbd_head_front/rgb_camera_info"
            self.sub_camerainfo = self.create_subscription(
                CameraInfo, self.topic_name, self.cb_camerainfo, qos)
            self.get_logger().info(
                f"✅ Subscribing RGB CameraInfo: {self.topic_name}")

        elif self.topic_type == "depth_camera_info":
            self.topic_name = "/aima/hal/sensor/rgbd_head_front/depth_camera_info"
            self.sub_camerainfo = self.create_subscription(
                CameraInfo, self.topic_name, self.cb_camerainfo, qos)
            self.get_logger().info(
                f"✅ Subscribing Depth CameraInfo: {self.topic_name}")

        else:
            self.get_logger().error(f"Unknown topic_type: {self.topic_type}")
            raise ValueError("Unknown topic_type")

        # Internal state
        self.last_print = self.get_clock().now()
        self.print_allowed = False
        self.arrivals = deque()

    def update_arrivals(self):
        """Calculate received FPS"""
        now = self.get_clock().now()
        self.arrivals.append(now)
        while self.arrivals and (now - self.arrivals[0]).nanoseconds * 1e-9 > 1.0:
            self.arrivals.popleft()

    def get_fps(self):
        """Get FPS"""
        return len(self.arrivals)

    def should_print(self, master=True):
        """Control print frequency"""
        if not master:
            return self.print_allowed
        now = self.get_clock().now()
        if (now - self.last_print).nanoseconds * 1e-9 >= 1.0:
            self.last_print = now
            self.print_allowed = True
        else:
            self.print_allowed = False
        return self.print_allowed

    def cb_image(self, msg: Image):
        """Image callback (Depth/RGB image) 解码 + 弹窗显示"""
        self.update_arrivals()

        # ========== 核心解码与窗口显示 ==========
        if self.topic_type == "rgb_image":
            # RGB彩色图 rgb8
            img_rgb = np.frombuffer(msg.data, dtype=np.uint8).reshape(msg.height, msg.width, 3)
            img_bgr = cv2.cvtColor(img_rgb, cv2.COLOR_RGB2BGR)
            cv2.imshow("RGB Camera Window", img_bgr)

        elif self.topic_type == "depth_image":
            # 深度图一般为 uint16 (毫米值)
            depth_raw = np.frombuffer(msg.data, dtype=np.uint16).reshape(msg.height, msg.width)
            # 归一化转为灰度图方便查看（0~6000mm映射到0~255）
            depth_norm = cv2.normalize(depth_raw, None, 0, 255, cv2.NORM_MINMAX, dtype=cv2.CV_8U)
            cv2.imshow("Depth Camera Window", depth_norm)

        cv2.waitKey(1)  # 窗口刷新必须

        # 原有日志打印
        if self.should_print():
            stamp_sec = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            self.get_logger().info(
                f"📸 {self.topic_type} received\n"
                f"  • frame_id:        {msg.header.frame_id}\n"
                f"  • stamp (sec):     {stamp_sec:.6f}\n"
                f"  • encoding:        {msg.encoding}\n"
                f"  • size (WxH):      {msg.width} x {msg.height}\n"
                f"  • recv FPS (1s):   {self.get_fps():.1f}"
            )

        # Only RGB image supports video dump
        if self.topic_type == "rgb_image" and self.dump_video_path:
            self.dump_image_to_video(msg, img_bgr)

    def cb_compressed(self, msg: CompressedImage):
        """CompressedImage callback"""
        self.update_arrivals()
        # 压缩图解码弹窗
        data_arr = np.frombuffer(msg.data, np.uint8)
        img_decode = cv2.imdecode(data_arr, cv2.IMREAD_COLOR)
        cv2.imshow("Compressed RGB Window", img_decode)
        cv2.waitKey(1)

        if self.should_print():
            stamp_sec = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
            self.get_logger().info(
                f"🗜️  CompressedImage received\n"
                f"  • frame_id:        {msg.header.frame_id}\n"
                f"  • stamp (sec):     {stamp_sec:.6f}\n"
                f"  • format:          {msg.format}\n"
                f"  • data size:       {len(msg.data)}\n"
                f"  • recv FPS (1s):   {self.get_fps():.1f}"
            )

    def cb_camerainfo(self, msg: CameraInfo):
        """CameraInfo callback (camera intrinsic parameters)"""
        stamp_sec = msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        d_str = ", ".join([f"{d:.6f}" for d in msg.d])
        k_str = ", ".join([f"{k:.6f}" for k in msg.k])
        p_str = ", ".join([f"{p:.6f}" for p in msg.p])

        self.get_logger().info(
            f"📷 {self.topic_type} received\n"
            f"  • frame_id:        {msg.header.frame_id}\n"
            f"  • stamp (sec):     {stamp_sec:.6f}\n"
            f"  • width x height:  {msg.width} x {msg.height}\n"
            f"  • distortion_model:{msg.distortion_model}\n"
            f"  • D: [{d_str}]\n"
            f"  • K: [{k_str}]\n"
            f"  • P: [{p_str}]\n"
            f"  • binning_x: {msg.binning_x}\n"
            f"  • binning_y: {msg.binning_y}\n"
            f"  • roi: {{ x_offset: {msg.roi.x_offset}, y_offset: {msg.roi.y_offset}, height: {msg.roi.height}, width: {msg.roi.width}, do_rectify: {msg.roi.do_rectify} }}"
        )

    def dump_image_to_video(self, msg: Image, img_bgr):
        """RGB图片保存实现"""
        save_dir = Path(self.dump_video_path)
        save_dir.mkdir(parents=True, exist_ok=True)
        filename = f"rgb_{msg.header.stamp.sec}_{msg.header.stamp.nanosec//1000000}.jpg"
        full_path = str(save_dir / filename)
        cv2.imwrite(full_path, img_bgr)
        if self.should_print(master=False):
            self.get_logger().info(f"图片已保存：{full_path}")

def main(args=None):
    rclpy.init(args=args)
    node = None
    try:
        node = CameraTopicEcho()
        rclpy.spin(node)
    except KeyboardInterrupt:
        print("程序正常退出")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        cv2.destroyAllWindows()  # 关闭所有OpenCV窗口
        if node is not None:
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()
