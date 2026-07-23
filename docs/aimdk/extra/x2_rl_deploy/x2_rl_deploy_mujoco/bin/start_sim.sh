#!/bin/bash

# 获取当前脚本名称
script_name=$(basename "$0")

# 显示帮助信息
show_help() {
  echo "Usage: $script_name [options]"
  echo "Options:"
  echo "  -h, --help                   Show this help message and exit"
  echo "  -c <dir>                     Specify the configuration directory"
  echo "  -s                           Clear cache"
  echo "  -g                           Run with gdb"
}

# 检查是否有同名脚本在运行
check_running_instance() {
  if pgrep -f "$script_name" | grep -v "$$" >/dev/null; then
    other_pid=$(pgrep -f "$script_name" | grep -v "$$" | head -n 1)
    echo "Another instance of '$script_name' is already running [PID: $other_pid]. Please stop it first."
    exit 1
  fi
}

# 设置环境变量
set_environment_variables() {
  current_dir=$(cd $(dirname $0) && pwd)
  install_dir=${current_dir}/../
  ld_path="${current_dir}:${install_dir}/bin:${install_dir}/lib"
  export LD_LIBRARY_PATH=${ld_path}:$LD_LIBRARY_PATH

  export EM_APP_NAME=${EM_APP_NAME:-"sim"}
  export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
  export AGIBOT_ENABLE_HDS_COMPONENT=false
  export AGIBOT_ENABLE_EVENT_COMPONENT=false
  export AGIBOT_ENABLE_MONITOR_COMPONENT=false
  export AGIBOT_ENABLE_MONITOR=true
  export AGIBOT_ENABLE_AUDIT_COMPONENT=false
  export AIMRT_PLUGIN_SHM_DEFAULT_WAIT_TIME_US=300
}

# 初始化变量
initialize_variables() {
  robot_name=""
  clear_cache=false
  use_gdb=false
  robot_name_cache_file="${current_dir}/sim_robot_name_cache.txt"
  configuration_directory_cache_file="${current_dir}/sim_configuration_directory_cache.txt"
}

# 加载配置目录路径
load_configuration_directory_from_cache() {
  if [ -f "$configuration_directory_cache_file" ]; then
    configuration_directory=$(cat "$configuration_directory_cache_file")
  fi

  echo "Selected configuration directory: $configuration_directory"
  if [ -z "$configuration_directory" ]; then
    configuration_directory="${install_dir}/configuration"
    echo "No configuration directory specified. Using default: $configuration_directory"
    save_configuration_directory_to_cache
  fi

  robot_directory="${configuration_directory}/robot" # 更新 robot_directory 路径
}

# 保存配置目录路径到缓存
save_configuration_directory_to_cache() {
  echo "$configuration_directory" >"$configuration_directory_cache_file"
}

# 解析命令行参数
parse_arguments() {
  while getopts "hc:sg-:" opt; do
    case $opt in
    h)
      show_help
      exit 0
      ;;
    c)
      if [ -z "$OPTARG" ]; then
        echo "Usage: $0 -c <configuration_directory>"
        exit 1
      fi
      configuration_directory=$OPTARG
      save_configuration_directory_to_cache
      ;;
    s)
      clear_cache=true
      ;;
    g)
      use_gdb=true
      ;;
    -)
      case "${OPTARG}" in
      help)
        show_help
        exit 0
        ;;
      *)
        echo "Invalid option: --$OPTARG" >&2
        exit 1
        ;;
      esac
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
    esac
  done
}

# 设置机器人名称和模式
set_robot_name_and_mode() {
  echo "$robot_name" >"$robot_name_cache_file"
}

# 清除缓存
clear_cache_if_needed() {
  if $clear_cache; then
    robot_name=""              # 清空机器人名称缓存
    configuration_directory="" # 清空配置目录缓存
    rm -f "$robot_name_cache_file"
    rm -f "$configuration_directory_cache_file"
  fi
}

# 读取缓存文件
read_cache_files() {
  if [ -z "$robot_name" ] && [ -f "$robot_name_cache_file" ]; then
    robot_name=$(cat "$robot_name_cache_file")
  fi
  load_configuration_directory_from_cache
}

# 选择机器人
select_robot() {
  if [ -z "$robot_name" ]; then
    directories=($(find "$robot_directory" -maxdepth 1 -mindepth 1 -type d | sort))
    echo "Please select a robot: "
    for i in "${!directories[@]}"; do
      dir_name=$(basename "${directories[$i]}")
      echo -e "\e[1;31m$i\e[0m: \e[1;32m$dir_name\e[0m"
    done
    read -p "Please enter your choice: " choice
    if [[ "$choice" =~ ^[0-9]+$ && "$choice" -ge 0 && "$choice" -lt "${#directories[@]}" ]]; then
      selected_robot_directory="${directories[$choice]}"
      robot_name=$(basename "$selected_robot_directory")
    else
      echo "Invalid choice. Exiting."
      exit 1
    fi
    echo "Selected robot: $robot_name"
    echo "$robot_name" >"$robot_name_cache_file"
  fi

  if [ -z "$robot_name" ]; then
    echo "Robot name is empty. Exiting."
    exit 1
  fi
}

# 启动机器人
start_robot() {
  export SIM_ROBOT_PATH="${robot_directory}/${robot_name}"
  export SIM_RESOURCE_MODEL_PATH="${install_dir}/resource/model"

  sim_exe="./aima-sim-app"
  cfg_file_path="$robot_directory/$robot_name/simulator/default.yaml"

  if $use_gdb; then
    echo "gdb -ex run --args $sim_exe --cfg_file_path=$cfg_file_path"
    gdb -ex run --args $sim_exe --cfg_file_path=$cfg_file_path
  else
    $sim_exe --cfg_file_path=$cfg_file_path
  fi

  echo "gdb run command:"
  echo "export LD_LIBRARY_PATH=${ld_path}:\$LD_LIBRARY_PATH"
  echo "gdb -ex run --args $sim_exe --cfg_file_path=$cfg_file_path"
}

# 主函数
main() {
  check_running_instance
  set_environment_variables
  initialize_variables
  parse_arguments "$@"
  clear_cache_if_needed
  read_cache_files
  select_robot
  start_robot "$@"
}

# 调用主函数
main "$@"
