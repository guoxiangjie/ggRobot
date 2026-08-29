
#include <rclcpp/rclcpp.hpp>

#include "x2_rl_deploy_controller/motion_control_node.h"

/**
 * @brief Global variables and signal handling
 */
// Global variables to control program state
std::atomic<bool> g_running(true);
std::atomic<bool> g_emergency_stop(false);

// Signal handler function
void signal_handler(int)
{
  g_running = false;
  RCLCPP_INFO(rclcpp::get_logger("main"), "Received termination signal, shutting down...");
  rclcpp::shutdown();
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  // Set up signal handling
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  // Default model path
  std::string config_path = "x2_rl_deploy_controller/config/motion_control.yaml";
  if (argc > 1) config_path = argv[1];
  auto node = std::make_shared<MotionControlNode>("motion_control_node", config_path);

  try {
    // Main thread is only responsible for callback
    rclcpp::spin(node);
  } catch (const std::exception &e) {
    RCLCPP_ERROR(rclcpp::get_logger("main"), "Exception occurred: %s", e.what());
    node->DampingDefault();
  }

  RCLCPP_INFO(rclcpp::get_logger("main"), "Program exited safely");
  node->DampingDefault();
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  rclcpp::shutdown();
  return 0;
}