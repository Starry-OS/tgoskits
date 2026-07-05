#pragma once

#include "asking_star/digitalset/digital_set_record.hpp"
#include "asking_star/timeline/time_axis_seed.hpp"

#include <optional>
#include <string>
#include <vector>

namespace asking_star::v5 {

struct PrimordialDigitalSet {
  DigitalSetRecordHeader header{0, RecordTypeTag::Primordial, 1, 1, 0, {}, {}};
  std::vector<std::string> decode_rules;
  std::vector<std::string> star_fast_table;
  std::optional<TimeAxisSeedRecord> time_axis_seed;
};

struct PrimordialDigitalSetView {
  PrimordialDigitalSet record;
};

inline bool has_time_axis_seed(const PrimordialDigitalSet& primordial) {
  return primordial.time_axis_seed.has_value();
}

}  // namespace asking_star::v5

