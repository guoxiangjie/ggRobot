# 多机编排模块 — 开发跟进指南（面向后续开发者 / AI 模型）

> 分支：`2.0` ｜ 设计文档：`docs/choreo-design.md`（协议规范）｜ 本文：实现思路 + 代码地图 + 扩展指引
> 状态：**M1–M3 已实现并测试通过**（45 项断言），M4 实机验证待机器人上线
> 阅读顺序：§1 概览 → §2 数据流 → §3 设计决策（**必读，含踩坑**）→ §4 代码地图 → §5 协议 → §6 测试 → §7 扩展

---

## 1. 模块概述（一分钟理解）

**解决什么问题**：1.0 有两个编排模块（Task 作业 / Project 快捷动作台），编辑器复杂、bug 多，且**只能控制单台机器人**。2.0 要一个简单实用的**多机共同编排**——多台机器人在同一时间轴上演节目（齐舞、对话接龙、双机表演）。

**怎么解决**：**时间线多轨模型**。每台机器人一条轨道，轨道上是按 `at`（相对执行开始的秒偏移）排序的步骤；执行时平台把各机轨道预分发下去，广播一个**统一的绝对开始时刻** `start_ts`，各 agent 以它为时间轴原点**本地按 `at` 到点触发**。多机之间的"同时"由同一个墙钟锚定，不依赖网络往返对齐。

**范围**：agent（执行器）→ platform（编排器/CRUD）→ 前端（编辑器/监控）三端全链路。

```
编排定义 (platform SQLite)         执行中                     执行后
┌───────────────────┐   run →   ┌─────────────┐   终态 →   ┌──────────────┐
│ {name, tracks: [  │ ────────► │ 平台编排器：  │ ────────► │ 最近执行历史  │
│   {robot_id,      │           │ 分发→广播→聚合│           │ (每机结果)    │
│    steps:[{type,  │           └─────────────┘           └──────────────┘
│     at, ...}]}    │
└───────────────────┘
```

---

## 2. 数据流（执行全链路时序）

```
前端 Choreo 页                                platform server                    agent (每台)
─────────────────                          ────────────────                 ──────────────
1. 保存编排 → POST /api/choreos (tracks) → SQLite 落盘
2. 执行     → POST /api/choreos/{id}/run → runner.run()
                                           ├─ 校验：离线机跳过(offline 列表)
                                           ├─ 并发 POST /api/choreo/load {run_id, steps}
                                           ├─ start_ts = now + 1.5s
                                           ├─ 并发 POST /api/choreo/start {run_id, start_ts} ──► ChoreoRunner.start()
                                           │                                        │ 以 start_ts 为原点
                                           │                                        ▼ 执行线程按 at 推进
                                           ├─ 轮询各机 /api/choreo/status (1s) ◄─────── 步骤失败→记 failed 跳过
                                           │   掉线 3 次→该机 failed，其余继续
                                           └─ 全终态 → run finished → 记入 history
3. 前端轮询 /api/choreo/run/{id}/status → 展示每机 current/total + failed
   hub WS 每 5s 推 active runs（其他端触发的运行也可见）
```

**状态机**：
- run（平台级）：`pending → running → finished / stopped / failed`
- 机器人（平台聚合视图）：`loading → running → finished / stopped / failed / unavailable`（unavailable=启动前离线未参与）
- agent（单机）：`loaded → running → finished / stopped / failed`

---

## 3. 核心设计决策（必读——每个决策背后都是踩坑）

### 3.1 为什么用"时间线多轨"而不是 1.0 的并行组/分支块
- 时间线天然表达并发（多机同时做），不需要"并行组"这种抽象
- 没有分支/条件——编排是表演脚本，不是程序逻辑
- 编辑器因此极简：选机器人 → 排步骤时间点，没有 863 行的嵌套编辑器

### 3.2 为什么用"时间戳锚定"而不是平台逐条下发
- 平台逐条下发：每步一次 HTTP RTT（几十 ms）+ agent 执行耗时，多机误差累积，越跑越不同步
- 时间戳锚定：agent 用 `start_ts`（**绝对墙钟时刻**）而非"收到 start 消息的时刻"作为原点——各机 start 消息到达有先后（网络延迟差）不影响对齐；误差只取决于墙钟漂移（局域网 NTP 下 <100ms）
- 平台广播时给 `now + 1.5s` 余量，保证所有 agent 先收到 start 再开始

