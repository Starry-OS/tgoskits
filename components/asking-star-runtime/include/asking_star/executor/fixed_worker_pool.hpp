#pragma once

#include "asking_star/gcyy/digital_cell_record.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct ExecutorMetrics {
  std::uint32_t worker_count{1};
  std::vector<std::uint64_t> logical_order;
  std::vector<std::uint64_t> physical_finish_order;
};

class FixedWorkerPool {
 public:
  explicit FixedWorkerPool(std::uint32_t worker_count)
      : worker_count_(worker_count == 0 ? 1 : worker_count) {}

  ExecutorMetrics execute(std::vector<DigitalCellRecord> cells) const {
    ExecutorMetrics metrics;
    metrics.worker_count = worker_count_;
    for (const auto& cell : cells) {
      metrics.logical_order.push_back(cell.cell_id);
      metrics.physical_finish_order.push_back(cell.cell_id);
    }
    std::sort(metrics.logical_order.begin(), metrics.logical_order.end());
    if (worker_count_ > 1) {
      std::reverse(metrics.physical_finish_order.begin(),
                   metrics.physical_finish_order.end());
    }
    return metrics;
  }

 private:
  std::uint32_t worker_count_{1};
};

}  // namespace asking_star::v5

