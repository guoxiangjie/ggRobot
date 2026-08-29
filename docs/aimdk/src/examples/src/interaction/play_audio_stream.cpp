/**
 * Raw audio stream playback example
 *
 * This example gets audio focus first and then publishes raw audio data at a
 * fixed rate to the `/aima/hal/audio/playback` topic. It stops playing when
 * audio focus is lost.
 *
 * Usage:
 *   ros2 run examples play_audio_stream --ros-args -p
 * raw_audio_path:=/path/to/file.pcm
 */

#include <aimdk_msgs/msg/audio_data.hpp>
#include <aimdk_msgs/msg/audio_info.hpp>
#include <aimdk_msgs/msg/audio_playback.hpp>
#include <aimdk_msgs/msg/common_state.hpp>
#include <aimdk_msgs/msg/focus_requester.hpp>
#include <aimdk_msgs/msg/focus_response.hpp>
#include <aimdk_msgs/srv/abandon_audio_focus.hpp>
#include <aimdk_msgs/srv/request_audio_focus.hpp>
#include <chrono>
#include <csignal>
#include <fstream>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <thread>
#include <vector>

// ---------------------------------------------------------------------------
// FakeMicDevice: simulates a real-time microphone from a raw PCM file
// ---------------------------------------------------------------------------
class FakeMicDevice {
public:
  explicit FakeMicDevice(const std::string &raw_audio_file)
      : channels_(1), sample_rate_(16000), bytes_per_sample_(2), index_(0),
        start_time_(std::chrono::steady_clock::time_point{}) {
    std::ifstream f(raw_audio_file, std::ios::binary);
    if (!f.is_open()) {
      throw std::runtime_error("Cannot open audio file: " + raw_audio_file);
    }
    audio_data_ = std::vector<uint8_t>(std::istreambuf_iterator<char>(f),
                                       std::istreambuf_iterator<char>());
  }

  int get_channel_count() const { return channels_; }
  int get_sample_rate() const { return sample_rate_; }

  std::vector<uint8_t> get_cached_data() {
    auto now = std::chrono::steady_clock::now();
    if (start_time_ == std::chrono::steady_clock::time_point{}) {
      // fake init: assume audio data started 1s ago
      start_time_ = now - std::chrono::seconds(1);
    }

    double elapsed = std::chrono::duration<double>(now - start_time_).count();
    size_t tail = static_cast<size_t>(elapsed * sample_rate_) * channels_ *
                  bytes_per_sample_;

    std::vector<uint8_t> data;
    if (tail < audio_data_.size()) {
      data = std::vector<uint8_t>(audio_data_.begin() + index_,
                                  audio_data_.begin() + tail);
      index_ = tail;
    } else {
      // loopback
      data =
          std::vector<uint8_t>(audio_data_.begin() + index_, audio_data_.end());
      index_ = 0;
      start_time_ = now;
    }
    return data;
  }

private:
  int channels_;
  int sample_rate_;
  int bytes_per_sample_;
  size_t index_;
  std::chrono::steady_clock::time_point start_time_;
  std::vector<uint8_t> audio_data_;
};

// ---------------------------------------------------------------------------
// AudioStreamPlayer node
// ---------------------------------------------------------------------------
using RequestAudioFocus = aimdk_msgs::srv::RequestAudioFocus;
using AbandonAudioFocus = aimdk_msgs::srv::AbandonAudioFocus;

class AudioStreamPlayer : public rclcpp::Node {
public:
  AudioStreamPlayer() : rclcpp::Node("audio_stream_player") {
    this->declare_parameter<std::string>("raw_audio_path", "");
    std::string raw_audio_path =
        this->get_parameter("raw_audio_path").as_string();

    mic_device_ = std::make_unique<FakeMicDevice>(raw_audio_path);

    pkg_name_ = "audio_stream_player" + std::to_string(getpid());
    focus_ = false;
    focus_force_ = true;

    RCLCPP_INFO(this->get_logger(), "local pkg name: %s", pkg_name_.c_str());

    // Create focus request/release clients
    request_client_ = this->create_client<RequestAudioFocus>(
        "/aimdk_5Fmsgs/srv/RequestAudioFocus");
    release_client_ = this->create_client<AbandonAudioFocus>(
        "/aimdk_5Fmsgs/srv/AbandonAudioFocus");

    // Wait for service to become available
    while (!request_client_->wait_for_service(std::chrono::seconds(2))) {
      RCLCPP_INFO(this->get_logger(), "Service unavailable, waiting...");
    }
    RCLCPP_INFO(this->get_logger(),
                "Service available, ready to send request.");

    // Subscriber: focus events
    auto focus_qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
    sub_ = this->create_subscription<aimdk_msgs::msg::FocusResponse>(
        "/aima/hal/audio/focus_response", focus_qos,
        std::bind(&AudioStreamPlayer::focus_event_callback, this,
                  std::placeholders::_1));

    // Publisher: raw audio playback
    pub_ = this->create_publisher<aimdk_msgs::msg::AudioPlayback>(
        "/aima/hal/audio/playback", 10);
  }

  void send_request(bool focus) {
    if (focus) {
      send_focus_request();
    } else {
      send_focus_release();
    }
  }

  bool is_holding_focus() const { return focus_ && focus_force_; }

