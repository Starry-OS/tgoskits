#pragma once

#include "asking_star/gcyy/digital_cell_record.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

class DeterministicExecutor {
 public:
  std::vector<std::uint64_t> execute(
      const std::vector<DigitalCellRecord>& cells) const;
};

}  // namespace asking_star::v5

