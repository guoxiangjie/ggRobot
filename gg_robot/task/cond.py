"""条件表达式求值 — 安全子集（不用 eval）

支持：{{var.path}} 变量、== != > >= < <=、in / not in、
contains(A, B)（A 包含 B）、and / or / not、括号、数字、引号字符串。
用 ast 白名单解析，只允许字面量与比较/布尔运算，杜绝任意代码执行。
"""

import ast
import logging
import re

logger = logging.getLogger(__name__)

_TEMPLATE_RE = re.compile(r"\{\{\s*([\w.]+)\s*\}\}")


def resolve_var(ctx: dict, path: str):
    """从 ctx['responses'] 解析点分路径（dict 键 / list 下标），返回 (found, value)"""
    cur = ctx.get("responses", {})
    for part in path.split("."):
        if isinstance(cur, dict) and part in cur:
            cur = cur[part]
        elif isinstance(cur, list):
            try:
                cur = cur[int(part)]
            except (ValueError, IndexError):
                return False, None
        else:
            return False, None
    return True, cur


def _literal(v):
    """把运行时值转成可安全嵌入表达式文本的字面量"""
    if v is None:
        return "None"
    if isinstance(v, bool):
        return "True" if v else "False"
    if isinstance(v, (int, float, str)):
        return repr(v)
    if isinstance(v, (list, tuple, dict)):
        return repr(v)
    return "None"


def eval_cond(expr, ctx: dict) -> bool:
    """求值条件表达式；空条件视为真；变量未找到按 None；异常返回 False。"""
    if not expr or not str(expr).strip():
        return True

    def repl(m):
        found, val = resolve_var(ctx, m.group(1))
        return _literal(val) if found else "None"

    code = _TEMPLATE_RE.sub(repl, str(expr))
    code = _transform_contains(code)
    try:
        tree = ast.parse(code, mode="eval")
        return bool(_eval_node(tree.body))
    except Exception as e:
        logger.warning(f"条件表达式求值失败: {expr!r} → {code!r} ({e})")
        return False


def _find_op(s: str, op: str) -> int:
    """在括号深度 0 且字符串外查找操作符，返回起始下标；找不到返回 -1"""
    depth = 0
    in_str = False
    quote = ""
    i = 0
    while i < len(s):
        ch = s[i]
        if in_str:
            if ch == quote:
                in_str = False
            i += 1
            continue
        if depth == 0 and s.startswith(op, i):
            return i
        if ch in ('"', "'"):
            in_str = True
            quote = ch
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        i += 1
    return -1


def _transform_contains(s: str) -> str:
    """把 DSL 的 ` contains ` 中缀转成 _contains(左, 右) 函数调用（递归处理括号与 and/or）"""
    s = s.strip()
    if not s:
        return s
    # 整体被一对括号包裹 → 递归内部
    if s.startswith("(") and _find_op(s, "(") == 0 and _matching_paren(s) == len(s) - 1:
        return "(" + _transform_contains(s[1:-1]) + ")"
    idx = _find_op(s, " contains ")
    if idx >= 0:
        return "_contains({}, {})".format(_transform_contains(s[:idx]), _transform_contains(s[idx + len(" contains "):]))
    for op in (" and ", " or "):
        idx = _find_op(s, op)
        if idx >= 0:
            return _transform_contains(s[:idx]) + op + _transform_contains(s[idx + len(op):])
    return s


def _matching_paren(s: str) -> int:
    """返回从下标 0 的 '(' 匹配的右括号下标"""
    depth = 0
    in_str = False
    quote = ""
    for i, ch in enumerate(s):
        if in_str:
            if ch == quote:
                in_str = False
            continue
        if ch in ('"', "'"):
            in_str = True
            quote = ch
        elif ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return i
    return -1


def _eval_node(n):
    if isinstance(n, ast.Constant):
        return n.value
    if isinstance(n, (ast.List, ast.Tuple)):
        return [_eval_node(e) for e in n.elts]
    if isinstance(n, ast.BoolOp):
        if isinstance(n.op, ast.And):
            return all(_eval_node(v) for v in n.values)
        if isinstance(n.op, ast.Or):
            return any(_eval_node(v) for v in n.values)
        raise ValueError(f"不支持的布尔运算: {type(n.op).__name__}")
    if isinstance(n, ast.UnaryOp) and isinstance(n.op, ast.Not):
        return not _eval_node(n.operand)
    if isinstance(n, ast.Compare):
        left = _eval_node(n.left)
        for op, comparator in zip(n.ops, n.comparators):
            right = _eval_node(comparator)
            if isinstance(op, ast.Eq):
                ok = left == right
            elif isinstance(op, ast.NotEq):
                ok = left != right
            elif isinstance(op, ast.Lt):
                ok = left < right
            elif isinstance(op, ast.LtE):
                ok = left <= right
            elif isinstance(op, ast.Gt):
                ok = left > right
            elif isinstance(op, ast.GtE):
                ok = left >= right
            elif isinstance(op, ast.In):
                ok = left in right
            elif isinstance(op, ast.NotIn):
                ok = left not in right
            elif isinstance(op, ast.Is):
                ok = left is right
            elif isinstance(op, ast.IsNot):
                ok = left is not right
            else:
                raise ValueError(f"不支持的操作符: {type(op).__name__}")
            if not ok:
                return False
            left = right
        return True
    if isinstance(n, ast.Call) and isinstance(n.func, ast.Name) and n.func.id == "_contains" and len(n.args) == 2:
        # _contains(A, B) = "A 包含 B"
        return _eval_node(n.args[1]) in _eval_node(n.args[0])
    raise ValueError(f"不支持的表达式节点: {type(n).__name__}")
