//
// Created by agiuser on 2026/1/27.
//
#include <aimdk_msgs/msg/hand_command_array.hpp>
#include <aimdk_msgs/msg/hand_state_array.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class HandStateSubscriber : public rclcpp::Node {
public:
  HandStateSubscriber() : Node("hand_state_subscriber") {
    publisher_ = this->create_publisher<aimdk_msgs::msg::HandCommandArray>(
        "/aima/hal/joint/hand/command", 10);
    rclcpp::QoS qos_profile(rclcpp::KeepLast(10));
    qos_profile.best_effort(); // Set reliability to BEST_EFFORT
    // Create subscriber
    subscription_ = this->create_subscription<aimdk_msgs::msg::HandStateArray>(
        "/aima/hal/joint/hand/state", qos_profile,
        std::bind(&HandStateSubscriber::topic_callback, this,
                  std::placeholders::_1));
    // Create a timer to publish once per second
    timer_ = this->create_wall_timer(
        1s, std::bind(&HandStateSubscriber::publish_command, this));
    RCLCPP_INFO(
        this->get_logger(),
        "Subscriber started, listening to /aima/hal/joint/hand/state topic...");
  }

private:
  void topic_callback(const aimdk_msgs::msg::HandStateArray::SharedPtr msg) {
    // Print message header information
    RCLCPP_INFO(this->get_logger(),
                "Message received - Sequence: %u, Timestamp: %d.%09d",
                msg->header.sequence, msg->header.stamp.sec,
                msg->header.stamp.nanosec);

    // Print left hand touch sensor data
    print_touch_sensor_data("Left Hand", msg->left_touch_sensors);

    // Print right hand touch sensor data
    print_touch_sensor_data("Right Hand", msg->right_touch_sensors);

    std::cout << std::endl;
  }

  /**
   * @brief Print touch sensor data for a specific hand
   * @param hand_name Name of the hand (Left Hand/Right Hand)
   * @param sensor_data Touch sensor data structure
   */
  void print_touch_sensor_data(
      const std::string &hand_name,
      const aimdk_msgs::msg::HandTouchSensorData &sensor_data) {
    std::cout << "=== " << hand_name << " Touch Sensor Data ===" << std::endl;

    // Print palm touch data
    std::cout << "Palm Touch Data (36 elements): ";
    print_array(sensor_data.palm_touch_data);

    // Print back of hand touch data
    std::cout << "Back of Hand Touch Data (36 elements): ";
    print_array(sensor_data.back_of_hand_touch_data);

    // Print finger touch data
    std::cout << "Thumb Touch Data (16 elements): ";
    print_array(sensor_data.thumb_touch_data);

    std::cout << "Index Finger Touch Data (16 elements): ";
    print_array(sensor_data.index_finger_touch_data);

    std::cout << "Middle Finger Touch Data (16 elements): ";
    print_array(sensor_data.middle_finger_touch_data);

    std::cout << "Ring Finger Touch Data (16 elements): ";
    print_array(sensor_data.ring_finger_touch_data);

    std::cout << "Little Finger Touch Data (16 elements): ";
    print_array(sensor_data.little_finger_touch_data);
  }

  /**
   * @brief Print array of 25 uint8_t elements
   * @param arr Array to print
   */
  void print_array(const std::array<uint8_t, 36> &arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << std::setw(3) << static_cast<int>(arr[i]);
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << "]" << std::endl;
  }

  /**
   * @brief Print array of 16 uint8_t elements
   * @param arr Array to print
   */
  void print_array(const std::array<uint8_t, 16> &arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
      std::cout << std::setw(3) << static_cast<int>(arr[i]);
      if (i < arr.size() - 1)
        std::cout << " ";
    }
    std::cout << "]" << std::endl;
  }

  void publish_command() {
    auto message = aimdk_msgs::msg::HandCommandArray();

    // Set hander
    message.header.stamp = this->now();
    message.header.frame_id = "hand_command";

    // Set the hand type
    message.left_hand_type.value = 1;  // NIMBLE_HANDS
    message.right_hand_type.value = 1; // NIMBLE_HANDS

    // Create left hand command array
    message.left_hands.resize(10);

    // Set left thumb
    message.left_hands[0].name = "left_thumb";
    message.left_hands[0].position = 0.0;
    message.left_hands[0].velocity = 0.1;
    message.left_hands[0].acceleration = 0.0;
    message.left_hands[0].deceleration = 0.0;
    message.left_hands[0].effort = 0.0;
    // Set other left fingers
    for (int i = 1; i < 10; i++) {
      message.left_hands[i].name = "left_index";
      message.left_hands[i].position = 0.0;
      message.left_hands[i].velocity = 0.1;
      message.left_hands[i].acceleration = 0.0;
      message.left_hands[i].deceleration = 0.0;
      message.left_hands[i].effort = 0.0;
    }

    // Create right hand command array
    message.right_hands.resize(10);

    // Set right thumb
    message.right_hands[0].name = "right_thumb";
    message.right_hands[0].position = 0.0;
    message.right_hands[0].velocity = 0.1;
    message.right_hands[0].acceleration = 0.0;
    message.right_hands[0].deceleration = 0.0;
    message.right_hands[0].effort = 0.0;

    // Set other right fingers (pinky)
    for (int i = 1; i < 10; i++) {
      message.right_hands[i].name = "right_pinky";
      message.right_hands[i].position = 0.0;
      message.right_hands[i].velocity = 0.1;
      message.right_hands[i].acceleration = 0.0;
      message.right_hands[i].deceleration = 0.0;
      message.right_hands[i].effort = 0.0;
    }

    // Publish the message
    publisher_->publish(message);

    RCLCPP_INFO(this->get_logger(), "Published hand command");
  }

  rclcpp::Publisher<aimdk_msgs::msg::HandCommandArray>::SharedPtr publisher_;
  rclcpp::Subscription<aimdk_msgs::msg::HandStateArray>::SharedPtr
      subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<HandStateSubscriber>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
