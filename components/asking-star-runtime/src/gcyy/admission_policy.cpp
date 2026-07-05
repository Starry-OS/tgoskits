#include "asking_star/gcyy/admission_policy.hpp"

namespace asking_star::gcyy {

GcyyResult AdmissionPolicy::admit(const DigitalCell& cell,
                                  const RuntimeBudget& budget) const {
  auto cell_result = cell.validate();
  if (!cell_result.ok()) {
    return cell_result;
  }
  if (!budget.can_consume(1)) {
    return GcyyResult::failure(GcyyStatus::Denied,
                               "digital cell denied by budget");
  }
  return GcyyResult::success();
}

}  // namespace asking_star::gcyy

