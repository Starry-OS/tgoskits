#pragma once

#include "asking_star/digitalset/digital_set_ref_record.hpp"

#include <string>
#include <vector>

namespace asking_star::v5 {

struct OrganQueueRecord {
  std::string organ_id;
  std::vector<DigitalSetRefRecord> cell_refs;
};

struct OrganQueueView {
  OrganQueueRecord record;
};

}  // namespace asking_star::v5

