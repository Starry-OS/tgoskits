#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <cstdint>
#include <vector>

namespace asking_star::v5 {

struct JoinGroupRecord {
  std::uint64_t join_group_id{0};
  std::vector<DigitalSetRefRecord> task_refs;
};

struct JoinGroupView {
  JoinGroupRecord record;
};

}  // namespace asking_star::v5

