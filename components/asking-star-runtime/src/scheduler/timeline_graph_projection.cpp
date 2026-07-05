#include "asking_star/scheduler/timeline_graph_projection.hpp"

#include <algorithm>
#include <sstream>
#include <unordered_set>

namespace asking_star::v5 {

void TimelineGraphProjection::add_task(DigitalSetRefRecord task_ref,
                                       DigitalSetRefRecord slice_ref,
                                       DigitalSetRefRecord lane_ref,
                                       std::uint64_t algebra_index) {
  task_index_[task_ref.record_id] = TimelineGraphNodeProjection{
      task_ref, slice_ref, lane_ref, algebra_index};
  slice_to_tasks_[slice_ref.record_id].push_back(task_ref);
}

void TimelineGraphProjection::add_edge(DigitalSetRefRecord from_task_ref,
                                       DigitalSetRefRecord to_task_ref) {
  children_[from_task_ref.record_id].push_back(to_task_ref);
  parents_[to_task_ref.record_id].push_back(from_task_ref);
}

void TimelineGraphProjection::mark_completed(DigitalSetRefRecord task_ref) {
  completed_.insert(task_ref.record_id);
}

std::vector<DigitalSetRefRecord> TimelineGraphProjection::tasks_in_slice(
    DigitalSetRefRecord slice_ref) const {
  if (const auto it = slice_to_tasks_.find(slice_ref.record_id);
      it != slice_to_tasks_.end()) {
    return it->second;
  }
  return {};
}

std::vector<DigitalSetRefRecord> TimelineGraphProjection::parents(
    DigitalSetRefRecord task_ref) const {
  if (const auto it = parents_.find(task_ref.record_id); it != parents_.end()) {
    return it->second;
  }
  return {};
}

std::vector<DigitalSetRefRecord> TimelineGraphProjection::children(
    DigitalSetRefRecord task_ref) const {
  if (const auto it = children_.find(task_ref.record_id);
      it != children_.end()) {
    return it->second;
  }
  return {};
}

std::vector<DigitalSetRefRecord> TimelineGraphProjection::ready_frontier(
    const SlidingWindowRecord& slice_window) const {
  std::unordered_set<std::uint64_t> visible_slices;
  for (const auto& slice_ref : slice_window.slice_refs) {
    visible_slices.insert(slice_ref.record_id);
  }

  std::vector<DigitalSetRefRecord> ready;
  for (const auto& [task_id, projection] : task_index_) {
    if (!visible_slices.empty() &&
        !visible_slices.contains(projection.slice_ref.record_id)) {
      continue;
    }
    if (completed_.contains(task_id)) {
      continue;
    }
    bool parents_done = true;
    if (const auto it = parents_.find(task_id); it != parents_.end()) {
      parents_done = std::all_of(it->second.begin(), it->second.end(),
                                 [&](const auto& parent) {
                                   return completed_.contains(parent.record_id);
                                 });
    }
    if (parents_done) {
      ready.push_back(projection.task_ref);
    }
  }
  std::sort(ready.begin(), ready.end(), [](const auto& a, const auto& b) {
    return a.record_id < b.record_id;
  });
  return ready;
}

TimelineGraphNodeProjection TimelineGraphProjection::projection_for(
    DigitalSetRefRecord task_ref) const {
  if (const auto it = task_index_.find(task_ref.record_id);
      it != task_index_.end()) {
    return it->second;
  }
  return TimelineGraphNodeProjection{task_ref, {}, {}, 0};
}

std::string TimelineGraphProjection::debug_dump_projection() const {
  std::ostringstream out;
  out << "TimelineGraphProjection{tasks=" << task_index_.size()
      << ", completed=" << completed_.size() << "}";
  return out.str();
}

}  // namespace asking_star::v5