### 3.3 `at` 的语义："最早开始时刻"，不是"精确开始时刻"
```
实际开始 = max(start_ts + at, 上一步完成时刻)
```
- 步骤间**顺序执行**：上一步没做完（TTS 还在播、动作还在做），下一步到点也不会触发，等上一步完成
- 好处：同一轨不会自打架（不会出现"动作还没做完就被下一个动作打断"）
- 代价：`at` 只是"最早时刻"，若上一步超时，后续步骤整体顺延——**跨机对齐的精度取决于各轨步骤耗时是否正常**
- 排时间时若担心 TTS 超时拖慢，可在关键步骤后加 `wait` 缓冲步骤

### 3.4 为什么 agent 不用 task/steps.py 的 execute_step（重要！）
最初设计是复用，实测发现两个致命问题：
1. **`_tts` 在子线程里调 `_do_tts`**——异常被吞在子线程，choreo 收不到失败信号
2. **`execute_step` 内部 catch 异常只打日志、不重新抛**——choreo 根本不知道步骤失败

所以 `choreo.py` 内置轻量执行器 `_exec_step`（9 种类型各几行），失败直接 `raise`，由 `_execute` 记入 failed 并跳过继续。**复用**了 `task/motions.py` 的 `normalize_motion`（旧 ID 映射 + area 兜底）和 `motion_duration`（估时）。

### 3.5 失败处理：跳过继续 + 汇报
- 单步失败：记 `failed` 数组 → 继续下一步 → 结束时汇报
- 机器掉线（轮询连续 3 次无响应）：该机标 failed → 其余机继续跑
- 启动前离线/未登记：该机不参与（`offline` 列表返回前端提示），其余照跑
- 停止：平台并发调所有机 `stop`；agent 置停止标志 + 同步发全零速度收尾

### 3.6 会话锁集成
agent 的 POST 控制端点（load/start/stop）走中间件会话锁——同一时刻只有一个控制者（桌面端遥控、编排执行互斥），这是 2.0 的既有安全模型，编排不搞特殊。

### 3.7 步骤类型清单由 agent 上报（能力契约哲学）
前端表单不硬编码步骤类型——`GET /api/choreo/types` 由 agent 上报（`CHOREO_STEP_TYPES`），platform 透传，前端编辑器打开时拉取并覆盖本地 fallback。**多型号 agent（A2/A3/机器狗）接入只需裁剪这个清单，UI 无需发版**。

---

## 4. 代码地图

### 4.1 agent 侧（`agents/x2/gg_robot/`）

| 文件 | 职责 | 关键符号 |
|------|------|----------|
| `choreo.py` | 编排执行器（核心） | `ChoreoRunner`（load/start/stop/status）、`_Run`、`_execute`（调度循环）、`_exec_step`（9 类步骤执行）、`CHOREO_STEP_TYPES`（类型清单） |
| `routes/choreo.py` | REST 端点 | `POST /api/choreo/load\|start\|stop`、`GET /api/choreo/status\|types` |
| `routes/__init__.py` | 路由注册 | 已注册 choreo_router |
| `tests/test_choreo.py` | 调度回归单测 | 24 项断言（at 调度/失败跳过/停止/WS 上报/类型清单） |

**`_execute` 调度循环核心逻辑**（choreo.py）：
```python
for i, step in enumerate(run.steps):          # steps 已按 at 升序
    if run.stop_flag: break
    run.current = i
    due = run.start_ts + float(step.get("at", 0.0))
    while time.time() < due and not run.stop_flag:
        time.sleep(0.05)                       # 分片 sleep 等"最早时刻"
    if run.stop_flag: break
    report choreo.step started
    try:
        _exec_step(node, step)                 # 内部自带 motion/tts 估时等待
        report choreo.step done
    except Exception as e:
        run.failed.append(...); report choreo.step failed   # 跳过继续
# 收尾：发全零速度 → state = stopped|finished → report choreo.state
```

**线程模型**：执行在 daemon 线程（`threading.Thread`），只调线程安全的 node 方法（service 走 future 轮询、velocity 元组原子替换——与 1.0 task engine 的 parallel 分支同理）。**绝不阻塞 rclpy 回调**（executor 独立线程 spin，见 `__main__.py`）。

**WS 上报**：执行线程不能直接 await，用 `asyncio.run_coroutine_threadsafe(publish(...), run.loop)` 投递到 FastAPI 事件循环（`run.loop` 由 start 端点注入 `asyncio.get_running_loop()`）。模式照抄 `security.py` 的 `ControllerLock._notify_lost`。

### 4.2 platform 侧（`platform/server/ggplatform/`）

