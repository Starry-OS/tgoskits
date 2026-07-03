#pragma once

#include "asking_star/ai/ai_model_manifest.hpp"

#include <optional>
#include <string>
#include <vector>

namespace asking_star::ai {

class AiCapabilityRegistry {
 public:
  AiCapabilityRegistry();

  void register_model(AiModelManifest manifest);
  [[nodiscard]] bool has_model(const std::string& model_id) const;
  [[nodiscard]] std::optional<AiModelManifest> find_model(
      const std::string& model_id) const;
  [[nodiscard]] std::vector<AiModelManifest> list_models() const;
  [[nodiscard]] std::string status_report() const;

 private:
  std::vector<AiModelManifest> models_;
};

}  // namespace asking_star::ai
