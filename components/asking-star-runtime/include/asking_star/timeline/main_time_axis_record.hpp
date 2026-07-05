#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct MainTimeAxisRecord {
  std::uint64_t axis_id{0};
  std::uint64_t epoch{0};
  std::vector<DigitalSetRefRecord> slice_refs;
};

struct MainTimeAxisView {
  MainTimeAxisRecord record;
};

}  // namespace asking_star::v5

