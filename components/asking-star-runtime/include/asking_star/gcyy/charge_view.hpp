#pragma once

#include "asking_star/gcyy/gcyy_result.hpp"

#include <cstdint>
#include <string>

namespace asking_star::gcyy {

// ChargeView is the short-lived executable view expanded by Yang.
struct ChargeView {
  std::string charge_id;
  std::string origin_gene_id;
  std::string trace_id;
  std::string projection_id;
  std::string capability_kind;
  std::string execution_intent;
  std::string runtime_budget;
  int priority{0};
  std::string payload_ref;
  std::uint64_t lifetime_tick{0};

  [[nodiscard]] bool has_trace() const;
  [[nodiscard]] bool is_expired_at(std::uint64_t tick) const;
  [[nodiscard]] GcyyResult validate() const;
  [[nodiscard]] std::string debug_dump() const;
};

}  // namespace asking_star::gcyy

