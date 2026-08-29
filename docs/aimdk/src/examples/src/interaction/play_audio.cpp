#include <aimdk_msgs/srv/play_audio_file.hpp>
#include <filesystem>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <string>

using PlayAudioFile = aimdk_msgs::srv::PlayAudioFile;

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("play_audio_file_client_min");

  // 1) Service name
  const std::string service_name = "/aimdk_5Fmsgs/srv/PlayAudioFile";
  auto client = node->create_client<PlayAudioFile>(service_name);

  // 2) Input file path (prompt user if not provided as argument)
  std::string default_file =
      "/agibot/data/var/interaction/tts_cache/normal/demo.wav";
  std::string file_name;

  if (argc > 1) {
    file_name = argv[1];
  } else {
    std::cout << "Enter the media file path to play (default: " << default_file
              << "): ";
    if (!std::getline(std::cin, file_name) || !rclcpp::ok()) {
      std::cout << std::endl;
      rclcpp::shutdown();
      return 1;
    }
    if (file_name.empty()) {
      file_name = default_file;
    }
  }

  // 3) Build the request
  // Check if Ctrl+C was pressed during user input
  if (!rclcpp::ok()) {
    rclcpp::shutdown();
    return 1;
  }

  auto req = std::make_shared<PlayAudioFile::Request>();
  req->file.pkg_name = "demo_client";
  req->file.file_name = std::filesystem::path(file_name).filename().string();
  req->file.file_path =
      std::filesystem::path(file_name).parent_path().string() + "/";
  req->file.priority = 6;
  req->file.priority_weight = 0;

  // 4) Wait for service and call
  RCLCPP_INFO(rclcpp::get_logger("main"), "Waiting for service: %s",
              service_name.c_str());
  while (!client->wait_for_service(std::chrono::seconds(2))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(),
                   "Interrupted while waiting for the service. Exiting.");
      rclcpp::shutdown();
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "⏳ Service unavailable, waiting...");
  }

  rclcpp::FutureReturnCode rc = rclcpp::FutureReturnCode::TIMEOUT;
  std::shared_future<PlayAudioFile::Response::SharedPtr> future;
  for (int i = 0; i < 5; ++i) {
    req->request.header.stamp = node->now();
    future = client->async_send_request(req);
    rc = rclcpp::spin_until_future_complete(node, future,
                                            std::chrono::seconds(1));
    if (rc == rclcpp::FutureReturnCode::SUCCESS) {
      break;
    }
    if (rc == rclcpp::FutureReturnCode::INTERRUPTED) {
      // Check if Ctrl+C was pressed during spin_until_future_complete
      if (rclcpp::ok()) {
        RCLCPP_WARN(node->get_logger(), "Interrupted while waiting");
      }
      rclcpp::shutdown();
      return 1;
    }
    // retry as remote peer is NOT handled well by ROS
    RCLCPP_INFO(node->get_logger(), "trying ... [%d]", i);
  }

  if (rc != rclcpp::FutureReturnCode::SUCCESS) {
    // Check if Ctrl+C was pressed, avoid using node after shutdown
    if (rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "Call timed out or did not complete");
    }
    rclcpp::shutdown();
    return 1;
  }

  // 5) Handle response (success is in reponse.status)
  try {
    const auto resp = future.get();
    bool success = resp->reponse.status.value == 1;

    if (success) {
      RCLCPP_INFO(node->get_logger(), "✅ Audio file play request succeeded: %s",
                  file_name.c_str());
    } else {
      RCLCPP_ERROR(node->get_logger(), "❌ Audio file play request failed: %s",
                   file_name.c_str());
    }
  } catch (const std::exception &e) {
    RCLCPP_ERROR(node->get_logger(), "Call exception: %s", e.what());
  }

  rclcpp::shutdown();
  return 0;
}
