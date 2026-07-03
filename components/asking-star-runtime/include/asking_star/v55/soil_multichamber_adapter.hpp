#pragma once

#include "asking_star/v55/chamber_pouch.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

struct SoilAdapterResultRecord {
  std::uint64_t result_id{0};
  std::uint64_t execution_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  std::string payload;
  bool board_real_claim{false};
};

class SoilMultiChamberAdapter {
 public:
  [[nodiscard]] SoilAdapterResultRecord execute(
      const ChamberExecutionRecord& execution) const {
    SoilAdapterResultRecord result;
    result.result_id = execution.execution_id + 2000;
    result.execution_id = execution.execution_id;
    result.adapter_mode = execution.adapter_mode;
    result.payload = execution.request_payload;
    result.board_real_claim =
        adapter_mode_can_claim_board_real(execution.adapter_mode);
    return result;
  }
};

}  // namespace asking_star::v55
