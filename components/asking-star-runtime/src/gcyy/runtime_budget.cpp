#include "asking_star/gcyy/runtime_budget.hpp"

namespace asking_star::gcyy {

bool RuntimeBudget::can_consume(int units) const {
  return units >= 0 && semantic_units >= units;
}

GcyyResult RuntimeBudget::consume(int units) {
  if (!can_consume(units)) {
    return GcyyResult::failure(GcyyStatus::BudgetExhausted,
                               "runtime budget exhausted");
  }
  semantic_units -= units;
  return GcyyResult::success();
}

}  // namespace asking_star::gcyy

