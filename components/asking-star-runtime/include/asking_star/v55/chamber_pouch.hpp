#pragma once

#include "asking_star/v55/chamber_runtime.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v55 {

struct ChamberExecutionRecord {
  std::uint64_t execution_id{0};
  std::uint64_t placement_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  std::string request_payload;
};

struct ChamberPouchRecord {
  std::uint64_t pouch_id{0};
  std::uint64_t execution_id{0};
  AdapterMode adapter_mode{AdapterMode::Mock};
  std::string health;
  std::string output;
  std::string fallback;
  bool reflex_candidate{false};
};

class ChamberPouchView {
 public:
  [[nodiscard]] ChamberPouchRecord observe(
      const ChamberExecutionRecord& execution,
      const std::string& output,
      bool ok) const {
    ChamberPouchRecord pouch;
    pouch.pouch_id = execution.execution_id + 1000;
    pouch.execution_id = execution.execution_id;
    pouch.adapter_mode = execution.adapter_mode;
    pouch.health = ok ? "healthy" : "degraded";
    pouch.output = output;
    pouch.fallback = ok ? "" : "mock-fallback";
    pouch.reflex_candidate = ok && execution.adapter_mode != AdapterMode::BoardReal;
    return pouch;
  }
};

}  // namespace asking_star::v55
