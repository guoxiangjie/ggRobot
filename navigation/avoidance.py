#!/usr/bin/env python3
"""
X2 激光避障节点 — 第1阶段（安全过滤器模式）
════════════════════════════════════════════════
架构：接收目标速度 → 激光检测障碍物 → 输出安全速度
  可以作为手柄/Web/规划器的"安全过滤层"，也可以独立测试。

核心流程：
  手柄/规划器 → 目标速度(cmd_vel)
                     ↓
  激光点云 → ROI裁剪 → 地面去除 → 扇形分区 → 障碍距离
                     ↓
  安全过滤：根据障碍物修改速度 → 安全速度 → X2机器人

运行：
  python3 lidar_avoidance.py          # 过滤器模式（配合手柄/Web用）
  python3 lidar_avoidance.py --auto   # 独立模式（自动前进+避障）

依赖：numpy（ROS2自带），无额外依赖
"""

import math
import time
import struct
import sys
import signal
import threading

import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy

from sensor_msgs.msg import PointCloud2
from geometry_msgs.msg import Twist
from aimdk_msgs.msg import McLocomotionVelocity, MessageHeader, McInputSource, McInputAction
from aimdk_msgs.srv import SetMcInputSource


# ═══════════════════════════════════════════
# 配置（直接改这里，不用动代码逻辑）
# ═══════════════════════════════════════════

CFG = {
    # ── 输入源 ──
    "source_name": "x2_navigation",

    # ── 工作模式 ──
    #   "filter"  : 过滤器模式（订阅 /cmd_vel，根据障碍物修改后输出）
    #   "auto"    : 独立模式（自动驱动机器人前进，遇障避让）
    #   "dry_run" : 空跑模式（处理激光+打印决策，但不发速度、不注册输入源）
    "mode": "filter",

    # ── ROI 裁剪（机器人坐标系，X前 Y左 Z上） ──
    "roi_x_min": 0.2,
    "roi_x_max": 4.0,
    "roi_y_min": -2.0,
    "roi_y_max": 2.0,
    "roi_z_min": 0.1,      # 高于地面10cm以上才算障碍
    "roi_z_max": 1.8,      # 高于1.8m的不关心

    # ── 地面去除 ──
    "ground_tolerance": 0.08,
    "use_ransac_ground": True,  # RANSAC 拟合地平面，斜坡/倾斜仍有效，低矮≈8cm物体不误判为地面

    # ── 避障距离 ──
    "stop_distance": 0.4,    # 紧急停止
    "avoid_distance": 0.8,   # 转向避让
    "slow_distance": 1.5,    # 减速
    "robot_radius": 0.25,
    "safety_margin": 0.15,

    # ── 速度限制 ──
    "max_forward_speed": 0.4,
    "slow_forward_speed": 0.15,
    "max_angular_speed": 0.8,

    # 原地转向距离：小于此距离时不再前进，原地转向
    "turn_in_place_distance": 0.65,

    # ── 扇形分区（前方分成N个扇区，奇数） ──
    "num_sectors": 9,
    "sector_angle": 120.0,   # E1R 水平FOV=120°

    # ── 独立模式速度 ──
    "auto_forward_speed": 0.25,

    # ── 性能 ──
    "ransac_iterations": 30,     # RANSAC 迭代次数（体素降采样后 ~500点，30次足够）
}


# ═══════════════════════════════════════════
# 点云工具函数
# ═══════════════════════════════════════════

def pc2_to_xyz(msg: PointCloud2) -> np.ndarray:
    """PointCloud2 → N×3 数组"""
    offsets = {}
    for f in msg.fields:
        offsets[f.name] = f.offset

    if not all(k in offsets for k in ('x', 'y', 'z')):
        return np.zeros((0, 3))

    step = msg.point_step
    data = msg.data
    n = len(data) // step
    if n == 0:
        return np.zeros((0, 3))

    pts = np.zeros((n, 3), dtype=np.float32)
    ox, oy, oz = offsets['x'], offsets['y'], offsets['z']

    for i in range(n):
        base = i * step
        pts[i, 0] = struct.unpack_from('f', data, base + ox)[0]
        pts[i, 1] = struct.unpack_from('f', data, base + oy)[0]
        pts[i, 2] = struct.unpack_from('f', data, base + oz)[0]

    return pts


