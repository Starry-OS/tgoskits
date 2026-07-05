#pragma once

#include "asking_star/charge/preset_charge_bank.hpp"
#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/gcyy_result.hpp"
#include "asking_star/gcyy/sun_orchestrator.hpp"
#include "asking_star/gene/boot_reflex_registry.hpp"

#include <string>
#include <vector>

namespace asking_star::runtime {

struct BootReflexRunResult {
  std::vector<asking_star::gcyy::DigitalCell> admitted_cells;
  std::vector<std::string> trace_log;
};

class BootReflexRunner {
 public:
  [[nodiscard]] asking_star::gcyy::GcyyResult run(
      const asking_star::gene::BootReflexRegistry& genes,
      const asking_star::charge::PresetChargeBank& charges,
      asking_star::gcyy::SunOrchestrator& sun,
      const std::string& trace_id,
      BootReflexRunResult& out_result) const;
};

}  // namespace asking_star::runtime
