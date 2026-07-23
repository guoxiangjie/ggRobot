#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "aimdk_msgs/srv/get_system_state.hpp"
#include "aimdk_msgs/srv/migrate_system_state.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

/**
 * @class SystemStateMigrator
 * @brief ROS2 client for migrating system state to any target state
 */
class SystemStateMigrator : public rclcpp::Node {
public:
  /**
   * @brief Constructor for SystemStateMigrator
   * @param target_state The target system state to migrate to
   */
  SystemStateMigrator(const std::string &target_state)
      : Node("system_state_migrator"), target_state_(target_state) {
    // Create service clients
    migrate_client_ = this->create_client<aimdk_msgs::srv::MigrateSystemState>(
        "/aimdk_5Fmsgs/srv/MigrateSystemState");

    get_state_client_ = this->create_client<aimdk_msgs::srv::GetSystemState>(
        "/aimdk_5Fmsgs/srv/GetSystemState");

    // Log target state
    RCLCPP_INFO(this->get_logger(), "Target state: %s", target_state_.c_str());

    // Start the migration process
    start_migration_process();
  }

private:
  /**
   * @brief Start the migration process
   */
  void start_migration_process() {
    // Create a timer to check service availability
    check_timer_ = this->create_wall_timer(
        1s, std::bind(&SystemStateMigrator::check_services_and_start, this));
  }

  /**
   * @brief Check if services are available and start migration
   */
  void check_services_and_start() {
    // Check if both services are available
    if (migrate_client_->service_is_ready() &&
        get_state_client_->service_is_ready()) {
      // Services are available, cancel timer and start migration
      check_timer_->cancel();
      RCLCPP_INFO(this->get_logger(),
                  "Both services are available, starting migration to %s...",
                  target_state_.c_str());
      migrate_to_target_state();
    } else {
      RCLCPP_INFO(this->get_logger(), "Waiting for services...");
    }
  }

  /**
   * @brief Migrate system state to target state with retry
   */
  void migrate_to_target_state() {
    if (migrate_pending_) {
      return;
    }
    if (migrate_retry_count_ >= max_migrate_retries_) {
      RCLCPP_ERROR(this->get_logger(),
                   "Migration request failed after %d attempts",
                   max_migrate_retries_);
      rclcpp::shutdown();
      return;
    }

    auto request =
        std::make_shared<aimdk_msgs::srv::MigrateSystemState::Request>();

    auto now = this->now();
    request->header.header.stamp.sec = now.seconds();
    request->header.header.stamp.nanosec = now.nanoseconds() % 1000000000;

    request->state = target_state_;

    migrate_retry_count_++;
    migrate_pending_ = true;
    uint64_t req_id = ++migrate_request_id_;

    RCLCPP_INFO(this->get_logger(),
                "Sending migration request to %s state (attempt %d/%d)...",
                target_state_.c_str(), migrate_retry_count_,
                max_migrate_retries_);

    migrate_timeout_timer_ = this->create_wall_timer(30s, [this, req_id]() {
      if (req_id != migrate_request_id_) {
        return;
      }
      migrate_timeout_timer_.reset();
      migrate_pending_ = false;
      RCLCPP_WARN(this->get_logger(), "Migration request timeout, retrying...");
      migrate_to_target_state();
    });

    auto future = migrate_client_->async_send_request(
        request,
        [this, req_id](
            rclcpp::Client<aimdk_msgs::srv::MigrateSystemState>::SharedFuture
                future) {
          if (req_id != migrate_request_id_) {
            return;
          }
          if (migrate_timeout_timer_) {
            migrate_timeout_timer_->cancel();
            migrate_timeout_timer_.reset();
          }
          migrate_pending_ = false;

          try {
            auto response = future.get();
            if (response->header.status.value ==
                aimdk_msgs::msg::CommonState::SUCCESS) {
              migrate_retry_count_ = 0;
              ++migrate_request_id_;
              RCLCPP_INFO(this->get_logger(),
                          "Migration request accepted, starting to monitor "
                          "state...");
              start_state_monitoring();
            } else {
              ++migrate_request_id_;
              RCLCPP_ERROR(this->get_logger(),
                           "Migration request failed with status: %d, message: "
                           "%s",
                           response->header.status.value,
                           response->header.message.c_str());
              rclcpp::shutdown();
            }
          } catch (const std::exception &e) {
            ++migrate_request_id_;
            RCLCPP_ERROR(this->get_logger(),
                         "Migration service call failed: %s", e.what());
            rclcpp::shutdown();
          }
        });
  }

