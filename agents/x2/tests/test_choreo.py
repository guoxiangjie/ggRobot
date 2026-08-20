"""ChoreoRunner 调度逻辑回归测试（无 rclpy 依赖，纯标准库）

运行：/opt/homebrew/bin/python3.12 agents/x2/tests/test_choreo.py
      （本机系统 python3 是 3.9，项目用 3.10+ 语法，须用 3.10+）

覆盖：at 调度/顺序执行、失败跳过继续、stop+零速收尾、未 load 防护、
at 排序、8 种步骤类型执行。注入假 node 模块绕过 rclpy import。
"""

import os
import sys
import time
import types

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


# ── 注入假 node 模块（choreo._execute 内部 from . import node）──
class FakeNode:
    def __init__(self):
        self.calls = []

    def _do_velocity(self, f, l, a): self.calls.append(('vel', f, l, a))
    def _sleep(self, s): time.sleep(s)
    def _do_tts(self, text): self.calls.append(('tts', text)); return True
    def wait_tts_done(self, timeout=20.0): self.calls.append(('wait_tts_done',)); return True
    def stop_motion(self): self.calls.append(('stop_motion',))
    def _do_motion(self, area, mid, interrupt=True): self.calls.append(('motion', area, mid)); return {"ok": True}
    def _do_emoji(self, eid, mode=1): self.calls.append(('emoji', eid)); return {"ok": True}
    def _do_mode(self, desc, value=0): self.calls.append(('mode', desc, value)); return {"ok": True}
    def _do_set_volume(self, v): self.calls.append(('volume', v)); return {"volume": v}
    def _do_media_play(self, p, n): self.calls.append(('media', n)); return {"ok": True}
    def _play_resource(self, k, v="", t=""): self.calls.append(('linkcraft', k, t)); return {"ok": True}


fake = FakeNode()
fake_node_mod = types.ModuleType("gg_robot.node")
fake_node_mod._node = fake
fake_node_mod._cmd_queue = None
sys.modules["gg_robot.node"] = fake_node_mod

import gg_robot.choreo as ch

PASS = 0


def check(name, cond):
    global PASS
    assert cond, f"❌ FAIL: {name}"
    PASS += 1
    print(f"✅ {name}")


def run_join(rid, start_offset=0.05):
    ch.runner.start(rid, time.time() + start_offset, None)
    ch.runner._runs[rid].thread.join(timeout=5)
    return ch.runner.status(rid)


# ── 用例1：at 调度 + 顺序执行 + finished ──
ch.runner.load("t1", [
    {"type": "wait", "duration": 0.05, "at": 0.0},
    {"type": "wait", "duration": 0.05, "at": 0.15},
    {"type": "wait", "duration": 0.05, "at": 0.30},
])
st = time.time()
s = run_join("t1")
elapsed = time.time() - st
check("t1 state=finished", s["state"] == "finished")
check("t1 total=3", s["total"] == 3)
check("t1 current=2", s["current"] == 2)
check("t1 failed 空", s["failed"] == [])
check("t1 总耗时 ≥ at 末值", elapsed >= 0.30)

# ── 用例2：步骤失败（tts 返回 False）跳过继续 ──
fake._do_tts = lambda text: (fake.calls.append(('tts', text)), False)[1]
ch.runner.load("t2", [
    {"type": "tts", "text": "x", "at": 0.0},
    {"type": "wait", "duration": 0.03, "at": 0.1},
])
s = run_join("t2")
check("t2 state=finished（失败也继续）", s["state"] == "finished")
check("t2 failed 记录 1 条 tts", len(s["failed"]) == 1 and s["failed"][0]["type"] == "tts")
fake._do_tts = lambda text: (fake.calls.append(('tts', text)), True)[1]

# ── 用例3：motion 无效组合 → failed ──
ch.runner.load("t3m", [
    {"type": "motion", "motion_id": 99999, "area": 9, "at": 0.0},
    {"type": "wait", "duration": 0.02, "at": 0.05},
])
s = run_join("t3m")
check("t3m motion 无效组合记 failed 且继续", s["failed"] and s["failed"][0]["type"] == "motion")

# ── 用例4：未知类型 → failed ──
ch.runner.load("t3u", [
    {"type": "hack", "at": 0.0},
    {"type": "wait", "duration": 0.02, "at": 0.05},
])
s = run_join("t3u")
check("t3u 未知类型记 failed 且继续", s["failed"] and s["failed"][0]["type"] == "hack")

# ── 用例5：stop 生效 ──
ch.runner.load("t4", [
    {"type": "wait", "duration": 5.0, "at": 0.0},
    {"type": "wait", "duration": 0.01, "at": 1.0},
])
ch.runner.start("t4", time.time() + 0.02, None)
time.sleep(0.15)
ch.runner.stop("t4")
ch.runner._runs["t4"].thread.join(timeout=5)
s = ch.runner.status("t4")
check("t4 state=stopped", s["state"] == "stopped")
check("t4 stop 后发了零速", ('vel', 0.0, 0.0, 0.0) in fake.calls)

# ── 用例6：未 load 直接 start / status 不存在 ──
s = ch.runner.start("nope", time.time(), None)
check("t6 未 load start 报错", s.get("ok") is False)
s = ch.runner.status("nope")
check("t6 status 不存在报错", s.get("ok") is False)

# ── 用例7：at 升序排序（乱序输入）──
ch.runner.load("t7", [
    {"type": "wait", "duration": 0.02, "at": 0.5},
    {"type": "wait", "duration": 0.02, "at": 0.0},
])
run = ch.runner._runs["t7"]
check("t7 按 at 排序", [st_.get("at") for st_ in run.steps] == [0.0, 0.5])

# ── 用例8：step 类型齐全执行（motion/emoji/velocity/mode/volume/linkcraft）──
ch.runner.load("t8", [
    {"type": "motion", "motion_id": 1002, "area": 2, "at": 0.0},
    {"type": "emoji", "emotion_id": 90, "at": 0.05},
    {"type": "velocity", "forward": 0.2, "duration": 0.03, "at": 0.1},
    {"type": "mode", "action_desc": "STAND_DEFAULT", "at": 0.15},
    {"type": "volume", "volume": 60, "at": 0.2},
    {"type": "linkcraft", "resource_key": "k1", "resource_type": "BODY_MONTION", "at": 0.25,
     "wait_done": False},
])
s = run_join("t8")
check("t8 全类型 finished 无失败", s["state"] == "finished" and s["failed"] == [])
check("t8 各类型均被调用", all(any(c[0] == k for c in fake.calls)
      for k in ('motion', 'emoji', 'vel', 'mode', 'volume', 'linkcraft')))

print(f"\n🎉 全部 {PASS} 项断言通过")
