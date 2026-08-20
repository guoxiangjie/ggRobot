# 多机共同编排模块设计 v1（ggRobot 2.0）

> 状态：设计稿（待评审后分阶段实施）
> 分支：2.0

## 1. 背景与目标

1.0 有两个编排模块，均有明显不足：

| 模块 | 模型 | 主要问题 |
|------|------|----------|
| Task（作业） | 顺序步骤 + 并行组/分支块 | 编辑器 863 行过于复杂；并行/分支/合并弹窗 bug 多 |
| Project（快捷动作台） | 无序节点集合，手动单点执行 | 无流程概念，只适合快捷动作 |

**目标**：揉成一个简单实用的编排模块，核心新增能力是 **多台机器人共同参与编排执行**（齐舞、对话接龙、多机表演）。

**设计原则**：
- 简单：去掉并行组/分支块/变量模板/HTTP 步骤/AI 生成（第一版）
- 实用：步骤类型保留表演核心（语音/动作/表情/速度/模式/媒体/等待）
- 多机：时间线多轨模型 + 时间戳锚定同步，天然表达"谁在什么时候做什么"

## 2. 数据模型（platform SQLite）

```json
{
  "id": "ch_xxx",
  "name": "双机开场秀",
  "desc": "",
  "created_at": "…",
  "tracks": [
    {
      "robot_id": "<platform Robot.id>",
      "robot_name": "X2-1号",          // 冗余展示字段
      "steps": [
        {"type": "tts", "text": "大家好", "at": 0.0},
        {"type": "motion", "motion_id": 1007, "area": 3, "at": 2.0},
        {"type": "emoji", "emotion_id": 90, "mode": 1, "at": 4.5}
      ]
    },
    {
      "robot_id": "<Robot.id B>",
      "steps": [
        {"type": "tts", "text": "欢迎光临", "at": 0.5},
        {"type": "velocity", "forward": 0.3, "duration": 2.0, "at": 3.0}
      ]
    }
  ]
}
```

- **`at`**：步骤最早开始时刻（秒，相对执行开始时刻 `start_ts` 的偏移，float）
- **步骤类型**（复用 agent `task/steps.py` 的 STEP_HANDLERS 子集）：
  `tts` / `motion` / `emoji` / `velocity` / `mode` / `media` / `linkcraft` / `wait`
- 表结构：`choreographies`（id, name, desc, tracks_json, created_at, updated_at），SQLModel 定义在 `platform/server/ggplatform/models.py`
- 步骤参数校验：走 agent 的 `CAPABILITIES` 清单（前端表单动态生成，`GET /api/capabilities`）

## 3. 执行协议（platform ↔ agent）

新增 agent 端点（`agents/x2/gg_robot/routes/choreo.py`，控制类 POST 走会话锁）：

| 端点 | 方法 | 说明 |
|------|------|------|
| `/api/choreo/load` | POST | 预分发：`{run_id, steps}`，agent 存入内存并回复 loaded |
| `/api/choreo/start` | POST | 广播开始：`{run_id, start_ts}`（Unix 秒，浮点，**绝对墙钟时刻**） |
| `/api/choreo/stop` | POST | 停止：`{run_id}`，中止执行线程 |
| `/api/choreo/status` | GET | 主动查询：`{run_id}` → `{state, current, total, failed:[]}` |

WS 事件（agent → 平台/桌面端，topic `choreo.*`，沿用 WS v2 订阅制）：

```json
{"v":1,"type":"event","topic":"choreo.state","data":{"run_id":"…","state":"running|finished|stopped|failed"}}
{"v":1,"type":"event","topic":"choreo.step","data":{"run_id":"…","index":2,"type":"motion","at":2.0,"status":"started|done|failed"}}
```

**同步关键**：agent 用 `start_ts`（而不是收到 start 消息的本地时刻）作为时间轴原点 —— 平台广播时给 `now + 1.5s` 余量，各机即使 start 消息到达有先后（网络延迟差），时间轴仍锚定同一绝对时刻，误差取决于各机墙钟漂移（局域网 NTP 下 <100ms，可接受）。

## 4. agent 执行器（`agents/x2/gg_robot/choreo.py`）

```
ChoreoRunner（每 run_id 一个实例）
  load(run_id, steps)        # 存内存；同一 run 重复 load 覆盖
  start(run_id, start_ts)    # 起执行线程（daemon），不阻塞 rclpy 回调
  stop(run_id)               # 置停止标志 + 发全零速度
  status(run_id)             # 状态查询
```

**步骤调度（每轨内顺序，跨轨独立）**：
```
t0 = start_ts
for i, step in enumerate(steps):          # steps 已按 at 升序
    due = t0 + step.at                     # 最早开始时刻
    while now < due and not stop: sleep 50ms   # 等到点
    if stop: break
    execute_step(node, step, ctx)          # 复用现有执行器（含 motion/tts 等待逻辑）
    report choreo.step (done/failed)
report choreo.state (finished)
```

