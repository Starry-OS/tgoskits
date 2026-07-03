#pragma once

#include <string>
#include <vector>

namespace asking_star::ai {

struct AiModelManifest {
  std::string model_id;
  std::string model_name;
  std::string backend{"mock"};
  std::vector<std::string> input_kinds;
  std::vector<std::string> output_kinds;
  bool real_device_required{false};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::ai