  /**
   * @brief Start monitoring system state
   */
  void start_state_monitoring() {
    RCLCPP_INFO(this->get_logger(), "Starting to monitor system state...");

    // Create a timer to periodically check system state
    monitor_timer_ = this->create_wall_timer(
        1s, std::bind(&SystemStateMigrator::check_system_state, this));
  }

  /**
   * @brief Check current system state with retry
   */
  void check_system_state() {
    if (get_state_pending_) {
      return;
    }
    if (get_state_retry_count_ >= max_get_state_retries_) {
      RCLCPP_ERROR(this->get_logger(),
                   "Get system state failed after %d attempts, will retry on "
                   "next monitor cycle",
                   max_get_state_retries_);
      get_state_retry_count_ = 0;
      return;
    }

    auto request = std::make_shared<aimdk_msgs::srv::GetSystemState::Request>();

    auto now = this->now();
    request->header.header.stamp.sec = now.seconds();
    request->header.header.stamp.nanosec = now.nanoseconds() % 1000000000;

    get_state_retry_count_++;
    get_state_pending_ = true;
    uint64_t req_id = ++get_state_request_id_;

    get_state_timeout_timer_ = this->create_wall_timer(10s, [this, req_id]() {
      if (req_id != get_state_request_id_) {
        return;
      }
      get_state_timeout_timer_.reset();
      get_state_pending_ = false;
      RCLCPP_WARN(this->get_logger(),
                  "GetSystemState request timeout (attempt %d/%d), "
                  "retrying...",
                  get_state_retry_count_, max_get_state_retries_);
      check_system_state();
    });

    auto future = get_state_client_->async_send_request(
        request,
        [this,
         req_id](rclcpp::Client<aimdk_msgs::srv::GetSystemState>::SharedFuture
                     future) {
          if (req_id != get_state_request_id_) {
            return;
          }
          if (get_state_timeout_timer_) {
            get_state_timeout_timer_->cancel();
            get_state_timeout_timer_.reset();
          }
          get_state_pending_ = false;

          try {
            auto response = future.get();
            get_state_retry_count_ = 0;
            ++get_state_request_id_;

            RCLCPP_INFO(
                this->get_logger(), "Current State: %s, System Status: %u",
                response->cur_state.c_str(), response->curr_status.value);

            if (is_migration_complete(response)) {
              RCLCPP_INFO(this->get_logger(),
                          "Migration to %s completed successfully!",
                          target_state_.c_str());
              monitor_timer_->cancel();
              rclcpp::shutdown();
            } else {
              RCLCPP_INFO(this->get_logger(),
                          "Migration in progress, will check again in 1 "
                          "second...");
            }
          } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(),
                         "GetSystemState service call failed: %s", e.what());
          }
        });
  }

  /**
   * @brief Check if migration to target state is complete
   * @param response Response from GetSystemState service
   * @return true if migration is complete, false otherwise
   */
  bool is_migration_complete(
      const aimdk_msgs::srv::GetSystemState::Response::SharedPtr response) {
    // Convert current state and target state to lowercase for case-insensitive
    // comparison
    std::string current_state_lower = response->cur_state;
    std::transform(current_state_lower.begin(), current_state_lower.end(),
                   current_state_lower.begin(), ::tolower);

    std::string target_state_lower = target_state_;
    std::transform(target_state_lower.begin(), target_state_lower.end(),
                   target_state_lower.begin(), ::tolower);

    // Check conditions:
    // 1. Current state equals target state (case-insensitive)
    // 2. System status equals 1 (IN_READY)
    bool state_match = (current_state_lower == target_state_lower);
    bool status_match = (response->curr_status.value ==
                         aimdk_msgs::msg::SystemStatus::IN_READY);

    if (state_match && status_match) {
      return true;
    }

    // Log detailed information if not complete
    if (!state_match) {
      RCLCPP_INFO(this->get_logger(),
                  "State mismatch: current='%s', expected='%s'",
                  response->cur_state.c_str(), target_state_.c_str());
    }
    if (!status_match) {
      RCLCPP_INFO(this->get_logger(),
                  "Status mismatch: current= %u, expected=1 (IN_READY)",
                  response->curr_status.value);
    }
    if (state_match && !state_match) {
      RCLCPP_ERROR(this->get_logger(), "State Migrate Fail");
      exit(0);
    }

    return false;
  }

  // Target state to migrate to
  std::string target_state_;

  // Service clients
  rclcpp::Client<aimdk_msgs::srv::MigrateSystemState>::SharedPtr
      migrate_client_;
  rclcpp::Client<aimdk_msgs::srv::GetSystemState>::SharedPtr get_state_client_;

  // Timers
  rclcpp::TimerBase::SharedPtr check_timer_;
  rclcpp::TimerBase::SharedPtr monitor_timer_;

  // Retry counters and timeout timers for migration
  int migrate_retry_count_ = 0;
  const int max_migrate_retries_ = 5;
  uint64_t migrate_request_id_ = 0;
  bool migrate_pending_ = false;
  rclcpp::TimerBase::SharedPtr migrate_timeout_timer_;

  // Retry counters and timeout timers for get state
  int get_state_retry_count_ = 0;
  const int max_get_state_retries_ = 3;
  uint64_t get_state_request_id_ = 0;
  bool get_state_pending_ = false;
  rclcpp::TimerBase::SharedPtr get_state_timeout_timer_;
};