def crop_roi(pts: np.ndarray) -> np.ndarray:
    """ROI 裁剪"""
    c = CFG
    m = (
        (pts[:, 0] > c["roi_x_min"]) & (pts[:, 0] < c["roi_x_max"]) &
        (pts[:, 1] > c["roi_y_min"]) & (pts[:, 1] < c["roi_y_max"]) &
        (pts[:, 2] > c["roi_z_min"]) & (pts[:, 2] < c["roi_z_max"])
    )
    return pts[m]


def voxel_downsample(pts: np.ndarray, voxel_size: float = 0.05) -> np.ndarray:
    """体素降采样：把点云压到 ~500 点以内，大幅加速后续处理"""
    if len(pts) <= 500:
        return pts
    # 按体素网格分组，每个体素取一个代表点
    voxel_indices = np.floor(pts / voxel_size).astype(np.int32)
    # 用字典去重
    unique_dict = {}
    for i, idx in enumerate(voxel_indices):
        key = (idx[0], idx[1], idx[2])
        if key not in unique_dict:
            unique_dict[key] = pts[i]
    result = np.array(list(unique_dict.values()), dtype=np.float32)
    return result


def remove_ground_ransac(pts: np.ndarray, thresh: float = 0.06,
                          iters: int = 100) -> np.ndarray:
    """RANSAC 地平面拟合，返回非地面点"""
    if len(pts) < 100:
        return pts

    best_count = 0
    best_plane = None
    n = len(pts)

    for _ in range(iters):
        idx = np.random.choice(n, 3, replace=False)
        p1, p2, p3 = pts[idx]
        v1 = p2 - p1
        v2 = p3 - p1
        normal = np.cross(v1, v2)
        norm = np.linalg.norm(normal)
        if norm < 1e-6:
            continue
        normal /= norm
        # 地平面法向量应大致朝上
        if abs(normal[2]) < 0.3:
            continue
        d = -np.dot(normal, p1)
        dists = np.abs(np.dot(pts, normal) + d)
        count = int(np.sum(dists < thresh))
        if count > best_count:
            best_count = count
            best_plane = (normal, d)

    if best_plane is None:
        return pts
    normal, d = best_plane
    dists = np.abs(np.dot(pts, normal) + d)
    return pts[dists >= thresh]


def remove_ground_simple(pts: np.ndarray) -> np.ndarray:
    """简单高度过滤"""
    return pts[pts[:, 2] > CFG["ground_tolerance"]]


def divide_sectors(pts: np.ndarray) -> list:
    """扇形分区，返回每个扇区的最近障碍距离"""
    c = CFG
    n = c["num_sectors"]
    half = math.radians(c["sector_angle"] / 2)

    if len(pts) == 0:
        return [c["roi_x_max"]] * n

    angles = np.arctan2(pts[:, 1], pts[:, 0])
    dists = np.sqrt(pts[:, 0]**2 + pts[:, 1]**2)

    sectors = []
    for i in range(n):
        a_min = -half + (i * 2 * half / n)
        a_max = a_min + (2 * half / n)
        mask = (angles >= a_min) & (angles < a_max)
        if i == n - 1:
            mask = (angles >= a_min) & (angles <= a_max + 1e-6)
        if np.any(mask):
            sectors.append(float(np.min(dists[mask])))
        else:
            sectors.append(c["roi_x_max"])
    return sectors


# ═══════════════════════════════════════════
# 避障节点
# ═══════════════════════════════════════════