| 文件 | 职责 | 关键符号 |
|------|------|----------|
| `models.py` | 数据模型 | `Choreography` 表（tracks_json 存 JSON 字符串）；`Robot.port`（agent 端口，默认 8300） |
| `choreo/runner.py` | 编排执行器 | `ChoreoRunner`（run/stop/status/active_runs/history）、`ChoreoRun`、`_execute`（分发→广播→轮询聚合）、`_poll`（掉线判定） |
| `routes/choreo.py` | REST 端点 | CRUD（含 `_validate_tracks` 校验）+ run/stop/status/runs/types 透传 |
| `agent_client.py` | agent HTTP 客户端 | `choreo_load/start/stop/status`、`fetch_choreo_types` |
| `routes/hub.py` | hub 推送 | payload 附带 `choreo: active_runs` |
| `tests/test_choreo_e2e.py` | 端到端回归 | 21 项断言（假 agent×2 全链路） |

**`_execute` 关键参数**：`START_DELAY=1.5`（start_ts 余量）、`POLL_INTERVAL=1.0`（聚合轮询）、`POLL_FAIL_LIMIT=3`（掉线判定）、`RUN_TIMEOUT=600`（run 超时兜底）。全局同时只允许一个 active run（`_active_run_id` 锁）。

### 4.3 前端（`platform/desktop/src/renderer/src/`）

| 文件 | 职责 |
|------|------|
| `pages/Choreo.tsx` | 编排页：列表（卡片+执行/编辑/删除）→ 执行状态条（每机 current/total+停止）→ 编辑器弹窗（时间线多轨）→ 最近执行区块 |
| `api/platform.ts` | `api.listChoreos/getChoreo/saveChoreo/deleteChoreo/runChoreo/stopChoreoRun/choreoRunStatus/getChoreoTypes/choreoRuns` + `hubWs(onRobots, onChoreo?)` |

**编辑器交互**（刻意简单）：
- 机器人 Tag 点选 → 每台生成一条轨道（`tracks`）
- 轨道内步骤块按 `at` 排序横向排列，块显示时刻 + 类型图标 + 摘要
- 「+ 添加步骤」→ TypePicker 选类型 → StepModal 动态参数表单（字段来自 agent 上报的 types）
- 步骤块点击编辑、hover 出 × 删除；不做拖拽（第一版）
- 执行监控：run 后轮询 `choreoRunStatus` 1s 到终态；hub 实时显示其他端触发的 active run

**Semi Select 坑**：`<Select>` 泛型深度实例化（TS2589）——用显式泛型 `<Select<string> value optionList onChange>` 切断推断，别用 spread。

---

## 5. 协议规范（速查）

### 5.1 agent API（:8300，POST 走会话锁，Authorization: Bearer）

| 端点 | 请求 | 响应 |
|------|------|------|
| `POST /api/choreo/load` | `{run_id, steps}` | `{ok, run_id, loaded}` |
| `POST /api/choreo/start` | `{run_id, start_ts}` | `{ok, run_id, start_ts}` |
| `POST /api/choreo/stop` | `{run_id}` | `{ok, run_id}` |
| `GET /api/choreo/status` | `?run_id=` | `{ok, run_id, state, current, total, failed[]}` |
| `GET /api/choreo/types` | — | `{types: [{type,label,icon,color,fields[]}]}` |

### 5.2 platform API（127.0.0.1:8310）

| 端点 | 说明 |
|------|------|
| `GET/POST/PATCH/DELETE /api/choreos` | CRUD（tracks 结构见 §2） |
| `POST /api/choreos/{id}/run` | 执行 → `{ok, run_id, offline[]}` |
| `POST /api/choreo/run/{run_id}/stop` | 停止全部机器 |
| `GET /api/choreo/run/{run_id}/status` | 聚合状态（robots 数组） |
| `GET /api/choreo/runs` | 最近执行历史（内存 deque，20 条） |
| `GET /api/choreo/types?robot_id=` | 步骤类型透传（缺省第一台已登记有 IP 的机器人） |

### 5.3 WS 事件（agent → 订阅者，topic `choreo.*`）

```json
{"v":1,"type":"event","topic":"choreo.step","data":{"run_id":"…","index":2,"type":"motion","at":2.0,"status":"started|done|failed"}}
{"v":1,"type":"event","topic":"choreo.state","data":{"run_id":"…","state":"running|finished|stopped|failed","failed":[…]}}
```
平台目前靠**轮询**聚合（未订阅 WS），WS 事件是给桌面端直连 agent 数据面用的。

---

## 6. 测试与验证

```bash
make test          # 一键回归 = test-agent + test-e2e（45 项断言）
make test-agent    # agent 单测（无 rclpy 依赖，需 /opt/homebrew/bin/python3.12）
make test-e2e      # platform e2e（需 platform/server/.venv，端口 8300/8301/8320 空闲）
```