/**
 * @brief Print usage information with detailed mode descriptions
 */
void print_usage(const char *program_name) {
  std::cout << "Usage: " << program_name << " <target_state>" << std::endl;
  std::cout << std::endl;
  std::cout << "Available target states:" << std::endl;
  std::cout << "  " << program_name << " Ready" << std::endl;
  std::cout << "  " << program_name << " Develop_Nav" << std::endl;
  std::cout << "  " << program_name << " Develop_Audio_Linux" << std::endl;
  std::cout << "  " << program_name << " Develop_Audio_ROS" << std::endl;
  std::cout << "  " << program_name << " Develop_MC" << std::endl;
  std::cout << std::endl;

  std::cout << "Mode Descriptions:" << std::endl;
  std::cout << "==================" << std::endl;

  // Ready mode description
  std::cout << "1. Ready - System Default Mode" << std::endl;
  std::cout
      << "   • Description: System enters this mode by default after startup"
      << std::endl;
  std::cout << "   • Purpose: Normal operation mode, ready for general tasks"
            << std::endl;
  std::cout
      << "   • Use case: Return to normal operation after development work"
      << std::endl;
  std::cout << std::endl;

  // Develop_Nav mode description
  std::cout << "2. Develop_Nav - Navigation Development Mode" << std::endl;
  std::cout
      << "   • Description: Special mode for navigation system development"
      << std::endl;
  std::cout << "   • Purpose: Enables navigation-related debugging and testing"
            << std::endl;
  std::cout << "   • Use case: When developing or testing navigation "
               "algorithms, SLAM, path planning"
            << std::endl;
  std::cout << "   • Features: May provide access to raw sensor data, "
               "navigation debug topics"
            << std::endl;
  std::cout << std::endl;

  // Develop_Audio_Linux mode description
  std::cout << "3. Develop_Audio_Linux - System-Level Audio Development Mode"
            << std::endl;
  std::cout << "   • Description: Mode for low-level audio system development"
            << std::endl;
  std::cout << "   • Purpose: Access to system audio streams at Linux level"
            << std::endl;
  std::cout << "   • Use case: When developing audio drivers, audio processing "
               "at system level"
            << std::endl;
  std::cout << "   • Features: Direct access to audio hardware, "
               "ALSA/PulseAudio interfaces"
            << std::endl;
  std::cout << std::endl;

  // Develop_Audio_ROS mode description
  std::cout << "4. Develop_Audio_ROS - ROS Audio Development Mode" << std::endl;
  std::cout
      << "   • Description: Mode for ROS-based audio application development"
      << std::endl;
  std::cout << "   • Purpose: Access to audio data through ROS topics"
            << std::endl;
  std::cout << "   • Use case: When developing ROS nodes that process audio, "
               "speech recognition"
            << std::endl;
  std::cout << "   • Features: Audio data published as ROS topics, ROS message "
               "interfaces"
            << std::endl;
  std::cout << std::endl;

  // Develop_MC mode description
  std::cout << "5. Develop_MC - Motion Control Development Mode" << std::endl;
  std::cout << "   • Description: Mode for motion control system development"
            << std::endl;
  std::cout
      << "   • Purpose: Enables direct control and testing of motion systems"
      << std::endl;
  std::cout << "   • Use case: When developing motor control algorithms, "
               "testing motion hardware"
            << std::endl;
  std::cout << "   • Features: Low-level motor control access, motion system "
               "debugging tools"
            << std::endl;
  std::cout << std::endl;

  std::cout << "Program Workflow:" << std::endl;
  std::cout << "=================" << std::endl;
  std::cout
      << "1. Calls MigrateSystemState service with the specified target state"
      << std::endl;
  std::cout << "2. Continuously monitors GetSystemState service every second"
            << std::endl;
  std::cout << "3. Exits when both conditions are met:" << std::endl;
  std::cout << "   • Current State equals target state (case-insensitive)"
            << std::endl;
  std::cout << "   • System Status equals 1 (IN_READY)" << std::endl;
  std::cout << std::endl;
  std::cout << "Note: The program will automatically exit when migration is "
               "complete or on error."
            << std::endl;
}

