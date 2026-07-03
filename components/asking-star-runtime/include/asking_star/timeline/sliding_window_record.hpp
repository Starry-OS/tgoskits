#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct SlidingWindowRecord {
  std::uint64_t window_id{0};
  std::uint64_t center_tick{0};
  std::int64_t left{0};
  std::int64_t right{0};
  std::vector<DigitalSetRefRecord> slice_refs;
  std::vector<DigitalSetRefRecord> task_refs;
};

struct SlidingWindowView {
  SlidingWindowRecord record;
};

}  // namespace asking_star::v5

