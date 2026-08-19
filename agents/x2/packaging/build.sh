#!/bin/bash
# ggrobot-agent .deb 构建（macOS，前置: brew install dpkg）
# 产物: agents/x2/packaging/build/ggrobot-agent_<ver>_arm64.deb
set -e

REPO_ROOT="$(cd "$(dirname "$0")/../../.." && pwd)"
PKG_DIR="$(dirname "$0")"
BUILD_DIR="$PKG_DIR/build"

# 版本：git describe → dpkg 合法版本（'-' 转 '.'）
VER=$(cd "$REPO_ROOT" && git describe --tags --always --dirty 2>/dev/null || echo v0.0.0)
VER=${VER#v}
VER=$(echo "$VER" | tr '-' '.')

PKG="$BUILD_DIR/ggrobot-agent_${VER}_arm64"
DEB="$BUILD_DIR/ggrobot-agent_${VER}_arm64.deb"

echo "🔨 构建 ggrobot-agent $VER (arm64)..."

rm -rf "$BUILD_DIR"
mkdir -p "$PKG/DEBIAN" "$PKG/opt/ggrobot-agent"

# ── 代码 + 依赖清单（排除缓存/资产按需）──
rsync -a \
  --exclude '__pycache__' \
  --exclude '*.pyc' \
  --exclude '.DS_Store' \
  "$REPO_ROOT/agents/x2/gg_robot/" "$PKG/opt/ggrobot-agent/gg_robot/"
cp "$REPO_ROOT/agents/x2/requirements.txt" "$PKG/opt/ggrobot-agent/"


# ── DEBIAN 控制文件 ──
sed "s/@VERSION@/$VER/" "$PKG_DIR/control" > "$PKG/DEBIAN/control"
cp "$PKG_DIR/postinst" "$PKG_DIR/prerm" "$PKG/DEBIAN/"
chmod 755 "$PKG/DEBIAN/postinst" "$PKG/DEBIAN/prerm"

# ── 打包（--root-owner-group：macOS 无 root 概念，漏带必翻车）──
dpkg-deb --build --root-owner-group "$PKG"

echo "✅ 产物: $DEB"
echo "   检查: dpkg-deb -I $DEB && dpkg-deb -c $DEB | head -20"
