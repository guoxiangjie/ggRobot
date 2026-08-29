#include "x2_rl_deploy_controller/motion_control_node.h"

#include <yaml-cpp/yaml.h>

#include <algorithm>
#include <chrono>
#include <limits>
#include <string>

#include "x2_rl_deploy_controller/predictor/factory/predictor_factory.h"

static constexpr std::chrono::milliseconds kControlPeriod        = std::chrono::milliseconds(2);
static constexpr double                    kJointDefaultDuration = 1.5;

MotionControlNode::MotionControlNode(const std::string &node_name, const std::string &config_path, rclcpp::QoS qos)
    : Node(node_name), cfg_(std::make_shared<Option>())
{
  initJointNames();

  if (!loadConfig(config_path)) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load RL config from: %s", config_path.c_str());
    throw std::runtime_error("Load rl model failed.");
  }

  if (cfg_->rl_config.phase.end_count > 0.1f) {
    phase_.start_count = cfg_->rl_config.phase.start_count;
    phase_.end_count   = cfg_->rl_config.phase.end_count;
    need_phase_        = false;
  } else {
    need_phase_ = true;
  }

  const int num_actions = cfg_->rl_config.num_actions;
  const int num_q       = cfg_->rl_config.num_q;

  mimic_ref_pos_vec_       = Eigen::VectorXf::Zero(num_q);
  mimic_ref_vel_vec_       = Eigen::VectorXf::Zero(num_q);
  mimic_ref_anchor_quat_w_ = Eigen::VectorXf::Zero(4);
  mimic_obs_vec_           = Eigen::VectorXf::Zero(cfg_->rl_config.num_obs);
  action_vec_              = Eigen::VectorXf::Zero(num_actions);
  target_joint_pos_        = Eigen::VectorXf::Zero(num_actions);
  action_scale_            = Eigen::VectorXf::Ones(num_actions);
  default_pos_             = Eigen::VectorXf::Zero(num_q);

  if (static_cast<int>(cfg_->rl_config.default_dof_pos.size()) >= num_q) {
    for (int i = 0; i < num_q; ++i) {
      default_pos_(i) = static_cast<float>(cfg_->rl_config.default_dof_pos[i]);
    }
  }

  const auto &obs_seq = cfg_->rl_config.seq;
  const auto &act_seq = cfg_->rl_config.action_seq.empty() ? cfg_->rl_config.seq : cfg_->rl_config.action_seq;
  if (act_seq.size() != static_cast<size_t>(num_actions)) {
    RCLCPP_WARN(this->get_logger(), "action_seq size (%zu) != num_actions (%d), using min size for mapping", act_seq.size(), num_actions);
  }

  std::unordered_map<std::string, int> q_index;
  q_index.reserve(obs_seq.size());
  for (size_t i = 0; i < obs_seq.size(); ++i) {
    q_index[obs_seq[i]] = static_cast<int>(i);
  }

  action2q_mapping_index_.assign(num_actions, 0);
  const int mapping_size = std::min<int>(num_actions, static_cast<int>(act_seq.size()));
  for (int i = 0; i < mapping_size; ++i) {
    const auto &name = act_seq[i];
    auto        it   = q_index.find(name);
    if (it != q_index.end()) {
      action2q_mapping_index_[i] = it->second;
    } else {
      RCLCPP_WARN(this->get_logger(), "action_seq joint not in seq: %s", name.c_str());
    }
  }
  heart_count_ = phase_.start_count - 1.0f;

  std::string policy_path = cfg_->rl_config.policy.path;
  if (!policy_path.empty()) {
    if (!loadModel(policy_path)) {
      RCLCPP_ERROR(this->get_logger(), "Failed to load rl policy from: %s", policy_path.c_str());
      throw std::runtime_error("Load rl policy failed.");
    }
  } else {
    RCLCPP_ERROR(this->get_logger(), "No policy path in config.");
  }

  arm_sub_   = create_subscription<aimdk_msgs::msg::JointStateArray>("/aima/hal/joint/arm/state", qos,
                                                                   std::bind(&MotionControlNode::jointCallback, this, std::placeholders::_1));
  leg_sub_   = create_subscription<aimdk_msgs::msg::JointStateArray>("/aima/hal/joint/leg/state", qos,
                                                                   std::bind(&MotionControlNode::jointCallback, this, std::placeholders::_1));
  head_sub_  = create_subscription<aimdk_msgs::msg::JointStateArray>("/aima/hal/joint/head/state", qos,
                                                                    std::bind(&MotionControlNode::jointCallback, this, std::placeholders::_1));
  waist_sub_ = create_subscription<aimdk_msgs::msg::JointStateArray>("/aima/hal/joint/waist/state", qos,
                                                                     std::bind(&MotionControlNode::jointCallback, this, std::placeholders::_1));

  chest_imu_sub_ = create_subscription<sensor_msgs::msg::Imu>("/aima/hal/imu/chest/state", qos, [this](const sensor_msgs::msg::Imu::SharedPtr msg) {
    StateDB state;
    state_db_.GetData(state);
    state.imu_chest = *msg;
    state_db_.SetData(state);
  });
  torso_imu_sub_ = create_subscription<sensor_msgs::msg::Imu>("/aima/hal/imu/torso/state", qos, [this](const sensor_msgs::msg::Imu::SharedPtr msg) {
    StateDB state;
    state_db_.GetData(state);
    state.imu_torso = *msg;
    state_db_.SetData(state);
  });

  joy_sub_ = create_subscription<sensor_msgs::msg::Joy>("/joy", qos, std::bind(&MotionControlNode::joyCallback, this, std::placeholders::_1));

  arm_pub_   = create_publisher<aimdk_msgs::msg::JointCommandArray>("/aima/hal/joint/arm/command", qos);
  leg_pub_   = create_publisher<aimdk_msgs::msg::JointCommandArray>("/aima/hal/joint/leg/command", qos);
  head_pub_  = create_publisher<aimdk_msgs::msg::JointCommandArray>("/aima/hal/joint/head/command", qos);
  waist_pub_ = create_publisher<aimdk_msgs::msg::JointCommandArray>("/aima/hal/joint/waist/command", qos);

  control_thread_ = std::thread(&MotionControlNode::controlLoop, this);
  publish_thread_ = std::thread(&MotionControlNode::publishLoop, this);
}

