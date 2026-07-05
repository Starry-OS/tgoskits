#pragma once

#include "asking_star/gcyy/charge_view.hpp"
#include "asking_star/gcyy/runtime_budget.hpp"
#include "asking_star/soil/soil_execution_status.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace asking_star::charge {

struct PresetCharge {
  std::string charge_id;
  std::string origin_gene;
  asking_star::soil::OperationKind operation_kind{
      asking_star::soil::OperationKind::Noop};
  std::string target_kind{"boot.reflex"};
  std::vector<std::byte> payload;
  asking_star::gcyy::RuntimeBudget budget;
  int priority{0};
  std::uint64_t lifetime_tick{0};
  bool lazy_materialized{true};

  [[nodiscard]] bool is_valid() const;
  [[nodiscard]] asking_star::gcyy::ChargeView to_charge_view(
      const std::string& trace_id) const;
  [[nodiscard]] std::string payload_as_string() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::charge
