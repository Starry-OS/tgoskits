#pragma once

#include "asking_star/v55/chamber_starryos_dryrun_bridge.hpp"
#include "asking_star/v55/pouch_trace_bridge.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v56::soil {

struct StarryOSDryRunDualChamberResult {
  v55::ChamberExecutionRecord execution;
  v55::StarryOSDryRunBridgeRecord starryos;
  v55::ChamberPouchRecord pouch;
  v55::PouchTraceBridgeRecord trace;
  std::string adapter_mode{"DryRun"};
  bool board_real_claim{false};

  [[nodiscard]] bool is_valid() const;
};

class StarryOSDryRunDualChamber {
 public:
  [[nodiscard]] StarryOSDryRunDualChamberResult execute(
      std::uint64_t execution_id,
      std::uint64_t placement_id,
      std::string payload,
      std::uint64_t logical_order) const;
};

}  // namespace asking_star::v56::soil
