//
// Created by agiuser on 2026/3/3.
//

#include <aimdk_msgs/srv/execute_action_resource.hpp>
#include <aimdk_msgs/srv/get_robot_resources.hpp>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <vector>

using namespace std::chrono_literals;

class RobotResourceClient : public rclcpp::Node {
public:
  RobotResourceClient() : Node("robot_resource_client") {
    get_resource_client_ =
        this->create_client<aimdk_msgs::srv::GetRobotResources>(
            "/aimdk_5Fmsgs/srv/GetRobotResources");
    play_resource_client_ =
        this->create_client<aimdk_msgs::srv::ExecuteActionResource>(
            "/aimdk_5Fmsgs/srv/ExecuteActionResource");
  }

  bool get_robot_resources() {
    while (!get_resource_client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        return false;
      }
      RCLCPP_INFO(this->get_logger(),
                  "Service not available, waiting again...");
    }

    if (!rclcpp::ok()) {
      return false;
    }

    auto request =
        std::make_shared<aimdk_msgs::srv::GetRobotResources::Request>();

    auto future_result = get_resource_client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(),
                                           future_result) !=
        rclcpp::FutureReturnCode::SUCCESS) {
      if (rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "Failed to call GetRobotResources");
      }
      return false;
    }

    auto response = future_result.get();
    resources_ = response->robot_resources;
    RCLCPP_INFO(this->get_logger(), "Found %zu resources", resources_.size());
    return true;
  }

  void print_resource_menu() {
    if (resources_.empty()) {
      std::cout << "(no resources)\n";
      return;
    }

    std::cout << "\n=== Available Robot Resources ===\n";
    for (size_t i = 0; i < resources_.size(); ++i) {
      const auto &ver = resources_[i].current_version;
      std::cout << "[" << i << "] "
                << (ver.name.empty() ? "<no name>" : ver.name) << "\n";
      std::cout << "     key:     " << resources_[i].resource_key << "\n";
      std::cout << "     version: " << ver.version << "\n";
    }
    std::cout << "=================================\n\n";
  }

  int pick_resource() {
    if (resources_.empty()) {
      return -1;
    }

    std::string line;
    while (true) {
      std::cout << "Select resource index [0-" << resources_.size() - 1
                << "] (q to quit): ";
      if (!std::getline(std::cin, line)) {
        return -1;
      }
      if (line == "q" || line == "quit" || line == "exit") {
        return -1;
      }
      try {
        int idx = std::stoi(line);
        if (idx >= 0 && idx < static_cast<int>(resources_.size())) {
          return idx;
        }
        std::cout << "Index out of range (0-" << resources_.size() - 1
                  << ").\n";
      } catch (...) {
        std::cout << "Please enter a number.\n";
      }
    }
  }

  void play_resource(int idx) {
    while (!play_resource_client_->wait_for_service(1s)) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(),
                     "Interrupted while waiting for service.");
        return;
      }
      RCLCPP_INFO(this->get_logger(), "Service not available, waiting...");
    }

    if (!rclcpp::ok()) {
      return;
    }

    const auto &resource = resources_[idx];
    auto request =
        std::make_shared<aimdk_msgs::srv::ExecuteActionResource::Request>();

    request->resource_key = resource.resource_key;
    request->resource_version = resource.current_version.version;

    if (request->resource_key.find("onnx") != std::string::npos) {
      request->meta = R"({"resource_type": "BODY_MONTION"})";
    } else {
      request->meta = R"({"resource_type": "ARM_MONTION"})";
    }

    RCLCPP_INFO(this->get_logger(), "Sending request:");
    RCLCPP_INFO(this->get_logger(), "  resource_key: %s",
                request->resource_key.c_str());
    RCLCPP_INFO(this->get_logger(), "  resource_version: %s",
                request->resource_version.c_str());
    RCLCPP_INFO(this->get_logger(), "  meta: %s", request->meta.c_str());

    auto future = play_resource_client_->async_send_request(request);

    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(),
                                           future) ==
        rclcpp::FutureReturnCode::SUCCESS) {
      handle_response(future.get());
    } else {
      if (rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(),
                     "Failed to call ExecuteActionResource");
      }
    }
  }

private:
  rclcpp::Client<aimdk_msgs::srv::GetRobotResources>::SharedPtr
      get_resource_client_;
  rclcpp::Client<aimdk_msgs::srv::ExecuteActionResource>::SharedPtr
      play_resource_client_;
  std::vector<aimdk_msgs::msg::RobotResource> resources_;

  void handle_response(
      const aimdk_msgs::srv::ExecuteActionResource::Response::SharedPtr
          response) {
    RCLCPP_INFO(this->get_logger(), "Service response received:");
    RCLCPP_INFO(this->get_logger(), "Response Header:");
    RCLCPP_INFO(this->get_logger(), "  stamp: %d.%09u",
                response->header.header.stamp.sec,
                response->header.header.stamp.nanosec);
    RCLCPP_INFO(this->get_logger(), "  code: %ld",
                response->header.header.code);
    RCLCPP_INFO(this->get_logger(), "Status:");
    RCLCPP_INFO(this->get_logger(), "  value: %d",
                response->header.status.value);
    RCLCPP_INFO(this->get_logger(), "  message: %s",
                response->header.message.c_str());
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto client_node = std::make_shared<RobotResourceClient>();

  if (!client_node->get_robot_resources()) {
    rclcpp::shutdown();
    return 1;
  }

  client_node->print_resource_menu();
  int chosen = client_node->pick_resource();
  if (chosen < 0) {
    RCLCPP_INFO(client_node->get_logger(), "No resource selected, exiting.");
    rclcpp::shutdown();
    return 0;
  }

  client_node->play_resource(chosen);
  rclcpp::shutdown();
  return 0;
}
