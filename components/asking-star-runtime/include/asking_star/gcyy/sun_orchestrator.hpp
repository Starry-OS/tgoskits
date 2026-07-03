#pragma once

#include "asking_star/gcyy/admission_policy.hpp"
#include "asking_star/gcyy/sun_tick.hpp"
#include "asking_star/heat/heat_record.hpp"
#include "asking_star/scheduler/scheduler_decision_record.hpp"
#include "asking_star/scheduler/task_graph_view.hpp"
#include "asking_star/timeline/timeline_view.hpp"

namespace asking_star::gcyy {

class SunOrchestrator {
 public:
  [[nodiscard]] SunTick next_tick(std::string trace_id);
  [[nodiscard]] GcyyResult admit(const DigitalCell& cell,
                                 const RuntimeBudget& budget) const;
  [[nodiscard]] asking_star::v5::SchedulerDecisionRecord step_parallel_view(
      const asking_star::v5::TimelineView& timeline,
      const asking_star::v5::TaskGraphView& graph,
      const asking_star::v5::HeatRecord& heat,
      const RuntimeBudget& budget);

 private:
  std::uint64_t next_tick_id_{1};
  AdmissionPolicy policy_;
};

}  // namespace asking_star::gcyy
