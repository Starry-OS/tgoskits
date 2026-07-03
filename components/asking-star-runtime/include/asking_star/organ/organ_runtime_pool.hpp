#pragma once

#include "asking_star/gcyy/digital_cell_record.hpp"
#include "asking_star/organ/organ_queue_record.hpp"
#include "asking_star/organ/organ_result_record.hpp"

#include <vector>

namespace asking_star::v5 {

class OrganRuntimePool {
 public:
  std::vector<OrganResultRecord> dispatch_refs(
      const OrganQueueRecord& queue) const {
    std::vector<OrganResultRecord> results;
    for (const auto& cell_ref : queue.cell_refs) {
      results.push_back({queue.organ_id, cell_ref.record_id, cell_ref.trace_id,
                         true, "executed-cell-ref"});
    }
    return results;
  }

  std::vector<OrganResultRecord> dispatch(
      const std::vector<DigitalCellRecord>& cells) const {
    std::vector<OrganResultRecord> results;
    for (const auto& cell : cells) {
      results.push_back({"MockComputeOrgan", cell.cell_id, cell.trace_id, true,
                         "executed"});
    }
    return results;
  }
};

}  // namespace asking_star::v5
