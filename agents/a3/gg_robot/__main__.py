"""A3 agent 入口 — python -m gg_robot（rclpy 守护线程 → FastAPI :8300）

架构同 X2（CLAUDE.md 命令队列模式），差异：
- ros_spin 里构造 A3Node（订阅+速度发布；控制走 HTTP RPC 无需 Service Client）
- 无 task/project 1.0 数据迁移（A3 无历史包袱）
"""

import sys
import threading
import logging
import time

logging.basicConfig(level=logging.INFO,
                    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s")
logger = logging.getLogger("gg_robot")


def ros_spin():
    """独立线程：rclpy init → A3Node → spin（订阅回调 + 50Hz 速度 timer）"""
    import rclpy
    rclpy.init(args=sys.argv)

    from .node import A3Node, CommandQueue

    node = A3Node()
    cmd_queue = CommandQueue()

    from . import node as node_mod
    node_mod._node = node
    node_mod._cmd_queue = cmd_queue

    executor = rclpy.executors.MultiThreadedExecutor(num_threads=2)
    executor.add_node(node.node)

    # 命令处理线程（同 X2：长阻塞命令不饿死传感器回调）
    def cmd_loop():
        while rclpy.ok():
            try:
                node.process_commands()
            except Exception:
                logger.exception("命令处理异常")
            time.sleep(0.005)

    threading.Thread(target=cmd_loop, daemon=True, name="cmd").start()
    logger.info("📬 命令队列就绪（控制类经 HTTP RPC，速度经 topic）")

    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node_mod._node = None
        node_mod._cmd_queue = None
        node.destroy()
        rclpy.shutdown()
        logger.info("rclpy 已关闭")


def wait_for_queue(timeout: float = 15.0):
    from . import node as node_mod
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if node_mod._cmd_queue is not None:
            return
        time.sleep(0.5)
    raise TimeoutError("rclpy 初始化超时（检查 ROS2 Jazzy / env.sh）")


def main():
    import uvicorn

    # 主线程先 import node（rclpy init 抢 GIL 死锁问题，X2 踩过）
    from . import node as _node_warmup
    del _node_warmup

    ros_thread = threading.Thread(target=ros_spin, daemon=True, name="rclpy")
    ros_thread.start()

    try:
        wait_for_queue()
    except TimeoutError:
        logger.error("rclpy 初始化超时退出")
        sys.exit(1)

    from .server import create_app
    from .config import AGENT_PORT
    from .security import is_paired, agent_sn

    app = create_app()

    import socket
    logger.info(f"🌐 服务地址: http://{socket.gethostname()}:{AGENT_PORT}")
    logger.info(f"🔑 配对状态: {'已配对 sn=' + str(agent_sn()) if is_paired() else '未配对（控制端点关闭，仅 /api/health）'}")
    logger.info("🚀 启动 ggrobot-agent (A3-Ultra)...")
    uvicorn.run(app, host="0.0.0.0", port=AGENT_PORT, log_level="info")


if __name__ == "__main__":
    main()
