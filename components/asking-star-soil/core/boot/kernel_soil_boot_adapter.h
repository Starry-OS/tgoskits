#pragma once

#include "core/boot/boot_plan.h"
#include "core/kernelsoil/soil_result.h"

namespace asking_star::core::boot {

class KernelSoilBootAdapter {
 public:
  [[nodiscard]] asking_star::core::kernelsoil::SoilResult dispatch_boot(
      const BootPlan& plan) const {
    if (!plan.is_valid()) {
      return {"invalid-boot",
              "reject",
              0,
              {"invalid boot plan"},
              true,
              "INVALID_BOOT_PLAN",
              "invalid-boot",
              asking_star::core::kernelsoil::ExecutionMode::Qemu};
    }
    if (!plan.soil_request.can_dispatch()) {
      return {plan.soil_request.id,
              "blocked",
              0,
              {"blocked by gate: " +
               plan.soil_request.gate_trace.decision.reason},
              true,
              "GATE_BLOCKED",
              plan.soil_request.trace_id(),
              plan.soil_request.mode};
    }

    return {plan.soil_request.id,
            plan.soil_request.dry_run ? "qemu-boot-dry-run"
                                      : "qemu-boot-allowed",
            0,
            {"artifact=" + plan.artifact.artifact_id,
             "kernel=" + plan.artifact.kernel_image,
             "rootfs=" + plan.artifact.rootfs_image,
             "serial=" + plan.artifact.serial_endpoint,
             "gate=" + plan.soil_request.gate_trace.decision.reason},
            plan.soil_request.dry_run,
            "",
            plan.soil_request.trace_id(),
            plan.soil_request.mode};
  }

  [[nodiscard]] bool bypasses_gate() const { return false; }

  [[nodiscard]] bool writes_genebank() const { return false; }
};

}  // namespace asking_star::core::boot
