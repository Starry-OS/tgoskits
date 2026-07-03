#pragma once

#include <string>

namespace asking_star::ai {

struct AiInferenceRequest {
  std::string request_id;
  std::string trace_id;
  std::string model_id;
  std::string input_kind{"text"};
  std::string payload;
  bool allow_real_device{false};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::ai
