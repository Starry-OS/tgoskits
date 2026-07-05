#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <vector>

namespace asking_star::v5 {

enum class TimelineLane {
  StarYinLane,
  GeneChargeCellLane,
  OrganSoilReturnLane
};

struct WangSliceLaneRecord {
  TimelineLane lane{TimelineLane::StarYinLane};
  std::vector<DigitalSetRefRecord> record_refs;
};

struct WangSliceLaneView {
  WangSliceLaneRecord record;
};

}  // namespace asking_star::v5

