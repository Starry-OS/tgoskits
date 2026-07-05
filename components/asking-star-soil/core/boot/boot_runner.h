#pragma once

#include "core/boot/boot_event_recorder.h"
#include "core/boot/boot_gate.h"
#include "core/boot/kernel_soil_boot_adapter.h"

#include <optional>
#include <utility>

namespace asking_star::core::boot {

class BootRunner {
 public:
  explicit BootRunner(JianmuArtifactIndex index) : index_(std::move(index)) {}

  [[nodiscard]] std::optional<BootPlan> make_plan(
      const BootIntent& intent) const {
    if (!intent.is_valid()) {
      return std::nullopt;
    }
    auto artifact = index_.select(intent.artifact_id);
    if (!artifact.has_value()) {
      return std::nullopt;
    }

    BootGate gate;
    auto token = gate.make_token(intent, *artifact);
    auto gate_trace = gate.decide(token);

    asking_star::core::kernelsoil::SoilRequest request;
    request.id = "soil-boot-" + intent.id;
    request.operation =
        asking_star::core::kernelsoil::SoilOperation::KernelIoctl;
    request.gate_trace = gate_trace;
    request.payload = artifact->kernel_image + "|" + artifact->rootfs_image;
    request.route_id = "route-boot-" + artifact->artifact_id;
    request.dry_run = !intent.allow_real_qemu;

    BootPlan plan{"boot-plan-" + intent.id,
                  intent,
                  *artifact,
                  token,
                  request,
                  {"boot_intent:" + intent.id,
                   "artifact:" + artifact->artifact_id,
                   "gate:" + gate_trace.decision.reason}};
    if (!plan.is_valid()) {
      return std::nullopt;
    }
    return plan;
  }

  [[nodiscard]] BootResult run_plan(
      const BootPlan& plan, asking_star::core::event::EventStore* events,
      asking_star::core::genebank::GeneBank* gene_bank) const {
    recorder_.record_plan(plan, events);
    auto soil = adapter_.dispatch_boot(plan);
    BootResult result{
        plan.id,
        soil.status,
        plan.artifact.serial_endpoint,
        soil.status == "qemu-boot-allowed" ||
            soil.status == "qemu-boot-dry-run",
        !plan.artifact.serial_endpoint.empty(),
        false,
        false,
        soil.trace};
    recorder_.record_result(plan, result, events, gene_bank);
    result.authoritative_fact_written = gene_bank != nullptr;
    result.trace.push_back("authoritative_fact_written=" +
                           std::string(result.authoritative_fact_written
                                           ? "true"
                                           : "false"));
    return result;
  }

  [[nodiscard]] bool bypasses_jianmu() const { return false; }

 private:
  JianmuArtifactIndex index_;
  KernelSoilBootAdapter adapter_;
  BootEventRecorder recorder_;
};

}  // namespace asking_star::core::boot
