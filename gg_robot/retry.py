"""跨板 Service 调用 8 次重试封装

依赖后台 executor 线程持续 spin 来完成 service future（见 __main__.py 的
executor.spin()）。本函数只做 future.done() 超时轮询，不再重入
rclpy.spin_until_future_complete —— 那会与 MultiThreadedExecutor 抢锁导致死锁。
"""

import logging
import time
from typing import Callable, TypeVar

T = TypeVar("T")
logger = logging.getLogger(__name__)

MAX_RETRIES = 8
TIMEOUT_SEC = 0.25


def call_with_retry(
    node,
    client,
    build_request: Callable,
    service_name: str = "",
    timeout: float = TIMEOUT_SEC,
    retries: int = MAX_RETRIES,
) -> T | None:
    """跨板 Service 调用的标准重试模板（timeout/retries 可调）。

    executor 在独立线程 spin，会自动完成 future；这里只轮询，不重入 spin。
    """
    for i in range(retries):
        req = build_request()
        future = client.call_async(req)
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            if future.done():
                return future.result()
            time.sleep(0.01)
        logger.info(f"{service_name} 重试 [{i}]")
    logger.error(f"{service_name} 全部 {retries} 次重试失败")
    return None