MotionControlNode::~MotionControlNode()
{
  g_running = false;
  if (control_thread_.joinable()) control_thread_.join();
  if (publish_thread_.joinable()) publish_thread_.join();
}

void MotionControlNode::PassiveDefault()
{
  std::map<std::string, JointCommand> commands;

  for (const auto &name : all_joint_names_) {
    JointCommand command;
    command.name      = name;
    command.position  = 0.0;
    command.velocity  = 0.0;
    command.effort    = 0.0;
    command.stiffness = 0.0;
    command.damping   = 0.0;

    commands[name] = command;
  }

  command_db_.SetData(commands);
}

void MotionControlNode::DampingDefault()
{
  std::map<std::string, JointCommand> commands;

  for (const auto &name : all_joint_names_) {
    JointCommand command;
    command.name      = name;
    command.position  = 0.0;
    command.velocity  = 0.0;
    command.effort    = 0.0;
    command.stiffness = 0.0;
    command.damping   = 5.0;

    commands[name] = command;
  }

  command_db_.SetData(commands);
}

void MotionControlNode::JointDefault()
{
  if (!is_interp_) {
    StateDB state;
    if (!state_db_.GetData(state)) return;

    interp_pos_.clear();
    for (const auto &[name, joint_state] : state.joints) interp_pos_[name] = joint_state.position;

    curr_cycles_ = 0.0;
    is_interp_   = true;
    RCLCPP_INFO(this->get_logger(), "[JOINT_DEFAULT] Start Interpolation.");
  }

  total_cycles_ = kJointDefaultDuration / std::chrono::duration<double>(kControlPeriod).count();
  if (curr_cycles_ < total_cycles_) {
    ++curr_cycles_;
  }

  double progress = curr_cycles_ / total_cycles_;

  std::map<std::string, JointCommand> commands;

  for (const auto &name : all_joint_names_) {
    double start_pos = 0.0;
    if (interp_pos_.count(name)) start_pos = interp_pos_.at(name);

    double target_pos = 0.0;
    double kp         = cfg_->default_kp;
    double kd         = cfg_->default_kd;

    if (cfg_->default_joints.joints.count(name)) {
      const auto &param = cfg_->default_joints.joints.at(name);
      target_pos        = param.position;
      kp                = param.kp;
      kd                = param.kd;
    }

    double       curr_pos = start_pos + (target_pos - start_pos) * progress;
    JointCommand command;
    command.name      = name;
    command.position  = curr_pos;
    command.velocity  = 0.0;
    command.effort    = 0.0;
    command.stiffness = kp;
    command.damping   = kd;

    commands[name] = command;
  }

  command_db_.SetData(commands);
}

