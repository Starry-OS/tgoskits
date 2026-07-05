#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <string>

namespace asking_star::gcyy {

struct RuntimeBudget {
  std::string budget_id;
  std::string trace_id;
  int semantic_units{0};
  int charge_units{0};

  [[nodiscard]] bool can_consume(int units) const;
  [[nodiscard]] GcyyResult consume(int units);
};

}  // namespace asking_star::gcyy

