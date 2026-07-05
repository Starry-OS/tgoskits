#pragma once

#include "asking_star/organ/organ_queue_record.hpp"
#include "asking_star/scheduler/scheduler_decision_record.hpp"

#include <string>

namespace asking_star::v5 {

// OrganDispatchPort is the only Sun -> OrganRuntime dispatch adapter.
// It only forwards approved CellRef records.
class OrganDispatchPort {
 public:
  explicit OrganDispatchPort(std::string organ_id = "MockComputeOrgan");

  [[nodiscard]] OrganQueueRecord to_queue_record(
      const SchedulerDecisionRecord& decision) const;

 private:
  std::string organ_id_;
};

}  // namespace asking_star::v5
