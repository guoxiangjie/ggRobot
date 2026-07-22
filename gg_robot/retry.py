"""跨板 Service 调用 8 次重试封装"""

import logging
from typing import Callable, TypeVar
import rclpy

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
    """跨板 Service 调用的标准重试模板（timeout/retries 可调）"""
    for i in range(retries):
        req = build_request()
        future = client.call_async(req)
        rclpy.spin_until_future_complete(node, future, timeout_sec=timeout)
        if future.done():
            return future.result()
        logger.info(f"{service_name} 重试 [{i}]")
    logger.error(f"{service_name} 全部 {retries} 次重试失败")
    return None
