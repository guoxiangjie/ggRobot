"""A3 能力数据 — 资源服务动态拉取（GetResourceList）+ 静态兜底

与 X2 的差异：X2 是静态 motions.yaml；A3 动作/表情/技能是机上资源体系，
RPC 拉取真实清单（自带 duration 毫秒——编排无需实测估时）。
限频约束：GetResourceList 是查询类 RPC，长缓存（默认 300s）+ 显式刷新端点。
"""

import logging
import time

logger = logging.getLogger(__name__)

# ── 模式（Action 状态机，docs 7.1.1）──
MODE_LIST = [
    {"action": "MOTION", "name": "运动模式（行走/上肢）", "safe": True},
    {"action": "PD_STAND", "name": "位控站立", "safe": True},
    {"action": "DAMPING", "name": "阻尼模式", "safe": True},
    {"action": "PASSIVE", "name": "默认模式", "safe": True},
]

# 仅推荐程序切换的（其余 SIT_DOWN/LIE_DOWN 等涉及吊装，手动操作，不上报）
MIGRATE_STATES: list = []   # A3 无 X2 的模式迁移语义

# ── 速度档位（m/s；A3 日常行走 <1.2，上限见 config.VEL_MAX_*）──
GEAR_PRESETS = [
    {"name": "低速", "forward": 0.3, "lateral": 0.2, "angular": 0.4},
    {"name": "标准", "forward": 0.6, "lateral": 0.4, "angular": 0.7},
    {"name": "高速", "forward": 0.9, "lateral": 0.6, "angular": 1.0},
]

# ── 资源类型（docs 7.5.2）──
RT_MOTION = "RESOURCE_TYPE_MOTION"
RT_EMOTICON = "RESOURCE_TYPE_EMOTICON"
RT_AUDIO = "RESOURCE_TYPE_AUDIO"
RT_SKILL = "RESOURCE_TYPE_SKILL"

_cache: dict[str, tuple[float, list[dict]]] = {}


def _fetch_resources(rt: str, force: bool = False) -> list[dict]:
    """拉取并缓存某类资源清单。返回 [{id,name,duration,path}]（id=资源文件路径）"""
    from . import config
    now = time.time()
    hit = _cache.get(rt)
    if hit and not force and now - hit[0] < config.MOTIONS_CACHE_TTL:
        return hit[1]
    items: list[dict] = []
    try:
        from . import rpc
        r = rpc.resource_list(rt)
        for res in r.get("resources", []):
            extra = {}
            for k in ("motion_extra_info", "emoticon_extra_info", "audio_extra_info"):
                if res.get(k):
                    extra = res[k]
                    break
            disp = extra.get("display_name") or {}
            name = (disp.get("zh_CN") if isinstance(disp, dict) else None) or res.get("resource_name", "")
            extra_motion = extra if rt == RT_MOTION else {}
            items.append({
                "id": res.get("resource_path", ""),
                "name": str(name),
                "duration": round(float(res.get("duration", 0)) / 1000, 2),  # ms → s
                "path": res.get("resource_path", ""),
                "resource_id": res.get("resource_id"),
                "source": res.get("source", ""),
                # 资源能力属性（docs 7.5.2 motion_extra_info）——前端编排/执行提示用
                "allow_walk": bool(extra_motion.get("allow_walk_and_do", False)),
                "allow_interrupt": bool(extra_motion.get("allow_interrupt", False)),
            })
    except Exception as e:  # noqa: BLE001 —— RPC 不可达时返回旧缓存/空表，agent 不崩
        logger.warning(f"资源清单拉取失败({rt}): {e}")
        if hit:
            return hit[1]
    _cache[rt] = (now, items)
    return items


def get_motions(force: bool = False) -> list[dict]:
    """动作清单（编排/自由控制数据源；duration 单位秒）"""
    return _fetch_resources(RT_MOTION, force)


def get_emoticons(force: bool = False) -> list[dict]:
    return _fetch_resources(RT_EMOTICON, force)


def get_skills(force: bool = False) -> list[dict]:
    """舞蹈/技能清单（RESOURCE_TYPE_SKILL，全身舞蹈）"""
    return _fetch_resources(RT_SKILL, force)


def refresh_all() -> None:
    for rt in (RT_MOTION, RT_EMOTICON, RT_SKILL):
        _fetch_resources(rt, force=True)