- 步骤间**顺序执行**：每步实际开始 = `max(due, 上一步完成时刻)`。`at` 只是"最早开始时刻" —— 这样同一轨内不会自打架（TTS 未播完不会和下一步冲突），跨机同步仍由 `at` 锚定（各机对同一 `start_ts` 有相同的"最早时刻"约束）
- **失败跳过**：步骤异常 → 记入 failed 列表、上报 `choreo.step failed`、**继续下一步**；结束后 `choreo.state finished` 携带 failed 明细
- **停止**：停止标志 + 立即发全零速度（安全收尾）
- 会话锁：`load/start/stop` 走 HTTP 中间件锁（与其它控制操作一致，同一时刻只有一个控制者）

## 5. platform 编排器（`platform/server/ggplatform/choreo/`）

```
Choreo CRUD（routes/choreo.py）
  GET/POST/PATCH/DELETE /api/choreo(s)         # SQLite 持久化
  POST /api/choreo/{id}/run                    # 执行编排
  POST /api/choreo/run/{run_id}/stop           # 停止全部机器
  GET  /api/choreo/run/{run_id}/status         # 聚合状态（供轮询/hub 推送）

执行流程（ChoreoRunner.run）：
  1. 校验：所有 track 的 robot 都在线（health 通）且未被其它会话占用
  2. 分发：对每台 robot 并发 POST /api/choreo/load {run_id, steps}
  3. 等全部 loaded（超时 5s，超时视为失败跳过该机）
  4. start_ts = now + 1.5s；并发广播 POST /api/choreo/start
  5. 监控：轮询各机 /api/choreo/status（1s）或订阅 WS choreo.*
     → 聚合进 run 状态：每机 {state, current, total, failed[]}
  6. 全部 finished/stopped → run 结束，落库执行记录（可选）
  7. 失败处理：某机掉线/超时 → 标记该机 failed，其余机继续（跳过继续+汇报）
```

- 运行状态经 hub WS 推送前端（`{"type":"choreo","run":{…}}`），前端执行页实时刷新
- 与全局急停联动：`/api/estop` 也应能停编排（同机并发 stop）

## 6. 前端设计（platform/desktop React）

侧边栏新增 **编排** 入口，三个视图：

### 6.1 编排列表（ChoreoList）
复用 RobotList 的卡片风格：名称/描述/参与机器人数/步骤数，新建/编辑/删除/执行。

### 6.2 编排编辑器（ChoreoEditor）—— 时间线多轨，刻意保持简单
- 顶部：名称/描述 + **机器人多选**（从平台 `/api/robots` 拉，选中的每台生成一条轨道）
- 主体：**每台机器人一行轨道**（左列机器人名），轨道内步骤块按 `at` 升序横向排列，块上显示 `at` 时刻 + 摘要（如 `"你好"` / `🕺 比心`）
- 交互（不做拖拽，第一版）：
  - 「+ 添加步骤」：选轨道 → 选类型（下拉，选项来自 agent capabilities）→ 填参数 + `at` 时刻 → 追加
  - 步骤块点击 → 编辑弹窗（参数表单 + at）；删除按钮；上下移（调整顺序/at）
- 时间提示：块下方显示**估算结束时刻**（motion/tts 用时长表估时，帮用户排布不打架）

### 6.3 执行监控（ChoreoRun）
- 每台机器一行：状态标签（等待/执行中/完成/失败）+ 当前步骤摘要 + 进度（current/total）
- 全局：开始时刻、已耗时、停止按钮、结束汇总（各机 failed 明细）

## 7. 与 1.0 的取舍（明确砍掉）

| 砍掉 | 原因 |
|------|------|
| 并行组 / 分支块 / 合并弹窗 | 复杂度与 bug 源头；时间线天然表达并发 |
| 变量模板 {{var}} / HTTP 步骤 | 对接场景，非表演核心；需要时单机 task 仍保留 |
| AI 生成 | 用户决策暂不做 |
| 任务/项目双入口 | 合并为单一编排入口 |

## 8. 分阶段实施

| 阶段 | 内容 | 验证 |
|------|------|------|
| M1 | agent choreo 执行器 + 路由 + WS 上报 | 单机 load/start/stop 本地跑通（mock start_ts） |
| M2 | platform choreo CRUD + 编排器（分发/广播/聚合/失败跳过） | 双机（或 mock agent）跑通全链路 |
| M3 | 前端列表/编辑器/执行监控 | 桌面端全流程可用 |
| M4 | 实机验证 + 时序校准 | X2 实机多机表演 |

## 9. 遗留问题（后续版本）

- 步骤级"等某机某步完成"依赖（对话接龙更精准）—— 需 agent 完成事件跨机联动
- 拖拽式时间线编辑
- 执行记录持久化 + 回放
- 编排预演（dry-run 预览时间轴）