Eigen::Quaternionf MotionControlNode::pitchOffsetQuaternion(const Eigen::Quaternionf &q, float roll_offset, float pitch_offset)
{
  double             half_angle_roll = roll_offset * 0.5f;
  Eigen::Quaternionf q_roll(std::cos(half_angle_roll), std::sin(half_angle_roll), 0.0f, 0.0f);

  double             half_angle_pitch = pitch_offset / 2.0;
  Eigen::Quaternionf q_pitch(std::cos(half_angle_pitch), 0.0, std::sin(half_angle_pitch), 0.0);

  Eigen::Quaternionf q_offset = q_roll * q_pitch;
  Eigen::Quaternionf q_new    = q * q_offset;

  q_new.normalize();
  return q_new;
}

Eigen::Vector3f MotionControlNode::getGravityOrientation(float w, float x, float y, float z)
{
  Eigen::Vector3f gravity_orientation;
  float           qw     = w;
  float           qx     = x;
  float           qy     = y;
  float           qz     = z;
  gravity_orientation(0) = 2 * (-qz * qx + qw * qy);
  gravity_orientation(1) = -2 * (qz * qy + qw * qx);
  gravity_orientation(2) = 1 - 2 * (qw * qw + qz * qz);
  return gravity_orientation;
}

void MotionControlNode::RlDefault(bool force_predict)
{
  static uint64_t debug_counter = 0;
  // Get state
  StateDB state;
  if (!state_db_.GetData(state)) return;

  if (obs_vec_.size() != cfg_->rl_config.num_obs) {
    obs_vec_.resize(cfg_->rl_config.num_obs);
    obs_vec_.setZero();
    action_vec_.resize(cfg_->rl_config.num_actions);
    action_vec_.setZero();

    // Resize the input shape to match the resized obs_vec_
    if (!input_shape_.empty()) {
      input_shape_[1] = cfg_->rl_config.num_obs;
    } else {
      input_shape_ = {1, (int64_t)cfg_->rl_config.num_obs};
    }
  }

  // Construct observation vector
  std::map<std::string, Eigen::VectorXf> obs_map;

  Eigen::VectorXf dof_pos_vec = Eigen::VectorXf::Zero(cfg_->rl_config.num_q);
  Eigen::VectorXf dof_vel_vec = Eigen::VectorXf::Zero(cfg_->rl_config.num_q);
  Eigen::VectorXf ang_vel_vec = Eigen::VectorXf::Zero(3);
  Eigen::VectorXf action_vec  = Eigen::VectorXf::Zero(cfg_->rl_config.num_actions);

  for (size_t i = 0; i < cfg_->rl_config.seq.size(); i++) {
    int         idx  = static_cast<int>(i);
    std::string name = cfg_->rl_config.seq[i];
    double      pos  = 0.0;
    double      vel  = 0.0;
    if (state.joints.count(name)) {
      pos = state.joints[name].position;
      vel = state.joints[name].velocity;
    }
    double default_pos = (idx < (int)cfg_->rl_config.default_dof_pos.size()) ? cfg_->rl_config.default_dof_pos[idx] : 0.0;
    dof_pos_vec(idx)   = (pos - default_pos) * cfg_->rl_config.obs_scales.dof_pos;
    dof_vel_vec(idx)   = vel * cfg_->rl_config.obs_scales.dof_vel;
  }

  for (int i = 0; i < cfg_->rl_config.num_actions; i++) {
    action_vec(i) = action_vec_(i);
  }

  auto torso_imu = state.imu_torso;
  auto imu_omega = torso_imu.angular_velocity;
  ang_vel_vec(0) = static_cast<float>(imu_omega.x) * cfg_->rl_config.obs_scales.ang_vel;
  ang_vel_vec(1) = static_cast<float>(imu_omega.y) * cfg_->rl_config.obs_scales.ang_vel;
  ang_vel_vec(2) = static_cast<float>(imu_omega.z) * cfg_->rl_config.obs_scales.ang_vel;

  auto               imu_quat = torso_imu.orientation;
  Eigen::Quaternionf imu_quat_f(imu_quat.w, imu_quat.x, imu_quat.y, imu_quat.z);
  imu_quat_f                      = pitchOffsetQuaternion(imu_quat_f, 0.0f, 0.0f);
  Eigen::Vector3f gravity_project = getGravityOrientation(imu_quat_f.w(), imu_quat_f.x(), imu_quat_f.y(), imu_quat_f.z());

  Eigen::VectorXf motion_anchor_ori_b = Eigen::VectorXf::Zero(6);

  obs_map["command"]             = Eigen::VectorXf::Zero(cfg_->rl_config.num_q * 2);
  obs_map["command_dof_pos"]     = mimic_ref_pos_vec_;
  obs_map["command_dof_vel"]     = mimic_ref_vel_vec_;
  obs_map["dof_pos"]             = dof_pos_vec;
  obs_map["dof_vel"]             = dof_vel_vec;
  obs_map["base_ang_vel"]        = ang_vel_vec;
  obs_map["motion_anchor_ori_b"] = motion_anchor_ori_b;
  obs_map["projected_gravity"]   = gravity_project;
  obs_map["actions"]             = action_vec;

  std::vector<std::string> actor_obs_str = {"command_dof_pos", "command_dof_vel", "projected_gravity", "base_ang_vel", "dof_pos",
                                            "dof_vel",         "actions"};
  int                      offset        = 0;
  for (const auto &factor : actor_obs_str) {
    int element_size = obs_map[factor].size();
    if (offset + element_size > mimic_obs_vec_.size()) {
      RCLCPP_ERROR(this->get_logger(), "Observation size mismatch for %s", factor.c_str());
      break;
    }
    mimic_obs_vec_.segment(offset, element_size) = obs_map[factor];
    offset += element_size;
  }

  for (int i = 0; i < mimic_obs_vec_.size(); i++) {
    mimic_obs_vec_(i) = std::clamp(mimic_obs_vec_(i), -cfg_->rl_config.clips.obs_clip, cfg_->rl_config.clips.obs_clip);
  }
  if (++debug_counter % 500 == 0) {
    const float obs_min = mimic_obs_vec_.size() ? mimic_obs_vec_.minCoeff() : 0.0f;
    const float obs_max = mimic_obs_vec_.size() ? mimic_obs_vec_.maxCoeff() : 0.0f;
    RCLCPP_INFO(this->get_logger(), "[mimic] obs size=%ld min=%.3f max=%.3f ang_vel=(%.3f,%.3f,%.3f) gravity=(%.3f,%.3f,%.3f)",
                static_cast<long>(mimic_obs_vec_.size()), obs_min, obs_max, ang_vel_vec(0), ang_vel_vec(1), ang_vel_vec(2), gravity_project(0),
                gravity_project(1), gravity_project(2));
  }
  // Model predict
  auto now        = std::chrono::steady_clock::now();
  bool do_predict = force_predict;
  if (!do_predict) {
    if (last_predict_time_.time_since_epoch().count() == 0) {
      do_predict = true;
    } else {
      const auto period = std::chrono::duration<double>(cfg_->rl_config.dt);
      do_predict        = (now - last_predict_time_) >= period;
    }
  }
  if (do_predict) {
    predictActions();
    last_predict_time_ = now;
  }

  // Write actions
  const auto                         &act_seq = cfg_->rl_config.action_seq.empty() ? cfg_->rl_config.seq : cfg_->rl_config.action_seq;
  std::map<std::string, JointCommand> commands;
  for (size_t i = 0; i < act_seq.size(); ++i) {
    if (i >= (size_t)action_vec_.size()) break;
    std::string name = act_seq[i];

    int    q_index     = (i < action2q_mapping_index_.size()) ? action2q_mapping_index_[i] : -1;
    double default_pos = (q_index >= 0 && q_index < (int)cfg_->rl_config.default_dof_pos.size()) ? cfg_->rl_config.default_dof_pos[q_index] : 0.0;
    double kp          = (q_index >= 0 && q_index < (int)cfg_->rl_config.kps.size()) ? cfg_->rl_config.kps[q_index] : cfg_->default_kp;
    double kd          = (q_index >= 0 && q_index < (int)cfg_->rl_config.kds.size()) ? cfg_->rl_config.kds[q_index] : cfg_->default_kd;

    // This implements residual control: the policy outputs a deviation (action) from a nominal pose.
    // target_pos = action * scale + default_pos
    double target_pos = action_vec_(i) * cfg_->rl_config.action_scale + default_pos;

    JointCommand cmd;
    cmd.name      = name;
    cmd.position  = target_pos;
    cmd.velocity  = 0.0;
    cmd.effort    = 0.0;
    cmd.stiffness = kp;
    cmd.damping   = kd;

    commands[name] = cmd;
  }
  if (debug_counter % 500 == 0 && !act_seq.empty()) {
    const size_t idx0 = 0;
    const size_t idx1 = std::min<size_t>(1, act_seq.size() - 1);
    const size_t idx2 = std::min<size_t>(2, act_seq.size() - 1);
    RCLCPP_INFO(this->get_logger(), "[mimic] act[0..2]=%.3f,%.3f,%.3f target_pos[0..2]=%.3f,%.3f,%.3f", action_vec_(idx0), action_vec_(idx1),
                action_vec_(idx2), commands[act_seq[idx0]].position, commands[act_seq[idx1]].position, commands[act_seq[idx2]].position);
  }

  command_db_.SetData(commands);
}

