#pragma once

#include <Eigen/Eigen>
#include <string>

namespace rl::predictor {
struct MotionOutputs
{
  Eigen::VectorXf action;
  Eigen::VectorXf joint_pos;
  Eigen::VectorXf joint_vel;
  Eigen::MatrixXf body_pos_w;
  Eigen::MatrixXf body_quat_w;
  Eigen::MatrixXf body_lin_vel_w;
  Eigen::MatrixXf body_ang_vel_w;
  Eigen::VectorXf motion_phase;
  Eigen::VectorXf default_pos;
  Eigen::VectorXf action_scale;
  Eigen::VectorXf stiffness;
  Eigen::VectorXf damping;
};

class IPredictor
{
 public:
  virtual ~IPredictor() = default;

  virtual bool            LoadModel(const std::string& model_path)                                  = 0;
  virtual Eigen::VectorXf Predict(Eigen::VectorXf& input)                                           = 0;
  virtual MotionOutputs   Predict(Eigen::VectorXf& input, float time_step, bool need_phase = false) = 0;
  virtual void            ReleaseModel()                                                            = 0;
  virtual void            SetDevice(const std::string& device)                                      = 0;
  virtual bool            HasOutput(const std::string& name) const                                  = 0;
};
}  // namespace rl::predictor
