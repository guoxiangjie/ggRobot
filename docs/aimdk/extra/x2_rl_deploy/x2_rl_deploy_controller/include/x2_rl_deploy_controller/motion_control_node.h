#pragma once
#include <onnxruntime_cxx_api.h>

#include <Eigen/Dense>
#include <aimdk_msgs/msg/joint_command_array.hpp>
#include <aimdk_msgs/msg/joint_state_array.hpp>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/joy.hpp>

#include "x2_rl_deploy_controller/data_board.h"
#include "x2_rl_deploy_controller/predictor/interface/i_predictor.h"
#include "x2_rl_deploy_controller/robot_model.h"

enum class McAction
{
  PASSIVE_DEFAULT = 0,  // Sateft default action
  DAMPING_DEFAULT = 1,  // Safety exit action
  JOINT_DEFAULT   = 2,  // Prepare action
  RL_DEFAULT      = 3,  // Rl deployment action
};

extern std::atomic<bool> g_running;
extern std::atomic<bool> g_emergency_stop;

/**
 * @brief Represents the state of a joint.
 * @details The state of a joint includes the position, velocity, and effort.
 */
struct JointState
{
  std::string name;
  double      position{0.0}; /**< The position of the joint. Unit rad or m. */
  double      velocity{0.0}; /**< The velocity of the joint. Unit rad/s or m/s. */
  double      effort{0.0};   /**< The effort applied to the joint. Unit NM or N. */
};

/**
 * @brief Represents the command for a joint.
 * @details The command for a joint includes the desired position, velocity,
 * effort, stiffness, and damping.
 * @details MIT style, tau=Kp*(q_des-q)+Kv*(q_dot_des-q_dot)+tau_ff
 */
struct JointCommand
{
  std::string name;
  double      position{0.0};  /**< The desired position for the joint. Unit rad or m. */
  double      velocity{0.0};  /**< The desired velocity for the joint. Unit rad/s or m/s. */
  double      effort{0.0};    /**< The desired effort for the joint. Unit N·m or N. */
  double      stiffness{0.0}; /**< The stiffness of the joint. Unit N·m/rad or N/m */
  double      damping{0.0};   /**< The damping of the joint. Unit N·s/m or N·m·s/rad*/
};

struct DefaultParam
{
  std::string name;
  double      position = 0.0;
  double      kp       = 0.0;
  double      kd       = 0.0;
};

struct Option
{
  double default_kp{20.0};
  double default_kd{0.0};

  struct DefaultJoints
  {
    std::unordered_map<std::string, DefaultParam> joints{};
  } default_joints;

  struct RlConfig
  {
    struct Policy
    {
      std::string path{};
      std::string type{"onnx"};
      std::string device{"cpu"};
    } policy;

    struct VelocityScale
    {
      double x{0.5};
      double y{0.3};
      double yaw{0.5};
    } velocity_scale;
    struct
    {
      int frame_stack = 0;
    } infer;

    struct
    {
      float ang_vel       = 0.25;
      float dof_pos       = 1.0;
      float dof_vel       = 0.05;
      float actions       = 0.25;
      float lin_vel       = 1.0;
      float history_actor = 1.0;
    } obs_scales;
    struct
    {
      float obs_clip    = 100.0;
      float action_clip = 100.0;
    } clips;

    struct Phase
    {
      float start_count{0.0f};
      float end_count{0.0f};
    } phase;

    double action_scale{0.25};
    double dt{0.02};
    int    frame_stack{1};
    int    num_actions{12};
    int    num_obs{47};
    int    num_q{29};

    std::vector<std::string> seq;
    std::vector<std::string> action_seq;
    std::vector<double>      default_dof_pos;
    std::vector<double>      kps;
    std::vector<double>      kds;
  } rl_config;

  Eigen::VectorXf default_pos_;
  Eigen::VectorXf action_scale_;

  Eigen::VectorXf mimic_ref_pos_vec_;
  Eigen::VectorXf mimic_ref_vel_vec_;
  Eigen::VectorXf action_vec_;

  float start_count_ = 0;
  float heart_count_ = 0;
  bool  need_phase_  = false;
};

class MotionControlNode : public rclcpp::Node
{
 public:
  /**
   * @brief Constructor
   * @param node_name Node name
   * @param model_path Path of onnx model file
   * @param qos QoS configuration
   */
  MotionControlNode(const std::string &node_name, const std::string &config_path, rclcpp::QoS qos = rclcpp::SensorDataQoS());

  /**
   * @brief Destructor
   */
  ~MotionControlNode();

 public:
  /**
   * @brief Emergency stop all joints
   */
  void PassiveDefault();

  /**
   * @brief Safely stop all joints
   */
  void DampingDefault();

  /**
   * @brief Prepare pose to rl action
   */
  void JointDefault();

  /**
   * @brief Rl deploy action
   */
  void RlDefault(bool force_predict = false);

 private:
  /**
   * @brief Loads the ONNX model from file.
   * @param model_path Path to the .onnx file.
   * @return true if successful, false otherwise.
   */
  bool loadModel(const std::string &model_path);

  /**
   * @brief Loads configuration from YAML file.
   * @param config_path Path to the .yaml file.
   * @return true if successful, false otherwise.
   */
  bool loadConfig(const std::string &config_path);

