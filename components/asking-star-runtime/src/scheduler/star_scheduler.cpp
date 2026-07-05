#include "asking_star/scheduler/star_scheduler.hpp"

#include "asking_star/scheduler/deterministic_executor.hpp"

#include <utility>

namespace asking_star::v5 {

void StarScheduler::submit(DigitalSetFragment fragment) {
  snapshot_.submitted_fragment_ids.push_back(fragment.header.record_id);
  pending_fragments_.push_back(std::move(fragment));
}

void StarScheduler::submit_batch(
    const std::vector<DigitalSetFragment>& fragments) {
  for (auto fragment : fragments) {
    submit(std::move(fragment));
  }
}

void StarScheduler::step(SunTick tick) {
  snapshot_.logical_tick = tick.tick;
  for (const auto& fragment : pending_fragments_) {
    DigitalCellRecord cell;
    cell.cell_id = fragment.header.record_id;
    cell.gene_ref = DigitalSetRefRecord{fragment.header.record_id,
                                        RecordTypeTag::Gene,
                                        fragment.header.generation,
                                        0,
                                        {},
                                        fragment.header.trace_id};
    cell.trace_id = fragment.header.trace_id;
    ready_cells_.push_back(cell);
  }
  pending_fragments_.clear();

  DeterministicExecutor executor;
  snapshot_.logical_order = executor.execute(ready_cells_);
  snapshot_.ready_cell_ids = snapshot_.logical_order;
}

std::vector<DigitalCellRecord> StarScheduler::drain_ready_cells() {
  auto cells = ready_cells_;
  ready_cells_.clear();
  return cells;
}

}  // namespace asking_star::v5