bool MotionControlNode::loadModel(const std::string &model_path)
{
  predictor_ = rl::predictor::PredictorFactory::CreatePredictor(cfg_->rl_config.policy.type);
  if (!predictor_) {
    RCLCPP_ERROR(this->get_logger(), "Unsupported predictor type: %s", cfg_->rl_config.policy.type.c_str());
    return false;
  }

  predictor_->SetDevice(cfg_->rl_config.policy.device);
  if (!predictor_->LoadModel(model_path)) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load predictor model: %s", model_path.c_str());
    return false;
  }

  return true;
}

bool MotionControlNode::loadConfig(const std::string &config_path)
{
  try {
    YAML::Node config = YAML::LoadFile(config_path);

    if (config["default_kp"]) cfg_->default_kp = config["default_kp"].as<float>();
    if (config["default_kd"]) cfg_->default_kd = config["default_kd"].as<float>();

    if (config["default_joints"] && config["default_joints"]["joints"]) {
      const auto &joints_node = config["default_joints"]["joints"];

      for (const auto &joint_node : joints_node) {
        DefaultParam param;
        param.name     = joint_node["name"].as<std::string>();
        param.position = joint_node["position"].as<float>();
        param.kp       = joint_node["kp"].as<float>();
        param.kd       = joint_node["kd"].as<float>();

        cfg_->default_joints.joints[param.name] = param;
      }
    }

    if (config["phase"]) {
      if (config["phase"]["start_count"]) cfg_->rl_config.phase.start_count = config["phase"]["start_count"].as<float>();
      if (config["phase"]["end_count"]) cfg_->rl_config.phase.end_count = config["phase"]["end_count"].as<float>();
    }

    // Get rl config here
    if (config["rl_config"]) {
      const auto &rl_node = config["rl_config"];

      if (rl_node["policy"]) {
        cfg_->rl_config.policy.path   = rl_node["policy"]["path"].as<std::string>();
        cfg_->rl_config.policy.type   = rl_node["policy"]["type"].as<std::string>();
        cfg_->rl_config.policy.device = rl_node["policy"]["device"].as<std::string>();
      }

      if (rl_node["velocity_scale"]) {
        cfg_->rl_config.velocity_scale.x   = rl_node["velocity_scale"]["x"].as<double>();
        cfg_->rl_config.velocity_scale.y   = rl_node["velocity_scale"]["y"].as<double>();
        cfg_->rl_config.velocity_scale.yaw = rl_node["velocity_scale"]["yaw"].as<double>();
      }

      if (rl_node["seq"]) {
        for (const auto &item : rl_node["seq"]) {
          cfg_->rl_config.seq.push_back(item.as<std::string>());
        }
      }
      if (rl_node["action_seq"]) {
        for (const auto &item : rl_node["action_seq"]) {
          cfg_->rl_config.action_seq.push_back(item.as<std::string>());
        }
      }
      if (rl_node["default_dof_pos"]) {
        cfg_->rl_config.default_dof_pos.clear();
        for (const auto &item : rl_node["default_dof_pos"]) cfg_->rl_config.default_dof_pos.push_back(item.as<double>());
      }
      if (rl_node["kps"]) {
        cfg_->rl_config.kps.clear();
        for (const auto &item : rl_node["kps"]) cfg_->rl_config.kps.push_back(item.as<double>());
      }
      if (rl_node["kds"]) {
        cfg_->rl_config.kds.clear();
        for (const auto &item : rl_node["kds"]) cfg_->rl_config.kds.push_back(item.as<double>());
      }

      if (rl_node["action_scale"]) cfg_->rl_config.action_scale = rl_node["action_scale"].as<double>();
      if (rl_node["dt"]) cfg_->rl_config.dt = rl_node["dt"].as<double>();
      if (rl_node["frame_stack"]) cfg_->rl_config.frame_stack = rl_node["frame_stack"].as<int>();
      if (rl_node["infer"] && rl_node["infer"]["frame_stack"]) cfg_->rl_config.frame_stack = rl_node["infer"]["frame_stack"].as<int>();
      if (rl_node["num_actions"]) cfg_->rl_config.num_actions = rl_node["num_actions"].as<double>();
      if (rl_node["num_obs"]) cfg_->rl_config.num_obs = rl_node["num_obs"].as<double>();
    }

    return true;
  } catch (const YAML::Exception &e) {
    RCLCPP_ERROR(this->get_logger(), "Load yaml error: %s", e.what());
    return false;
  }
}

