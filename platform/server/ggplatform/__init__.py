"""GG Robot 平台后端（FastAPI sidecar，127.0.0.1:8310 + SQLite）

边界铁律：本包永不 import rclpy/ROS2 —— 机器人交互全部经 agent HTTP/WS。
"""
