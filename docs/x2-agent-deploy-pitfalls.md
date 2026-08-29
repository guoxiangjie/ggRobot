# X2 实机部署踩坑实录（2.0 Phase 0，2026-08-18~19）

所有结论均在 10.10.4.175（Orin NX, Ubuntu 22.04, AimDK 1.0+沙盒）实机验证。
新机器人接入 / agent 排障前先读本文。

## 一、沙盒架构（一切怪象的总根源）

X2 1.0+ 引入 **agi rootfs 文件系统隔离沙盒**：用户程序（ssh 登录后的全部世界）跑在独立
沙盒 rootfs，与系统 rootfs（运控/agibot_* 服务所在）隔离。沙盒与真系统通过
bind mount 共享部分目录——**`/home/agi`（沙盒视图）与 `/agibot/data/home/agi`（真系统视图）
是同一目录的两个视角**，这个特性是 unit/脚本路径设计的基础。

| 现象 | 根因 |
|---|---|
| dpkg 维护脚本里 systemctl 报 `Running in chroot` | dpkg 在沙盒 rootfs，探测到真系统 PID1 |
| sudoers 免密仅 `apt/nmcli/nmtui/ifconfig` | 官方开放的沙盒安全出口 |
| user systemd manager 启的进程看不到 /opt 的文件 | user manager 在真系统侧视图，沙盒内装的文件它看不见 |
| `AGIBOT_SN` 非交互 ssh 读不到 | 定义在沙盒 .bashrc 交互段（非交互 shell 提前 return） |

## 二、自启动正解（实测版，综合官方 SOP 与固件差异）

unit：`~/.config/systemd/user/ggrobot-agent.service`（postinst 自动生成）：

```ini
[Service]
WorkingDirectory=/agibot/data/home/agi/
ExecStart=/usr/bin/agirun /bin/bash /agibot/data/home/agi/.config/systemd/ggrobot-start.sh
StandardOutput=journal+console
Restart=on-failure
```

关键实测修正（**与官方 SOP 文档的差异**）：
- SOP 写的 `/bin/bash /usr/bin/agirun ...` 双 bash 包裹在本机报
  `agirun: cannot execute binary file`(126)——**本机 agirun 是 ELF 二进制，直接执行**，外层套 bash 会把它当脚本解析
- 启动脚本（`~/.config/systemd/ggrobot-start.sh`）内**必须** source
  `/agibot/data/home/agi/.aima/env/bashrc`（user systemd 场景的 DDS 配置未与机器同步，官方 SOP 明示）
- **linger 无法开启**（交互/非交互均被 polkit 拒）→ 无登录时段 user systemd 不运行。
  实测本机重启后 agent 能自启（登录会话触发 user manager → enabled unit 拉起）
- **不能用 cron 保活 + unit 双通道**：会双开抢 8300；如需并存必须 flock 单实例锁
  `/tmp/ggrobot-agent.lock`（当前方案已精简为纯 unit）

## 三、SN 读取

正确姿势（装机向导 / 任何需要 SN 的场景）：

```bash
bash -ic 'echo $AGIBOT_SN'        # 交互模拟，读 .bashrc 交互段 → X220028C6Y0243
```

- `runuser -u agi -- bash -lc` 拿不到（root 环境差异）；`ssh host 'echo $AGIBOT_SN'` 也拿不到（非交互）
- 兜底链：bash -ic AGIBOT_SN → /etc/environment grep → `tr -d '\0' < /proc/device-tree/serial-number`
  （模组 SN，**必须 tr 清 \0 尾巴**，它是定长缓冲区属性）
- postinst（root 环境）bash -ic 不可靠 → **向导读到的 SN 随 /tmp/gg-sn 下发**，postinst 优先吸收

## 四、token 与 conf

- conf 位置：`~/.config/ggrobot-agent.conf`（**agi 域**，600 agi:agi）——SSH 可直写 →
  平台**快速配对**（写 token + `systemctl --user restart`，免 apt 重装）
