#pragma once

#include "core/kernelsoil/soil_request.h"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::core::kernelsoil {

struct SoilResult {
  std::string request_id;
  std::string status;
  std::uint64_t latency_us{0};
  std::vector<std::string> trace;
  bool dry_run{true};
  std::string error_code;
  std::string trace_id;
  ExecutionMode mode{ExecutionMode::Mock};

  [[nodiscard]] bool is_valid() const {
    return !request_id.empty() && !status.empty() && !trace.empty() &&
           !trace_id.empty();
  }

  [[nodiscard]] bool ok() const {
    return error_code.empty() && status != "reject" && status != "blocked";
  }
};

class DryRunSoilExecutor {
 public:
  [[nodiscard]] SoilResult dispatch(const SoilRequest& request) const {
    if (!request.is_valid()) {
      return {"invalid",
              "reject",
              0,
              {"invalid soil request"},
              true,
              "INVALID_SOIL_REQUEST",
              "invalid",
              ExecutionMode::Mock};
    }
    if (!request.can_dispatch()) {
      return {request.id,
              "blocked",
              0,
              {"blocked by gate: " + request.gate_trace.decision.reason},
              true,
              "GATE_BLOCKED",
              request.trace_id(),
              request.mode};
    }
    return {request.id,
            "dry-run",
            50,
            {"dry-run " + std::string{to_string(request.operation)},
             "mode=" + std::string{to_string(request.mode)}},
            true,
            "",
            request.trace_id(),
            request.mode};
  }

  [[nodiscard]] bool executes_real_kernel() const { return false; }
};

}  // namespace asking_star::core::kernelsoil
