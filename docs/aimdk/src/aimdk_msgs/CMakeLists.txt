cmake_minimum_required(VERSION 3.8)
project(aimdk_msgs)

# 始终使用Release模式编译，除非用户明确指定
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 如果存在 src/interface 目录, 执行脚本分发协议文件并注册 configure 依赖
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/interface)
  file(GLOB_RECURSE _INTERFACE_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/*.msg" "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/*.srv")
  set_property(
    DIRECTORY
    APPEND
    PROPERTY CMAKE_CONFIGURE_DEPENDS ${_INTERFACE_SRC_FILES})

  execute_process(
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/tools/distribute_proto.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE SCRIPT_RESULT)
elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/interface)
  file(GLOB_RECURSE _INTERFACE_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/interface/*.msg" "${CMAKE_CURRENT_SOURCE_DIR}/interface/*.srv")
  set_property(
    DIRECTORY
    APPEND
    PROPERTY CMAKE_CONFIGURE_DEPENDS ${_INTERFACE_SRC_FILES})
else()
  message(FATAL_ERROR "no interface found")
endif()

# 包含预编译包加载模块
include(cmake/aimdk_msgs_prebuilt.cmake)

# 如果使用预编译包，则退出配置，不进行源码编译
if(USE_PREBUILT_PACKAGE)
  # 退出配置，不进行源码编译
  return()
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(action_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

# 扫描 srv 目录下所有的 .srv 文件
file(GLOB_RECURSE SRV_FILES_ABS "interface/*.srv")
get_filename_component(SRV_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/interface" ABSOLUTE)
set(SRV_FILES_REL "")
foreach(ABS_PATH ${SRV_FILES_ABS})
  file(RELATIVE_PATH REL_PATH "${SRV_BASE_DIR}" "${ABS_PATH}")
  list(APPEND SRV_FILES_REL "interface/${REL_PATH}")
endforeach()

# 扫描 msg 目录下所有的 .msg 文件
file(GLOB_RECURSE MSG_FILES_ABS "interface/*.msg")
get_filename_component(MSG_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/interface" ABSOLUTE)
set(MSG_FILES_REL "")
foreach(ABS_PATH ${MSG_FILES_ABS})
  file(RELATIVE_PATH REL_PATH "${MSG_BASE_DIR}" "${ABS_PATH}")
  list(APPEND MSG_FILES_REL "interface/${REL_PATH}")
endforeach()

message(STATUS "SRV files: ${SRV_FILES_REL}")
message(STATUS "MSG files: ${MSG_FILES_REL}")

# 生成接口文件
rosidl_generate_interfaces(
  ${PROJECT_NAME}
  ${SRV_FILES_REL}
  ${MSG_FILES_REL}
  DEPENDENCIES
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

# 源码编译完成后自动更新预编译包
if(NOT USE_PREBUILT_PACKAGE)
  # 确保TARGET_ARCH变量有值
  if(NOT DEFINED TARGET_ARCH)
    # 检测当前系统架构
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
      set(TARGET_ARCH "x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
      set(TARGET_ARCH "aarch64")
    else()
      set(TARGET_ARCH "unknown")
    endif()
  endif()

  message(STATUS "Configuring automatic prebuilt package update after install for arch: ${TARGET_ARCH}")

  # 在安装完成后执行更新脚本
  install(
    CODE "execute_process(COMMAND \${CMAKE_COMMAND} -DTARGET_ARCH=${TARGET_ARCH} -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DINSTALL_DIR=${CMAKE_INSTALL_PREFIX} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/update_prebuilt.cmake)"
  )
endif()