void MotionControlNode::controlLoop()
{
  auto     next_period = std::chrono::steady_clock::now() + kControlPeriod;
  McAction last_action = curr_action_;

  while (g_running && rclcpp::ok()) {
    if (g_emergency_stop) {
      curr_action_ = McAction::DAMPING_DEFAULT;
    }

    // In case of switching same action
    if (curr_action_ != last_action) {
      if (curr_action_ == McAction::JOINT_DEFAULT) is_interp_ = false;
      if (curr_action_ == McAction::RL_DEFAULT) {
        heart_count_       = phase_.start_count - 1.0f;
        need_phase_        = (phase_.end_count <= 0.1f);
        warmup_frames_     = std::max(1, cfg_->rl_config.frame_stack);
        last_predict_time_ = std::chrono::steady_clock::time_point{};
        for (int i = 0; i < warmup_frames_; ++i) {
          RlDefault(true);
        }
      }

      last_action = curr_action_;
    }

    switch (curr_action_) {
      case McAction::PASSIVE_DEFAULT:
        PassiveDefault();
        break;
      case McAction::DAMPING_DEFAULT:
        DampingDefault();
        break;
      case McAction::JOINT_DEFAULT:
        JointDefault();
        break;
      case McAction::RL_DEFAULT:
        RlDefault();
        break;
      default:
        PassiveDefault();
        break;
    }

    std::this_thread::sleep_until(next_period);
    next_period += kControlPeriod;
  }
}

