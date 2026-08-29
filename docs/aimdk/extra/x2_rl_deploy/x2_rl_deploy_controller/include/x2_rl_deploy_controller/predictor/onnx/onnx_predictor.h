#pragma once

#include <onnxruntime_cxx_api.h>

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "x2_rl_deploy_controller/predictor/interface/i_predictor.h"

namespace rl::predictor {
class OnnxPredictor : public IPredictor
{
 public:
  OnnxPredictor()           = default;
  ~OnnxPredictor() override = default;

  bool            LoadModel(const std::string& model_path) override;
  Eigen::VectorXf Predict(Eigen::VectorXf& input) override;
  MotionOutputs   Predict(Eigen::VectorXf& input, float time_step, bool need_phase) override;
  void            ReleaseModel() override {}
  void            SetDevice(const std::string& device) override { device_ = device; }
  bool            HasOutput(const std::string& name) const override;

 private:
  std::string device_;

  std::unique_ptr<Ort::Session> policy_session_;
  std::vector<float>            actions_;
  std::vector<float>            observations_;
  std::shared_ptr<Ort::Env>     onnx_env_;

  std::vector<int64_t>            input_shape_;
  std::vector<int64_t>            output_shape_;
  std::string                     input_name_;
  std::string                     output_name_;
  std::unordered_set<std::string> output_name_set_;
};
}  // namespace rl::predictor
