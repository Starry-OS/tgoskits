#include "asking_star/scheduler/deterministic_executor.hpp"

#include <algorithm>

namespace asking_star::v5 {

std::vector<std::uint64_t> DeterministicExecutor::execute(
    const std::vector<DigitalCellRecord>& cells) const {
  std::vector<std::uint64_t> order;
  order.reserve(cells.size());
  for (const auto& cell : cells) {
    order.push_back(cell.cell_id);
  }
  std::sort(order.begin(), order.end());
  return order;
}

}  // namespace asking_star::v5

