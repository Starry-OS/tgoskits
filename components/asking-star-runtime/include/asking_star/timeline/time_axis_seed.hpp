#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>

namespace asking_star::v5 {

struct TimeAxisSeedRecord {
  std::uint64_t epoch0{0};
  std::uint64_t tick0{0};
  std::uint64_t slice_width{1};
  std::int64_t default_window_left{0};
  std::int64_t default_window_right{4};
  double default_heat_decay{0.95};
  std::uint32_t default_max_inflight{1};
  std::uint64_t timeline_record_base{0};
  std::uint64_t graph_record_base{0};
  std::uint64_t trace_record_base{0};
};

struct TimeAxisSeedView {
  TimeAxisSeedRecord record;
};

}  // namespace asking_star::v5

