#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>

// Class definition for publishing commands to control SLAM operations
class SlamCommandPublisher : public rclcpp::Node {
public:
  // Constructor for the SlamCommandPublisher class
  SlamCommandPublisher()
      : Node("slam_command_publisher") // Initialize the node with the name
                                       // "slam_command_publisher"
  {
    // Match SLAM subscriber QoS: TRANSIENT_LOCAL + RELIABLE
    rclcpp::QoS qos(10);
    qos.transient_local().reliable();
    publisher_ = this->create_publisher<std_msgs::msg::String>(
        "/integrated_command", qos);
  }

  // Method to publish the "start_mapping" command
  void publish_start_mapping() {
    auto message = std_msgs::msg::String();
    message.data = "start_mapping";
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  // Method to publish the "stop_mapping" command with a specified map name
  void publish_stop_mapping(const std::string &map_name) {
    auto message = std_msgs::msg::String();
    message.data = "stop_mapping:" + map_name;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

private:
  // Publisher object to publish messages to the "/integrated_command" topic
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
  // Initialize the ROS 2 communication system
  rclcpp::init(argc, argv);
  // Create an instance of the SlamCommandPublisher node
  auto node = std::make_shared<SlamCommandPublisher>();

  int input;
  std::string map_name;

  // Infinite loop to continuously accept user input
  while (rclcpp::ok()) {
    std::cout << "Enter 1 to start mapping, 2 to stop mapping: ";
    std::cin >> input;

    if (input == 1) {
      // Publish the "start_mapping" command
      node->publish_start_mapping();
    } else if (input == 2) {
      // Prompt the user to enter the map name
      std::cout << "Enter map name: ";
      std::cin >> map_name;
      // Publish the "stop_mapping" command with the specified map name
      node->publish_stop_mapping(map_name);
      break;
    } else {
      // Handle invalid input
      std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
    }
  }

  // Shutdown the ROS 2 communication system
  rclcpp::shutdown();
  return 0;
}
