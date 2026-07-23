#include "x2_rl_deploy_controller/predictor/onnx/onnx_predictor.h"

#include <array>
#include <chrono>
#include <iostream>

namespace rl::predictor {
bool OnnxPredictor::LoadModel(const std::string& path)
{
  try {
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    onnx_env_       = std::make_shared<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "MotionControlNode");
    policy_session_ = std::make_unique<Ort::Session>(*onnx_env_, path.c_str(), session_options);

    input_shape_.clear();
    output_shape_.clear();
    Ort::AllocatorWithDefaultOptions allocator;

    size_t                   num_inputs = policy_session_->GetInputCount();
    std::vector<std::string> input_names;
    for (size_t i = 0; i < num_inputs; i++) {
      auto name_alloc = policy_session_->GetInputNameAllocated(i, allocator);
      input_names.push_back(name_alloc.get());
    }
    input_name_  = input_names[0];
    input_shape_ = policy_session_->GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();

    size_t                   num_outputs = policy_session_->GetOutputCount();
    std::vector<std::string> output_names;
    output_name_set_.clear();
    for (size_t i = 0; i < num_outputs; i++) {
      auto name_alloc = policy_session_->GetOutputNameAllocated(i, allocator);
      output_names.push_back(name_alloc.get());
      output_name_set_.insert(output_names.back());
    }
    output_name_  = output_names[0];
    output_shape_ = policy_session_->GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();

    std::cout << "Inputs (" << num_inputs << "):" << std::endl;
    for (const auto& n : input_names) {
      std::cout << "  " << n << std::endl;
    }

    std::cout << "Outputs (" << num_outputs << "):" << std::endl;
    for (const auto& n : output_names) {
      std::cout << "  " << n << std::endl;
    }

    return true;
  } catch (const Ort::Exception& e) {
    std::cerr << "ONNX Error: " << e.what() << std::endl;
    return false;
  }
}

bool OnnxPredictor::HasOutput(const std::string& name) const
{
  return output_name_set_.count(name) > 0;
}

Eigen::VectorXf OnnxPredictor::Predict(Eigen::VectorXf& input)
{
  Ort::MemoryInfo memory_info  = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeCPU);
  Ort::Value      input_tensor = Ort::Value::CreateTensor<float>(memory_info, input.data(), input.size(), input_shape_.data(), input_shape_.size());

  std::vector<const char*> input_names  = {input_name_.c_str()};
  std::vector<const char*> output_names = {output_name_.c_str()};
  Ort::RunOptions          run_options;
  std::vector<Ort::Value>  output_tensors = policy_session_->Run(run_options, input_names.data(), &input_tensor, 1, output_names.data(), 1);

  auto output_tensor = output_tensors[0].GetTensorMutableData<float>();
  return Eigen::Map<Eigen::VectorXf>(output_tensor, output_shape_[1]);
}

MotionOutputs OnnxPredictor::Predict(Eigen::VectorXf& x, float time_step, bool need_phase)
{
  Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeCPU);

  Ort::Value             input_tensor_x  = Ort::Value::CreateTensor<float>(memory_info, x.data(), x.size(), input_shape_.data(), input_shape_.size());
  std::array<int64_t, 2> ts_shape        = {1, 1};
  Ort::Value             input_tensor_ts = Ort::Value::CreateTensor<float>(memory_info, &time_step, 1, ts_shape.data(), ts_shape.size());

  std::vector<const char*> input_names = {"obs", "time_step"};

  std::vector<const char*> output_names = {"actions", "joint_pos", "joint_vel", "body_pos_w", "body_quat_w", "body_lin_vel_w", "body_ang_vel_w"};
  if (need_phase) {
    output_names.push_back("motion_phase");
    output_names.push_back("default_joint_pos");
    output_names.push_back("action_scale");
    output_names.push_back("joint_stiffness");
    output_names.push_back("joint_damping");
  }

  Ort::RunOptions           run_options;
  std::array<Ort::Value, 2> input_tensors = {std::move(input_tensor_x), std::move(input_tensor_ts)};

  std::vector<Ort::Value> output_tensors =
      policy_session_->Run(run_options, input_names.data(), input_tensors.data(), input_tensors.size(), output_names.data(), output_names.size());

  MotionOutputs outputs;

  auto map_tensor = [&](Ort::Value& val, int dim) {
    float* data = val.GetTensorMutableData<float>();
    return Eigen::Map<Eigen::VectorXf>(data, dim);
  };

  if (x.size() == 151) {
    outputs.action         = map_tensor(output_tensors[0], 29);
    outputs.joint_pos      = map_tensor(output_tensors[1], 29);
    outputs.joint_vel      = map_tensor(output_tensors[2], 29);
    outputs.body_pos_w     = map_tensor(output_tensors[3], 3);
    outputs.body_quat_w    = map_tensor(output_tensors[4], 4);
    outputs.body_lin_vel_w = map_tensor(output_tensors[5], 3);
    outputs.body_ang_vel_w = map_tensor(output_tensors[6], 3);
    if (need_phase) {
      outputs.motion_phase = map_tensor(output_tensors[7], 2);
      outputs.default_pos  = map_tensor(output_tensors[8], 29);
      outputs.action_scale = map_tensor(output_tensors[9], 29);
      outputs.stiffness    = map_tensor(output_tensors[10], 29);
      outputs.damping      = map_tensor(output_tensors[11], 29);
    }
  } else if (x.size() == 131) {
    outputs.action         = map_tensor(output_tensors[0], 25);
    outputs.joint_pos      = map_tensor(output_tensors[1], 25);
    outputs.joint_vel      = map_tensor(output_tensors[2], 25);
    outputs.body_pos_w     = map_tensor(output_tensors[3], 3);
    outputs.body_quat_w    = map_tensor(output_tensors[4], 4);
    outputs.body_lin_vel_w = map_tensor(output_tensors[5], 3);
    outputs.body_ang_vel_w = map_tensor(output_tensors[6], 3);
    if (need_phase) {
      outputs.motion_phase = map_tensor(output_tensors[7], 2);
      outputs.default_pos  = map_tensor(output_tensors[8], 25);
      outputs.action_scale = map_tensor(output_tensors[9], 25);
      outputs.stiffness    = map_tensor(output_tensors[10], 25);
      outputs.damping      = map_tensor(output_tensors[11], 25);
    }
  }

  return outputs;
}
}  // namespace rl::predictor
