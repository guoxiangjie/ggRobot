#!/usr/bin/env python3
"""定位 service call 失败根因 —— 复现 gg_robot 的调用方式（MultiThreadedExecutor + 后台 spin + future 轮询），
对比 default / Reentrant callback group、以及有无高频传感器订阅。

跑法（在 Orin 上）：
  source /opt/ros/humble/setup.bash
  source ~/aimdk/install/local_setup.bash
  python3 ~/ggRobot/test_srv.py
"""
import rclpy
import threading
import time
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.qos import qos_profile_sensor_data
from aimdk_msgs.srv import GetRobotResources
from sensor_msgs.msg import Imu

imu_count = [0]
def on_imu(_m):
    imu_count[0] += 1

def call_wait(client, label, timeout=5.0):
    fut = client.call_async(GetRobotResources.Request())
    t0 = time.time()
    while time.time() - t0 < timeout:
        if fut.done():
            r = fut.result()
            n = len(r.robot_resources) if r else 0
            print(f'  [{label}] ✅ {time.time()-t0:.2f}s  resources={n}')
            return
        time.sleep(0.01)
    print(f'  [{label}] ❌ TIMEOUT  future.done()={fut.done()}')

def main():
    rclpy.init()
    node = rclpy.create_node('test_srv_call')
    c_def = node.create_client(GetRobotResources, '/aimdk_5Fmsgs/srv/GetRobotResources')
    c_rec = node.create_client(GetRobotResources, '/aimdk_5Fmsgs/srv/GetRobotResources',
                               callback_group=ReentrantCallbackGroup())
    print('service ready:', c_def.wait_for_service(timeout_sec=5))

    exe = MultiThreadedExecutor(num_threads=4)
    exe.add_node(node)
    threading.Thread(target=exe.spin, daemon=True).start()
    time.sleep(0.3)

    print('\n== 无传感器干扰 ==')
    call_wait(c_def, 'default  ')
    call_wait(c_rec, 'reentrant')

    print('\n== 加高频 IMU 订阅（500Hz，模拟 gg_robot）==')
    node.create_subscription(Imu, '/aima/hal/imu/torso/state', on_imu, qos_profile_sensor_data)
    time.sleep(1.0)
    print(f'  IMU 收到 {imu_count[0]} 条（1秒内）')
    call_wait(c_def, 'default  ')
    call_wait(c_rec, 'reentrant')

    exe.shutdown()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
