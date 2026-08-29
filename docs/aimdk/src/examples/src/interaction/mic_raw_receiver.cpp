/**
 * Microphone raw data receiving example
 *
 * This example subscribes to the `/aima/hal/audio/capture` topic to receive
 * the robot's raw audio data. It supports both the built-in microphone and the
 * external microphone audio streams, and automatically saves complete audio
 * data as PCM files split by channel.
 *
 * Features:
 * - Automatically saves raw audio as PCM files
 * - Stores files categorized by timestamp and mic source
 */

#include <aimdk_msgs/msg/audio_capture.hpp>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <rclcpp/rclcpp.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

class RawAudioSubscriber : public rclcpp::Node {
public:
  RawAudioSubscriber() : rclcpp::Node("raw_audio_subscriber") {
    mic_channels_ = 0;
    ref_channels_ = 0;
    inited_ = false;

    // Create audio output directory named by current timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()) %
              1000;
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t_now), "%Y%m%d_%H%M%S_")
        << std::setw(3) << std::setfill('0') << ms.count();
    audio_output_dir_ = "audio_recordings/" + oss.str();
    fs::create_directories(audio_output_dir_);

    // Note: deep queue to avoid missing data
    auto qos = rclcpp::QoS(rclcpp::KeepLast(500)).best_effort();

    subscription_ = this->create_subscription<aimdk_msgs::msg::AudioCapture>(
        "/aima/hal/audio/capture", qos,
        std::bind(&RawAudioSubscriber::audio_callback, this,
                  std::placeholders::_1));

    RCLCPP_INFO(this->get_logger(), "Start subscribing to raw audio data...");
  }

  void run() {
    timer_ = this->create_wall_timer(
        std::chrono::seconds(1),
        std::bind(&RawAudioSubscriber::save_audio_segments, this));
    rclcpp::spin(shared_from_this());
  }

private:
  void audio_callback(const aimdk_msgs::msg::AudioCapture::SharedPtr msg) {
    if (!inited_) {
      mic_channels_ = msg->mic_channels;
      ref_channels_ = msg->ref_channels;
      inited_ = true;
    } else if (mic_channels_ != msg->mic_channels ||
               ref_channels_ != msg->ref_channels) {
      // quit as MIC switched
      RCLCPP_ERROR(
          this->get_logger(),
          "MIC channels info changed (mic:%u ref:%u) -> (mic:%u ref:%u)",
          mic_channels_, ref_channels_, msg->mic_channels, msg->ref_channels);
      rclcpp::shutdown();
      return;
    }

    handle_audio_data(msg->data.data);
  }

  void handle_audio_data(const std::vector<uint8_t> &audio_data) {
    // Split S16LE data into channels
    int channels =
        static_cast<int>(ref_channels_) + static_cast<int>(mic_channels_);
    if (channels == 0)
      return;

    const int bytes_per_channel = 2;
    const int unit_size = channels * bytes_per_channel;
    size_t num_frames = audio_data.size() / unit_size;

    for (size_t k = 0; k < num_frames; ++k) {
      for (int i = 0; i < channels; ++i) {
        size_t base = k * unit_size + i * bytes_per_channel;
        audio_buffers_[i].push_back(audio_data[base]);
        audio_buffers_[i].push_back(audio_data[base + 1]);
      }
    }
  }

  void save_audio_segments() {
    RCLCPP_INFO(this->get_logger(), "Flashing cached audio data...");
    int total =
        static_cast<int>(mic_channels_) + static_cast<int>(ref_channels_);
    for (int i = 0; i < total; ++i) {
      bool is_ref = (i >= static_cast<int>(mic_channels_));
      save_audio_segment(i, is_ref);
    }
  }

  void save_audio_segment(int channel, bool is_ref) {
    auto &buf = audio_buffers_[channel];
    if (buf.empty())
      return;

    std::string channel_type = is_ref ? "ref" : "mic";
    std::string filename =
        "channel_" + std::to_string(channel) + "_" + channel_type + ".pcm";
    fs::path filepath = fs::path(audio_output_dir_) / filename;

    try {
      // Append mode (equivalent to Python 'ab')
      std::ofstream ofs(filepath, std::ios::binary | std::ios::app);
      ofs.write(reinterpret_cast<const char *>(buf.data()), buf.size());
      ofs.close();

      RCLCPP_INFO(this->get_logger(),
                  "Audio segment saved: %s append: %zu bytes", filepath.c_str(),
                  buf.size());
      buf.clear();
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Failed to save audio file: %s",
                   e.what());
    }
  }

  bool inited_;
  uint8_t mic_channels_;
  uint8_t ref_channels_;
  std::string audio_output_dir_;
  std::unordered_map<int, std::vector<uint8_t>> audio_buffers_;
  rclcpp::Subscription<aimdk_msgs::msg::AudioCapture>::SharedPtr subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RawAudioSubscriber>();
  RCLCPP_INFO(node->get_logger(),
              "Listening to raw audio data, press Ctrl+C to exit...");
  node->run();
  rclcpp::shutdown();
  return 0;
}
