#pragma once

#include "asking_star/v56/compat/v55_board_evidence_bridge.hpp"

#include <string>

namespace asking_star::v56::board {

struct BoardSmokeReuseRecord {
  std::string marker;
  std::string boot_path{"v5.5"};
  std::string adapter_mode{"DryRun"};
  bool board_real_allowed{false};
  bool board_real_claim{false};
  compat::BoardEvidence evidence;

  [[nodiscard]] bool is_valid() const;
};

class BoardSmokeReuseGate {
 public:
  [[nodiscard]] BoardSmokeReuseRecord evaluate(
      const compat::BoardEvidence& evidence) const;
};

}  // namespace asking_star::v56::board
