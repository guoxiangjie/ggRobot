#!/bin/bash

cd $(dirname $0)

clang-format --version
cmake-format --version
autopep8 --version

# ruff check src --fix
# ruff format .

# clang-format, version v15 is required
find x2_rl_deploy_controller -regex '.*\.cc\|.*\.cpp\|.*\.h\|.*\.proto' -and -not -regex '.*\.pb\.cc\|.*\.pb\.h\|.*src/aimdk_msgs/.*' | xargs clang-format -i --style=file

# cmake-format, apt install cmake-format
find x2_rl_deploy_controller -regex '.*\.cmake\|.*CMakeLists\.txt$' -and -not -regex '\./.*build.*/.*\|\./docs/.*\|\.*/src/aimdk_msgs/.*' | xargs cmake-format -c ./.cmake-format.py -i

# autopep8, apt install python3-autopep8
find x2_rl_deploy_controller -regex '.*\.py' -and -not -regex '\./.*build.*/.*\|\./docs/.*\|\.*/src/aimdk_msgs/.*' | xargs -r autopep8 -i --global-config ./.pycodestyle

