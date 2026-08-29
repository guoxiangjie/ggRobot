#include <chrono>
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

class RelocalizationNode : public rclcpp::Node {
public:
  RelocalizationNode() : Node("relocalization_node") {
    // /integrated_command subscriber requires TRANSIENT_LOCAL durability
    auto command_qos = rclcpp::QoS(rclcpp::KeepLast(10));
    command_qos.transient_local();

    integrated_command_pub_ = this->create_publisher<std_msgs::msg::String>(
        "/integrated_command", command_qos);
    relocalization_pose_pub_ = this->create_publisher<geometry_msgs::msg::Pose>(
        "/relocalization_pose", 10);

    // Create subscriber with BEST_EFFORT QoS
    auto lidar_loc_qos = rclcpp::QoS(rclcpp::KeepLast(10));
    lidar_loc_qos.best_effort();

    odometry_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
        "/slam/lidar_odom", lidar_loc_qos,
        std::bind(&RelocalizationNode::odometryCallback, this,
                  std::placeholders::_1));

    // Wait for subscribers before publishing
    publish_timer_ = this->create_wall_timer(200ms, [this]() {
      // Wait until both publishers have at least one subscriber
      if (integrated_command_pub_->get_subscription_count() == 0 ||
          relocalization_pose_pub_->get_subscription_count() == 0) {
        RCLCPP_INFO_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "Waiting for subscribers... (command: %zu, pose: %zu)",
            integrated_command_pub_->get_subscription_count(),
            relocalization_pose_pub_->get_subscription_count());
        return;
      }
      publish_timer_->cancel();

      // Publish integrated_command
      auto integrated_command_msg = std_msgs::msg::String();
      integrated_command_msg.data = "start_relocalization:1774430080403";
      integrated_command_pub_->publish(integrated_command_msg);
      RCLCPP_INFO(this->get_logger(), "Published integrated_command");

      // Schedule relocalization_pose publication after delay
      this->relocalization_pose_timer_ = this->create_wall_timer(1s, [this]() {
        this->relocalization_pose_timer_->cancel();

        auto relocalization_pose_msg = geometry_msgs::msg::Pose();
        relocalization_pose_msg.position.x = 273;
        relocalization_pose_msg.position.y = 200;
        relocalization_pose_msg.position.z = 0.0;
        relocalization_pose_msg.orientation.x = 0.0;
        relocalization_pose_msg.orientation.y = 0.0;
        relocalization_pose_msg.orientation.z = 0.0;
        relocalization_pose_msg.orientation.w = 1.0;

        relocalization_pose_pub_->publish(relocalization_pose_msg);
        RCLCPP_INFO(this->get_logger(), "Published relocalization_pose");

        // Start timeout timer (5 seconds)
        this->timeout_timer_ = this->create_wall_timer(30s, [this]() {
          if (!success_received_) {
            RCLCPP_ERROR(this->get_logger(),
                         "Timeout reached - Relocalization failed!");
            rclcpp::shutdown();
          }
        });

        RCLCPP_INFO(this->get_logger(),
                    "Waiting for robot pose data (timeout: 30s)...");
      });
    });
  }

private:
  // get robot pose here
  void odometryCallback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    if (!success_received_) {
      success_received_ = true;
      if (timeout_timer_) {
        timeout_timer_->cancel();
      }
      RCLCPP_INFO(this->get_logger(),
                  "Received odometry data - Relocalization successful!");
      rclcpp::shutdown();
    }
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr integrated_command_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr
      relocalization_pose_pub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_sub_;

  // Timers
  rclcpp::TimerBase::SharedPtr publish_timer_;
  rclcpp::TimerBase::SharedPtr relocalization_pose_timer_;
  rclcpp::TimerBase::SharedPtr timeout_timer_;

  bool success_received_ = false;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RelocalizationNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
