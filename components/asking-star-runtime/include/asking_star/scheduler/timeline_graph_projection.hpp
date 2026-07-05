#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"
#include "asking_star/scheduler/dag_edge_record.hpp"
#include "asking_star/timeline/sliding_window_record.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace asking_star::v5 {

struct TimelineGraphNodeProjection {
  DigitalSetRefRecord task_ref;
  DigitalSetRefRecord slice_ref;
  DigitalSetRefRecord lane_ref;
  std::uint64_t algebra_index{0};
};

// TimelineGraphProjection is a decoded index over Timeline and DAG records.
// It is not a GraphRuntime and it does not execute tasks.
class TimelineGraphProjection {
 public:
  void add_task(DigitalSetRefRecord task_ref, DigitalSetRefRecord slice_ref,
                DigitalSetRefRecord lane_ref, std::uint64_t algebra_index);
  void add_edge(DigitalSetRefRecord from_task_ref,
                DigitalSetRefRecord to_task_ref);
  void mark_completed(DigitalSetRefRecord task_ref);

  [[nodiscard]] std::vector<DigitalSetRefRecord> tasks_in_slice(
      DigitalSetRefRecord slice_ref) const;
  [[nodiscard]] std::vector<DigitalSetRefRecord> parents(
      DigitalSetRefRecord task_ref) const;
  [[nodiscard]] std::vector<DigitalSetRefRecord> children(
      DigitalSetRefRecord task_ref) const;
  [[nodiscard]] std::vector<DigitalSetRefRecord> ready_frontier(
      const SlidingWindowRecord& slice_window) const;
  [[nodiscard]] TimelineGraphNodeProjection projection_for(
      DigitalSetRefRecord task_ref) const;
  [[nodiscard]] std::string debug_dump_projection() const;

 private:
  std::unordered_map<std::uint64_t, TimelineGraphNodeProjection> task_index_;
  std::unordered_map<std::uint64_t, std::vector<DigitalSetRefRecord>>
      slice_to_tasks_;
  std::unordered_map<std::uint64_t, std::vector<DigitalSetRefRecord>> parents_;
  std::unordered_map<std::uint64_t, std::vector<DigitalSetRefRecord>> children_;
  std::unordered_set<std::uint64_t> completed_;
};

}  // namespace asking_star::v5
