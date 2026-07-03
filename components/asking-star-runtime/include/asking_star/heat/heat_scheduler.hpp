#pragma once

#include "asking_star/heat/heat_record.hpp"

#include <algorithm>
#include <vector>

namespace asking_star::v5 {

class HeatScheduler {
 public:
  std::vector<DigitalSetRefRecord> select(const HeatRecord& heat,
                                          std::size_t budget) const {
    auto entries = heat.entries;
    std::stable_sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
      return (a.score + static_cast<double>(a.age) * 0.01) >
             (b.score + static_cast<double>(b.age) * 0.01);
    });
    std::vector<DigitalSetRefRecord> refs;
    for (const auto& entry : entries) {
      if (refs.size() >= budget) {
        break;
      }
      refs.push_back(entry.record_ref);
    }
    return refs;
  }
};

}  // namespace asking_star::v5