- **agent 单测**（`agents/x2/tests/test_choreo.py`）：注入假 `gg_robot.node` 模块（绕过 rclpy import）+ 假 `ws.stream.publish`，直接测 `ChoreoRunner` 调度逻辑
- **e2e**（`platform/server/tests/test_choreo_e2e.py`）：起 2 个假 agent（模拟 choreo 协议）+ 真 platform，走 pair/register → 建编排 → run → 聚合 → stop → 历史全链路
- 前端：`cd platform/desktop && ./node_modules/.bin/tsc --noEmit -p tsconfig.web.json && ./node_modules/.bin/electron-vite build`

**改 agent/platform 代码后必跑**：`make test`。改前端后必跑 tsc + build。

---

## 7. 部署与实机验证（M4）

```bash
make agent-deb      # 打 deb（需 /opt/homebrew/bin 在 PATH：dpkg-deb）
make agent-deploy   # scp deb → sudo -n apt install（实机在线时）
cd platform/desktop && pnpm dev   # 桌面端（sidecar 自动拉起，8310 已有实例则复用）
```

**实机验证步骤**：
1. 设备页确认机器人 active（pending → active 需 hub 刷新 + token 校验）
2. 编排页 → 新建 → 选两台机器人 → 各排一条轨道（如 A 机"大家好"+挥手 at=2，B 机"欢迎光临"+比心 at=1）
3. 执行 → 观察状态条每机 current/total + 实际动作时序是否对齐
4. 时序校准：TTS 超时会顺延后续步骤（§3.3），必要时加 `wait` 缓冲步骤

**实机坑（部署链路已验证）**：
- 新加 `.py` 文件必须 `chmod 644`，否则 rsync 进 deb 后 root:root 600，agent 以 agi 运行会 PermissionError（已踩）
- agent 改动后三连验证（CLAUDE.md 铁律）：pyflakes → curl /api/health → WS 握手

---

## 8. 已知限制与遗留（后续可做）

| 遗留 | 说明 | 建议方案 |
|------|------|----------|
| 步骤级跨机依赖 | 现无"等某机某步完成"原语，对话接龙靠 at 估算 | agent 完成事件跨机联动（WS 事件 + 平台协调） |
| 拖拽时间线 | 编辑器是"添加步骤+填 at"，非拖拽 | canvas/dnd 时间线，二期 |
| 执行记录持久化 | history 在内存（重启丢） | 落 SQLite 表 + 回放 |
| 编排预演 | 无 dry-run | 前端按 motion_duration/估时画时间轴预览 |
| 多型号类型并集 | 类型清单取第一台机器 | 编辑器按参与机器人分别拉取并集 |

---

## 9. 后续模型开发指引（常见任务怎么做）

**加一个步骤类型**（如"播放照片"）：
1. agent `choreo.py`：`_exec_step` 加 `elif t == "photo":` 分支（调 node 方法，失败 raise）+ `CHOREO_STEP_TYPES` 加清单项（字段定义驱动前端表单）
2. `make test-agent`（类型清单断言会自动校验字段结构）
3. 前端无需改（动态组装）；想本地兜底可在 `Choreo.tsx` 的 `STEP_META` 补一份

**加一个新 agent 控制端点**：照 `routes/choreo.py` 模式（POST 自动走会话锁），`agent_client.py` 加 fetch 函数，runner/routes 接上，e2e 假 agent 补端点 + 断言。

**调同步精度**：
- `START_DELAY`（1.5s）太小 → 慢机器 start 消息到得晚，可加大
- 墙钟漂移大 → 检查机器人 NTP；或将来在 start 前加"对时"握手（agent 回传本地时间偏差）

**排查"某机没动"**：
1. `GET /api/choreo/run/{id}/status` 看该机 state/error
2. agent 侧日志（`systemctl --user status ggrobot-agent`）看 `🎬` 前缀日志
3. 确认该机 agent 版本含 choreo（`curl /api/choreo/types` 有响应 = 已注册）
4. 确认执行时该机没被其他端会话锁占用（POST 会 409）

**改前端编排页**：`Choreo.tsx` 单文件为主（列表/编辑器/监控/历史都在），样式在 `global.css` 的 `choreo-*` 类。

---

## 10. 提交历史与状态

```
a762071  M1 agent choreo 执行器（时间戳锚定 + at 调度 + 失败跳过）
c52e01c  M2 platform 编排器（CRUD/分发/广播/聚合 + Robot.port）
4bd108f  M3 React 编排页（列表/监控/时间线编辑器）
0944b33  WS 上报单测 + hub 推送 e2e + make test
f92b0d5  步骤类型清单 agent 上报（前端表单动态组装）
1e200ee  CLAUDE.md 多机编排章节
43d5f6f  最近执行历史（终态回看）
```

**完成定义（M4 验收）**：两台 X2 实机 → 编排页排双机时间线 → 执行 → 各机动作/语音按 at 对齐（误差目测 <0.5s）→ 状态条与失败汇报正确 → 停止/中断有效。
