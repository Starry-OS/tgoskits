#pragma once

#include "core/kernelsoil/soil_request.h"
#include "core/kernelsoil/soil_result.h"

namespace asking_star::core::boot {

class StarryOSRuntimeAdapter {
 public:
  [[nodiscard]] asking_star::core::kernelsoil::SoilResult map_runtime_request(
      const asking_star::core::kernelsoil::SoilRequest& request) const {
    if (!request.is_valid()) {
      return {"invalid-runtime-request", "reject", 0, {"invalid request"},
              true, "INVALID_RUNTIME_REQUEST", "invalid-runtime-request",
              asking_star::core::kernelsoil::ExecutionMode::Qemu};
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
            request.dry_run ? "runtime-dry-run" : "runtime-ready",
            0,
            {"operation=" +
                 std::string(asking_star::core::kernelsoil::to_string(
                     request.operation)),
             "payload=" + request.payload},
            request.dry_run,
            "",
            request.trace_id(),
            request.mode};
  }

  [[nodiscard]] bool executes_driver_without_gate() const { return false; }
};

}  // namespace asking_star::core::boot