- 旧 `/etc/ggrobot-agent.conf`（root 域）由 postinst 自动迁移；agi 无法写 /etc
- agent 的 conf 只在**进程启动时读一次**（内存缓存）——token 更新后必须重启服务
- 装机向导下发的 token 是"配对"语义：postinst 里 conf 已存在时 sed 更新（不是"永不覆盖"）

## 五、Python 环境

- **系统 python3，不用 venv**（与 1.0 启动环境完全一致）：aimdk_msgs 依赖的 numpy、
  ROS PYTHONPATH 全在系统层；venv 隔离会 `ModuleNotFoundError: numpy`
- postinst 用 `pip3 install -r requirements.txt`（Ubuntu 22.04 无 PEP668 限制，幂等）
- start 脚本**绝不能 `set -u`**：ROS2 setup.bash 引用未定义变量
  （`AMENT_TRACE_SETUP_FILES: unbound variable`）直接炸；`set -e` 慎用（见下）

## 六、脚本与打包的隐形坑

- **`set -e` 陷阱**：独立语句 `[ -f x ] && cmd` 在条件假时整体返回非零 → 中断脚本。
  必须写 `[ -f x ] && cmd || true`（postinst 曾因此中断，agent 被 pkill 后无人拉起）
- **import 名不一致 py_compile 抓不到**（运行时才炸）：`ws/stream.py` 曾 import
  `verify_token` 而 security.py 定义的是 `verify_bearer`，本地无 ROS 起不了进程测不出。
  **每次改 agent 代码后必须 `pyflakes` + 实机 curl /api/health + WS 握手三连验证**
- deb 构建必须 `dpkg-deb --build --root-owner-group`（Mac 无 root 概念）

## 七、Mac 侧（Electron/平台）

- **electron 二进制下载**：`ELECTRON_MIRROR=https://npmmirror.com/mirrors/electron/`
- **extract-zip 解压 Electron.app 会丢 Frameworks**（symlink 处理缺陷）→
  手动 `curl + unzip` 到 node_modules 对应目录并写 `path.txt`（无换行）
- pnpm v11 构建脚本白名单在 `pnpm-workspace.yaml` 的 `allowBuilds`
- Semi Design：css 子路径未在 package.json exports 映射 → vite alias 直指文件绕过；
  `Select` 泛型深递归 → 相机选择换按钮组
- **PyInstaller 入口必须 `run.py` 模块导入**（`from ggplatform.__main__ import main`），
  直接以 `__main__.py` 为入口则包内相对导入失效
- **spawn 的 cwd 不存在时 Node 报 ENOENT 指向 file**（误导性报错）——prod sidecar cwd
  用二进制所在目录
- sidecar **单例复用**：启动前探测 8310-8330 已有 ggplatform 直接复用（多 App 窗口
  共享同一 sidecar/DB）；App 退出不杀 sidecar（常驻复用，下次秒连）
- 平台 DB 在 `app.getPath('userData')/data.db`（GG_PLATFORM_DB 注入；默认相对路径会
  写进 .app 包内，重装即丢）

## 八、快速配对流程（最终形态）

```
扫描网段（TCP :8300 + health 免token）→ 未登记设备「配对」→ SSH 密码
→ bash -ic 读 SN → 平台 register 生成 token → sftp 直写 ~/.config/ggrobot-agent.conf
→ systemctl --user restart → health+token 双确认 → 总览点亮
```

新机器人（无 agent）仍走完整装机：推 deb → `sudo -n apt install`（免密白名单）→
postinst（pip 依赖/SN 烧录/conf/unit 注册/启动）。

## 九、版本

- deb 版本 = `git describe --tags --always --dirty`（tag v2.0.0 → 2.0.0）
- agent `/api/health` 返回 version，平台可提示升级
