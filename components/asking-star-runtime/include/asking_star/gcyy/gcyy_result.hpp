#pragma once

#include <string>

namespace asking_star::gcyy {

enum class GcyyStatus {
  Ok,
  InvalidArgument,
  MissingTraceId,
  MissingPayload,
  MissingGene,
  InvalidState,
  NotFound,
  Denied,
  BudgetExhausted,
  AdapterError,
};

// Minimal explicit result for Round 1 validation paths.
struct GcyyResult {
  GcyyStatus status{GcyyStatus::Ok};
  std::string message;

  [[nodiscard]] bool ok() const;
  [[nodiscard]] std::string debug_dump() const;

  [[nodiscard]] static GcyyResult success();
  [[nodiscard]] static GcyyResult failure(GcyyStatus status,
                                          std::string message);
};

[[nodiscard]] const char* to_string(GcyyStatus status);

}  // namespace asking_star::gcyy
