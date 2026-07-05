#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <optional>
#include <string>

namespace asking_star::v5 {

// DigitalCellRecord is a DigitalSet record made from GeneRef plus optional
// ChargeRef. It is not the DigitalCell runtime body.
struct DigitalCellRecord {
  std::uint64_t cell_id{0};
  DigitalSetRefRecord gene_ref;
  std::optional<DigitalSetRefRecord> charge_ref;
  std::string trace_id;
};

}  // namespace asking_star::v5
