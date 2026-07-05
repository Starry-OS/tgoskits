#pragma once

#include "asking_star/timeline/wang_slice_lane_record.hpp"

#include <array>
#include <cstdint>

namespace asking_star::v5 {

// TimelineSliceRecord is a DigitalSet record decoded as a C++ value object.
// TimelineSlice itself must not become an independent scheduler body.
struct TimelineSliceRecord {
  std::uint64_t slice_id{0};
  std::uint64_t epoch{0};
  std::uint64_t tick{0};
  std::array<WangSliceLaneRecord, 3> lanes{
      WangSliceLaneRecord{TimelineLane::StarYinLane, {}},
      WangSliceLaneRecord{TimelineLane::GeneChargeCellLane, {}},
      WangSliceLaneRecord{TimelineLane::OrganSoilReturnLane, {}}};
};

struct TimelineSliceView {
  TimelineSliceRecord record;
};

}  // namespace asking_star::v5
