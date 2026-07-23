#include "aimdk_msgs/msg/common_request.hpp"
#include "aimdk_msgs/msg/common_state.hpp"
#include "aimdk_msgs/srv/get_mic_source_request.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>
#include <signal.h>

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

class GetMicSourceRequestClient : public rclcpp::Node {
public:
  GetMicSourceRequestClient() : Node("get_mic_source_request_client") {
    client_ = this->create_client<aimdk_msgs::srv::GetMicSourceRequest>(
        "/aimdk_5Fmsgs/srv/GetMicSourceRequest");

    RCLCPP_INFO(this->get_logger(),
                "✅ GetMicSourceRequest client node created.");

    // Wait for the service to become available
    while (!client_->wait_for_service(std::chrono::seconds(2))) {
      RCLCPP_INFO(this->get_logger(), "⏳ Service unavailable, waiting...");
    }
    RCLCPP_INFO(this->get_logger(),
                "🟢 Service available, ready to send request.");
  }

  void send_request() {
    try {
      auto request =
          std::make_shared<aimdk_msgs::srv::GetMicSourceRequest::Request>();
      request->header = aimdk_msgs::msg::CommonRequest();

      RCLCPP_INFO(this->get_logger(), "📨 Sending request to get MIC source");

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
          RCLCPP_INFO(this->get_logger(), "✅ MIC source get successfully.");
          RCLCPP_INFO(this->get_logger(), "MIC id: %d", response->mic_source);
        } else {
          RCLCPP_ERROR(this->get_logger(), "❌ Failed to get MIC source: %s",
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
  rclcpp::Client<aimdk_msgs::srv::GetMicSourceRequest>::SharedPtr client_;
};

int main(int argc, char *argv[]) {
  try {
    rclcpp::init(argc, argv);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    g_node = std::make_shared<GetMicSourceRequestClient>();
    auto client = std::dynamic_pointer_cast<GetMicSourceRequestClient>(g_node);

    if (client) {
      client->send_request();
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
