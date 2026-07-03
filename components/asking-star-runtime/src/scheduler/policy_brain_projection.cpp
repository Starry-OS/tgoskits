#include "asking_star/scheduler/policy_brain_projection.hpp"

#include <algorithm>
#include <sstream>

namespace asking_star::v5 {

PolicyBrainProjection::PolicyBrainProjection(std::uint64_t wheel_size)
    : wheel_size_(wheel_size == 0 ? 1 : wheel_size) {}

std::uint64_t PolicyBrainProjection::tick_to_slot(std::uint64_t tick) const {
  return tick % wheel_size_;
}

std::uint64_t PolicyBrainProjection::slot_to_angle_units(
    std::uint64_t slot) const {
  return (slot % wheel_size_) * 360000 / wheel_size_;
}

PolicyTaskProjection PolicyBrainProjection::project_task(
    const TimelineGraphProjection& projection,
    DigitalSetRefRecord task_ref) const {
  const auto node = projection.projection_for(task_ref);
  const auto slot = node.slice_ref.record_id % wheel_size_;
  return PolicyTaskProjection{task_ref,
                              node.slice_ref,
                              slot,
                              task_ref.record_id % 4,
                              task_ref.record_id,
                              node.algebra_index};
}

std::vector<DigitalSetRefRecord> PolicyBrainProjection::ready_frontier(
    const TimelineGraphProjection& projection, const SlidingWindowRecord& window,
    std::uint64_t tick, std::uint64_t priority_ring) const {
  const auto current_slot = tick_to_slot(tick);
  auto frontier = projection.ready_frontier(window);
  frontier.erase(std::remove_if(frontier.begin(), frontier.end(),
                                [&](const auto& task_ref) {
                                  const auto projected =
                                      project_task(projection, task_ref);
                                  return projected.wheel_slot != current_slot ||
                                         projected.priority_ring != priority_ring;
                                }),
                 frontier.end());
  return frontier;
}

std::vector<DigitalSetRefRecord> PolicyBrainProjection::dispatch_candidates(
    const TimelineGraphProjection& projection, const SlidingWindowRecord& window,
    std::uint64_t tick, std::uint64_t priority_ring, std::size_t budget) const {
  auto candidates = ready_frontier(projection, window, tick, priority_ring);
  if (candidates.size() > budget) {
    candidates.resize(budget);
  }
  return candidates;
}

std::string PolicyBrainProjection::debug_dump_policy_projection(
    std::uint64_t tick) const {
  const auto slot = tick_to_slot(tick);
  std::ostringstream out;
  out << "PolicyBrainProjection{slot=" << slot
      << ", angle_units=" << slot_to_angle_units(slot)
      << ", wheel_size=" << wheel_size_ << "}";
  return out.str();
}

}  // namespace asking_star::v5