void MotionControlNode::publishLoop()
{
  auto next_pub_period = std::chrono::steady_clock::now() + kControlPeriod;
  while (g_running && rclcpp::ok()) {
    std::map<std::string, JointCommand> cmds;
    if (command_db_.GetData(cmds)) {
      publishCommands(cmds);
    }

    std::this_thread::sleep_until(next_pub_period);
    next_pub_period += kControlPeriod;
  }
}

void MotionControlNode::publishCommands(const std::map<std::string, JointCommand> &commands)
{
  if (!arm_joint_names_.empty()) {
    arm_pub_->publish(createCommand(arm_joint_names_, commands));
  }
  if (!leg_joint_names_.empty()) {
    leg_pub_->publish(createCommand(leg_joint_names_, commands));
  }
  if (!head_joint_names_.empty()) {
    head_pub_->publish(createCommand(head_joint_names_, commands));
  }
  if (!waist_joint_names_.empty()) {
    waist_pub_->publish(createCommand(waist_joint_names_, commands));
  }
}

void MotionControlNode::predictActions()
{
  heart_count_++;
  if (heart_count_ >= phase_.end_count) heart_count_ = phase_.end_count;
  RCLCPP_INFO(this->get_logger(), "heart_count=%.3f", heart_count_);
  static uint64_t debug_counter = 0;
  if (!predictor_) {
    if (++debug_counter % 500 == 0) {
      RCLCPP_WARN(this->get_logger(), "[mimic] predictor not ready");
    }
    return;
  }

  try {
    bool request_phase = need_phase_;
    if (request_phase && !predictor_->HasOutput("motion_phase")) {
      RCLCPP_WARN(this->get_logger(), "[mimic] model has no motion_phase output, disable phase request");
      request_phase = false;
      need_phase_   = false;
      if (phase_.end_count <= 0.1f) {
        phase_.end_count = std::numeric_limits<float>::max();
      }
    }
    auto predictor_tensor    = predictor_->Predict(mimic_obs_vec_, heart_count_, request_phase);
    auto output_tensor       = predictor_tensor.action;
    mimic_ref_pos_vec_       = predictor_tensor.joint_pos;
    mimic_ref_vel_vec_       = predictor_tensor.joint_vel;
    mimic_ref_anchor_quat_w_ = predictor_tensor.body_quat_w.col(0).transpose();

    if (request_phase) {
      phase_.start_count = predictor_tensor.motion_phase(0);
      phase_.end_count   = predictor_tensor.motion_phase(1);
      action_scale_      = predictor_tensor.action_scale;
      default_pos_       = predictor_tensor.default_pos;
      heart_count_       = phase_.start_count - 1;
      need_phase_        = false;
    }

    auto action_value = action_vec_;

    for (int i = 0; i < cfg_->rl_config.num_actions; i++) {
      float action_scale   = action_scale_(i);
      action_vec_(i)       = std::clamp(output_tensor(i), -cfg_->rl_config.clips.action_clip, cfg_->rl_config.clips.action_clip);
      auto default_index   = action2q_mapping_index_[i];
      target_joint_pos_(i) = action_vec_(i) * action_scale + default_pos_(default_index);
    }
    if (++debug_counter % 500 == 0) {
      const float out_min = output_tensor.size() ? output_tensor.minCoeff() : 0.0f;
      const float out_max = output_tensor.size() ? output_tensor.maxCoeff() : 0.0f;
      RCLCPP_INFO(this->get_logger(), "[mimic] output size=%ld min=%.3f max=%.3f need_phase=%d ", static_cast<long>(output_tensor.size()), out_min,
                  out_max, request_phase ? 1 : 0);
    }
  } catch (const std::exception &e) {
    RCLCPP_ERROR(this->get_logger(), "Predictor inference error: %s", e.what());
  }
}

