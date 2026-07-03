#pragma once

#include "core/kernelsoil/qemu_dry_run_soil_adapter.h"
#include "asking_star/v55/chamber_pouch.hpp"
#include "asking_star/v55/skin_ui_projection.hpp"

#include <string>

namespace asking_star::v55 {

struct QemuReportBridgeRecord {
  ChamberPouchRecord pouch;
  SkinStateProjectionRecord skin;
  bool source_is_qemu_dry_run{true};
  bool board_real_claim{false};
};

class QemuReportBridge {
 public:
  [[nodiscard]] QemuReportBridgeRecord project(
      const ChamberExecutionRecord& execution,
      const asking_star::core::kernelsoil::QemuObservation& observation) const {
    QemuReportBridgeRecord record;
    const bool observed_ok = observation.is_valid() && observation.boot_success;
    const std::string output =
        "source_mode=qemu_dry_run;boot_state=" +
        (observation.final_boot_state.empty() ? std::string{"unknown"}
                                              : observation.final_boot_state);

    ChamberPouchView pouch_view;
    record.pouch = pouch_view.observe(execution, output, observed_ok);
    record.pouch.fallback = observed_ok ? "" : "qemu-dry-run-report-missing";

    record.skin.sun_tick = execution.execution_id;
    record.skin.current_joint_id = execution.execution_id;
    record.skin.selected_chamber_id = execution.placement_id;
    record.skin.pouch_health = record.pouch.health;
    record.skin.trace_status = observation.is_valid() ? "qemu-observed"
                                                      : "qemu-not-observed";
    record.skin.adapter_mode = AdapterMode::DryRun;
    record.skin.reflex_hit = !observed_ok;
    record.board_real_claim = false;
    return record;
  }
};

}  // namespace asking_star::v55
