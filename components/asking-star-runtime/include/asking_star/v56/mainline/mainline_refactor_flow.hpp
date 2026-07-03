#pragma once

#include "asking_star/gcyy/trace_event.hpp"
#include "asking_star/v56/sky/sky_ingress.hpp"
#include "asking_star/v56/soil/soil_dual_chamber.hpp"
#include "asking_star/v56/vessel/vessel_bus.hpp"

#include <string>
#include <vector>

namespace asking_star::v56::mainline {

struct MainlineRefactorResult {
  sky::SkyIngressResult sky;
  gcyy::DigitalCell cell;
  vessel::VesselBusResult sky_to_core;
  vessel::VesselBusResult core_to_soil;
  soil::SoilDualChamberResult soil;
  std::vector<gcyy::TraceEvent> trace_events;

  [[nodiscard]] bool trace_continuous() const;
  [[nodiscard]] bool board_real_claimed() const;
};

class MainlineRefactorFlow {
 public:
  [[nodiscard]] MainlineRefactorResult run_command(
      const std::string& command,
      const std::string& trace_id,
      soil::OSProfileKind profile = soil::OSProfileKind::Mock) const;
};

}  // namespace asking_star::v56::mainline

