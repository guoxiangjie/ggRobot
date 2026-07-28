"""ggRobot 入口 — python -m gg_robot"""

import sys
import threading
import logging
import time

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
)
logger = logging.getLogger("gg_robot")


def ros_spin():
    """在独立线程中运行 rclpy spin + 处理命令队列"""
    import rclpy
    rclpy.init(args=sys.argv)

    from .node import X2Node, CommandQueue

    node = X2Node()
    cmd_queue = CommandQueue()

    # 注入模块级引用，供 routes 使用
    from . import node as node_mod
    node_mod._node = node
    node_mod._cmd_queue = cmd_queue

    executor = rclpy.executors.MultiThreadedExecutor()
    executor.add_node(node)

    # 命令处理独立线程 —— 耗时命令（_do_action_sequence / _do_run_task / wait_tts_done）
    # 不再阻塞 executor 的回调调度。否则这些命令在 rclpy 线程里同步执行时，
    # executor.spin_once() 长时间不被调用，传感器回调被饿死，battery/imu 停在旧值。
    def cmd_loop():
        while rclpy.ok():
            try:
                node.process_commands()
            except Exception:
                logger.exception("命令处理异常")
            time.sleep(0.005)

    threading.Thread(target=cmd_loop, daemon=True, name="cmd").start()

    logger.info("📬 命令队列就绪，开始处理...")

    try:
        # 阻塞式持续分派传感器 / service 响应 / 定时器回调，
        # 与命令处理线程解耦，传感器数据实时刷新不再受命令耗时影响。
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node_mod._node = None
        node_mod._cmd_queue = None
        node.destroy_node()
        rclpy.shutdown()
        logger.info("rclpy 已关闭")


def wait_for_queue(timeout: float = 15.0):
    """阻塞等待命令队列初始化完成"""
    from . import node as node_mod
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if node_mod._cmd_queue is not None:
            return
        time.sleep(0.5)
    raise TimeoutError("rclpy 初始化超时，请检查 ROS2 环境")


def main():
    import uvicorn

    # 0. ⚠️ 必须在主线程先 import node，否则后台线程 rclpy.init() 会
    #    和主线程的 rclpy import 抢 GIL 导致死锁
    from . import node as node_mod  # noqa: F811

    # 1. 启动 rclpy 线程
    ros_thread = threading.Thread(target=ros_spin, daemon=True, name="rclpy")
    ros_thread.start()

    # 2. 等待命令队列就绪
    try:
        wait_for_queue()
    except TimeoutError:
        logger.error("rclpy 初始化超时，请检查 ROS2 环境")
        sys.exit(1)

    # 3. 初始化内置任务
    from .task.store import init_builtin_tasks
    init_builtin_tasks()

    # 4. 启动 FastAPI
    from .server import create_app
    app = create_app()

    import socket
    hostname = socket.gethostname()
    logger.info(f"🌐 服务地址: http://{hostname}:8000")
    logger.info("🚀 启动 ggRobot...")
    uvicorn.run(app, host="0.0.0.0", port=8000, log_level="info")


if __name__ == "__main__":
    main()
