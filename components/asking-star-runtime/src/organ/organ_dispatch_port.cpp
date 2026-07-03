#include "asking_star/organ/organ_dispatch_port.hpp"

#include <utility>

namespace asking_star::v5 {

OrganDispatchPort::OrganDispatchPort(std::string organ_id)
    : organ_id_(std::move(organ_id)) {}

OrganQueueRecord OrganDispatchPort::to_queue_record(
    const SchedulerDecisionRecord& decision) const {
  return OrganQueueRecord{organ_id_, decision.cell_refs};
}

}  // namespace asking_star::v5
