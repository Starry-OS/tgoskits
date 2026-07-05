#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <string>

namespace asking_star::v5 {

// ChargeRecord is the DigitalSet record form for a short-lived execution
// intent. Long-term state must return to DigitalSet / Gene / Trace records.
struct ChargeRecord {
  std::uint64_t charge_id{0};
  DigitalSetRefRecord gene_ref;
  std::string execution_intent;
  std::uint64_t ttl_ticks{1};
  std::string trace_id;
};

}  // namespace asking_star::v5
