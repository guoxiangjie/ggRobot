"""M2 端到端回归测试：假 agent ×2 + platform，验证编排 分发→广播→聚合→失败跳过

运行：platform/server/.venv/bin/python platform/server/tests/test_choreo_e2e.py
依赖：venv（fastapi/uvicorn/httpx/sqlmodel/websockets），端口 8300/8301/8320 需空闲
覆盖：pair/register(含 port) → 编排 CRUD/校验 → run 分发广播聚合 → 双机执行 +
失败跳过 → 幽灵机离线跳过 → stop → hub 推送 choreo。假 agent 模拟 choreo 协议（无鉴权）。
"""

import asyncio
import json
import os
import socket
import sys
import threading
import time

SERVER_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, SERVER_DIR)

import websockets

from fastapi import FastAPI
from fastapi.responses import JSONResponse
import httpx
import uvicorn


def port_free(port: int) -> bool:
    """探测端口可绑定（SO_REUSEADDR 匹配 uvicorn 行为，避免 TIME_WAIT 误判）"""
    s = socket.socket()
    try:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(("127.0.0.1", port))
        return True
    except OSError:
        return False
    finally:
        s.close()


async def _grab_hub_choreo(port: int, timeout: float = 5.0) -> list:
    """连 hub 拿一条带 choreo 的消息（连上即推全量）"""
    async with websockets.connect(f"ws://127.0.0.1:{port}/hub") as ws:
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                msg = json.loads(await asyncio.wait_for(ws.recv(), timeout=max(0.1, deadline - time.time())))
            except Exception:
                break
            if msg.get("type") == "hub":
                return msg.get("choreo") or []
    return []


# ── 假 agent（无鉴权，模拟 choreo 协议）──
class FakeAgent:
    def __init__(self, sn: str, host: str, port: int, fail_step: bool = False):
        self.sn = sn
        self.host = host
        self.port = port
        self.fail_step = fail_step
        self.runs: dict[str, dict] = {}
        self.loaded: dict[str, list] = {}
        self.app = FastAPI()
        self._routes()

    def _routes(self):
        a = self.app

        @a.get("/api/health")
        def health():
            return {"ok": True, "service": "ggrobot-agent", "sn": self.sn,
                    "model": "x2", "version": "2.0.1", "paired": True}

        @a.post("/api/choreo/load")
        def load(req: dict):
            self.loaded[req["run_id"]] = req.get("steps", [])
            return {"ok": True, "run_id": req["run_id"], "loaded": len(req.get("steps", []))}

        @a.post("/api/choreo/start")
        def start(req: dict):
            rid = req["run_id"]
            steps = self.loaded.get(rid, [])
            self.runs[rid] = {"state": "running", "current": -1, "total": len(steps), "failed": []}

            def _work():
                for i, st in enumerate(steps):
                    # wait 步骤按 duration 模拟（上限 5s 防测试卡死），其余步骤 0.25s
                    if st.get("type") == "wait":
                        time.sleep(min(float(st.get("duration", 0.25) or 0.25), 5.0))
                    else:
                        time.sleep(0.25)
                    self.runs[rid]["current"] = i
                    if self.fail_step and i == 0:
                        self.runs[rid]["failed"].append(
                            {"index": i, "type": st.get("type"), "at": st.get("at"), "error": "sim-fail"})
                self.runs[rid]["state"] = "finished"
            threading.Thread(target=_work, daemon=True).start()
            return {"ok": True, "run_id": rid}

        @a.post("/api/choreo/stop")
        def stop(req: dict):
            rid = req["run_id"]
            if rid in self.runs:
                self.runs[rid]["state"] = "stopped"
            return {"ok": True, "run_id": rid}

        @a.get("/api/choreo/types")
        def types():
            return {"types": [
                {"type": "tts", "label": "语音", "icon": "🗣️", "color": "#4CAF50",
                 "fields": [{"name": "text", "label": "播报文字", "kind": "text", "required": True}]},
                {"type": "motion", "label": "预设动作", "icon": "🕺", "color": "#FF9800",
                 "fields": [{"name": "motion_id", "label": "动作 ID", "kind": "number", "required": True}]},
            ]}

        @a.get("/api/choreo/status")
        def status(run_id: str):
            r = self.runs.get(run_id)
            if r is None:
                return JSONResponse({"ok": False, "error": "run 不存在"}, status_code=404)
            return {"ok": True, **r}

    def start(self):
        threading.Thread(target=uvicorn.run, args=(self.app,),
                         kwargs={"host": self.host, "port": self.port, "log_level": "warning"},
                         daemon=True).start()


def wait_http(url, timeout=8.0):
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            httpx.get(url, timeout=1.0)
            return True
        except Exception:
            time.sleep(0.2)
    return False


PASS = 0


def check(name, cond):
    global PASS
    assert cond, f"❌ FAIL: {name}"
    PASS += 1
    print(f"✅ {name}")


