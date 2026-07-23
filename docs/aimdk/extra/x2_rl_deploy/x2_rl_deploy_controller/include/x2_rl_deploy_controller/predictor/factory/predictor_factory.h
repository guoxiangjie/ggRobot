#pragma once

#include <memory>
#include <string>

#include "x2_rl_deploy_controller/predictor/interface/i_predictor.h"
#include "x2_rl_deploy_controller/predictor/onnx/onnx_predictor.h"

namespace rl::predictor {
class PredictorFactory
{
 public:
  static std::unique_ptr<IPredictor> CreatePredictor(const std::string& type)
  {
    if (type == "onnx") {
      return std::make_unique<OnnxPredictor>();
    }

    return nullptr;
  }
};
}  // namespace rl::predictor
