//
// Created by agiuser on 2026/3/2.
//

#include "aimdk_msgs/srv/get_stored_map_by_name.hpp"
#include "rclcpp/rclcpp.hpp"
#include <memory>

class MapClient : public rclcpp::Node {
public:
  MapClient() : Node("get_map_client") {
    client_ = this->create_client<aimdk_msgs::srv::GetStoredMapByName>(
        "/aimdk_5Fmsgs/srv/GetStoredMapByName");
  }

  void send_request(const std::string &map_name) {
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(),
                     "Interrupted while waiting for service.");
        return;
      }
      RCLCPP_INFO(this->get_logger(),
                  "Service not available, waiting again...");
    }

    auto request =
        std::make_shared<aimdk_msgs::srv::GetStoredMapByName::Request>();

    request->header.stamp = this->now();
    request->header.frame_id = "";

    request->map_name = map_name;

    auto result_future = client_->async_send_request(request);

    // Use a fresh executor to spin, avoiding any pre-existing state.
    rclcpp::executors::SingleThreadedExecutor exec;
    exec.add_node(shared_from_this());
    if (exec.spin_until_future_complete(result_future,
                                        std::chrono::seconds(10)) !=
        rclcpp::FutureReturnCode::SUCCESS) {
      RCLCPP_ERROR(this->get_logger(), "Service call failed or timed out.");
      return;
    }

    auto result = result_future.get();

    if (result->code == 0) {
      RCLCPP_INFO(this->get_logger(), "Service call succeeded");
      RCLCPP_INFO(this->get_logger(), "Map path: %s", result->map_path.c_str());
      RCLCPP_INFO(this->get_logger(), "Map resolution: %f",
                  result->map_info.resolution);
      RCLCPP_INFO(this->get_logger(), "Map width: %u", result->map_info.width);
      RCLCPP_INFO(this->get_logger(), "Map height: %u",
                  result->map_info.height);
      RCLCPP_INFO(this->get_logger(), "Map id: %ld", result->map_id);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Service call failed with code: %lu",
                   result->code);
    }
  }

private:
  rclcpp::Client<aimdk_msgs::srv::GetStoredMapByName>::SharedPtr client_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  auto client = std::make_shared<MapClient>();
  client->send_request("map_name");

  rclcpp::shutdown();
  return 0;
}
