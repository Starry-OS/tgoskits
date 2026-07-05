#pragma once

#include "asking_star/ai/ai_capability_registry.hpp"
#include "asking_star/ai/ai_inference_request.hpp"
#include "asking_star/ai/ai_inference_result.hpp"

namespace asking_star::ai {

class MockAiInferenceAdapter {
 public:
  explicit MockAiInferenceAdapter(AiCapabilityRegistry registry = {});

  [[nodiscard]] AiInferenceResult infer(
      const AiInferenceRequest& request) const;
  [[nodiscard]] const AiCapabilityRegistry& registry() const;

 private:
  AiCapabilityRegistry registry_;
};

}  // namespace asking_star::ai