  void spin_until_focus() {
    while (rclcpp::ok()) {
      focus_force_ = true;
      send_request(true);
      if (is_holding_focus())
        return;

      RCLCPP_INFO(this->get_logger(), "need retry to get focus");
      auto t0 = std::chrono::steady_clock::now();
      while (rclcpp::ok()) {
        auto t1 = std::chrono::steady_clock::now();
        if (std::chrono::duration<double>(t1 - t0).count() >= 1.0)
          break;
        rclcpp::spin_some(shared_from_this());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  }

  void run() {
    RCLCPP_INFO(this->get_logger(), "publishing audio data ...");
    while (rclcpp::ok() && is_holding_focus()) {
      run_once();
      rclcpp::spin_some(shared_from_this());
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    if (!is_holding_focus()) {
      RCLCPP_INFO(this->get_logger(), "focus out, exiting...");
    }
  }

private:
  void send_focus_request() {
    auto req = std::make_shared<RequestAudioFocus::Request>();
    aimdk_msgs::msg::FocusRequester requester;
    requester.pkg_name = pkg_name_;
    requester.priority = 6;
    req->focus_requester = requester;

    RCLCPP_INFO(this->get_logger(), "Sending RequestAudioFocus request");
    std::shared_future<RequestAudioFocus::Response::SharedPtr> future;
    for (int i = 0; i < 8; ++i) {
      future = request_client_->async_send_request(req).future.share();
      auto status = rclcpp::spin_until_future_complete(
          shared_from_this(), future, std::chrono::milliseconds(250));
      if (status == rclcpp::FutureReturnCode::SUCCESS)
        break;
      RCLCPP_INFO(this->get_logger(), "trying ... [%d]", i);
    }

    auto response = future.get();
    if (!response) {
      RCLCPP_ERROR(this->get_logger(), "Service call failed or timed out.");
      return;
    }
    if (response->reponse.status.value ==
        aimdk_msgs::msg::CommonState::SUCCESS) {
      focus_ = response->focus_response.focus_gain;
      RCLCPP_INFO(this->get_logger(), "RequestAudioFocus done: focus %s",
                  focus_ ? "true" : "false");
    } else {
      RCLCPP_ERROR(this->get_logger(),
                   "Failed in response of RequestAudioFocus: %s",
                   response->reponse.message.c_str());
    }
  }

  void send_focus_release() {
    auto req = std::make_shared<AbandonAudioFocus::Request>();
    aimdk_msgs::msg::FocusRequester requester;
    requester.pkg_name = pkg_name_;
    req->focus_requester = requester;

    RCLCPP_INFO(this->get_logger(), "Sending AbandonAudioFocus request");
    std::shared_future<AbandonAudioFocus::Response::SharedPtr> future;
    for (int i = 0; i < 8; ++i) {
      future = release_client_->async_send_request(req).future.share();
      auto status = rclcpp::spin_until_future_complete(
          shared_from_this(), future, std::chrono::milliseconds(250));
      if (status == rclcpp::FutureReturnCode::SUCCESS)
        break;
      RCLCPP_INFO(this->get_logger(), "trying ... [%d]", i);
    }

    auto response = future.get();
    if (!response) {
      RCLCPP_ERROR(this->get_logger(), "Service call failed or timed out.");
      return;
    }
    if (response->reponse.status.value ==
        aimdk_msgs::msg::CommonState::SUCCESS) {
      // always focus False after abandon
      focus_ = response->focus_response.focus_gain;
      RCLCPP_INFO(this->get_logger(), "AbandonAudioFocus done: focus %s",
                  focus_ ? "true" : "false");
    } else {
      RCLCPP_ERROR(this->get_logger(),
                   "Failed in response of AbandonAudioFocus: %s",
                   response->reponse.message.c_str());
    }
  }

  void
  focus_event_callback(const aimdk_msgs::msg::FocusResponse::SharedPtr msg) {
    if (msg->pkg_name == pkg_name_) {
      RCLCPP_INFO(this->get_logger(),
                  "receive focus out event: focus state: %s",
                  msg->focus_gain ? "true" : "false");
      focus_force_ = msg->focus_gain;
    }
  }

  void run_once() {
    aimdk_msgs::msg::AudioPlayback msg;
    msg.pkg_name = pkg_name_;
    msg.token_id = pkg_name_;

    aimdk_msgs::msg::AudioInfo info;
    info.channels = static_cast<uint8_t>(mic_device_->get_channel_count());
    info.sample_rate = static_cast<uint32_t>(mic_device_->get_sample_rate());

    aimdk_msgs::msg::AudioData audio_data;
    audio_data.data = mic_device_->get_cached_data();

    msg.info = info;
    msg.data = audio_data;
    pub_->publish(msg);
  }

  std::string pkg_name_;
  bool focus_;
  bool focus_force_;
  std::unique_ptr<FakeMicDevice> mic_device_;
  rclcpp::Client<RequestAudioFocus>::SharedPtr request_client_;
  rclcpp::Client<AbandonAudioFocus>::SharedPtr release_client_;
  rclcpp::Subscription<aimdk_msgs::msg::FocusResponse>::SharedPtr sub_;
  rclcpp::Publisher<aimdk_msgs::msg::AudioPlayback>::SharedPtr pub_;
};

// ---------------------------------------------------------------------------
// Signal handling
// ---------------------------------------------------------------------------
static std::shared_ptr<AudioStreamPlayer> g_node;

void signal_handler(int sig) {
  if (g_node) {
    if (g_node->is_holding_focus()) {
      g_node->send_request(false);
    }
    RCLCPP_INFO(g_node->get_logger(),
                "Received signal %d, abandon audio focus and shutting down",
                sig);
  }
  rclcpp::shutdown();
}

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);

  try {
    auto node = std::make_shared<AudioStreamPlayer>();
    g_node = node;
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    node->spin_until_focus();
    node->run();

  } catch (const std::exception &e) {
    RCLCPP_ERROR(rclcpp::get_logger("main"),
                 "Program exited with exception: %s", e.what());
  }

  if (rclcpp::ok()) {
    rclcpp::shutdown();
  }
  return 0;
}
