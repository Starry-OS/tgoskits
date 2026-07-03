#pragma once

#include "core/boot/boot_plan.h"
#include "asking_star/v55/chamber_pouch.hpp"

#include <string>
#include <utility>

namespace asking_star::v55 {

struct BootRunnerAdmissionRecord {
  asking_star::core::boot::BootIntent intent;
  std::uint64_t chamber_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  bool bootrunner_required{false};
  bool board_real_claim{false};
};

class BootRunnerAdmissionBridge {
 public:
  [[nodiscard]] BootRunnerAdmissionRecord make_intent(
      const ChamberPlacementRecord& placement,
      const ChamberExecutionRecord& execution,
      bool allow_real_qemu = false,
      std::string artifact_id = "starryos-current") const {
    BootRunnerAdmissionRecord record;
    record.chamber_id = placement.selected_chamber_id;
    record.adapter_mode = execution.adapter_mode;
    record.bootrunner_required = execution.adapter_mode == AdapterMode::DryRun ||
                                 execution.adapter_mode == AdapterMode::HostMock ||
                                 execution.adapter_mode == AdapterMode::BoardReal;
    record.board_real_claim = false;
    record.intent.id = "v55-boot-" + std::to_string(execution.execution_id);
    record.intent.artifact_id = std::move(artifact_id);
    record.intent.reason =
        "v55 chamber " + std::to_string(placement.selected_chamber_id) +
        " placement " + std::to_string(placement.placement_id);
    record.intent.allow_real_qemu =
        allow_real_qemu && execution.adapter_mode == AdapterMode::BoardReal;
    return record;
  }
};

}  // namespace asking_star::v55
