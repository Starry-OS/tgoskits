#pragma once

#include "asking_star/digitalset/digital_set_fragment.hpp"
#include "asking_star/gcyy/digital_cell_record.hpp"
#include "asking_star/scheduler/scheduler_snapshot.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct SunTick {
  std::uint64_t tick{0};
};

class StarScheduler {
 public:
  void submit(DigitalSetFragment fragment);
  void submit_batch(const std::vector<DigitalSetFragment>& fragments);
  void step(SunTick tick);
  std::vector<DigitalCellRecord> drain_ready_cells();
  SchedulerSnapshot snapshot() const { return snapshot_; }

 private:
  std::vector<DigitalSetFragment> pending_fragments_;
  std::vector<DigitalCellRecord> ready_cells_;
  SchedulerSnapshot snapshot_;
};

}  // namespace asking_star::v5

