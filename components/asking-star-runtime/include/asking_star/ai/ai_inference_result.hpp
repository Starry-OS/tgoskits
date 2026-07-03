#pragma once

#include <cstdint>
#include <string>

namespace asking_star::ai {

enum class AiInferenceStatus {
  Ok,
  InvalidRequest,
  ModelUnavailable,
  RealDeviceUnavailable,
  AdapterFailed,
};

struct AiInferenceResult {
  std::string request_id;
  std::string trace_id;
  AiInferenceStatus status{AiInferenceStatus::Ok};
  std::string output_kind{"classification"};
  std::string payload;
  std::uint64_t latency_ns{0};
  std::string message;

  [[nodiscard]] bool ok() const;
  [[nodiscard]] std::string debug_dump() const;
};

[[nodiscard]] const char* to_string(AiInferenceStatus status);

}  // namespace asking_star::ai
