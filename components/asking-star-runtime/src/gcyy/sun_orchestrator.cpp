#include "asking_star/gcyy/sun_orchestrator.hpp"

#include "asking_star/heat/heat_scheduler.hpp"

#include <algorithm>
#include <unordered_set>
#include <utility>

namespace asking_star::gcyy {

SunTick SunOrchestrator::next_tick(std::string trace_id) {
  return SunTick{next_tick_id_++, 1, std::move(trace_id)};
}

GcyyResult SunOrchestrator::admit(const DigitalCell& cell,
                                  const RuntimeBudget& budget) const {
  return policy_.admit(cell, budget);
}

asking_star::v5::SchedulerDecisionRecord SunOrchestrator::step_parallel_view(
    const asking_star::v5::TimelineView& timeline,
    const asking_star::v5::TaskGraphView& graph,
    const asking_star::v5::HeatRecord& heat, const RuntimeBudget& budget) {
  auto trace_id = std::string{"sun-axis-"} + std::to_string(timeline.axis.axis_id);
  if (!timeline.window.slice_refs.empty()) {
    trace_id = timeline.window.slice_refs.front().trace_id;
  }
  const auto tick = next_tick(std::move(trace_id));
  asking_star::v5::SchedulerDecisionRecord decision;
  decision.decision_id = tick.tick_id;
  decision.sun_tick = tick.tick_id;
  decision.trace_id = tick.trace_id;
  decision.budget_allowed = budget.can_consume(1);
  decision.status = decision.budget_allowed ? "ready" : "budget_blocked";
  if (!decision.budget_allowed) {
    return decision;
  }

  std::unordered_set<std::uint64_t> visible_slices;
  for (const auto& slice_ref : timeline.window.slice_refs) {
    visible_slices.insert(slice_ref.record_id);
  }

  std::unordered_set<std::uint64_t> completed_tasks;
  std::unordered_set<std::uint64_t> blocked_tasks;
  for (const auto& task : graph.tasks) {
    if (task.state == asking_star::v5::TaskState::Completed) {
      completed_tasks.insert(task.task_id);
    }
    if (task.state == asking_star::v5::TaskState::Cancelled ||
        task.state == asking_star::v5::TaskState::Failed ||
        task.state == asking_star::v5::TaskState::Skipped) {
      blocked_tasks.insert(task.task_id);
    }
  }

  std::unordered_set<std::uint64_t> heat_allowed;
  asking_star::v5::HeatScheduler heat_scheduler;
  for (const auto& ref : heat_scheduler.select(heat, graph.tasks.size())) {
    heat_allowed.insert(ref.record_id);
  }
  const bool has_heat_filter = !heat.entries.empty();

  std::vector<const asking_star::v5::TaskRecord*> candidates;
  for (const auto& task : graph.tasks) {
    if (task.state != asking_star::v5::TaskState::Created &&
        task.state != asking_star::v5::TaskState::Ready) {
      continue;
    }
    if (blocked_tasks.contains(task.task_id)) {
      continue;
    }
    if (!visible_slices.empty() &&
        !visible_slices.contains(task.slice_ref.record_id)) {
      continue;
    }
    if (has_heat_filter && !heat_allowed.contains(task.task_id)) {
      continue;
    }
    bool parents_done = true;
    for (const auto& edge : graph.edges) {
      if (edge.to_task_ref.record_id == task.task_id &&
          !completed_tasks.contains(edge.from_task_ref.record_id)) {
        parents_done = false;
        break;
      }
    }
    if (parents_done) {
      candidates.push_back(&task);
    }
  }

  std::stable_sort(candidates.begin(), candidates.end(),
                   [](const auto* lhs, const auto* rhs) {
                     return lhs->task_id < rhs->task_id;
                   });
  const auto budget_limit =
      static_cast<std::size_t>(std::max(1, budget.semantic_units));
  for (const auto* task : candidates) {
    if (decision.task_refs.size() >= budget_limit) {
      break;
    }
    decision.task_refs.push_back(asking_star::v5::DigitalSetRefRecord{
        task->task_id, asking_star::v5::RecordTypeTag::Task, 1, 0, {},
        decision.trace_id});
    decision.cell_refs.push_back(task->cell_ref);
  }
  return decision;
}

}  // namespace asking_star::gcyy