  /**
   * @brief Main control loop running at high frequency(default: 500hz).
   */
  void controlLoop();

  /**
   * @brief Loop for publishing joint commands(default: 500hz).
   */
  void publishLoop();

  /**
   * @brief Publishes commands to ROS topics.
   * @param commands Map of joint commands to publish.
   */
  void publishCommands(const std::map<std::string, JointCommand> &commands);

  /**
   * @brief Applies roll and pitch offsets to a quaternion.
   *
   * @param q Original quaternion.
   * @param roll_offset Roll offset in radians.
   * @param pitch_offset Pitch offset in radians.
   * @return Eigen::Quaternionf Rotated quaternion.
   */
  Eigen::Quaternionf pitchOffsetQuaternion(const Eigen::Quaternionf &q, float roll_offset, float pitch_offset);

  /**
   * @brief Calculates the gravity vector in the body frame from the body orientation quaternion.
   *
   * @param w Quaternion w component.
   * @param x Quaternion x component.
   * @param y Quaternion y component.
   * @param z Quaternion z component.
   * @return Eigen::Vector3f Projected gravity vector [gx, gy, gz].
   */
  Eigen::Vector3f getGravityOrientation(float w, float x, float y, float z);

  /**
   * @brief Runs ONNX inference using obs_vec_ and updates action_vec_.
   */
  void predictActions();

  /**
   * @brief Callback for joint state updates.
   */
  void jointCallback(const aimdk_msgs::msg::JointStateArray::SharedPtr msg);

  /**
   * @brief Callback for joystick input.
   */
  void joyCallback(const sensor_msgs::msg::Joy::SharedPtr msg);

  /**
   * @brief Initializes joint name lists based on robot model.
   */
  void initJointNames();

  /**
   * @brief Helper to append joint names from robot model info.
   */
  void appendJoints(const std::vector<JointInfo> &joint_infos, std::vector<std::string> &joint_name);

  /**
   * @brief Creates a ROS message from internal command map.
   */
  aimdk_msgs::msg::JointCommandArray createCommand(const std::vector<std::string> &joint_names, const std::map<std::string, JointCommand> &commands);

 private:
  std::vector<JointInfo> joint_info_;
  std::thread            control_thread_;
  std::thread            publish_thread_;

  rclcpp::Subscription<aimdk_msgs::msg::JointStateArray>::SharedPtr arm_sub_;
  rclcpp::Subscription<aimdk_msgs::msg::JointStateArray>::SharedPtr leg_sub_;
  rclcpp::Subscription<aimdk_msgs::msg::JointStateArray>::SharedPtr head_sub_;
  rclcpp::Subscription<aimdk_msgs::msg::JointStateArray>::SharedPtr waist_sub_;

  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr chest_imu_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr torso_imu_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;

  rclcpp::Publisher<aimdk_msgs::msg::JointCommandArray>::SharedPtr arm_pub_;
  rclcpp::Publisher<aimdk_msgs::msg::JointCommandArray>::SharedPtr leg_pub_;
  rclcpp::Publisher<aimdk_msgs::msg::JointCommandArray>::SharedPtr head_pub_;
  rclcpp::Publisher<aimdk_msgs::msg::JointCommandArray>::SharedPtr waist_pub_;

 private:
  std::shared_ptr<Option> cfg_;
  struct StateDB
  {
    std::map<std::string, JointState> joints;
    sensor_msgs::msg::Imu             imu_torso;
    sensor_msgs::msg::Imu             imu_chest;
  };

  DataBoard<StateDB>                             state_db_;
  DataBoard<std::map<std::string, JointCommand>> command_db_;

  std::vector<std::string> leg_joint_names_;
  std::vector<std::string> arm_joint_names_;
  std::vector<std::string> head_joint_names_;
  std::vector<std::string> waist_joint_names_;
  std::vector<std::string> all_joint_names_;

  McAction curr_action_{McAction::PASSIVE_DEFAULT};

  double                                  total_cycles_{0.0};
  double                                  curr_cycles_{0.0};
  bool                                    is_interp_{false};
  std::unordered_map<std::string, double> interp_pos_;
  int                                     warmup_frames_{0};
  std::chrono::steady_clock::time_point   last_predict_time_{};

 private:
  struct Phase
  {
    float start_count{0.0f};
    float end_count{0.0f};
  };

  Phase phase_;

  std::shared_ptr<Ort::Env>     env_;
  std::shared_ptr<Ort::Session> session_;
  std::vector<std::string>      input_names_;
  std::vector<std::string>      output_names_;
  std::vector<int64_t>          input_shape_;
  std::vector<int64_t>          output_shape_;

  std::unique_ptr<rl::predictor::IPredictor> predictor_;

  double          phase_time_{0.0};
  Eigen::VectorXf obs_vec_;
  Eigen::VectorXf action_vec_;

  Eigen::VectorXf mimic_obs_vec_;
  Eigen::VectorXf mimic_ref_pos_vec_;
  Eigen::VectorXf mimic_ref_vel_vec_;
  Eigen::VectorXf mimic_ref_anchor_quat_w_;

  Eigen::VectorXf  action_scale_;
  Eigen::VectorXf  default_pos_;
  Eigen::VectorXf  target_joint_pos_;
  std::vector<int> action2q_mapping_index_;

  float heart_count_{0.0f};
  bool  need_phase_{false};
};
