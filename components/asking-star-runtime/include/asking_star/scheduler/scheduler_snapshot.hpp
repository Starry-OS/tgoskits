#pragma once

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct SchedulerSnapshot {
  std::uint64_t logical_tick{0};
  std::vector<std::uint64_t> submitted_fragment_ids;
  std::vector<std::uint64_t> ready_cell_ids;
  std::vector<std::uint64_t> logical_order;
};

}  // namespace asking_star::v5