/**
 * @brief Validate if the target state is a known development mode
 * @param state The state to validate
 * @return true if state is valid, false otherwise
 */
bool is_valid_state(const std::string &state) {
  // List of known valid states
  const std::vector<std::string> valid_states = {
      "Ready", "Develop_Nav", "Develop_Audio_Linux", "Develop_Audio_ROS",
      "Develop_MC"};

  // Convert input to lowercase for case-insensitive comparison
  std::string state_lower = state;
  std::transform(state_lower.begin(), state_lower.end(), state_lower.begin(),
                 ::tolower);

  // Check if state is in the list of valid states
  for (const auto &valid_state : valid_states) {
    std::string valid_state_lower = valid_state;
    std::transform(valid_state_lower.begin(), valid_state_lower.end(),
                   valid_state_lower.begin(), ::tolower);

    if (state_lower == valid_state_lower) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Main function
 * @param argc Argument count
 * @param argv Argument vector
 * @return Exit code
 */
int main(int argc, char **argv) {
  // Check command line arguments
  if (argc != 2) {
    print_usage(argv[0]);
    return 1;
  }

  // Get target state from command line argument
  std::string target_state = argv[1];

  // Validate target state
  if (target_state.empty()) {
    std::cerr << "Error: Target state cannot be empty" << std::endl;
    print_usage(argv[0]);
    return 1;
  }

  // Optional: Validate against known states
  if (!is_valid_state(target_state)) {
    std::cout << "Warning: '" << target_state
              << "' is not in the list of known states." << std::endl;
    std::cout << "The program will still attempt to migrate to this state."
              << std::endl;
    std::cout << "Continue? (y/n): ";

    std::string response;
    std::getline(std::cin, response);

    if (response != "y" && response != "Y") {
      std::cout << "Operation cancelled." << std::endl;
      return 0;
    }
  }

  // Initialize ROS2
  rclcpp::init(argc, argv);

  // Create migrator node with target state
  auto node = std::make_shared<SystemStateMigrator>(target_state);

  // Create single-threaded executor
  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();

  // Add node to executor
  executor->add_node(node);

  // Run executor (blocking call)
  executor->spin();

  // Cleanup
  executor->remove_node(node);
  rclcpp::shutdown();

  return 0;
}