# 更新预编译包的CMake脚本
# 这个脚本在源码编译完成后执行，用于自动更新预编译包
# 采用直接使用预编译目录的方式（根据用户建议）

# 配置参数
set(PROJECT_NAME aimdk_msgs)

# 确保所有必需的变量都已设置
if(NOT DEFINED TARGET_ARCH)
  message(FATAL_ERROR "TARGET_ARCH variable not defined")
endif()

if(NOT DEFINED SOURCE_DIR)
  message(FATAL_ERROR "SOURCE_DIR variable not defined")
endif()

if(NOT DEFINED INSTALL_DIR)
  message(FATAL_ERROR "INSTALL_DIR variable not defined")
endif()

set(PREBUILT_DIR "${SOURCE_DIR}/prebuilt_${TARGET_ARCH}")

message(STATUS "Updating prebuilt package directory for ${TARGET_ARCH}...")

# 清理旧的预编译包目录
file(REMOVE_RECURSE "${PREBUILT_DIR}")

# 创建预编译包目录
file(MAKE_DIRECTORY "${PREBUILT_DIR}")

# 复制安装文件到预编译包目录
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${INSTALL_DIR}/include" "${PREBUILT_DIR}/include")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${INSTALL_DIR}/lib" "${PREBUILT_DIR}/lib")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${INSTALL_DIR}/share" "${PREBUILT_DIR}/share")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${INSTALL_DIR}/local" "${PREBUILT_DIR}/local")

# 生成消息定义检查文件
set(MESSAGE_DEF_DIR "${PREBUILT_DIR}/share/${PROJECT_NAME}")
set(MESSAGE_DEF_FILE "${MESSAGE_DEF_DIR}/message_definitions.txt")
file(MAKE_DIRECTORY "${MESSAGE_DEF_DIR}")
file(WRITE "${MESSAGE_DEF_FILE}" "")

# 遍历所有.msg和.srv文件，生成哈希值
file(GLOB_RECURSE MSG_FILES "${SOURCE_DIR}/interface/*.msg")
file(GLOB_RECURSE SRV_FILES "${SOURCE_DIR}/interface/*.srv")
list(APPEND ALL_MSG_FILES ${MSG_FILES} ${SRV_FILES})

foreach(FILE ${ALL_MSG_FILES})
  # 计算相对路径
  file(RELATIVE_PATH REL_PATH "${SOURCE_DIR}" "${FILE}")
  # 计算SHA256哈希值
  execute_process(COMMAND sha256sum "${FILE}" OUTPUT_VARIABLE HASH_OUTPUT)
  string(REGEX MATCH "^([a-f0-9]+)" HASH "${HASH_OUTPUT}")
  # 写入文件
  file(APPEND "${MESSAGE_DEF_FILE}" "${REL_PATH}:${HASH}\n")
endforeach()

message(STATUS "Generated message definitions file: ${MESSAGE_DEF_FILE}")
message(STATUS "Prebuilt package directory updated successfully: ${PREBUILT_DIR}")