class LidarAvoidance(Node):
    """
    激光避障安全过滤器

    架构（过滤器模式）：
      手柄/规划器 → /cmd_vel(目标速度)
      激光点云    → 障碍物检测
      本节点      → 安全过滤 → 输出安全速度

    架构（独立模式）：
      本节点      → 自动前进 + 激光避障
    """

    def __init__(self, mode: str = "filter"):
        super().__init__("lidar_avoidance")

        CFG["mode"] = mode
        self._dry_run = (mode == "dry_run")
        self._fwd_cmd = 0.0
        self._ang_cmd = 0.0
        self._fwd_des = 0.0
        self._ang_des = 0.0
        self._state = "IDLE"
        self._obstacle = {}
        self._registered = False
        self._enabled = True
        self._lock = threading.Lock()
        self._busy = False      # 防止回调堆积：还在处理上一帧就跳过新帧

        # EMA 平滑：消除相邻帧之间的抖动
        self._ema_alpha = 0.3  # 0.3 = 70%旧值 + 30%新值
        self._front_ema = CFG["roi_x_max"]
        self._left_ema = CFG["roi_x_max"]
        self._right_ema = CFG["roi_x_max"]
        self._last_turn_dir = 0  # -1=上次左转, +1=上次右转, 0=无
        self._turn_streak = 0    # 同方向连续帧数

        # ── QoS ──
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
        )
        vel_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            durability=DurabilityPolicy.VOLATILE,
            depth=10,
        )

        # ── 订阅激光 ──
        self._lidar_sub = self.create_subscription(
            PointCloud2,
            "/aima/hal/sensor/lidar_chest_front/lidar_pointcloud",
            self._on_lidar,
            sensor_qos,
        )

        # ── 订阅目标速度（过滤器模式用） ──
        self._cmd_vel_sub = self.create_subscription(
            Twist,
            "/cmd_vel",
            self._on_cmd_vel,
            vel_qos,
        )

        # ── 发布安全速度 ──
        self._vel_pub = self.create_publisher(
            McLocomotionVelocity,
            "/aima/mc/locomotion/velocity",
            vel_qos,
        )

        # ── Service 客户端 ──
        self._input_cli = self.create_client(
            SetMcInputSource,
            "/aimdk_5Fmsgs/srv/SetMcInputSource",
        )

        # ── 定时器 ──
        self._vel_timer = self.create_timer(0.02, self._pub_velocity)     # 50Hz
        self._status_timer = self.create_timer(0.5, self._print_status)    # 2Hz

        # ── 启动 ──
        titles = {"filter": "过滤器", "auto": "独立自动", "dry_run": "🔇空跑测试"}
        title = titles.get(mode, mode)
        self.get_logger().info("=" * 50)
        self.get_logger().info(f"X2 激光避障节点 [{title}] 启动")
        if self._dry_run:
            self.get_logger().warn("🔇 空跑模式：处理激光+决策，但不发速度，不注册输入源")
        self.get_logger().info(f"  停止:{CFG['stop_distance']}m 避障:{CFG['avoid_distance']}m 减速:{CFG['slow_distance']}m")
        self.get_logger().info("=" * 50)

        if not self._dry_run:
            self._register_input_source()
        else:
            self._registered = True

    # ── 目标速度回调 ────────────────────────

    def _on_cmd_vel(self, msg: Twist):
        """接收外部速度指令（手柄/规划器）"""
        with self._lock:
            self._fwd_des = msg.linear.x
            self._ang_des = msg.angular.z

    # ── 激光回调 ────────────────────────────

    def _on_lidar(self, msg: PointCloud2):
        """主感知+决策链路"""
        if not self._enabled:
            return

        # 还在处理上一帧 → 跳过，防止回调堆积
        if self._busy:
            return

        self._busy = True
        t0 = time.time()

        # 1. 点云解析 + ROI
        pts = pc2_to_xyz(msg)
        pts = crop_roi(pts)

        # 1.5 体素降采样（压到 ~500 点，加速后续 RANSAC）
        pts = voxel_downsample(pts, voxel_size=0.05)

        if len(pts) < 10:
            self._state = "GO"
            self._apply_desired()
            return

        # 2. 地面去除：RANSAC + 高度过滤 取并集，防止任一方法漏检
        if CFG["use_ransac_ground"]:
            pts_ransac = remove_ground_ransac(pts, iters=CFG["ransac_iterations"])
            pts_height = remove_ground_simple(pts)
            # 取并集：RANSAC 能处理斜坡，高度过滤兜底近距离
            if len(pts_ransac) > 0 and len(pts_height) > 0:
                pts = np.unique(np.vstack([pts_ransac, pts_height]), axis=0)
            else:
                pts = pts_ransac if len(pts_ransac) > len(pts_height) else pts_height
        else:
            pts = remove_ground_simple(pts)

        if len(pts) < 5:
            self._state = "GO"
            self._apply_desired()
            return

        # 3. 扇形分区
        sector_dists = divide_sectors(pts)
        n = len(sector_dists)
        mid = n // 2

        front = sector_dists[mid]
        left_min = min(sector_dists[:mid]) if mid > 0 else CFG["roi_x_max"]
        right_min = min(sector_dists[mid+1:]) if mid+1 < n else CFG["roi_x_max"]

        # 3.5 EMA 平滑
        a = self._ema_alpha
        self._front_ema = a * front + (1 - a) * self._front_ema
        self._left_ema = a * left_min + (1 - a) * self._left_ema
        self._right_ema = a * right_min + (1 - a) * self._right_ema

        # 4. 决策（用平滑后的距离）
        self._state = self._compute_decision(self._front_ema, self._left_ema, self._right_ema)

        # 5. 记录
        self._obstacle = {
            "front": self._front_ema, "left": self._left_ema, "right": self._right_ema,
            "n_obs": len(pts), "ms": (time.time() - t0) * 1000,
        }
        self._busy = False

    # ── 决策 ─────────────────────────────────

    def _compute_decision(self, front: float, left: float, right: float) -> str:
        """核心避障决策，返回状态字符串，同时设置速度指令"""
        c = CFG

        with self._lock:
            fwd_des = self._fwd_des
            ang_des = self._ang_des

        if c["mode"] == "auto":
            fwd_des = c["auto_forward_speed"]
            ang_des = 0.0

        # 静止/后退时不干预
        if fwd_des <= 0.001:
            self._fwd_cmd = 0.0
            self._ang_cmd = max(-c["max_angular_speed"],
                                min(c["max_angular_speed"], ang_des))
            return "IDLE"

        # ── 1. 紧急停止（极近） ──
        if front < c["stop_distance"]:
            self._fwd_cmd = 0.0
            self._ang_cmd = 0.0
            return "STOP"

        # ── 1.5 两侧都堵死 → 停住等 ──
        min_clearance = c["robot_radius"] + c["safety_margin"]
        if left < min_clearance and right < min_clearance:
            self._fwd_cmd = 0.0
            self._ang_cmd = 0.0
            return "TRAPPED"

        # ── 2. 避障转向 ──
        if front < c["avoid_distance"]:
            # 方向锁死：差距<0.15m时沿用上次方向，防止左右打架
            dir_deadband = 0.15
            if abs(left - right) < dir_deadband and self._last_turn_dir != 0:
                go_left = (self._last_turn_dir == -1)
                self._turn_streak += 1
            else:
                go_left = (left > right)
                self._turn_streak = 0

            self._last_turn_dir = -1 if go_left else 1
            self._ang_cmd = c["max_angular_speed"] if go_left else -c["max_angular_speed"]
            direction = "←L" if go_left else "→R"

            # 2a. 太近时原地转向
            if front < c["turn_in_place_distance"]:
                self._fwd_cmd = 0.0
                return f"TURN{direction}"

            # 2b. 还有距离，减速+转向
            ratio = (front - c["turn_in_place_distance"]) / (
                c["avoid_distance"] - c["turn_in_place_distance"])
            self._fwd_cmd = fwd_des * ratio * 0.3
            return f"AVOID{direction}"

        # ── 3. 减速 ──
        if front < c["slow_distance"]:
            self._last_turn_dir = 0  # 退出避障，重置方向记忆
            self._turn_streak = 0
            ratio = (front - c["avoid_distance"]) / (
                c["slow_distance"] - c["avoid_distance"])
            self._fwd_cmd = fwd_des * max(0.3, ratio)
            self._ang_cmd = ang_des
            return "SLOW"

        # ── 4. 畅通 ──
        self._last_turn_dir = 0
        self._turn_streak = 0
        self._apply_desired()
        return "GO"

    def _apply_desired(self):
        """应用目标速度（无修改）"""
        with self._lock:
            fwd = self._fwd_des
            ang = self._ang_des
        if CFG["mode"] == "auto":
            fwd = CFG["auto_forward_speed"]
            ang = 0.0
        self._fwd_cmd = fwd
        self._ang_cmd = ang

    # ── 速度发布 ─────────────────────────────

    def _pub_velocity(self):
        """50Hz 定时发布安全速度"""
        if self._dry_run or not self._registered:
            return

        msg = McLocomotionVelocity()
        msg.header = MessageHeader()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.source = CFG["source_name"]
        msg.forward_velocity = float(self._fwd_cmd)
        msg.lateral_velocity = 0.0
        msg.angular_velocity = float(self._ang_cmd)
        self._vel_pub.publish(msg)

    def _stop(self):
        self._fwd_cmd = 0.0
        self._ang_cmd = 0.0

    # ── 状态打印 ─────────────────────────────

    def _print_status(self):
        if not self._obstacle:
            return
        d = self._obstacle
        icons = {"GO": "🟢", "SLOW": "🟡", "AVOID": "🟠", "TURN": "🔄", "TRAPPED": "🚫", "STOP": "🔴", "IDLE": "⚪"}
        icon = icons.get(self._state.split("←")[0].split("→")[0], "❓")
        self.get_logger().info(
            f"{icon} [{self._state:>8s}] "
            f"前:{d['front']:.2f}m 左:{d['left']:.2f}m 右:{d['right']:.2f}m | "
            f"障碍点:{d['n_obs']} | "
            f"目标→({self._fwd_des:.2f},{self._ang_des:.2f}) "
            f"输出→({self._fwd_cmd:.2f},{self._ang_cmd:.2f}) | "
            f"{d['ms']:.0f}ms"
        )

    # ── 输入源管理 ───────────────────────────

    def _register_input_source(self):
        name = CFG["source_name"]
        self.get_logger().info(f"注册输入源: {name}...")

        if not self._input_cli.wait_for_service(timeout_sec=3.0):
            self.get_logger().warn("服务不可用，跳过")
            self._registered = True
            return

        del_req = SetMcInputSource.Request()
        del_req.request.header.stamp = self.get_clock().now().to_msg()
        del_req.action = McInputAction(); del_req.action.value = 1003
        del_req.input_source = McInputSource(); del_req.input_source.name = name
        self._input_cli.call_async(del_req)
        self._spin_for(0.3)

        add_req = SetMcInputSource.Request()
        add_req.request.header.stamp = self.get_clock().now().to_msg()
        add_req.action = McInputAction(); add_req.action.value = 1001
        add_req.input_source = McInputSource()
        add_req.input_source.name = name
        add_req.input_source.priority = 40
        add_req.input_source.timeout = 1000
        future = self._input_cli.call_async(add_req)
        self._spin_for(0.5)

        ok = future.done() and future.result().response.header.code == 0
        self.get_logger().info("✅ 已注册" if ok else "⚠️ 注册异常（继续尝试）")
        self._registered = True

    def _unregister_input_source(self):
        if not self._registered:
            return
        name = CFG["source_name"]
        del_req = SetMcInputSource.Request()
        del_req.request.header.stamp = self.get_clock().now().to_msg()
        del_req.action = McInputAction(); del_req.action.value = 1003
        del_req.input_source = McInputSource(); del_req.input_source.name = name
        self._input_cli.call_async(del_req)
        self._spin_for(0.2)

    def _spin_for(self, sec):
        t0 = self.get_clock().now()
        while (self.get_clock().now() - t0).nanoseconds / 1e9 < sec:
            rclpy.spin_once(self, timeout_sec=0.02)

    def shutdown(self):
        self.get_logger().info("关闭中...")
        self._stop()
        if not self._dry_run:
            for _ in range(5):
                self._pub_velocity()
                self._spin_for(0.02)
        if not self._dry_run:
            self._unregister_input_source()
        self.get_logger().info("✅ 安全关闭")


# ═══════════════════════════════════════════
# 入口
# ═══════════════════════════════════════════

def main():
    rclpy.init(args=sys.argv)
    if "--dry-run" in sys.argv:
        mode = "dry_run"
    elif "--auto" in sys.argv:
        mode = "auto"
    else:
        mode = "filter"
    node = LidarAvoidance(mode=mode)

    def handler(sig, frame):
        node.shutdown()
        rclpy.shutdown()
        sys.exit(0)

    signal.signal(signal.SIGINT, handler)
    signal.signal(signal.SIGTERM, handler)

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