void MotionControlNode::jointCallback(const aimdk_msgs::msg::JointStateArray::SharedPtr msg)
{
  StateDB state;
  state_db_.GetData(state);
  for (const auto &joint : msg->joints) {
    state.joints[joint.name] = JointState{
        joint.name,
        joint.position,
        joint.velocity,
        joint.effort,
    };
  }

  state_db_.SetData(state);
}

void MotionControlNode::joyCallback(const sensor_msgs::msg::Joy::SharedPtr msg)
{
  // buttons[0]: ❌
  // buttons[1]: ⭕️
  // buttons[2]: 🔺
  // buttons[3]: 🟥

  if (msg->buttons[0] == 1) {
    RCLCPP_INFO(this->get_logger(), "Switch to PASSIVE_DEFAULT");
    curr_action_ = McAction::PASSIVE_DEFAULT;
  } else if (msg->buttons[1] == 1) {
    RCLCPP_INFO(this->get_logger(), "Switch to DAMPING_DEFAULT");
    curr_action_ = McAction::DAMPING_DEFAULT;
  } else if (msg->buttons[2] == 1) {
    RCLCPP_INFO(this->get_logger(), "Switch to JOINT_DEFAULT");
    curr_action_ = McAction::JOINT_DEFAULT;
  } else if (msg->buttons[3] == 1) {
    RCLCPP_INFO(this->get_logger(), "Switch to RL_DEFAULT");
    curr_action_ = McAction::RL_DEFAULT;
  }
}

