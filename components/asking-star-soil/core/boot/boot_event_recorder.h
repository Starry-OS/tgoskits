#pragma once

#include "core/boot/boot_plan.h"
#include "core/dualchain/dual_gene_anchor.h"
#include "core/event/event.h"
#include "core/genebank/gene_bank.h"
#include "core/responsibility/responsibility_trace.h"
#include "core/statechain/state_gene_fragment.h"

namespace asking_star::core::boot {

class BootEventRecorder {
 public:
  void record_plan(const BootPlan& plan,
                   asking_star::core::event::EventStore* events) const {
    if (events == nullptr || !plan.is_valid()) {
      return;
    }
    events->append(asking_star::EventType::Input, "boot_requested:" + plan.id,
                   "boot_requested artifact=" + plan.artifact.artifact_id);
    events->append(asking_star::EventType::Input,
                   "artifact_selected:" + plan.id,
                   "artifact_selected kernel=" + plan.artifact.kernel_image);
    events->append(asking_star::EventType::Input, "gate_passed:" + plan.id,
                   "gate=" + plan.soil_request.gate_trace.decision.reason);
  }

  void record_result(const BootPlan& plan, const BootResult& result,
                     asking_star::core::event::EventStore* events,
                     asking_star::core::genebank::GeneBank* gene_bank) const {
    if (events != nullptr && result.is_valid()) {
      events->append(asking_star::EventType::Input,
                     "qemu_started:" + result.boot_id,
                     result.qemu_started ? "qemu_started"
                                         : "qemu_not_started");
      events->append(asking_star::EventType::Input,
                     "terminal_attached:" + result.boot_id,
                     result.terminal_attached ? "terminal_attached"
                                              : "terminal_not_attached");
    }

    if (gene_bank == nullptr || !plan.is_valid() || !result.is_valid()) {
      return;
    }

    const auto state_id =
        asking_star::core::statechain::make_state_gene_id(
            "", "boot-xing-artifact", result.status,
            "Sheng / State Generation Protocol: boot result admission",
            plan.soil_request.gate_trace.id, result.boot_id, plan.id);
    asking_star::core::statechain::StateGeneFragment state{
        state_id,
        std::nullopt,
        "starryos-boot",
        "boot",
        "Xing / Intrinsic Constraints: " + plan.artifact.artifact_id,
        "Ming / Runtime Trajectory: " + result.status,
        "Sheng / State Generation Protocol: boot result admission",
        "boot inertia follows artifact and gate history",
        plan.soil_request.gate_trace.id,
        asking_star::StateDiff{
            "StarryOS boot result " + result.status,
            {"boot_state", "terminal_endpoint"},
            {},
            {}},
        asking_star::RuntimeMode::AskingStar,
        plan.id,
        asking_star::now(),
        asking_star::core::statechain::GenerationStatus::Generated,
        "boot result recorded"};

    auto trace_id =
        asking_star::core::responsibility::make_responsibility_trace_id(
            "boot-pulse", "BootRunner", plan.intent.reason, plan.id,
            result.status);
    asking_star::core::responsibility::ResponsibilityTrace trace{
        trace_id,
        "boot-pulse",
        {"BootRunner", "system"},
        {"start-starryos", "boot StarryOS through KernelSoil"},
        plan.intent.reason,
        result.qemu_started
            ? asking_star::core::responsibility::ResponsibilityStatus::Executed
            : asking_star::core::responsibility::ResponsibilityStatus::Failed,
        result.status,
        "boot responsibility returned feedback"};

    gene_bank->append_state(state);
    gene_bank->append_trace(trace);
    gene_bank->anchor_dual_link(
        asking_star::core::dualchain::make_dual_gene_anchor(
            state_id, trace_id, "boot result anchored",
            "event-" + result.boot_id));
  }
};

}  // namespace asking_star::core::boot