def main():
    for p in (8300, 8301, 8320):
        assert port_free(p), f"端口 {p} 被占用，测试需空闲端口"

    agent_a = FakeAgent("sim-A1", "127.0.0.1", 8300)
    agent_b = FakeAgent("sim-B2", "127.0.0.1", 8301, fail_step=True)
    agent_a.start()
    agent_b.start()

    db = "/tmp/choreo-e2e.db"
    if os.path.exists(db):
        os.remove(db)
    os.environ["GG_PLATFORM_DB"] = db
    from ggplatform.app import create_app
    threading.Thread(target=uvicorn.run, args=(create_app(),),
                     kwargs={"host": "127.0.0.1", "port": 8320, "log_level": "warning"},
                     daemon=True).start()

    base = "http://127.0.0.1:8320"
    assert wait_http(f"{base}/healthz"), "platform 未就绪"
    assert wait_http("http://127.0.0.1:8300/api/health"), "agent A 未就绪"
    assert wait_http("http://127.0.0.1:8301/api/health"), "agent B 未就绪"
    print("🟢 三个服务就绪")

    c = httpx.Client(base_url=base, timeout=5.0)

    # 1. 登记两台机器人（B 用 8301 端口）
    ra = c.post("/api/pair/register", json={"sn": "sim-A1", "ip": "127.0.0.1", "name": "A机", "model": "x2"}).json()
    rb = c.post("/api/pair/register", json={"sn": "sim-B2", "ip": "127.0.0.1", "name": "B机", "model": "x2", "port": 8301}).json()
    check("pair/register A", ra.get("token") is not None)
    check("pair/register B", rb.get("token") is not None)
    id_a, id_b = ra["robot"]["id"], rb["robot"]["id"]

    # 2. 创建双机编排
    rc = c.post("/api/choreos", json={"name": "双机测试", "desc": "e2e", "tracks": [
        {"robot_id": id_a, "robot_name": "A机", "steps": [
            {"type": "wait", "duration": 0.1, "at": 0.0},
            {"type": "wait", "duration": 0.1, "at": 0.3}]},
        {"robot_id": id_b, "robot_name": "B机", "steps": [
            {"type": "tts", "text": "hi", "at": 0.0},
            {"type": "wait", "duration": 0.1, "at": 0.3}]},
    ]}).json()
    check("创建编排", rc.get("id") is not None)
    check("编排统计", rc["robot_count"] == 2 and rc["step_count"] == 4)
    choreo_id = rc["id"]

    # 3. 校验：缺 robot_id 的轨道被拒；步骤类型清单透传
    check("非法轨道 400", c.post("/api/choreos", json={"name": "bad", "tracks": [{"steps": []}]}).status_code == 400)
    rt = c.get("/api/choreo/types").json()
    check("choreo/types 透传 agent 上报",
          len(rt.get("types") or []) == 2 and rt.get("robot_id") in (id_a, id_b))

    # 4. 执行
    rr = c.post(f"/api/choreos/{choreo_id}/run").json()
    check("run 返回 run_id", rr.get("ok") and rr.get("run_id"))
    check("run 无离线机", rr.get("offline") == [])
    run_id = rr["run_id"]

    # 5. 轮询到终态
    state = None
    for _ in range(30):
        state = c.get(f"/api/choreo/run/{run_id}/status").json()
        if state.get("state") in ("finished", "stopped", "failed"):
            break
        time.sleep(0.5)
    check("run 最终 finished", state.get("state") == "finished")
    by_id = {rb_["robot_id"]: rb_ for rb_ in state["robots"]}
    check("A 机 finished", by_id[id_a]["state"] == "finished")
    check("B 机 finished（失败也跑完）", by_id[id_b]["state"] == "finished")
    check("B 机 failed 记录 sim-fail", len(by_id[id_b]["failed"]) == 1)
    check("A 机无失败", by_id[id_a]["failed"] == [])

    # 6. 幽灵机（未登记）离线跳过，A 照常执行
    rc3 = c.post("/api/choreos", json={"name": "三机", "tracks": [
        {"robot_id": id_a, "steps": [{"type": "wait", "duration": 0.1, "at": 0.0}]},
        {"robot_id": "ghost-robot", "steps": [{"type": "wait", "duration": 0.1, "at": 0.0}]},
    ]}).json()
    rr3 = c.post(f"/api/choreos/{rc3['id']}/run").json()
    check("幽灵机离线跳过", rr3.get("ok") and rr3.get("offline") == ["ghost-robot(未登记)"])
    st3 = None
    for _ in range(20):
        st3 = c.get(f"/api/choreo/run/{rr3['run_id']}/status").json()
        if st3.get("state") in ("finished", "stopped", "failed"):
            break
        time.sleep(0.5)
    check("三机 run A 照常 finished",
          [r for r in st3["robots"] if r["robot_id"] == id_a][0]["state"] == "finished")

    # 7. 停止功能 + hub 推送 choreo 验证（长跑 30s，hub 连上即推能抓到 active run）
    rl = c.post("/api/choreos", json={"name": "长跑", "tracks": [
        {"robot_id": id_a, "steps": [{"type": "wait", "duration": 30, "at": 0.0}]},
    ]}).json()
    rrl = c.post(f"/api/choreos/{rl['id']}/run").json()
    time.sleep(1.0)
    hub_choreo = asyncio.run(_grab_hub_choreo(8320))
    check("hub 推送含 choreo active runs",
          any(r["run_id"] == rrl["run_id"] and r["state"] == "running" for r in hub_choreo))
    check("stop 返回 ok", c.post(f"/api/choreo/run/{rrl['run_id']}/stop").json().get("ok"))
    time.sleep(1.0)
    stl = c.get(f"/api/choreo/run/{rrl['run_id']}/status").json()
    check("长跑 run 已停止", stl.get("state") in ("stopped", "finished"))

    print(f"\n🎉 M2 端到端：全部 {PASS} 项断言通过")


if __name__ == "__main__":
    main()