void MotionControlNode::initJointNames()
{
  if (robot_model.count(JointArea::ARM)) appendJoints(robot_model[JointArea::ARM], arm_joint_names_);
  if (robot_model.count(JointArea::LEG)) appendJoints(robot_model[JointArea::LEG], leg_joint_names_);
  if (robot_model.count(JointArea::HEAD)) appendJoints(robot_model[JointArea::HEAD], head_joint_names_);
  if (robot_model.count(JointArea::WAIST)) appendJoints(robot_model[JointArea::WAIST], waist_joint_names_);
}

void MotionControlNode::appendJoints(const std::vector<JointInfo> &joint_infos, std::vector<std::string> &joint_name)
{
  for (const auto &joint_info : joint_infos) {
    joint_name.push_back(joint_info.name);
    all_joint_names_.push_back(joint_info.name);
  }
}

aimdk_msgs::msg::JointCommandArray MotionControlNode::createCommand(const std::vector<std::string>            &joint_names,
                                                                    const std::map<std::string, JointCommand> &commands)
{
  aimdk_msgs::msg::JointCommandArray msg;

  for (const auto &joint_name : joint_names) {
    if (!commands.count(joint_name)) continue;
    const auto                   &command = commands.at(joint_name);
    aimdk_msgs::msg::JointCommand ros_command;
    ros_command.name      = command.name;
    ros_command.position  = command.position;
    ros_command.velocity  = command.velocity;
    ros_command.effort    = command.effort;
    ros_command.damping   = command.damping;
    ros_command.stiffness = command.stiffness;

    msg.joints.push_back(ros_command);
  }
  return msg;
}
