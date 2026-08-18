"""PyInstaller 打包入口 — 以模块导入方式调 main()，保证 ggplatform 包内相对导入正常"""

from ggplatform.__main__ import main

if __name__ == "__main__":
    main()
