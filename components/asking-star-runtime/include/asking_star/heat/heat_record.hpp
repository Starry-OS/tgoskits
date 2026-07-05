#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct HeatEntryRecord {
  DigitalSetRefRecord record_ref;
  double score{0.0};
  std::uint64_t age{0};
};

struct HeatRecord {
  std::uint64_t heat_id{0};
  std::vector<HeatEntryRecord> entries;
};

struct HeatView {
  HeatRecord record;
};

}  // namespace asking_star::v5

