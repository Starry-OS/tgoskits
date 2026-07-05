#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v5 {

// SchedulerDecisionRecord is a DigitalSet record-form decision emitted by
// SunOrchestrator. It carries logical refs, not executable task objects.
struct SchedulerDecisionRecord {
  std::uint64_t decision_id{0};
  std::uint64_t sun_tick{0};
  std::string trace_id;
  std::vector<DigitalSetRefRecord> task_refs;
  std::vector<DigitalSetRefRecord> cell_refs;
  std::uint64_t policy_brain_ref{0};
  std::uint64_t timewheel_slot{0};
  std::uint64_t timewheel_angle_units{0};
  std::uint64_t priority_ring{0};
  bool budget_allowed{true};
  std::string status{"ready"};
};

struct SchedulerDecisionView {
  SchedulerDecisionRecord record;
};

}  // namespace asking_star::v5
