#pragma once

#include "asking_star/heat/heat_scheduler.hpp"
#include "asking_star/scheduler/scheduler_decision_record.hpp"
#include "asking_star/scheduler/timeline_graph_projection.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace asking_star::v5 {

struct PolicyTaskProjection {
  DigitalSetRefRecord task_ref;
  DigitalSetRefRecord slice_ref;
  std::uint64_t wheel_slot{0};
  std::uint64_t priority_ring{0};
  std::uint64_t graph_node{0};
  std::uint64_t algebra_index{0};
};

// PolicyBrainProjection is SunOrchestrator's internal strategy projection.
// It is not a second scheduler and cannot dispatch work by itself.
class PolicyBrainProjection {
 public:
  explicit PolicyBrainProjection(std::uint64_t wheel_size = 8);

  [[nodiscard]] std::uint64_t tick_to_slot(std::uint64_t tick) const;
  [[nodiscard]] std::uint64_t slot_to_angle_units(std::uint64_t slot) const;
  [[nodiscard]] PolicyTaskProjection project_task(
      const TimelineGraphProjection& projection,
      DigitalSetRefRecord task_ref) const;
  [[nodiscard]] std::vector<DigitalSetRefRecord> ready_frontier(
      const TimelineGraphProjection& projection,
      const SlidingWindowRecord& window, std::uint64_t tick,
      std::uint64_t priority_ring) const;
  [[nodiscard]] std::vector<DigitalSetRefRecord> dispatch_candidates(
      const TimelineGraphProjection& projection,
      const SlidingWindowRecord& window, std::uint64_t tick,
      std::uint64_t priority_ring, std::size_t budget) const;
  [[nodiscard]] std::string debug_dump_policy_projection(
      std::uint64_t tick) const;

 private:
  std::uint64_t wheel_size_{8};
};

}  // namespace asking_star::v5
