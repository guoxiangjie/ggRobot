# aimdk_msgs 预编译包加载模块
# 功能：
# 1. 判断是否存在对应架构的预编译目录
# 2. 比较预编译目录中的消息定义与源码中的消息定义是否一致
# 3. 如果一致则使用预编译包，否则回退到源码编译

# 检测当前系统架构
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(TARGET_ARCH "x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  set(TARGET_ARCH "aarch64")
else()
  set(TARGET_ARCH "unknown")
endif()

message(STATUS "Current architecture: ${CMAKE_SYSTEM_PROCESSOR}, Target arch: ${TARGET_ARCH}")

# 默认不使用预编译包
set(USE_PREBUILT_PACKAGE FALSE)

# 预编译包配置 - 直接使用预编译目录（根据用户建议）
set(PREBUILT_PACKAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_${TARGET_ARCH}")

# 步骤1: 判断是否存在预编译目录
if(EXISTS "${PREBUILT_PACKAGE_PATH}")
  message(STATUS "Found prebuilt package directory: ${PREBUILT_PACKAGE_PATH}")

  if(EXISTS "${PREBUILT_PACKAGE_PATH}/share/${PROJECT_NAME}"
     AND EXISTS "${PREBUILT_PACKAGE_PATH}/include"
     AND EXISTS "${PREBUILT_PACKAGE_PATH}/lib")
    message(STATUS "Prebuilt package structure is valid")

    # 步骤2: 判断预编译目录中的消息种类和定义是否与interface目录下的内容相符
    set(MESSAGE_MISMATCH FALSE)

    # 获取源码中的所有.msg和.srv文件
    file(GLOB_RECURSE SOURCE_MSG_FILES "${CMAKE_CURRENT_SOURCE_DIR}/interface/*.msg")
    file(GLOB_RECURSE SOURCE_SRV_FILES "${CMAKE_CURRENT_SOURCE_DIR}/interface/*.srv")

    # 检查预编译包中是否有对应的消息定义记录
    set(PREBUILT_MESSAGE_CHECK_FILE "${PREBUILT_PACKAGE_PATH}/share/${PROJECT_NAME}/message_definitions.txt")
    if(EXISTS "${PREBUILT_MESSAGE_CHECK_FILE}")
      message(STATUS "Found message definitions check file")

      # 读取预编译包中的消息定义记录
      file(READ "${PREBUILT_MESSAGE_CHECK_FILE}" PREBUILT_MESSAGE_CONTENT)

      # 检查每个源码消息文件
      foreach(SOURCE_FILE ${SOURCE_MSG_FILES} ${SOURCE_SRV_FILES})
        # 计算源码文件的相对路径
        file(RELATIVE_PATH RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE_FILE}")

        # 计算文件的哈希值
        file(SHA256 "${SOURCE_FILE}" SOURCE_HASH)

        # 检查该文件是否在预编译包记录中
        string(FIND "${PREBUILT_MESSAGE_CONTENT}" "${RELATIVE_PATH}:${SOURCE_HASH}" HASH_FOUND)
        if(HASH_FOUND EQUAL -1)
          message(WARNING "Message definition mismatch: ${RELATIVE_PATH}")
          message(WARNING "  Source hash: ${SOURCE_HASH}")
          set(MESSAGE_MISMATCH TRUE)
          break()
        endif()
      endforeach()

      # 检查预编译包中是否有额外的消息文件
      # 使用文件读取的方式逐行处理
      file(READ "${PREBUILT_MESSAGE_CHECK_FILE}" PREBUILT_LINES)
      string(REPLACE "\n" ";" PREBUILT_LINES_LIST "${PREBUILT_LINES}")

      foreach(PREBUILT_LINE ${PREBUILT_LINES_LIST})
        if(PREBUILT_LINE STREQUAL "")
          continue()
        endif()

        # 提取文件路径（冒号分隔的第一部分）
        string(FIND "${PREBUILT_LINE}" ":" COLON_POS)
        if(COLON_POS GREATER -1)
          string(SUBSTRING "${PREBUILT_LINE}" 0 ${COLON_POS} PREBUILT_FILE)

          # 检查该文件是否存在于源码中
          set(FULL_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${PREBUILT_FILE}")
          if(NOT EXISTS "${FULL_SOURCE_PATH}")
            message(WARNING "Extra message file in prebuilt: ${PREBUILT_FILE}")
            set(MESSAGE_MISMATCH TRUE)
            break()
          endif()
        endif()
      endforeach()
    else()
      message(WARNING "No message definitions check file found in prebuilt package")
      set(MESSAGE_MISMATCH TRUE)
    endif()

    if(NOT MESSAGE_MISMATCH)
      message(STATUS "All message definitions match, will use prebuilt package")
      set(USE_PREBUILT_PACKAGE TRUE)
    else()
      message(WARNING "Message definitions mismatch, will build from source")
    endif()
  else()
    message(WARNING "Prebuilt package structure is invalid")
  endif()
else()
  message(STATUS "No prebuilt package directory found for ${TARGET_ARCH}: ${PREBUILT_PACKAGE_PATH}")
endif()

# 如果使用预编译包
if(USE_PREBUILT_PACKAGE)

  # 安装预编译包到目标位置
  install(
    DIRECTORY "${PREBUILT_PACKAGE_PATH}/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}"
    USE_SOURCE_PERMISSIONS)

  # 标记使用了预编译包
  set(AIMDK_MSGS_USE_PREBUILT
      TRUE
      CACHE BOOL "Whether aimdk_msgs is using prebuilt package" FORCE)
endif()
