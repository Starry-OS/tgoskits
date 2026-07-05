#pragma once

#include "asking_star/gcyy/digital_cell.hpp"
#include "asking_star/gcyy/runtime_budget.hpp"

namespace asking_star::gcyy {

class AdmissionPolicy {
 public:
  [[nodiscard]] GcyyResult admit(const DigitalCell& cell,
                                 const RuntimeBudget& budget) const;
};

}  // namespace asking_star::gcyy

