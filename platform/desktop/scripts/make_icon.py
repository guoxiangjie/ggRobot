#!/usr/bin/env python3
"""生成 GG Robot 应用图标（1024 png，electron-builder 自动转 icns/ico）

用法: cd platform/desktop && ../../platform/server/.venv/bin/python scripts/make_icon.py
产物: resources/icon.png
"""

from PIL import Image, ImageDraw, ImageFilter

SIZE = 1024
ACCENT = (77, 166, 255, 255)      # 品牌蓝
ACCENT_DARK = (38, 100, 180, 255)
BG_TOP = (32, 41, 56, 255)
BG_BOTTOM = (13, 18, 27, 255)


def vertical_gradient(size: int, top, bottom) -> Image.Image:
    img = Image.new("RGBA", (size, size))
    for y in range(size):
        t = y / (size - 1)
        color = tuple(int(top[i] + (bottom[i] - top[i]) * t) for i in range(4))
        for_x = Image.new("RGBA", (size, 1), color)
        img.paste(for_x, (0, y))
    return img


def rounded_mask(size: int, radius: int) -> Image.Image:
    m = Image.new("L", (size, size), 0)
    d = ImageDraw.Draw(m)
    d.rounded_rectangle([0, 0, size - 1, size - 1], radius=radius, fill=255)
    return m


def main() -> None:
    # 1. 渐变背景 + macOS squircle 风格圆角
    icon = vertical_gradient(SIZE, BG_TOP, BG_BOTTOM)
    icon.putalpha(rounded_mask(SIZE, 230))

    # 2. 机器人脸（居中圆角方块，品牌蓝，顶部高光）
    face_l, face_t, face_r, face_b = 232, 300, 792, 760
    overlay = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    d = ImageDraw.Draw(overlay)
    d.rounded_rectangle([face_l, face_t, face_r, face_b], radius=110, fill=ACCENT)

    # 脸部渐变（上亮下暗）
    face_grad = vertical_gradient(SIZE, ACCENT, ACCENT_DARK)
    face_grad.putalpha(overlay.split()[3])
    face_only = Image.composite(face_grad, Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0)),
                                _face_only_mask(face_l, face_t, face_r, face_b))
    icon.alpha_composite(face_only)

    # 顶部高光条（玻璃感）
    hl = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    hd = ImageDraw.Draw(hl)
    hd.rounded_rectangle([face_l + 26, face_t + 22, face_r - 26, face_t + 96], radius=44,
                         fill=(255, 255, 255, 46))
    icon.alpha_composite(hl)

    # 3. 天线（头顶细杆 + 圆点）
    ant = ImageDraw.Draw(icon)
    cx = (face_l + face_r) // 2
    ant.rounded_rectangle([cx - 9, 200, cx + 9, face_t + 8], radius=9, fill=ACCENT)
    ant.ellipse([cx - 34, 148, cx + 34, 216], fill=ACCENT)
    ant.ellipse([cx - 16, 164, cx + 16, 196], fill=(255, 255, 255, 230))

    # 4. 眼睛（两道白色圆角竖条 — 友好的极简表情）
    eye_w, eye_h, eye_r = 58, 148, 29
    eye_y = face_t + 130
    for ex in (cx - 128, cx + 70):
        ant.rounded_rectangle([ex, eye_y, ex + eye_w, eye_y + eye_h], radius=eye_r,
                              fill=(255, 255, 255, 245))

    # 5. 嘴（微笑弧线）
    smile = Image.new("RGBA", (SIZE, SIZE), (0, 0, 0, 0))
    sd = ImageDraw.Draw(smile)
    sd.arc([cx - 110, eye_y + 96, cx + 110, eye_y + 250], start=18, end=162,
           fill=(255, 255, 255, 210), width=26)
    smile = smile.filter(ImageFilter.GaussianBlur(1.2))
    icon.alpha_composite(smile)

    icon.save("resources/icon.png")
    print("✅ resources/icon.png (1024x1024)")


def _face_only_mask(l: int, t: int, r: int, b: int) -> Image.Image:
    m = Image.new("L", (SIZE, SIZE), 0)
    d = ImageDraw.Draw(m)
    d.rounded_rectangle([l, t, r, b], radius=110, fill=255)
    return m


if __name__ == "__main__":
    main()
