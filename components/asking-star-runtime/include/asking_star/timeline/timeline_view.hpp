#pragma once

#include "asking_star/timeline/main_time_axis_record.hpp"
#include "asking_star/timeline/sliding_window_record.hpp"
#include "asking_star/timeline/timeline_slice_record.hpp"

#include <vector>

namespace asking_star::v5 {

// TimelineView is a C++ decoded view over DigitalSet timeline records.
// It does not own timeline facts.
struct TimelineView {
  MainTimeAxisRecord axis;
  std::vector<TimelineSliceRecord> slices;
  SlidingWindowRecord window;
};

}  // namespace asking_star::v5
