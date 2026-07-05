#pragma once

#include "asking_star/digitalset/digital_set_record.hpp"

#include <string>
#include <vector>

namespace asking_star::v5 {

struct DigitalSetFragment {
  DigitalSetRecordHeader header{0, RecordTypeTag::Fragment, 1, 1, 0, {}, {}};
  std::vector<DigitalSetRecord> records;
};

struct FragmentView {
  DigitalSetFragment fragment;
};

}  // namespace asking_star::v5

