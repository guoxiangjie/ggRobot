#include "aimdk_msgs/msg/common_request.hpp"
#include "aimdk_msgs/msg/common_state.hpp"
#include "aimdk_msgs/srv/set_mic_source_request.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <map>
#include <memory>
#include <signal.h>
#include <string>

std::shared_ptr<rclcpp::Node> g_node = nullptr;

void signal_handler(int signal) {
  if (g_node) {
    RCLCPP_INFO(g_node->get_logger(), "Received signal %d, shutting down...",
                signal);
    g_node.reset();
  }
  rclcpp::shutdown();
  exit(signal);
}

class SetMicSourceRequestClient : public rclcpp::Node {
public:
  SetMicSourceRequestClient() : Node("set_mic_source_request_client") {
    client_ = this->create_client<aimdk_msgs::srv::SetMicSourceRequest>(
        "/aimdk_5Fmsgs/srv/SetMicSourceRequest");

    RCLCPP_INFO(this->get_logger(),
                "✅ SetMicSourceRequest client node created.");

    // Wait for the service to become available
    while (!client_->wait_for_service(std::chrono::seconds(2))) {
      RCLCPP_INFO(this->get_logger(), "⏳ Service unavailable, waiting...");
    }
    RCLCPP_INFO(this->get_logger(),
                "🟢 Service available, ready to send request.");
  }

  void send_request(int mic_source) {
    try {
      auto request =
          std::make_shared<aimdk_msgs::srv::SetMicSourceRequest::Request>();
      request->header = aimdk_msgs::msg::CommonRequest();
      request->mic_source = mic_source;

      RCLCPP_INFO(this->get_logger(), "📨 Sending request to set mic source: %d",
                  mic_source);

      auto timeout = std::chrono::milliseconds(250);
      for (int i = 0; i < 8; i++) {
        request->header.header.stamp = this->now();
        auto future = client_->async_send_request(request);
        auto retcode = rclcpp::spin_until_future_complete(
            this->shared_from_this(), future, timeout);
        if (retcode != rclcpp::FutureReturnCode::SUCCESS) {
          // retry as remote peer is NOT handled well by ROS
          RCLCPP_INFO(this->get_logger(), "trying ... [%d]", i);
          continue;
        }
        // future.done
        auto response = future.get();
        if (response->header.status.value ==
            aimdk_msgs::msg::CommonState::SUCCESS) {
          RCLCPP_INFO(this->get_logger(), "✅ MIC source set successfully.");
        } else {
          RCLCPP_ERROR(this->get_logger(), "❌ Failed to set MIC source: %s",
                       response->header.message.c_str());
        }
        return;
      }
      RCLCPP_ERROR(this->get_logger(), "❌ Service call failed or timed out.");
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Exception occurred: %s", e.what());
    }
  }

private:
  rclcpp::Client<aimdk_msgs::srv::SetMicSourceRequest>::SharedPtr client_;
};

int main(int argc, char *argv[]) {
  // abbr -> mic_id mapping
  // 0: internal MIC, 1: external MIC
  const std::map<std::string, int> choices = {{"int", 0}, {"ext", 1}};

  try {
    rclcpp::init(argc, argv);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::string mic_abbr;
    if (argc > 1) {
      mic_abbr = argv[1];
    } else {
      printf("%-4s - %-6s : %s\n", "abbr", "mic_id", "description");
      printf("%-4s - %-6d : %s\n", "int", 0, "internal MIC");
      printf("%-4s - %-6d : %s\n", "ext", 1, "external MIC");
      printf("Enter abbr of MIC source: ");
      std::cin >> mic_abbr;
    }

    auto it = choices.find(mic_abbr);
    if (it == choices.end()) {
      RCLCPP_ERROR(rclcpp::get_logger("main"), "Invalid abbr of MIC source: %s",
                   mic_abbr.c_str());
      return 1;
    }
    int mic_id = it->second;

    g_node = std::make_shared<SetMicSourceRequestClient>();
    auto client = std::dynamic_pointer_cast<SetMicSourceRequestClient>(g_node);

    if (client) {
      client->send_request(mic_id);
    }

    g_node.reset();
    rclcpp::shutdown();
    return 0;
  } catch (const std::exception &e) {
    RCLCPP_ERROR(rclcpp::get_logger("main"),
                 "Program exited with exception: %s", e.what());
    return 1;
  }
}
